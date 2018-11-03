#include "LocalSocket.h"
#include "BVLC.h"

BACnetResult LocalSocket::WriteBVLL(sockaddr_in to, U8 messageid, U8* pBuffer, U16 BufferLength)
{
	U16 length = (BufferLength)+4;
	U8 bvll[4] = {
		0x81,
		messageid,
		(U8)((length & 0xFF00) >> 8),
		(U8)(length & 0xFF),
	};
	WSABUF bufs[2] = {
		{ sizeof(bvll),(char*)bvll, },
		{ BufferLength,(char*)pBuffer, },
	};
	DWORD bw = 0;
	WSASendTo(sock, bufs, ARRAYSIZE(bufs), &bw, 0, (sockaddr*)&to, sizeof(to), nullptr, nullptr);
	return BC_OK;
}

BACnetResult LocalSocket::WriteBVLL(sockaddr_in to, U8 messageid, CObjectPtr<IBACnetTransmitBuffer> pBuffer)
{
	U16 length = (pBuffer->GetTotalBufferLength()) + 4;
	U8 bvll[4] = {
		0x81,
		messageid,
		(U8)((length & 0xFF00) >> 8),
		(U8)(length & 0xFF),
	};
	U32 nbufs = pBuffer->GetNumBuffers() + 1;
	WSABUF* bufs = (WSABUF*)calloc(nbufs, sizeof(WSABUF));
	bufs[0].buf = (char*)bvll;
	bufs[0].len = sizeof(bvll);
	for(U32 i = 1; i < nbufs; ++i)
	{
		CObjectPtr<IBACnetBuffer> buf = pBuffer->GetBuffer(i - 1);
		bufs[i].len = buf->GetSize();
		bufs[i].buf = (char*)buf->GetBuffer();
	}
	DWORD bw = 0;
	WSASendTo(sock, bufs, nbufs, &bw, 0, (sockaddr*)&to, sizeof(to), nullptr, nullptr);
	free(bufs);
	return BC_OK;
}

BACnetResult LocalSocket::StartListenerThread()
{
	return Listener->Start();
}

BACnetResult LocalSocket::StopListenerThread()
{
	Listener->Cancel();
	if(BCE_FAILED(WaitForObject(Listener, 10000)))
	{
		//problem.
		Listener->Terminate(BCNRESULT_FROM_SYSTEM(ERROR_DBG_TERMINATE_THREAD));
	}
	return Listener->GetExitCode();
}

// 1 ms = 1000 us. 1 us = 10 hns.
// 1 ms = 10000 hns
#define MStoHNS 10000

BACnetResult LocalSocket::StartRegistrationTimer()
{
	return FDRegTimer->WaitFor(FDLifetime * MStoHNS, 100, 0);
}

BACnetResult LocalSocket::StopRegistrationTimer()
{
	return FDRegTimer->Cancel();
}

BACnetResult LocalSocket::SendCommandAndWait(sockaddr_in to, U8 messageid, U8 * pBuffer, U16 BufferLength, U16& ResponseCode)
{
	ResponseCode = 0;
	if(HasPendingCommand)
	{
		return BCE_BVLC_COMMAND_PENDING;
	}
	HasPendingCommand = true;
	HasResponse->Reset();
	BACnetResult r = WriteBVLL(to, messageid, pBuffer, BufferLength);
	if(BCE_FAILED(r))
	{
		HasPendingCommand = false;
		return r;
	}
	CObjectPtr<IBACnetWaitableObject> o[] = { Listener->GetCancellationEvent(), HasResponse };
	U32 object = 0;
	r = WaitForObjects(o, object, false);
	if(BCE_FAILED(r))
	{
		HasPendingCommand = false;
		return r;
	}
	if(object == 0)
	{
		//canceled.  <<<<< I think you can tell where I'm from with this.
		HasPendingCommand = false;
		return BCE_OPERATION_CANCELED;
	}
	//not an error, not a cancellation. Only option - we got back a response!
	ResponseCode = AsyncResultCode;
	HasPendingCommand = false;
	return BC_OK;
}

BACnetResult LocalSocket::SignalCommandResponse(U16 ResponseCode)
{
	//a command must be pending to signal a response to another thread.
	if(!HasPendingCommand)
	{
		//we don't actually care about this return code.
		return BCE_BVLC_NO_PENDING_COMMAND;
	}
	//store aside the response code.
	AsyncResultCode = ResponseCode;
	//and wake up the waiting thread.
	HasResponse->Set();
	return BC_OK;
}

