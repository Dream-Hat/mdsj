#include "Datagram.h"

std::string MainDatagram::getGameData()
{
	std::string retStr("");
	retStr.append(1,getOneByte(_magic)); //首先是类型 1B
	retStr.append(1,getOneByte(getSize() >> 8));//
	retStr.append(1,getOneByte(getSize()));
	retStr.append(1,getOneByte(_type));
	if(_body) retStr.append(_body->getGameData());
	return retStr;
}

std::string HandshakeDatagram::getGameData()
{
	std::string retStr("");
	retStr.append(1,getOneByte(_type)); //首先是类型 1B
	retStr.append(_version); //s
	retStr.append(_requestType);//s
	return retStr;
}

std::string DataDatagram::getGameData()
{
	std::string retStr("");
	retStr.append(1,getOneByte(_type)); //首先是类型1B
	if(_id != -1){
		retStr.append(1,getOneByte(_id >> 24));//ID   4B
		retStr.append(1,getOneByte(_id >> 16));
		retStr.append(1,getOneByte(_id >> 8));
		retStr.append(1,getOneByte(_id));
	}
	retStr.append(1,getOneByte(_route >> 8));
	retStr.append(1,getOneByte(_route));//route  2B
	retStr.append(_body);//s
	return retStr;
}

int MainDatagram::getSize()
{
	int bodySize = 0; 
	if(_body) bodySize = _body->getSize(); 
	return ( bodySize + 4 ) ;//4 表示size + magic + type 的长度
}

int HandshakeDatagram::getSize()
{
	return (_version.size() + 1 + _requestType.size());
}

int DataDatagram::getSize()
{
	int idSize = 0, routeSize = 0;
	if(_id != -1) idSize = 4;
	if(_route != -1) routeSize = 2;
	return (idSize + routeSize + _body.size() + 1);
}