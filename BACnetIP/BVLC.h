#pragma once

enum BVLLMessageType
{
	BVLC_Result,
	BVLC_WriteBDT,
	BVLC_ReadBDT,
	BVLC_ReadBDTAck,
	BVLC_ForwardedNPDU,
	BVLC_RegisterForeignDevice,
	BVLC_ReadFDT,
	BVLC_ReadFDTAck,
	BVLC_DeleteForeignDevice,
	BVLC_DistributeBroadcastToNetwork,
	BVLC_OriginalUnicast,
	BVLC_OriginalBroadcast,
	BVLC_SecureBVLL,
};