BACnetResult LocalSocket::ListenerThread(CObjectPtr<IBACnetThread> thread)
{
	static U8 bvll[4] = { 0 };
	static U8 tmpbuf[1536] = { 0 };
	while(1)
	{
		WSAOVERLAPPED o;
		o.hEvent = HasRXData->GetWaitHandle();
		WSABUF bufs[2] = {
			{sizeof(bvll),(char*)bvll,},
			{sizeof(tmpbuf),(char*)tmpbuf,},
		};
		sockaddr_in from = { 0 };
		int srcaddrsz = sizeof(from);
		DWORD br = 0;
		DWORD flags = 0;
		int status = WSARecvFrom(sock, bufs, ARRAYSIZE(bufs), &br, &flags, (sockaddr*)&from, &srcaddrsz, &o, nullptr);
		if(status)
		{
			CObjectPtr<IBACnetWaitableObject> h[2] = { HasRXData, thread->GetCancellationEvent() };
			U32 object = 0;
			BACnetResult r = WaitForObjects(h, object, false);
			if(BCE_FAILED(r))
			{
				return r;
			}
			if(object == 1)
			{
				//close the thread. This will also cancel the pending I/O.
				return BC_OK;
			}
			//Data came in.
			//check the overlapped result.
			if(!WSAGetOverlappedResult(sock, &o, &br, FALSE, &flags))
			{
				int code = WSAGetLastError();
				switch(code)
				{
				case WSA_IO_INCOMPLETE:
					//shouldn't happen. This indicates a fault in Windows.
					__debugbreak();
					break;
				default:
					return BCNRESULT_FROM_SYSTEM(code);
				}
			}
		}
		U16 errcode;
		CObjectPtr<IBACnetAddress> sender = nullptr;
		CObjectPtr<IBACnetBuffer> msg = nullptr;
		//packet is available.
		//check the BVLL code.
		switch(bvll[1])
		{
		case BVLC_Result:
			//response from something.
			SignalCommandResponse(ntohs(((U16*)tmpbuf)[0]));
			break;
		case BVLC_WriteBDT:
			//WriteBDT
			errcode = htons(0x0010);
			goto writeerr;
		case BVLC_ReadBDT:
			//ReadBDT
			errcode = htons(0x0020);
			goto writeerr;
		case BVLC_RegisterForeignDevice:
			//Register Foreign Device
			errcode = htons(0x0030);
			goto writeerr;
		case BVLC_ReadFDT:
			//Read FDT
			errcode = htons(0x0040);
			goto writeerr;
		case BVLC_DeleteForeignDevice:
			//Delete Foreign Device
			errcode = htons(0x0050);
			goto writeerr;
		case BVLC_DistributeBroadcastToNetwork:
			//Distribute Broadcast To Network
			errcode = htons(0x0060);
		writeerr:
			WriteBVLL(from, 0x00, (U8*)&errcode, 2);
			break;
		case BVLC_ForwardedNPDU:
			//Forwarded NPDU
			//source address is stored AFTER the BVLL header.
			sender = CreateAddress(6, tmpbuf);
			msg = CreateBACnetBuffer(br - 10, tmpbuf+6);
			goto InvokeCallback;
		case BVLC_OriginalUnicast:
			//Original Unicast
		case BVLC_OriginalBroadcast:
			//Original Broadcast
			sender = IPAddress::CreateIPAddress(from);
			msg = CreateBACnetBuffer(br - 4, tmpbuf);
		InvokeCallback:
			{
				pool->QueueAsyncCallback([this,sender,msg](CObjectPtr<IBACnetThreadPool> pPool, CallbackHandle hInst)
				{
					pPool->CallbackRunsLong(hInst);
					return RXCallback(sender, msg);
				});
				break;
			}
		default:
			//Unknown or unsupported.
			//drop it.
			break;
		}
		//Wait for the next message.
		HasRXData->Reset();
	}
	return BC_OK;
}

