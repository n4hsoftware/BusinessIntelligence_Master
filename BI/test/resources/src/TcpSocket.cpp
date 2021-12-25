#include "TcpSocket.h"
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>
TcpSocket::TcpSocket()
{
	iSocketFd=-1;
}
int TcpSocket::CreateSocket(const std::string& sInterfaceIp,int iPortNumber, int iTTL)
{
	iSocketFd = socket(AF_INET,SOCK_STREAM,0);
	if(0 > iSocketFd)
	{
		perror("Failed to create socket");    
		return TCP_SOCKERROR_CREATE;
	}
	bzero(&SocketConfig,0);
	SocketConfig.sin_family = AF_INET;
	if(sInterfaceIp.empty())
	{
		SocketConfig.sin_addr.s_addr = INADDR_ANY;
	}
	else
	{
		SocketConfig.sin_addr.s_addr = inet_addr(sInterfaceIp.c_str());
	}

	SocketConfig.sin_port = htons(iPortNumber);
	return TCP_SUCCESS;

}
//Binding is done at port level
int TcpSocket::CreateAndBind(const std::string& sInterfaceIp,int iPortNumber, int iTTL)
{
	iSocketFd = socket(AF_INET,SOCK_STREAM,0);
	if(0 > iSocketFd)
	{
		perror("Failed to create socket");    
		return TCP_SOCKERROR_CREATE;
	}
	/*int so_reuseaddr =1;
	  int iResultVal = setsockopt(iSocketFd, SOL_SOCKET,SO_REUSEADDR,&so_reuseaddr,
	  sizeof(so_reuseaddr));
	  if(-1 == iResultVal)
	  {
	  return TCP_SOCKERROR_REUSEADDR;
	  }*/
	memset(&SocketConfig,0,sizeof(SocketConfig));
	SocketConfig.sin_family = AF_INET;
	if(sInterfaceIp.empty())
	{
		SocketConfig.sin_addr.s_addr = INADDR_ANY;
	}
	else
	{
		SocketConfig.sin_addr.s_addr = inet_addr(sInterfaceIp.c_str());
	}

	SocketConfig.sin_port = htons(iPortNumber);
	int iBindResult = bind(iSocketFd,(struct sockaddr*)&SocketConfig,sizeof(SocketConfig));
	if(-1 == iBindResult)
	{
		return TCP_SOCKERROR_BIND;
	}
	/*int iTtl = iTTL >= 0 ? iTTL : 1;
	  int iTtlResultVal = setsockopt(iSocketFd, IPPROTO_IP, IP_TTL,&iTtl,sizeof(iTtl));
	  if(-1 == iTtlResultVal)
	  {
	  return TCP_SOCKERROR_TTL;
	  }*/
	return TCP_SUCCESS;
}

