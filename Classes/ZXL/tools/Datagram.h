#ifndef  __Datagram_H__
#define __Datagram_H__
#include "Includes.h"

using namespace DatagramDef;

#define getOneByte(_val) (_val)&0xFF
#define defAndOpt(_val, _bytePos) (_val&(0xFF<<_bytePos * 8))

//数据拼接待验证
class GameDatagram : public CCObject
{
public:
	GameDatagram():_type(0xCC){}
	virtual ~GameDatagram(){}
	virtual int getSize() = 0;
	virtual std::string getGameData() = 0;
	virtual bool isOK(){
		if(_type != 0xCC && getSize() > 0) 
			return true;
		else 
			return false;
	}
	//unsigned int16 _size;
	int _type;
	
};

class MainDatagram : public GameDatagram
{
public:
	MainDatagram():_magic(0),_body(NULL){}
	~MainDatagram(){CC_SAFE_DELETE(_body);}
	int getSize();
	std::string getGameData();
	int _magic;
	GameDatagram* _body;
};

class HandshakeDatagram : public GameDatagram
{
public:
	HandshakeDatagram():_version(""),_requestType(""){}
	~HandshakeDatagram(){}
	int getSize();
	std::string getGameData();
	std::string _version;
	std::string _requestType;

};

class DataDatagram : public GameDatagram
{
public:
	DataDatagram():_id(-1),_route(-1),_body(""){}
	~DataDatagram(){}
	int getSize();
	std::string getGameData();
	int _id;
	int _route;
	std::string _body;
};

class HeartbeatDatagram : public GameDatagram
{
public:
	int getSize(){return 0;}
	std::string getGameData(){return "";}
};

class KickDatagram : public GameDatagram
{
public:
	int getSize(){return 0;}
	std::string getGameData(){
		return "";
	}
};


//}//namespace Datagram end
#endif