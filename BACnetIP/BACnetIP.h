#ifndef _BACNET_IP_H_
#define _BACNET_IP_H_

#include <BACnetInterface.h>

#ifdef BACNETIP_EXPORTS
#define BACNETIP_ENTRYPOINT BACNET_EXPORT
#else
#define BACNETIP_ENTRYPOINT BACNET_IMPORT
#endif

#ifndef __IBACnetIPComponent__FWD_DEFINED__
#define __IBACnetIPComponent__FWD_DEFINED__
typedef struct IBACnetIPPort IBACnetIPPort;
#endif

#ifndef __IBACnetLocalSubnet__FWD_DEFINED__
#define __IBACnetLocalSubnet__FWD_DEFINED__
typedef struct IBACnetLocalSubnet IBACnetLocalSubnet;
#endif

#ifndef __IBACnetWideAreaSubnet__FWD_DEFINED__
#define __IBACnetWideAreaSubnet__FWD_DEFINED__
typedef struct IBACnetWideAreaSubnet IBACnetWideAreaSubnet;
#endif

#ifndef __IBACnetRemoteSubnet__FWD_DEFINED__
#define __IBACnetRemoteSubnet__FWD_DEFINED__
typedef struct IBACnetRemoteSubnet IBACnetRemoteSubnet;
#endif

#ifndef __IBACnetIPAddress__FWD_DEFINED__
#define __IBACnetIPAddress__FWD_DEFINED__
typedef struct IBACnetIPAddress IBACnetIPAddress;
#endif

struct BDTEntry
{
	U8 IpAddress[4];
	U16 Port;
	U8 SubnetMask[4];
};

struct FDTEntry
{
	U8 IpAddress[4];
	U16 Port;
	U16 TimeToLive;
	U16 RemainingTime;
};

BACNET_INTERFACE("{E4B1D612-6A5C-4B87-BC31-51C89FFFAFA6}")
IBACnetIPAddress: public IBACnetAddress
{
	BCNMETHODTYPE(U16, GetPort() const) BCPURE;
	BCNMETHOD(GetSubnetMask(U8* const pSubnetMask, U8 uiMaskSize) const) BCPURE;
	BCNMETHOD(GetIpAddress(U8* const pIpAddress, U8 uiAddressSize) const) BCPURE;
};

BACNET_INTERFACE("{5080A26F-1B1A-4B90-A6F6-F7C5FC7F9479}")
IBACnetIPPort: public IBACnetPort
{
	BCNMETHODTYPE(CObjectPtr<IBACnetIPAddress>, CreateIPAddress(const U8* const pIpAddress, U16 usPort, const U8* const pSubnetMask = nullptr) const) BCPURE;
	BCNMETHOD(ReadForeignDeviceTable(const FDTEntry* &ppFDTEntries, size_t &pFDTEntryCount)) BCPURE;
	BCNMETHOD(WriteForeignDeviceTable(const FDTEntry* pFDTEntries, size_t FDTEntryCount)) BCPURE;
	BCNMETHOD(ReadBroadcastTable(const BDTEntry* &ppBDTEntries, size_t &pBDTEntryCount)) BCPURE;
	BCNMETHOD(WriteBroadcastTable(const BDTEntry* pBDTEntries, size_t BDTEntryCount)) BCPURE;
	BCNMETHOD(SetIPPort(U16 usPortNumber)) BCPURE;
};

//Local IP subnet (single BACnet subnetwork).
//No BBMD support, but can register as a foreign device.
BACNET_INTERFACE("{10777267-CBC4-40A8-9116-B45FE41C62A1}")
IBACnetLocalSubnet: public IBACnetIPPort
{
	BCNMETHOD(RegisterAsForeignDevice(const CObjectPtr<IBACnetIPAddress> pRemoteAddress, U16 TimeToLive, bool AutoRefresh = true)) BCPURE;
	BCNMETHOD(RenewForeignDeviceRegistration()) BCPURE;
	BCNMETHOD(UnregisterAsForeignDevice()) BCPURE;

};

//Local IP subnet w/BBMD for foreign devices (single BACnet subnetwork).
BACNET_INTERFACE("{CCA00378-42A2-4C62-969D-1835F2C62D1C}")
IBACnetWideAreaSubnet: public IBACnetIPPort
{
	BCNMETHOD(AddRemotePeer(const CObjectPtr<IBACnetIPAddress> pRemoteAddress)) BCPURE;
};

//Foreign Device registration, no local (NAT/BBMD-Router).
BACNET_INTERFACE("{F7C94926-6066-42E7-9DF3-200290D7C999}")
IBACnetRemoteSubnet: public IBACnetPort
{
	BCNMETHOD(AddRemotePeer(const CObjectPtr<IBACnetIPAddress> pRemoteAddress)) BCPURE;
};

CObjectPtr<IBACnetLocalSubnet>
BACNETIP_ENTRYPOINT
CreateLocalSubnet(
	CObjectPtr<IBACnetThreadPool> pThreadPool,
	U16 PortNumber = 0xBAC0);

#endif