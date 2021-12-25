#include<ExchngConnector.h>
using namespace OMSToExcng;
namespace ExchngConnector
{
	int NSEConnector::ConnectToNSE()
	{
		ErrorCode=TcpObj.CreateSocket("10.222.168.241",9602,1);
		if(TcpObj.IsError(ErrorCode,ErrorMsg))
		{
			std::cout<<"Error| OMS Sender : "<< ErrorMsg <<std::endl;
			return false;
		}
		ErrorCode = TcpObj.Connect();
		if(TcpObj.IsError(ErrorCode,ErrorMsg))
		{
			std::cout<<"Error| OMS Sender : "<< ErrorMsg <<std::endl;
			return false;
		}
		else
		{
			std::cout<<"App| Connected to server : "<< ErrorMsg <<std::endl;
		}
		objOfGRRquest.PopulateGRRequestPkt(MsgBuffer);
		/*Sending GR request packet to Exchange*/
		ErrorCode = TcpObj.SendData(MsgBuffer,1024);
		if(TcpObj.IsError(ErrorCode,ErrorMsg))
		{
			std::cout<<"Error| OMS Failed to Send Data : "<< ErrorMsg <<std::endl;
			return false;
		}
		else
		{
			std::cout<<"App| Data Sent successfully : "<< ErrorMsg <<std::endl;
		}
		ErrorCode = TcpObj.Receive(caRcvMsgBuffer,1024,iRcvMsgLength);
		if(TcpObj.IsError(ErrorCode,ErrorMsg))
		{
			std::cout<<"Error| OMS Failed to Receive Data "<< ErrorMsg <<std::endl;
			return false;
		}
		else
		{
			std::cout<<"App| Data Receive successfully : "<< ErrorMsg <<std::endl;
		}
		objOfGRRespns = reinterpret_cast<GRRespns*>(caRcvMsgBuffer);
		std::cout<<"Received IP From GR:-"<<objOfGRRespns->caIPAddress<<endl;
		std::cout<<"Received Port From GR:-"<<objOfGRRespns->lPort<<endl;
		/*Sending Box Login Request Packet*/
		/*Reset Msg Buffer To Populate BoxLoginReq*/
		memset(MsgBuffer,0,sizeof(MsgBuffer));
		objOfBoxLoginReq.PopulateBoxLoginReq(objOfGRRespns,MsgBuffer);

		ErrorCode=TcpObjOfLogin.CreateSocket(objOfGRRespns->caIPAddress,objOfGRRespns->lPort,1);
		if(TcpObjOfLogin.IsError(ErrorCode,ErrorMsg))
		{
			std::cout<<"Error| OMS Sender : "<< ErrorMsg <<std::endl;
			return false;
		}
		ErrorCode = TcpObjOfLogin.Connect();
		if(TcpObjOfLogin.IsError(ErrorCode,ErrorMsg))
		{
			std::cout<<"Error| OMS Sender : "<< ErrorMsg <<std::endl;
			return false;
		}
		else
		{
			std::cout<<"App| Connected to server : "<< ErrorMsg <<std::endl;
		}

		ErrorCode = TcpObjOfLogin.SendData(MsgBuffer,1024);
		if(TcpObjOfLogin.IsError(ErrorCode,ErrorMsg))
		{
			std::cout<<"Error| OMS Failed to Send Data : "<< ErrorMsg <<std::endl;
			return false;
		}
		else
		{
			std::cout<<"App| Data Sent successfully : "<< ErrorMsg <<std::endl;
		}

		memset(caRcvMsgBuffer,0,sizeof(caRcvMsgBuffer));
		ErrorCode = TcpObjOfLogin.Receive(caRcvMsgBuffer,1024,iRcvMsgLength);
		if(TcpObj.IsError(ErrorCode,ErrorMsg))
		{
			std::cout<<"Error| OMS Failed to Receive Data "<< ErrorMsg <<std::endl;
			return false;
		}
		else
		{
			std::cout<<"App| Data Receive successfully : "<< ErrorMsg <<std::endl;
		}

		objOfBoxLoginRes = reinterpret_cast<BoxLoginResp*>(caRcvMsgBuffer);

		/*Sending Login Request Packet*/
		/*ResetMsg Buffer To populate Login Request Packet*/

		memset(MsgBuffer,0,sizeof(MsgBuffer));
		objOfLoginReq.PopulateLogonReqPkt(objOfBoxLoginRes,MsgBuffer);

		ErrorCode = TcpObjOfLogin.SendData(MsgBuffer,1024);
		if(TcpObjOfLogin.IsError(ErrorCode,ErrorMsg))
		{
			std::cout<<"Error| OMS Failed to Send Data : "<< ErrorMsg <<std::endl;
			return false;
		}
		else
		{
			std::cout<<"App| Data Sent successfully : "<< ErrorMsg <<std::endl;
		}

		memset(caRcvMsgBuffer,0,sizeof(caRcvMsgBuffer));
		ErrorCode = TcpObjOfLogin.Receive(caRcvMsgBuffer,1024,iRcvMsgLength);
		if(TcpObj.IsError(ErrorCode,ErrorMsg))
		{
			std::cout<<"Error| OMS Failed to Receive Data "<< ErrorMsg <<std::endl;
			return false;
		}
		else
		{
			std::cout<<"App| Data Receive successfully : "<< ErrorMsg <<std::endl;
		}

		objOfLoginResp = reinterpret_cast<LoginRes*>(caRcvMsgBuffer);


		return SUCCESS;
	}
}

