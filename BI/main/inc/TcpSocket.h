#ifndef _TCPSOCKET_H_
#define _TCPSOCKET_H_

#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define TCP_PROTOCOL 17
#define TCP_SUCCESS 1
#define TCP_SOCKERROR_CREATE -1
#define TCP_SOCKERROR_BIND -2
#define TCP_SOCKERROR_RECV -3
#define TCP_SOCKERROR_RECVTIMEOUT -4
#define TCP_SOCKERROR_NODATARCVD -5
#define TCP_SOCKERROR_REUSEADDR -6
#define TCP_SOCKERROR_TTL -7
#define TCP_SOCKERROR_TRUNCATED -8
#define TCP_SOCKERROR_NODATA -9
#define TCP_SOCKERROR_MCASTJOIN -10 
#define MAX_CLIENT 30
class TcpSocket
{
	private:
		int iSocketFd;
		struct sockaddr_in SocketConfig;
	public:
		TcpSocket();
		int GetSocketFd()
		{ 
			return iSocketFd; 
		}
		/*Create Socket for TCP Clienta and return socket fd*/
		int CreateSocket(const std::string& sInterfaceIp,int iPortNumber, int iTTL);
		/*Create the socket and bind the connection*/
		int CreateAndBind(const std::string& sInterfaceIp, int iPortNumber, int iTTL);
		int CreateAndBind(const std::string& sInterfaceIp,
		                  const std::string& sMulticastGroupIP,
						  int iPortNumber,
						  int iTTL);
		/*Join the Multicast IP and Port*/
		int JoinMcastGrp(const std::string& sInterfaceIp,
		                 const std::string& sMulticastGroupIP);
		int SetRecvTimeOutSocketOption(int TimeInSec);
		/*Receive data from TCP channel*/
		int Receive(char* Buffer,int BufferLength,int& MsgLength);
		int Receive(int Fd,unsigned char* Buffer,int BufferLength,int& MsgLength);
		int Receive(mmsghdr* Buffer,int BufferLength,int& MsgLength);
		int RecvFrom(unsigned char* Buffer,int BufferLength,int& MsgLength,
		             struct sockaddr* SrcAddr,socklen_t* SrcAddrLen);
		int Accept(int *iClientScoketFD,const std::string& sInterfaceIp);
		/*Establish the connection with socket FD*/
		int Connect();
		/*Wait on socket for client request*/
		int Listen();
		/*Send data over TCP channel*/
		int SendData(char *caMsgData, int iMsgLength);
		int SendTo(const char* Msg,int MsgLength,struct sockaddr* ToAddr,
		           socklen_t ToAddrLen);
		int SendTo(const unsigned char* Msg,int MsgLength,struct sockaddr* ToAddr,
		           socklen_t ToAddrLen);
		struct sockaddr_in GetSocketAddr(){
			return SocketConfig;
		}
		bool Close();
		static bool IsError(int ErrorCode,std::string& ErrorMsg);
		static bool IsSocketStale(int ErrorCode);
		static bool Close(int& SockFd);
		~TcpSocket();
};

#endif
