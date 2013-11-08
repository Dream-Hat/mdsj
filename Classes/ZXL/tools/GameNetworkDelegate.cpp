#include "GameNetworkDelegate.h"

//定义程序中使用的常量    
#define REMOTE_HOST "172.16.1.29" //服务器端IP地址    
#define REMOTE_PORT    12000         //服务器的端口号    
#define MSGSIZE        65535         //收发缓冲区的大小
#define PREREADSIZE    3                //预读字符大小

char readData[MSGSIZE];
char writeData[MSGSIZE];
char readHead[PREREADSIZE];

#include "DataPackageManager.h"

//pthread 相关声明
static pthread_t pid_heartbeat, pid_read;//进程PID  
pthread_mutex_t mutex_read;//read互斥锁

//static void* th_write(void *r);  //写函数
static void* th_read(void *r);//读函数
static void* th_heartbeat(void*);//读函数
static CPSocket* client; //跨平台socket

static bool heartbeatRunnable; //控制写进程的运行
static bool readRunnable; //控制读进程的运行

bool networkDelegateInit()
{
	bool bRet = false;
	do{
		client = new CPSocket();
		bRet = true;
	}while(0);
	return bRet;
}

bool startNetworkClient()
{
	bool bRet = false;
	do{
		CCLog("client connect start");
		if(! client->cpConnect((const char*)REMOTE_HOST , REMOTE_PORT)){
			CCLog("client connect ERROR");
			break;
		}
		CCLog("client connect OK");

		if(! startHeartbeatProcess()) break;
		if(! startReadProcess()) break;
		bRet = true;
		//m_bClientStart = true;
	}while(0);
	if(! bRet){
		destroyNetworkClient();
	}
	return bRet;
}

bool destroyNetworkClient()
{
	stopReadProcess();
	stopHeartbeatProcess();
	client->cpClose();
	CC_SAFE_DELETE(client);
	//stopWriteProcess();
	return true;
}

bool startHeartbeatProcess()
{
	heartbeatRunnable = true;
	pthread_create(&pid_heartbeat,NULL,th_heartbeat,0);
	return true;
}
bool startReadProcess()
{
	readRunnable = true;
	pthread_create(&pid_read,NULL,th_read,0);
	pthread_mutex_init(&mutex_read, NULL);
	return true;
}

void stopHeartbeatProcess()
{
	//pthread_cancel(pid_heartbeat);
	heartbeatRunnable = false;
}
void stopReadProcess()
{
	//pthread_cancel(pid_read);
	readRunnable = false;
	pthread_mutex_destroy(&mutex_read);
}
void* th_heartbeat(void *r)
{
	while(heartbeatRunnable){
		//...
	}
	return NULL;
}
void* th_read(void *r)
{
	std::string ret("");
	while (readRunnable)
	{
		ret = readDelegate();
		if(!ret.empty()){
			pthread_mutex_lock(&mutex_read);//上锁
			DataPackageManager::recvDataList->push_front(ret);
			pthread_mutex_unlock(&mutex_read);//解锁
			/*CCNode* pNode = CCNode::create();
			pNode->setUserData((void*)&ret);
			CCNotificationCenter::sharedNotificationCenter()->postNotification(CPSocketMsg,pNode );*/
		}
	}
	return NULL;
}

bool writeDelegate(void* ret)
{
	if(ret && client){
		memset(writeData ,0, MSGSIZE);
		GameDatagram* sendData = (GameDatagram* )ret;
		bool success = false;
		int wrCount = 0;
		std::string mydat = sendData->getGameData();
		mydat.copy(writeData, mydat.size(), 0);
		int sdCnt = sendData->getSize();
		wrCount = client->cpWrite(writeData,sdCnt);
		if(wrCount == sendData->getSize()) success = true;
		delete sendData;
		sendData = NULL;
		ret = NULL;
		CCLog("writeDelegate data count : %d" , wrCount);
		return success;
	}
	return false;
}
std::string readDelegate()
{
	memset(readHead ,0, PREREADSIZE);
	memset(readData ,0, MSGSIZE);
	int rdCount = 0;
	unsigned int totalsize = 0;
	rdCount = client->cpRead(readHead,PREREADSIZE);
	if(rdCount != PREREADSIZE || readHead[0] != 0x0b){
		return "";
	}
	totalsize = readHead[1];
	totalsize = (totalsize << 8) + defAndOpt(readHead[2],0);
	//std::string mstr(readHead);
	std::string mstr("");
	int needSize = totalsize - PREREADSIZE;
	int alreadyRdCode = 0;
	while(alreadyRdCode < (totalsize - PREREADSIZE) && (rdCount = client->cpRead(readData,needSize)) > 0 ){
		alreadyRdCode += rdCount;
		mstr.append(readData ,rdCount);
	} 
	//mstr.append('\0');
	//CCLog("readDelegate data  : %x" , mstr);
	return mstr;
}