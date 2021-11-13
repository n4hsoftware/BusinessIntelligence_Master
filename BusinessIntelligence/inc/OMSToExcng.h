#ifndef _OMSTONSE_H_
#define _OMSTONSE_H_

#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "ExcngCommon.h"
#include "OMSConstants.h"
using namespace std;
namespace OMSToExcng
{
	class GRRquest :private ExchngCommon::MsgHdr   //Transcode 2400
	{
		private:
			MsgHdr objMsgHdr;
			short sBoxID;
			char caBrokerID[5];
			char cFillr;
		public:
			int PopulateGRRequestPkt(char*);

	};
	class GRRespns :private ExchngCommon::MsgHdr   //Transcode 2401   
	{
		public:
			MsgHdr objMsgHdr;
			short sBoxID;
			char caBrokerID[5];
			char cFillr;
			char caIPAddress[16];
			long lPort;
			char caSessionKey[8];
		public:
			int PopulateGRResponsePkt();
	};
        class BoxLoginReq :private ExchngCommon::MsgHdr  //Transcode 23000
	{
		public:
			MsgHdr objMsgHdr;
			short sBoxID;
			char caBrokerID[5];
			char caReserved[5];
			char caSessionKey[8];
			int PopulateBoxLoginReq(GRRespns *obj, char*); 

	};
	class BoxLoginResp:private ExchngCommon::MsgHdr  //Transcode 23001
	{
		public:
			MsgHdr objMsgHdr;
			short sBoxID;
			char caReserved[10];
 
	};
	class LoginReq :private ExchngCommon::MsgHdr   //Transcode 2300
	{
		private:
			long lUserId;
			char caReserved[8];
			char caPassworf[8];
			char caReserved1[8];
			char caNewPasswd[8];
			char caTraderName[26];
			long lLastPasswdChngDate[4];
			char caBrokerID[5];
			char cReserved;
			short sBranchID;
			long lVersionNmbr;
			long lBatchToStartTime;
			char cHostSwitchContext;
			char caColour[50];
			char cReserved1;
			short sUserType;
			double dSequenceNmbr;
			char cWsClassName[14];
			char cBrokerStatus;
			char cShowIndex;
			char caBrokerEligibility[2];
			short sMemberType;
			char cClearingStatus;
			char cBrokerName[25];
			char caReserved2[48];


		public:
			int PopulateLogonReqPkt(BoxLoginResp*,char*);
			int SendLoginPktToNse();
			int RcvLogonRespFromExchg();

	};
	class LoginRes                                 //Transcode 2301
	{
		private:

			long lUserId;
			char caReserved[8];
			char caPassworf[8];
			char caReserved1[8];
			char caNewPasswd[8];
			char caTraderName[26];
			long lLastPasswdChngDate[4];
			char caBrokerID[5];
			char cReserved;
			short sBranchID;
			long lVersionNmbr;
			long lBatchToStartTime;
			char cHostSwitchContext;
			char caColour[50];
			char cReserved1;
			short sUserType;
			double dSequenceNmbr;
			char cWsClassName[14];
			char cBrokerStatus;
			char cShowIndex;
			char caBrokerEligibility[2];
			short sMemberType;
			char cClearingStatus;
			char cBrokerName[25];
			char caReserved2[48];

	};
}
#endif