LocalSocket::LocalSocket(CObjectPtr<IBACnetThreadPool> pThreadPool, U16 PortNumber) :
	WinSock(nullptr),
	sock(INVALID_SOCKET),
	HasRXData(CreateBACnetEvent(true, false)),
	HasResponse(CreateBACnetEvent(true, false)),
	Listener(CreateBACnetThread([this](auto thread) -> auto { return ListenerThread(thread); })),
	pool(pThreadPool),
	FDLifetime(0),
	BBMDAddress(nullptr),
	BroadcastAddress(nullptr),
	AutoRenew(false)
{
	BACnetResult r = CreateWSADevice(WinSock);
	if(BCE_FAILED(r))
	{
		throw BACnetException("Failed to initialize the Windows Sockets device.", r);
	}
	//Allow async I/O
	sock = WSASocket(AF_INET, SOCK_DGRAM, IPPROTO_UDP, nullptr, 0, WSA_FLAG_OVERLAPPED);
	if(sock == INVALID_SOCKET)
	{
		throw BACnetException("Failed to create the socket.", BCNRESULT_FROM_SYSTEM(WSAGetLastError()));
	}
	//now set up permissions:
	//allow broadcast
	BOOL bcast = TRUE;
	setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (char*)&bcast, sizeof(bcast));
	sockaddr_in tmpaddr = { 0 };
	tmpaddr.sin_family = AF_INET;
	tmpaddr.sin_port = htons(PortNumber);
	tmpaddr.sin_addr.s_addr = INADDR_ANY;
	if(::bind(sock, (sockaddr*)&tmpaddr, sizeof(tmpaddr)))
	{
		throw BACnetException("Failed to bind port 47808.", BCNRESULT_FROM_SYSTEM(WSAGetLastError()));
	}
	tmpaddr.sin_addr.s_addr = INADDR_BROADCAST;
	BroadcastAddress = IPAddress::CreateIPAddress(tmpaddr);
	//socket is now bound.
	//get the real address we're bound to.
	int addrsz = sizeof(Addr);
	if(getsockname(sock, (sockaddr*)&Addr, &addrsz))
	{
		//problem!
		throw BACnetException("Failed to retrieve bound address.", BCNRESULT_FROM_SYSTEM(WSAGetLastError()));
	}
	FDRegTimer = pool->CreateThreadpoolTimer([this](auto tp, auto h, auto t) -> BACnetResult
	{
		return RenewForeignDeviceRegistration();
	});
}

LocalSocket::~LocalSocket()
{
	Stop();
	closesocket(sock);
}

BACnetResult LocalSocket::WriteMessage(CObjectPtr<IBACnetAddress> pDestinationAddress, CObjectPtr<IBACnetTransmitBuffer> pMessage, bool WaitForTransmit)
{
	if(pDestinationAddress->GetTypeCode() != Address_BACnetIP)
	{
		return BCE_WRONG_ADDRESS_TYPE;
	}
	IPAddress* to = (IPAddress*)pDestinationAddress.GetInterface();
	if(to->IsBroadcast())
	{
		if(BBMDAddress)
		{
			//we're a foreign device on a BACnet network. Request a broadcast.
			return WriteBVLL(BBMDAddress->GetSocketAddress(), BVLC_DistributeBroadcastToNetwork, pMessage);
		}
		else
		{
			return WriteBVLL(to->GetSocketAddress(), BVLC_OriginalBroadcast, pMessage);
		}
	}
	return WriteBVLL(to->GetSocketAddress(), BVLC_OriginalUnicast, pMessage);
}

CObjectPtr<IBACnetAddress> LocalSocket::CreateAddress(U32 AddressSize, const U8* const AddressDataBuffer) const
{
	if(AddressSize < 6)
	{
		return nullptr;
	}
	sockaddr_in addr;
	memcpy(&addr.sin_addr.s_addr, AddressDataBuffer, 4);
	memcpy(&addr.sin_port, AddressDataBuffer + 4, 2);
	addr.sin_family = AF_INET;
	return IPAddress::CreateIPAddress(addr);
}

CObjectPtr<IBACnetAddress> LocalSocket::GetBroadcastAddress() const
{
	return BroadcastAddress;
}

BACnetResult LocalSocket::RegisterReceiverCallback(ReceiverCallbackFunction pCallback)
{
	if(!pCallback)
	{
		return BCE_INVALID_PARAMETER;
	}
	if(RXCallback)
	{
		return BCE_HANDLER_ALREADY_BOUND;
	}
	RXCallback = pCallback;
	return BC_OK;
}

BACnetResult LocalSocket::RemoveReceiverCallback()
{
	if(RXCallback)
	{
		Stop();
		RXCallback = nullptr;
	}
	return BC_OK;
}

BACnetResult LocalSocket::Start()
{
	if(RXCallback == nullptr)
	{
		return BCE_NOT_INITIALIZED;
	}
	//Start listener thread.
	BACnetResult r = StartListenerThread();
	if(BCE_FAILED(r))
	{
		return r;
	}
	if(BBMDAddress)
	{
		return RenewForeignDeviceRegistration();
	}
	return BC_OK;
}

BACnetResult LocalSocket::Stop()
{
	BACnetResult r = StopListenerThread();
	if(BCE_FAILED(r))
	{
		return r;
	}
	return StopRegistrationTimer();
}

