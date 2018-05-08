#ifndef _BACNET_MSTP_H_
#define _BACNET_MSTP_H_

#include <BACnetInterface.h>

#ifndef __IBACnetMSTPMaster__FWD_DEFINED__
#define __IBACnetMSTPMaster__FWD_DEFINED__
typedef struct IBACnetMSTPPort IBACnetMSTPPort;
#endif

/*


*/

BACNET_INTERFACE("{31448B33-A55B-4B6D-BDBD-68F1D3CF45E8}")
IBACnetMSTPPort: public IBACnetPort
{
	/*
	TS
	ReceivedInvalidFrame
	ReceivedValidFrame
	SilenceTimer
	EventCount
	DestAddr
	FrameType

	*/
};


#endif