//Binding is done to IP & Port combo
int TcpSocket::CreateAndBind(const std::string& sInterfaceIp,
		const std::string& sMulticastGroupIP,
		int iPortNumber,
		int iTTL)
{
	//Assuming IPv4 hence using AF_INET
	iSocketFd = socket(AF_INET,SOCK_DGRAM,TCP_PROTOCOL);
	if(0 > iSocketFd)
	{
		return TCP_SOCKERROR_CREATE;
	}
	/*int so_reuseaddr =1;
	  int iResultVal = setsockopt(iSocketFd, SOL_SOCKET,SO_REUSEADDR,&so_reuseaddr,
	  sizeof(so_reuseaddr));
	  if(-1 == iResultVal)
	  {
	  return TCP_SOCKERROR_REUSEADDR;
	  }*/
	memset(&SocketConfig,0,sizeof(SocketConfig));
	SocketConfig.sin_family = AF_INET;
	SocketConfig.sin_addr.s_addr = inet_addr(sMulticastGroupIP.c_str());
	SocketConfig.sin_port = htons(iPortNumber);
	int iBindResult = bind(iSocketFd,(struct sockaddr*)&SocketConfig,sizeof(SocketConfig));
	if(-1 == iBindResult)
	{
		return TCP_SOCKERROR_BIND;
	}
	/*int iTtl = iTTL >= 0 ? iTTL : 1;
	  int iTtlResultVal = setsockopt(iSocketFd, IPPROTO_IP, IP_TTL,&iTtl,sizeof(iTtl));
	  if(-1 == iTtlResultVal)
	  {
	  return TCP_SOCKERROR_TTL;
	  }*/
	return TCP_SUCCESS;
}      
int TcpSocket::Listen()
{
	if (listen(iSocketFd,MAX_CLIENT)<0)	
	{
		return errno;		
	}	
	return TCP_SUCCESS;
}
int TcpSocket::Accept(int *iClientScoketFD,const std::string& sInterfaceIp)
{
	int iSocketLibAddrLen;	
	*iClientScoketFD = -1;
	*iClientScoketFD = accept(iSocketFd,(struct sockaddr*)&SocketConfig,(socklen_t*)&iSocketLibAddrLen);
	if (*iClientScoketFD < 0 ) 	    
	{
		return errno; 	     
	}
	return TCP_SUCCESS;
}
int TcpSocket::Connect()
{
	if (iSocketFd < 0 )
	{    
		std::cout<<"Socket not created"<<std::endl;
	}
	if (connect(iSocketFd,(struct sockaddr*)&SocketConfig,sizeof(SocketConfig))<0)
	{
		perror("Failed To connect");
		return errno;
	}
	return TCP_SUCCESS;	
}
int TcpSocket::Receive(char* Buffer,int BufferLength,int& MsgLength)
{
	int iRcvdBytes{0};
	iRcvdBytes = recv(iSocketFd, Buffer, BufferLength,MSG_TRUNC);
	if(iRcvdBytes > BufferLength)
	{
		return TCP_SOCKERROR_TRUNCATED;
	}
	else if(-1 == iRcvdBytes)
	{
		if(errno == EAGAIN)
		{
			return TCP_SOCKERROR_RECVTIMEOUT;
		}
		else
		{
			return TCP_SOCKERROR_RECV;
		}

	}
	else if(0 == iRcvdBytes)
	{
		return TCP_SOCKERROR_NODATARCVD;
	}
	else
	{
		return TCP_SUCCESS;
	}
}
int TcpSocket::RecvFrom(unsigned char* Buffer,
		int BufferLength,
		int& MsgLength,
		struct sockaddr* SrcAddr,
		socklen_t* SrcAddrLen)
{
	int iRcvdBytes = recvfrom(iSocketFd, Buffer,BufferLength,MSG_TRUNC,SrcAddr,SrcAddrLen);
	MsgLength= iRcvdBytes;
	if(iRcvdBytes>BufferLength)
	{
		return TCP_SOCKERROR_TRUNCATED;
	}
	else if(-1==iRcvdBytes)
	{
		return TCP_SOCKERROR_RECV;
	}
	else if(0==iRcvdBytes)
	{
		return TCP_SOCKERROR_NODATARCVD;
	}

	return TCP_SUCCESS;

}
int TcpSocket::SendData(char *caMsgData, int iMsgLength)
{
	int iNumbOfByteSent = 0;
	iNumbOfByteSent = send(iSocketFd,    
			caMsgData,
			iMsgLength,
			MSG_NOSIGNAL);
	if (iNumbOfByteSent != iMsgLength)
	{
		std::cout<<"Number of bytes sent on scoket is"<<iNumbOfByteSent<<std::endl;
		perror("Failed to send data");
		return errno;     
	}
	return TCP_SUCCESS;

}

bool TcpSocket::Close()
{
	if(0 < iSocketFd)
	{
		if(shutdown(iSocketFd, SHUT_RDWR) ==0)
		{
			if(close(iSocketFd) == 0)
			{
				iSocketFd = -1;
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}
int TcpSocket::JoinMcastGrp(const std::string& sInterfaceIp,
		const std::string& sMulticastGroupIP)
{
	ip_mreq Mreq;
	memset(&Mreq,0,sizeof(Mreq));
	Mreq.imr_interface.s_addr=inet_addr(sInterfaceIp.c_str());
	Mreq.imr_multiaddr.s_addr=inet_addr(sMulticastGroupIP.c_str());
	int JoinRetVal=setsockopt(iSocketFd, IPPROTO_IP,IP_ADD_MEMBERSHIP,(const char*)&Mreq,sizeof(Mreq));
	if(JoinRetVal == -1)
	{
		return TCP_SOCKERROR_MCASTJOIN;
	}
	return TCP_SUCCESS;
}                
int TcpSocket::SetRecvTimeOutSocketOption(int TimeInSec)
{
	struct timeval T;
	T.tv_sec= TimeInSec;
	T.tv_usec=0;
	int RetVal=setsockopt(iSocketFd, SOL_SOCKET,SO_RCVTIMEO,&T,sizeof(T));
	if(RetVal ==-1)
	{
		return TCP_SOCKERROR_RECVTIMEOUT;
	}
	return TCP_SUCCESS;
}
bool TcpSocket::IsError(int ErrorCode,std::string& ErrorMsg)
{
	switch(ErrorCode)
	{
		case TCP_SUCCESS:
			return false;
		case TCP_SOCKERROR_CREATE:
			ErrorMsg="ERROR IN CREATING TCP SOCKET";
			return true;
		case TCP_SOCKERROR_BIND:
			ErrorMsg="ERROR in BINDING TCP SOCKET";
			return true;
		case TCP_SOCKERROR_RECVTIMEOUT:
			ErrorMsg="ERROR SETTING RECEIVE TIMEOUT OPTION ON TCP SOCKET";
			return true;
		case TCP_SOCKERROR_MCASTJOIN:
			ErrorMsg="ERROR IN SENDING MULTICAST JOIN ON TCP SOCKET";
			return true;
		case TCP_SOCKERROR_NODATARCVD:
			ErrorMsg="ERROR NO DATA RECEIVED FROM SOCKET (MESSAGELEN IS ZERO)";
			return true;
		default:
			ErrorMsg="UNKNOWN TCP ERROR";
	}
	return true;
}

TcpSocket::~TcpSocket()
{
}
