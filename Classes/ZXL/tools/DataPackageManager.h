#ifndef  __DataPackageManager_H__
#define __DataPackageManager_H__

#include "ZXL/tools/Includes.h"
#include "ZXL/tools/Datagram.h"

typedef void (CCObject::*SendCallback)(void*, void*);
#define datapackage_selector(_SELECTOR) (SendCallback)(&_SELECTOR)

/*
namespace GameRoute{
	static const int BAGNAME =2000;
	static const int BAGOPEN =BAGNAME+1;

	static const int SOULName =3000;
}*/


class DataPackageManager : public CCObject
{
public:
	DataPackageManager();
	~DataPackageManager();

	virtual bool init();
	static DataPackageManager* shareDataPackageManager() ;
	static void purgeDataPackageManager();
	void update(float dt);

public:
	static std::list<std::string>* recvDataList;
	
	//从队列中取出包
	//static GameDatagram* getDatagram(bool bClear = true);
	
	//将包装入队列
	//static bool putDatagram(GameDatagram* d);

	/*static char* getUnpackeData();*/

	//void putUnpackeData(char* _body ,int _route,int _type, SendCallback _cb, CCObject* _sender);

	
	bool putDelegate(GameDatagram* d);
	//校验
	bool checkDatagram(GameDatagram* d);

	//清理数据
	void clearAll();

	//封装数据包
	DataDatagram* packageDataDatagram(std::string _body,int _route ,int _type ,int _id);
	HandshakeDatagram* packageHandshakeDatagram(std::string _version, std::string _requestType ,int _type);
	MainDatagram* packageMainDatagram(GameDatagram* _body ,int _type, int _magic);

	//解开数据包
	bool analyzeDataDatagram(std::string& _dataData);
	bool analyzeHandshakeDatagram(std::string& _handshakeData);
	bool analyzeMainDatagram(std::string& _mainData);

	//static bool processBytesData(std::string data);

	SendCallback m_targetCallback;

	CCObject* m_pTarget;

	std::map<int, int> *m_routeOfId;

	int data_id;
	int m_id4Route;

public:
	void requestData(std::string _body ,int _route,SendCallback _cb, CCObject* _sender);
	void requestHandshake(SendCallback _cb, CCObject* _sender);
	void handshakeAck();

	int getClientState(){return m_clientState;}

private:
	ePackageMnangerState m_clientState;

	
};


#endif