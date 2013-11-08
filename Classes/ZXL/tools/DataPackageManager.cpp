#include "DataPackageManager.h"
#include "GameNetworkDelegate.h"

static DataPackageManager* s_shareDataPackageManager = NULL;

std::list<std::string>* DataPackageManager::recvDataList = new std::list<std::string>();

extern pthread_mutex_t mutex_read;

DataPackageManager::DataPackageManager()
{
	CCLog("DataPackageManager()");
}

DataPackageManager::~DataPackageManager()
{
	CC_SAFE_DELETE(m_routeOfId);
	destroyNetworkClient();
	CCLog("~DataPackageManager()");
}
void DataPackageManager::purgeDataPackageManager()
{
	CC_SAFE_DELETE(s_shareDataPackageManager->recvDataList);
	CC_SAFE_DELETE(s_shareDataPackageManager);
}

DataPackageManager* DataPackageManager::shareDataPackageManager()
{
	if(s_shareDataPackageManager == NULL){
		s_shareDataPackageManager = new DataPackageManager();
		CCAssert(s_shareDataPackageManager->init(),"DataPackageManager init error");
	}
	return s_shareDataPackageManager;
}

bool DataPackageManager::init()
{
	bool bRet = false;
	do 
	{
		m_targetCallback = NULL;
		m_pTarget = NULL;
		m_id4Route = 0;
		m_routeOfId = new std::map<int,int>();
		data_id = 0;
		m_clientState = ManangerState_Unknow;
		
		CC_BREAK_IF(! networkDelegateInit());
		CC_BREAK_IF(! startNetworkClient());

		CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(DataPackageManager::update), this, 0.01, false);
		
		bRet = true;
	} while (0);
	return bRet;
}

void DataPackageManager::update(float dt)
{
	if(! recvDataList->empty()){
		pthread_mutex_lock(&mutex_read);//上锁
		std::string data = (std::string)recvDataList->front();
		if(! analyzeMainDatagram(data) ){
			CCLog("analyzeMainDatagram is error");
		}
		recvDataList->pop_front();
		pthread_mutex_unlock(&mutex_read);//解锁
	}
}

/*
GameDatagram* DataPackageManager::getDatagram(bool bClear / * = true * /)
{
	//return getDelegate();
}*/

/*
bool DataPackageManager::putDatagram(GameDatagram* d)
{
	if(d){
		return putDelegate(d);
	}else{
		return false;
	}
}*/

bool DataPackageManager::checkDatagram(GameDatagram* d)
{
	return true;
}

void DataPackageManager::clearAll()
{

}

DataDatagram* DataPackageManager::packageDataDatagram(std::string _body ,int _route ,int _type ,int _id)
{
	DataDatagram* ret = NULL;
	switch(_type){
	case Data_REQUEST:
		ret = new DataDatagram();
		ret->_id = _id;
		ret->_route = _route;
		ret->_body = _body;
		ret->_type = _type;
		break;
	case Data_NOTIFY:
		ret = new DataDatagram();
		ret->_route = _route;
		ret->_body = _body;
		break;
	case Data_PUSH:
		break;
	}
	return ret;
}
HandshakeDatagram* DataPackageManager::packageHandshakeDatagram(std::string _version, std::string _requestType ,int _type)
{
	HandshakeDatagram* ret = NULL;
	switch(_type){
	case Handshake_REQUEST:
		ret = new HandshakeDatagram();
		ret->_version = _version;
		ret->_requestType = _requestType;
		ret->_type = _type;
		break;
	case Handshake_ACK:
		ret = new HandshakeDatagram();
		ret->_type = _type;
		break;
	}
	return ret;
}
MainDatagram* DataPackageManager::packageMainDatagram(GameDatagram* _body ,int _type, int _magic)
{
	MainDatagram* ret = new MainDatagram();
	ret->_type = _type;
	ret->_body = _body;
	ret->_magic = _magic;
	return ret;
}

bool DataPackageManager::analyzeMainDatagram(std::string& _mainData)
{
	bool bRet = false;
	unsigned char mainType = _mainData[0];
	_mainData.erase(0,1);
	switch(mainType){
	case Main_HANDSHAKE:
		bRet = analyzeHandshakeDatagram(_mainData);
		break;
	case Main_HEARTBEAT:
		break;
	case Main_DATA:
		bRet = analyzeDataDatagram(_mainData);
		break;
	case Main_KICK:
		bRet = true;
		break;
	}
	return bRet;
}

