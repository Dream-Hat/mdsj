#ifndef __CPSocket_H__ 
#define __CPSocket_H__
#include "cocos2d.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
//use winsock : these are head files or lib
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")

#elif CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#endif


#include <stdlib.h>
#include <iostream>
#include <stdio.h>
using namespace std;

enum{
	CLIENT_OK = 0,
	CLIENT_ERROR
};

class CPSocket
{
public:
	CPSocket();

	~CPSocket();

	bool cpConnect(const char* _adr,int _port);

	int cpRead(char *buf,int size);

	int cpWrite(char *buf,int size);

	bool cpClose();
protected:

	void cpInitSocket();
	void cpUninitSocket();

private:
	int m_state;

	string m_szAddress;

	int m_nPort;

#if CC_TARGET_PLATFORM==CC_PLATFORM_WIN32
	SOCKET m_handlerSocket;
#else
	int m_handlerSocket;
#endif
};


#endif