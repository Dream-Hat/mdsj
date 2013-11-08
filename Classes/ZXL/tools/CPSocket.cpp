#include "CPSocket.h"

CPSocket::CPSocket()
{
	cpInitSocket();
}
CPSocket::~CPSocket()
{
	cpUninitSocket();
}

void CPSocket::cpInitSocket()
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	WORD wVersionRequested;
	WSADATA wsaData;
	int ret;
	//WinSock初始化
	wVersionRequested = MAKEWORD(1, 1); //希望使用的WinSock DLL的版本
	ret = WSAStartup(wVersionRequested, &wsaData);
	if(ret!=0)
	{
		printf("WSAStartup() failed!\n");
		return;
	}
	//确认WinSock DLL支持版本2.2
	if(LOBYTE(wsaData.wVersion)!=1 || HIBYTE(wsaData.wVersion)!=1)
	{
		WSACleanup();
		printf("Invalid WinSock version!\n");
		return;
	}
#endif
}

void CPSocket::cpUninitSocket()
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	WSACleanup();
#endif
}

bool CPSocket::cpConnect(const char* _adr,int _port)
{
	printf("socket will be connected");
	m_szAddress = _adr;
	m_nPort = _port;
	sockaddr_in sa;
	struct hostent *hp;
	hp = gethostbyname(m_szAddress.c_str());
	if (hp)
	{
		const char *addr = inet_ntoa(*(struct in_addr *)hp->h_addr_list[0]);
		struct in_addr ip;
		ip.s_addr = inet_addr(addr);
		sa.sin_family = AF_INET;
		sa.sin_port = htons(m_nPort);
		sa.sin_addr = ip;
		//sa.sin_addr.S_un.S_addr = htonl()
	}
	if (sa.sin_port == 0)
	{
		return false;
	}
	int rs = 0;
	m_handlerSocket = socket(AF_INET, SOCK_STREAM, 0);
	rs = connect(m_handlerSocket, (sockaddr *)&sa, sizeof(sa));
	return rs > -1;
	
}

bool CPSocket::cpClose()
{
	int closeInt = -1;
#if defined(WIN32)
	printf("socket will be closed");
	//closeInt = shutdown(m_handlerSocket, 2);
	closeInt = closesocket(m_handlerSocket);
#else
	//closeInt = shutdown(handlerSocket, SHUT_RDWR);
	close(m_handlerSocket);
#endif
	if( closeInt == 0 )
	{
		return true;
	}else{
		//printf("close sock err : %d",WSAGetLastError());
		return false;
	}
}

int CPSocket::cpWrite(char *buf,int size)
{
	int writeInt = send(m_handlerSocket, buf, size, 0);
	printf("socket send count : %d", writeInt);
	return writeInt;
}

int CPSocket::cpRead(char *buf,int size)
{
	int readInt = recv(m_handlerSocket, buf, size, MSG_WAITALL);
	printf("socket recv count : %d", readInt);
	return readInt;
}




