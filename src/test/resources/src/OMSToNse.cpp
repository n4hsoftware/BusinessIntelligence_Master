#include "ExcngCommon.h"
#include "OMSToExcng.h"
using namespace OMSToExcng;

namespace OMSToExcng
{
	int GRRquest::PopulateGRRequestPkt(char *buffer)
	{
		buffer = new char[1024];
		GRRquest objOfGRRquest;
		objOfGRRquest.objMsgHdr.sTxnCode=2400;
		objOfGRRquest.objMsgHdr.lLogTime=0;
		objOfGRRquest.objMsgHdr.lTraderID=101;
		objOfGRRquest.objMsgHdr.sErrorCode=0;
		objOfGRRquest.objMsgHdr.llTimeStamp=0;
	        objOfGRRquest.objMsgHdr.sMsgLength=sizeof(objOfGRRquest);
		objOfGRRquest.sBoxID=0;
		memcpy(buffer,&objOfGRRquest,sizeof(objOfGRRquest));
		return SUCCESS;

	}
	int BoxLoginReq::PopulateBoxLoginReq(GRRespns *objOfGRRespns, char *buffer)
	{
		buffer = new char[1024];
		BoxLoginReq objOfBoxLoginReq;
		objOfBoxLoginReq.objMsgHdr.sTxnCode = 23000;
		objOfBoxLoginReq.objMsgHdr.lLogTime = 0;
		objOfBoxLoginReq.lTraderID=101;
		objOfBoxLoginReq.objMsgHdr.sErrorCode=0;
		objOfBoxLoginReq.objMsgHdr.llTimeStamp=0;
		objOfBoxLoginReq.objMsgHdr.sMsgLength=sizeof(objOfBoxLoginReq);
		objOfBoxLoginReq.sBoxID = objOfGRRespns->sBoxID;
		memcpy(objOfBoxLoginReq.caBrokerID,objOfGRRespns->caBrokerID,sizeof(objOfGRRespns->caBrokerID));

		memcpy(objOfBoxLoginReq.caSessionKey,objOfGRRespns->caSessionKey,sizeof(objOfGRRespns->caSessionKey));
		return SUCCESS;
	}
	int LoginReq::PopulateLogonReqPkt(BoxLoginResp *objOfBoxLoginResp,char *buffer)
	{

		/*Create Objects Of LoginReq Class and MsgHdrClass*/
		buffer = new char[1024];
		ExchngCommon::MsgHdr objMsgHdr;
		objMsgHdr.sTxnCode = 2300;	
		LoginReq objLoginReq;

		/*Returning logon req packet in buffer format*/
		memcpy(buffer,&objMsgHdr,sizeof(objMsgHdr));
		memcpy(buffer+sizeof(objMsgHdr),&objLoginReq,sizeof(objLoginReq));
		return SUCCESS;

	}

}
