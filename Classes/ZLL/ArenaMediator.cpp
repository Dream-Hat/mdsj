#include "ArenaMediator.h"
#include "EventMSG.h"
#include "ArenaLayer.h"

#include "../ZMQ/MessageCenter.h"
#include "../ZMQ/layerManager.h"

#include "../proto_files/LandProto.pb.h"
#include "../proto_files/AthleticProto.pb.h"

USING_NS_CC;
using namespace com::tiange::mdsj::proto;

ArenaMediator::ArenaMediator():_layer(NULL)
{
	startEventListen();
	startPackListen();
}

ArenaMediator::~ArenaMediator()
{
	closeEventListen();
	closePackListen();
}

void ArenaMediator::startEventListen()
{
	ADD_EVENT_LISTENER(OnEvent_ArenaOpen,NULL,this,ArenaEvent::ARENAVIEW_OPEN,ArenaMediator);
	ADD_EVENT_LISTENER(OnEvent_ArenaClose,NULL,this,ArenaEvent::ARENAVIEW_CLOSE,ArenaMediator);
}

void ArenaMediator::closeEventListen()
{
	REMOVE_EVENT_LISTENER(NULL,NULL,ArenaEvent::ARENAVIEW_OPEN);
	REMOVE_EVENT_LISTENER(NULL,NULL,ArenaEvent::ARENAVIEW_CLOSE);
}

void ArenaMediator::startPackListen()
{
	ADD_PACK_LISTENER(OnPackage_ModeList,this,SocketCMDConst::SMSG_ARENA_RESPONSEMODELIST,ArenaMediator);
	ADD_PACK_LISTENER(OnPackage_GameRoomList,this,SocketCMDConst::CMSG_ARENA_REQUESTROOMLIST,ArenaMediator);
}

void ArenaMediator::closePackListen()
{
	REMOVE_PACK_LISTENER(this,SocketCMDConst::CMSG_ARENA_REQUESTMODELIST);
	REMOVE_PACK_LISTENER(this,SocketCMDConst::CMSG_ARENA_REQUESTROOMLIST);
}

void ArenaMediator::OnEvent_ArenaOpen( CCObject* sender,int msgid,cocos2d::CCObject* obj )
{
	if (NULL==_layer)
	{
		_layer=ArenaLayer::create();
		_layer->m_ArenaMadiator=this;
		ADD_SCENE_TO_LAYER(_layer,LayerManager::otherUILayer);

		//发送请求获取模式列表的消息
		ModeListRequest modeListRequest;
		std::string strDat("");
		modeListRequest.SerializeToString(&strDat);
		SEND_PACK(SocketCMDConst::CMSG_ARENA_REQUESTMODELIST,strDat);
	}
}

void ArenaMediator::OnEvent_ArenaClose( cocos2d::CCObject* sender,int msgid,cocos2d::CCObject* obj )
{
	if (_layer)
	{
		REMOVE_SCENE_FROM_LAYER(_layer);
		_layer=NULL;
	}
}


void ArenaMediator::OnPackage_ModeList(int xy,void* pack)
{
	com::tiange::mdsj::proto::ModeListResponse modeList;
 	std::string str = *((std::string*)pack);
	modeList.ParseFromString(str);
	ModeListResponse_Mode* mode=modeList.mutable_modes(0);

	_layer->refreshModeList(modeList);
}

void ArenaMediator::OnPackage_GameRoomList(int xy,void* pack)
{

}


