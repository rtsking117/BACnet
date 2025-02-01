//Testbed - For diagnosing/testing components of the framework.
#include "Testbed.h"
#include "Support.h"
#include "BACnetRequestParser.h"

using std::cout;
using std::endl;

CObjectPtr<IBACnetEvent> close = nullptr;

static BOOL CALLBACK SignalHandler(DWORD ctrltype)
{
	switch(ctrltype)
	{
	case CTRL_C_EVENT:
	case CTRL_BREAK_EVENT:
	case CTRL_CLOSE_EVENT:
	case CTRL_LOGOFF_EVENT:
	case CTRL_SHUTDOWN_EVENT:
		close->Set();
		return TRUE;
	}
	return FALSE;
}

int main()
{
	setlocale(LC_ALL, nullptr);
	system("chcp 65001");
	close = CreateBACnetEvent(true, false);
	BOOL ret = SetConsoleCtrlHandler(SignalHandler, TRUE);
	CObjectPtr<IBACnetThreadpool> tp = CreateBACnetThreadpool();
	CObjectPtr<IBACnetLocalSubnet> local = CreateLocalSubnet(tp);
	CObjectPtr<IBACnetNetwork> net = CreateSimpleNetwork(tp);
	CObjectPtr<IBACnetTransactionManager> tsm = CreateTransactionManager(128);
	CObjectPtr<BACnetRequestParser> app = CreateRequestParser();
	local->SetIPPort(47808);
	net->AttachPort(1, local);
	tsm->AttachNetwork(net);
	app->AttachTransactionManager(tsm);
	CObjectPtr<IBACnetEvent> evt = CreateBACnetEvent(true, false);
	CObjectPtr<IBACnetSpinLock> l = CreateBACnetSpinLock();
	app->RegisterPreliminaryDisplayCallback([l](U8 ServiceChoice, bool IsConfirmed, BACnetValue &val) -> BACnetResult
	{
		l->Lock();
		cout << "Service: " << ConvertServiceToString(ServiceChoice, IsConfirmed) << endl;
		cout << "Parameters: " << endl;
		int ntabs = 1;
		PrintBACnetValue(val, ntabs);
		l->Unlock();
		return BC_OK;
	});
	app->Start();
	int deadlinecount = 0;
	bool exit = false;
	while(deadlinecount < 10 && !exit)
	{
		CObjectPtr<IBACnetWaitableObject> evts[] = { evt, close };
		U32 index = 0;
		BACnetResult ret = WaitForObjects(evts, index, false, 10000);
		switch(ret)
		{
		case BCE_WAIT_TIMEOUT:
			cout << "No Packets...." << endl;
			++deadlinecount;
			break;
		case BC_OK:
			if(index == 1)
			{
				cout << "Closing..." << endl;
				exit = true;
				continue;
			}
			break;
		default:
			cout << "Wait operation failed. " << endl;
			__debugbreak();
			return -1;
		}
		deadlinecount = 0;
		evt->Reset();
	}
	if(deadlinecount)
	{
		cout << "Closing due to inactivity." << endl;
	}
	app->Stop();
	return 0;
}
