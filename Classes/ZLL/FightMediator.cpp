#include "FightMediator.h"

#include "EventMSG.h"
#include "FightLayer.h"
#include "FightNode.h"

#include "../ZMQ/MessageCenter.h"
#include "../ZMQ/layerManager.h"

FightMediator::FightMediator():m_FightType(FightType_NULL),m_Layer(NULL),m_TurnIndex(1),m_MaxPlayerNum(0)
{
	startEventListen();
	initFightData();
}

FightMediator::~FightMediator()
{
	closeEventListen();
}

void FightMediator::startEventListen()
{
	ADD_EVENT_LISTENER(OnEvent_FightOpen,NULL,this,FightEvent::FIGHTVIEW_OPEN,FightMediator);
	ADD_EVENT_LISTENER(OnEvent_FightClose,NULL,this,FightEvent::FIGHTVIEW_CLOSE,FightMediator);
	ADD_EVENT_LISTENER(OnEvent_NextTurn,NULL,this,FightEvent::FIGHTVIEW_TURNOVER,FightMediator);
	ADD_EVENT_LISTENER(OnEvent_AddPlayer,NULL,this,FightEvent::FIGHTVIEW_ADDPLAYER,FightMediator);
	ADD_EVENT_LISTENER(OnEvent_GameStart,NULL,this,FightEvent::FIGHTVIEW_GAMESTART,FightMediator);
	ADD_EVENT_LISTENER(OnEvent_UseSkillOrTools,NULL,this,FightEvent::FIGHTVIEW_USESOULSKILL,FightMediator);
	ADD_EVENT_LISTENER(OnEvent_UseSkillOrTools,NULL,this,FightEvent::FIGHTVIEW_USETOOLS,FightMediator);
	ADD_EVENT_LISTENER(OnEvent_NotifyNextPlayerAct,NULL,this,FightEvent::FIGHTVIEW_NEXTPLAYER,FightMediator);
}

void FightMediator::closeEventListen()
{
	REMOVE_EVENT_LISTENER(NULL,NULL,FightEvent::FIGHTVIEW_OPEN);
	REMOVE_EVENT_LISTENER(NULL,NULL,FightEvent::FIGHTVIEW_OPEN);
	REMOVE_EVENT_LISTENER(NULL,NULL,FightEvent::FIGHTVIEW_TURNOVER);
	REMOVE_EVENT_LISTENER(NULL,NULL,FightEvent::FIGHTVIEW_ADDPLAYER);
	REMOVE_EVENT_LISTENER(NULL,NULL,FightEvent::FIGHTVIEW_GAMESTART);
	REMOVE_EVENT_LISTENER(NULL,NULL,FightEvent::FIGHTVIEW_USESOULSKILL);
	REMOVE_EVENT_LISTENER(NULL,NULL,FightEvent::FIGHTVIEW_USETOOLS);
	REMOVE_EVENT_LISTENER(NULL,NULL,FightEvent::FIGHTVIEW_NEXTPLAYER);
}

void FightMediator::OnEvent_FightOpen( cocos2d::CCObject* sender,int msgid,cocos2d::CCObject* obj )
{
	if (NULL==m_Layer)
	{
		clearData();
		m_Layer=FightLayer::create(-290);
		m_Layer->m_FightMediator=this;
		m_Layer->m_MainLayer->m_FightMediator=this;
		m_Layer->m_EffectLayer->mFightMediator=this;
		ADD_SCENE_TO_LAYER(m_Layer,LayerManager::fightLayer);
	}
}

void FightMediator::OnEvent_FightClose( cocos2d::CCObject* sender,int msgid,cocos2d::CCObject* obj )
{
	if (m_Layer)
	{
		REMOVE_SCENE_FROM_LAYER(m_Layer);
		m_Layer=NULL;
	}
}

void FightMediator::OnEvent_NextTurn( cocos2d::CCObject* sender,int msgid,cocos2d::CCObject* obj )
{
	changeTurnIndex();
	m_Layer->NotifyElementAct(m_TurnIndex);
}

void FightMediator::OnEvent_AddPlayer( cocos2d::CCObject* sender,int msgid,cocos2d::CCObject* obj )
{
	if (m_Layer)
	{
		EventParam* ep=(EventParam*)obj;
		addPlayer(ep->intParam);
	}
}

void FightMediator::OnEvent_GameStart(cocos2d::CCObject* sender,int msgid,cocos2d::CCObject* obj)
{
	m_TurnIndex=1;
	if (m_Layer)
	{
		m_Layer->NotifyMsg("GameStart");
		m_Layer->NotifyElementAct(m_TurnIndex);
		m_Layer->m_MainLayer->m_GameStarted=true;
	}
}

void FightMediator::OnEvent_UseSkillOrTools(cocos2d::CCObject* sender,int msgid,cocos2d::CCObject* obj)
{
	if (msgid==FightEvent::FIGHTVIEW_USESOULSKILL)
	{
		EventParam* ep=(EventParam*)obj;
		char pBuffer[100];
		sprintf(pBuffer,"use skill %d ",ep->intParam);
		m_Layer->NotifyMsg(pBuffer);
	}
	else if (msgid==FightEvent::FIGHTVIEW_USETOOLS)
	{
		EventParam* ep=(EventParam*)obj;
		char pBuffer[100];
		sprintf(pBuffer,"use tools %d ",ep->intParam);
		m_Layer->NotifyMsg(pBuffer);
	}
}

void FightMediator::OnEvent_NotifyNextPlayerAct(cocos2d::CCObject* sender,int msgid,cocos2d::CCObject* obj)
{
	m_Layer->setViewToNextPlayer(m_TurnIndex);
}
//////////////////////////////////////////////////////////////////////////
//测试用到的方法
void FightMediator::initFightData()
{
	//设置战斗类型，假设为PVP
	m_FightType=FightType_NULL;
	m_TurnIndex=-1;
	//设置最大玩家数
	if (m_FightType==FightType_PVP)
		m_MaxPlayerNum=m_Team_1_List.size()+m_Team_2_List.size();
	else if (m_FightType==FightType_PVE||m_FightType==FightType_PVBOSS)
		m_MaxPlayerNum=m_Team_1_List.size()+m_Monster_List.size();
	else
		m_MaxPlayerNum=0;
}
void FightMediator::addPlayer(int type)
{
	if (type==0||type>4)return;
	FightElementDataNode player;
	if (type==1)
	{
		player._id=type;
		player._turnIndex=type;
		player._name="player1";
		player._teamID=type;
		player._maxHp=100;
		player._hp=100;
		player._def=5;
		player._atk=10;
		player._startPoint=ccp(200,300);
	}
	else if (type==2)
	{
		player._id=type;
		player._turnIndex=type;
		player._name="player2";
		player._teamID=type;
		player._maxHp=100;
		player._hp=100;
		player._def=5;
		player._atk=10;
		player._startPoint=ccp(900,300);
	}
	m_Layer->m_MainLayer->addPlayer(player);
	m_MaxPlayerNum++;
}

void FightMediator::clearData()
{
	m_FightType=FightType_NULL;
	m_TurnIndex=0;
	m_MaxPlayerNum=0;
}

void FightMediator::changeTurnIndex()
{
	m_TurnIndex=(m_TurnIndex+1)%m_MaxPlayerNum;
	if (m_TurnIndex==0)m_TurnIndex=m_MaxPlayerNum;
}