bool DataPackageManager::analyzeDataDatagram(std::string& _dataData)
{
	bool bRet = false;
	unsigned char dataType = _dataData[0];
	int dataId = 0;
	int dataRoute = 0;
	int route = 0;
	unsigned char dataCode = 0;
	switch (dataType){
	case Data_REQUEST:

		break;
	case Data_NOTIFY:
		break;
	case Data_RESPONSE:
		dataId = (int)((_dataData[1]<<24) + defAndOpt((_dataData[2]<<16),2) + defAndOpt((_dataData[3]<<8),1) + defAndOpt(_dataData[4],0));
		m_id4Route = dataId;
		dataCode = (int)(_dataData[5]);
		
		if(dataCode == DataCode_ok){
			//success
			_dataData.erase(0,6);
			m_clientState = ManangerState_DataCodeOK;

			int route = 0;
			if(m_pTarget && m_targetCallback){
				std::map<int,int>::iterator it=m_routeOfId->find(m_id4Route);
				if (it!=m_routeOfId->end())
				{
					route = it->second;
					m_routeOfId->erase(it);
				}
				(m_pTarget->*m_targetCallback)((void*)(&_dataData),(void* )(++route));
				//.....
				CCLog("recvDataCallback to Sender ");
			}
			bRet = true;
		}else{
			m_clientState = ManangerState_DataCodeERR;
			switch(dataCode){
			case DataCode_no_server:
				CCLog("DataCode_no_server");
				break;
			case DataCode_logout_or_timeout:
				CCLog("DataCode_logout_or_timeout");
				break;
			case DataCode_param_or_type_err:
				CCLog("DataCode_param_or_type_err");
				break;
			case DataCode_server_err:
				CCLog("DataCode_server_err");
				break;
			}

		}//.....
		break;
	case Data_PUSH:
		//m_clientState = ManangerState_DataCodeOK;
		route = (int)((_dataData[1]<<8) + defAndOpt(_dataData[2], 0) );
		_dataData.erase(0,3);
		if(m_pTarget && m_targetCallback){
			(m_pTarget->*m_targetCallback)((void*)(&_dataData),(void* )route);
		}
		bRet = true;
		break;
	}
	return bRet;
}
bool DataPackageManager::analyzeHandshakeDatagram(std::string& _handshakeData)
{
	unsigned char handshakeType = _handshakeData[0];
	int handshakeCode = 0;
	
	switch (handshakeType)	{
	case Handshake_REQUEST:
		break;
	case Handshake_RESPONSE:
		handshakeCode = (( _handshakeData[1] << 8) + defAndOpt(_handshakeData[2],0) );//高位
		if(handshakeCode == HandshakeCode_ok){
			//....返回一个handshakeAck
			handshakeAck();
			m_clientState = ManangerState_HandshakeOK;
		}else{
			m_clientState = ManangerState_HandshakeERR;
			switch(handshakeCode){
			case HandshakeCode_failed:
				CCLog("HandshakeCode_failed");
				break;
			case HandshakeCode_version_err:
				CCLog("HandshakeCode_version_err");
				break;
			}
		}
		break;
	case Handshake_ACK:
		break;
	}
	return "";
}
void DataPackageManager::handshakeAck()
{
	HandshakeDatagram* handshakePack = packageHandshakeDatagram("","",Handshake_ACK );
	MainDatagram* mainPack = packageMainDatagram(handshakePack , Main_HANDSHAKE, DatagramHeadTag);
	putDelegate(mainPack);
}

void DataPackageManager::requestData(std::string _body ,int _route,SendCallback _cb, CCObject* _sender)
{
	//打包成data
	if(_cb) m_targetCallback = _cb;
	if(_sender) m_pTarget = _sender;
	DataDatagram* dataPack = packageDataDatagram(_body , _route, Data_REQUEST ,++data_id);
	MainDatagram* mainPack = packageMainDatagram(dataPack , Main_DATA, DatagramHeadTag);
	m_routeOfId->insert(pair<int,int>(data_id, _route));
	putDelegate(mainPack);
}
void DataPackageManager::requestHandshake(SendCallback _cb, CCObject* _sender)
{
	if(_cb) m_targetCallback = _cb;
	if(_sender) m_pTarget = _sender;
	HandshakeDatagram* handshakePack = packageHandshakeDatagram("handshake request","request type",Handshake_REQUEST );
	MainDatagram* mainPack = packageMainDatagram(handshakePack , Main_HANDSHAKE, DatagramHeadTag);
	putDelegate(mainPack);
}

/*
void DataPackageManager::putUnpackeData(char* _body ,int _route,int _type, SendCallback _cb, CCObject* _sender)
{

}*/

bool DataPackageManager::putDelegate(GameDatagram* d)
{
	if(d && d->isOK()){//isOK()  判断 _magic 字段是否设置正确
		return writeDelegate((void*)d);
	}
	return false;
}
/*

bool DataPackageManager::processBytesData(std::string data)
{
	if(data.empty()) return false;
	std::string mainData(data);
	unsigned char mainType = mainData.front();
	char* dataBody;
	mainData = mainData.substr(1,mainData.length()-1);
	switch(mainType){
	case Main_HANDSHAKE:
		break;
	case Main_HEARTBEAT:
		break;
	case Main_DATA:
		if(m_pSender && m_sendCallback){
			dataBody = analyzeDataDatagram(mainData);
			if(dataBody != ""){
				(m_pSender->*m_sendCallback)((void*)dataBody);
			}
		}
		break;
	case Main_KICK:
		break;
	}

	data.clear();
	mainData.clear();


	return true;
}*/