#pragma once
#include "cocoa/CCObject.h"
#include "cocoa/CCArray.h"
#include "support/CCNotificationCenter.h"
#include "cocoa/CCString.h"
#include <vector>
#include <map>
#include "AllCommandSignal.h"
#include "cocos2d.h"
#include "../ZXL/tools/DataPackageManager.h"

USING_NS_CC;
using namespace std;

class RecvStruct;
class RecvImpl;
class MessageStruct;
class PostDelay;

typedef void (cocos2d::CCObject::*ConnectPackageFuncXY)(int xy,void* pack);
#define ConnectPackageFuncXY_selector(_SELECTOR) (ConnectPackageFuncXY)(&_SELECTOR)


typedef void (cocos2d::CCObject::*MessageFunc)(CCObject* sender,int msgid,cocos2d::CCObject* obj);
#define MessageFunc_selector(_SELECTOR) (MessageFunc)(&_SELECTOR)

#define DECL_NET_PAK_HANDLER(fun) virtual void fun(short xyid, char* p,int len);// OnMsg!


#define DEF_NET_PAK_HANDLER(c,fun) \
void ##c::##fun(short xyid, char* p,int len){
#define DEF_NET_PAK_HANDLER_END() \
	}


#define ADD_PACK_LISTENER(fun,receiver,xyid,c)\
MessageCenter::instance->addRecvObserver(receiver,xyid,ConnectPackageFuncXY_selector(c::fun));

#define REMOVE_PACK_LISTENER(receiver,xyid)\
	if(MessageCenter::instance)MessageCenter::instance->removeRecvObserver(receiver,xyid);

#define REMOVE_ALL_PACK_LISTENER(receiver)\
	if(MessageCenter::instance)MessageCenter::instance->removeAllRecvObserver(receiver);

// #define SEND_PACKSHORT(cmd,s)\
// MessageCenter::instance->SendPackageS(cmd,s);
// 
// #define SEND_PACKINT(cmd,i)\
// MessageCenter::instance->SendPackageI(cmd,i);
// 
// #define SEND_PACKCHAR(cmd,c)\
// MessageCenter::instance->SendPackageC(cmd,c);

#define SEND_PACK(route,xieyi)\
	MessageCenter::instance->SendPackage(route,xieyi);

// #define SEND_PACK2(cmd)\
// MessageCenter::instance->SendPackage(cmd);


#define ADD_EVENT_LISTENER(fun,sender,receiver,eventid,c)\
MessageCenter::instance->addMsgObserver(sender,receiver,eventid,MessageFunc_selector(c::fun));

#define REMOVE_EVENT_LISTENER(sender,receiver,xyid)\
	if(MessageCenter::instance)MessageCenter::instance->removeMsgObserver(sender,receiver,xyid);

#define REMOVE_ALL_EVENT_LISTENER(receiver)\
	if(MessageCenter::instance)MessageCenter::instance->removeAllMsgObserver(receiver);

#define SEND_EVENT(sender,msgid,param)\
	if(MessageCenter::instance)MessageCenter::instance->postMessage(sender,msgid,param);


class MessageCenter : public CCObject
{
private:
	vector<RecvStruct*> rsVector;
	vector<RecvStruct*>rsVectorTemp;

	vector<MessageStruct*>  msgVector;
	vector<MessageStruct*>  msgVectorTemp;
	int ixy;
	int msgxycount;

	int xyr;
	int msgisclean;
	vector<PostDelay*> postVector;

	CCScheduler* m_pScheduler;

	int destory;

public:
	 MessageCenter();

    ~MessageCenter();
	static MessageCenter *instance;
	 
    static void purgeMessageCenter(void);

	void clear();

	// void OnConnectEvent(int ev,int code,CConnect* sender);
	// void OnPackage(char* pack,int len,CConnect* sender);
	 void OnPackage(void* data,void* route);
	 void addRecvObserver(CCObject *listen,int listenxyid,ConnectPackageFuncXY listenfun); //添加一个协议监听
	 void removeRecvObserver(CCObject *listen,int listenxyid);//移除一个协议监听
	 void removeAllRecvObserver(CCObject* listen);
	 void addMsgObserver(CCObject *sender,CCObject *listen,int listenmsgid,MessageFunc listenfun); //添加一个系统监听
	 void removeMsgObserver(CCObject *sender,CCObject *listen,int listenmsgid);//移除一个系统监听
	 void removeAllMsgObserver(CCObject *listen);
	 void postMessage(CCObject *sender,int msgid,CCObject* param);//发送系统监听


// 	void SendPackageC(short cmd,char c){// 发送协议
// 		char sss[3];
// 		Win32Tools::biostream bios(sss,3);
// 		bios << cmd << c;
// 		connect->SendPackage(sss,bios.length());
// 	}
// 	 void SendPackageS(short cmd,short s){// 发送协议
// 		 char sss[4];
// 		 Win32Tools::biostream bios(sss,4);
// 		 bios << cmd << s;
// 		 connect->SendPackage(sss,bios.length());
// 	 }
// 	 void SendPackageI(short cmd,int i){// 发送协议
// 		 char sss[8];
// 		 Win32Tools::biostream bios(sss,8);
// 		 bios << cmd << i;
// 		 connect->SendPackage(sss,bios.length());
// 	 }
// 	 template<class XIEYI> void SendPackage(short cmd,XIEYI xie){// 发送协议
// 		 char sss[4096];
// 		 Win32Tools::biostream bios(sss,4096);
// 		 bios << cmd << xie;
// 		 connect->SendPackage(sss,bios.length(),false);
// 	 }
	 void SendPackage(int route, std::string str){// 发送协议
		 DataPackageManager::shareDataPackageManager()->requestData(str, route,NULL,NULL);
	 }
// 	 void SendPackage(short cmd){
// 		 char sss[2];
// 		 Win32Tools::biostream bios(sss,2);
// 		 bios << cmd;
// 		connect->SendPackage(sss,2);
// 	 }

	 void connectGame();
private:
	 void postNotification(void* p,int route);//发送协议监听
	 virtual void update(float dt);


};

class EventParams:public cocos2d::CCObject
{
public:
	EventParams(){}
	void* mData;
};

class EventParam:public cocos2d::CCObject
{
public:
	int intParam;
};