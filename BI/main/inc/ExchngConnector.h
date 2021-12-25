#ifndef _EXCHNG_CONNECTOR_H_
#define _EXCHNG_CONNECTOR_H_

#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "OMSToExcng.h"
#include "ExcngCommon.h"
#include "OMSConstants.h"
#include "TcpSocket.h"
using namespace std;
using namespace OMSToExcng;
namespace ExchngConnector
{
	class NSEConnector
	{
		private:
			TcpSocket TcpObj;
			TcpSocket TcpObjOfLogin;
			int ErrorCode=0;
			char MsgBuffer[1024];
			char caRcvMsgBuffer[1024];
			std::string ErrorMsg="";
			int iRcvMsgLength;
			GRRquest objOfGRRquest;
			GRRespns *objOfGRRespns;
			BoxLoginReq objOfBoxLoginReq;
			BoxLoginResp *objOfBoxLoginRes;
			LoginReq     objOfLoginReq;
			LoginRes     *objOfLoginResp; 
		public:
			NSEConnector() {};
			int ConnectToNSE();
			bool Start();
			~NSEConnector() {};

	};
}
#endif