CObjectPtr<IBACnetIPAddress> LocalSocket::CreateIPAddress(const U8* const pIpAddress, U16 usPort, const U8* const pSubnetMask) const
{
	sockaddr_in addr;
	memcpy(&addr.sin_addr.s_addr, pIpAddress, 4);
	addr.sin_port = usPort;
	addr.sin_family = AF_INET;
	return IPAddress::CreateIPAddress(addr, pSubnetMask);
}

BACnetResult LocalSocket::ReadForeignDeviceTable(const FDTEntry *pFDTEntries, size_t & pFDTEntryCount)
{
	return BCE_INVALID_OPERATION;
}

BACnetResult LocalSocket::WriteForeignDeviceTable(const FDTEntry * pFDTEntries, size_t FDTEntryCount)
{
	return BCE_INVALID_OPERATION;
}

BACnetResult LocalSocket::ReadBroadcastTable(const BDTEntry *pBDTEntries, size_t & pBDTEntryCount)
{
	return BCE_INVALID_OPERATION;
}

BACnetResult LocalSocket::WriteBroadcastTable(const BDTEntry * pBDTEntries, size_t BDTEntryCount)
{
	return BCE_INVALID_OPERATION;
}

BACnetResult LocalSocket::SetIPPort(U16 usPortNumber)
{
	if(Addr.sin_port == htons(usPortNumber)) return BC_OK;
	bool restart = false;
	if(Listener->IsRunning())
	{
		Stop();
		restart = true;
	}
	U16 oldport = Addr.sin_port;
	Addr.sin_port = htons(usPortNumber);
	if(::bind(sock, (sockaddr*)&Addr, sizeof(Addr)))
	{
		Addr.sin_port = oldport;
		return BCNRESULT_FROM_SYSTEM(WSAGetLastError());
	}
	Addr.sin_addr.s_addr = INADDR_BROADCAST;
	BroadcastAddress = IPAddress::CreateIPAddress(Addr);
	if(restart) Start();
	return BC_OK;
}

BACnetResult LocalSocket::RegisterAsForeignDevice(const CObjectPtr<IBACnetIPAddress> pRemoteAddress, U16 TimeToLive, bool AutoRefresh)
{
	//are we currently registered as a foreign device?
	if(BBMDAddress)
	{
		BACnetResult r = UnregisterAsForeignDevice();
		if(BCE_FAILED(r))
		{
			return r;
		}
	}
	//set our remote BBMD address to the new one.
	BBMDAddress = CObjectPtr<IPAddress>((IPAddress*)pRemoteAddress.GetInterface());
	FDLifetime = TimeToLive;
	AutoRenew = AutoRefresh;
	//Register as a foreign device now.
	return RenewForeignDeviceRegistration();
}

BACnetResult LocalSocket::RenewForeignDeviceRegistration()
{
	if(!BBMDAddress)
	{
		return BCE_INVALID_OPERATION;
	}
	//send a RegisterForeignDevice command to the bbmd.
	U16 ttl = htons(FDLifetime);
	U16 rc = 0;
	BACnetResult r = SendCommandAndWait(BBMDAddress->GetSocketAddress(), BVLC_RegisterForeignDevice, (U8*)&ttl, 2, rc);
	if(BCE_FAILED(r))
	{
		return r;
	}
	if(rc != 0)
	{
		return BCE_BVLC_RENEWAL_FAILED;
	}
	//renewal worked. start the timer, unless we don't need to.
	if(FDLifetime != 0 && AutoRenew)
	{
		return StartRegistrationTimer();
	}
	return BC_OK;
}

BACnetResult LocalSocket::UnregisterAsForeignDevice()
{
	BACnetResult r = StopRegistrationTimer();
	if(BCE_FAILED(r))
	{
		return r;
	}
	//unregister
	sockaddr_in s = BBMDAddress->GetSocketAddress();
	U8 DeleteFDBuf[6] = {
		s.sin_addr.s_net,
		s.sin_addr.s_host,
		s.sin_addr.s_lh,
		s.sin_addr.s_impno,
		(U8)((s.sin_port & 0xFF00) >> 8),
		(U8)(s.sin_port & 0xFF),
	};
	U16 response = 0;
	r = SendCommandAndWait(s, BVLC_DeleteForeignDevice, DeleteFDBuf, sizeof(DeleteFDBuf), response);
	if(BCE_FAILED(r))
	{
		return r;
	}
	if(response == 0x0050)
	{
		//cannot delete the entry!
		return BCE_BVLC_CANNOT_DELETE_FD_ENTRY;
	}
	BBMDAddress = nullptr;
	FDLifetime = 0;
	AutoRenew = false;
	return BC_OK;
}
