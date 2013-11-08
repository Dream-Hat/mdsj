#ifndef  __GameNetworkDelegate_H__
#define  __GameNetworkDelegate_H__

#include "Includes.h"
#include "CPSocket.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
#include <./pthread/pthread.h>
#else
#include <pthread.h>
#endif

#include "Datagram.h"



bool writeDelegate(void* ret);
static std::string readDelegate();

bool networkDelegateInit();
bool startNetworkClient();
bool destroyNetworkClient();

bool startReadProcess();
bool startHeartbeatProcess();

//void stopWriteProcess();
void stopReadProcess();
void stopHeartbeatProcess();

#endif