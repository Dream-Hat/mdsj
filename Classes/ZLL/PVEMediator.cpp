#include "PVEMediator.h"
#include "PVELayer.h"
#include "EventMSG.h"
#include "Define.h"

#include "../ZMQ/MessageCenter.h"
#include "../ZMQ/layerManager.h"

#define PVELEVELLAYER 6	//游戏关卡界面层
#define PVEGAMEROOMLAYER 7 //游戏房间层

#define PVELEVELLAYERTAG 110

USING_NS_CC;
PVEMediator::PVEMediator():_layer(NULL)
{
	startEventListen();
}

PVEMediator::~PVEMediator()
{
	closeEventListen();
}

void PVEMediator::startEventListen()
{
	ADD_EVENT_LISTENER(OnEvent_PVEViewOpen,NULL,this,PVEEvent::PVEVIEW_OPEN,PVEMediator);
	ADD_EVENT_LISTENER(OnEvent_PVEViewClose,NULL,this,PVEEvent::PVEVIEW_CLOSE,PVEMediator);
	ADD_EVENT_LISTENER(OnEvent_PVEViewMove,NULL,this,PVEEvent::PVEVIEW_MAPMOVELEFT,PVEMediator);
	ADD_EVENT_LISTENER(OnEvent_PVEViewMove,NULL,this,PVEEvent::PVEVIEW_MAPMOVERIGHT,PVEMediator);
	ADD_EVENT_LISTENER(OnEvent_PVEViewMove,NULL,this,PVEEvent::PVEVIEW_MAPMOVEOVER,PVEMediator);
	ADD_EVENT_LISTENER(OnEvent_PVEViewOpenLevel,NULL,this,PVEEvent::PVEVIEW_OPENLEVEL,PVEMediator);
	ADD_EVENT_LISTENER(OnEvent_PVEViewEnterGameRoom,NULL,this,PVEEvent::PVEVIEW_ENTERGAMEROOM,PVEMediator);
	ADD_EVENT_LISTENER(OnEvent_PVEViewGotoTargetPage,NULL,this,PVEEvent::PVEVIEW_GOTOTARGETPAGE,PVEMediator);
	ADD_EVENT_LISTENER(OnEvent_PVELevelSetKeyPadTrue,NULL,this,PVEEvent::PVEVIEW_SETLEVELKEYPADTRUE,PVEMediator);
}

void PVEMediator::closeEventListen()
{
	REMOVE_EVENT_LISTENER(NULL,this,PVEEvent::PVEVIEW_OPEN);
	REMOVE_EVENT_LISTENER(NULL,this,PVEEvent::PVEVIEW_CLOSE);
	REMOVE_EVENT_LISTENER(NULL,this,PVEEvent::PVEVIEW_MAPMOVELEFT);
	REMOVE_EVENT_LISTENER(NULL,this,PVEEvent::PVEVIEW_MAPMOVERIGHT);
	REMOVE_EVENT_LISTENER(NULL,this,PVEEvent::PVEVIEW_MAPMOVEOVER);
	REMOVE_EVENT_LISTENER(NULL,this,PVEEvent::PVEVIEW_OPENLEVEL);
	REMOVE_EVENT_LISTENER(NULL,this,PVEEvent::PVEVIEW_ENTERGAMEROOM);
	REMOVE_EVENT_LISTENER(NULL,this,PVEEvent::PVEVIEW_GOTOTARGETPAGE);
	REMOVE_EVENT_LISTENER(NULL,this,PVEEvent::PVEVIEW_SETLEVELKEYPADTRUE);
}

void PVEMediator::OnEvent_PVEViewOpen( cocos2d::CCObject* sender,int msgid,cocos2d::CCObject* obj )
{
	if (NULL==_layer)
	{
		_layer=PVELayer::create();
		_layer->m_PVEMediator=this;
		ADD_SCENE_TO_LAYER(_layer,LayerManager::otherUILayer);
	}
}

void PVEMediator::OnEvent_PVEViewClose( cocos2d::CCObject* sender, int msgid,cocos2d::CCObject* obj )
{
	if (_layer)
	{
		REMOVE_SCENE_FROM_LAYER(_layer);
		_layer=NULL;
	}
}

void PVEMediator::OnEvent_PVEViewMove( cocos2d::CCObject* sender,int msgid,cocos2d::CCObject* obj )
{
	if (NULL==_layer)return;
	if (NULL==_layer->m_MapLayer)return;
	if (msgid==PVEEvent::PVEVIEW_MAPMOVELEFT)
	{
		//_layer->m_MapLayer->layerMove(true);
	}
	else if (msgid==PVEEvent::PVEVIEW_MAPMOVERIGHT)
	{
		//_layer->m_MapLayer->layerMove(false);
	}
	else if (msgid==PVEEvent::PVEVIEW_MAPMOVEOVER)
	{
		if (NULL==_layer->m_UILayer)return;
		_layer->m_UILayer->setMapCanMove(true);
		//设置按钮状态
		EventParam* ep=(EventParam*)obj;
		_layer->m_UILayer->setBtnsState(ep->intParam);
		//移除多余的背景
		//_layer->m_MapLayer->changeBackgroundPoint();
	}
}

void PVEMediator::OnEvent_PVEViewOpenLevel(cocos2d::CCObject* sender,int msgid,cocos2d::CCObject* obj)
{
	if (NULL==_layer)return;
	PVELevelLayer* levelLayer=PVELevelLayer::create(-160,PVEFightType_BOSS);
	_layer->addChild(levelLayer,PVELEVELLAYER,PVELEVELLAYERTAG);
}

void PVEMediator::OnEvent_PVEViewEnterGameRoom( cocos2d::CCObject* sender,int msgid,cocos2d::CCObject* obj )
{
	if (NULL==_layer)return;//
	PVEGameRoomLayer* gameRoomLayer=PVEGameRoomLayer::create((-170));
	_layer->addChild(gameRoomLayer,PVEGAMEROOMLAYER);
}

void PVEMediator::OnEvent_PVEViewGotoTargetPage( cocos2d::CCObject* sender,int msgid,cocos2d::CCObject* obj )
{
	EventParam* ep=(EventParam*)obj;
	if (NULL==ep)return;
	if (NULL==_layer)return;
	if (NULL==_layer->m_MapLayer)return;
	_layer->m_MapLayer->gotoTargetPage(ep->intParam);
}

void PVEMediator::OnEvent_PVELevelSetKeyPadTrue( cocos2d::CCObject* sender,int msgid,cocos2d::CCObject* obj )
{
	if (_layer)
	{
		PVELevelLayer* levelLayer=(PVELevelLayer*)_layer->getChildByTag(PVELEVELLAYERTAG);
		if (levelLayer!=NULL)
		{
			levelLayer->setKeypadEnabled(true);
		}
	}
}
