#include "PVENode.h"
#include "ToolsFun.h"
USING_NS_CC;


RatingNode::RatingNode():m_StarNum(0)
{
	//m_SpStar[0]=NULL;
	//m_SpStar[1]=NULL;
	//m_SpStar[2]=NULL;
}

RatingNode::~RatingNode()
{

}

bool RatingNode::init()
{
	bool bRet=false;
	do 
	{
		bRet=true;
	} while (0);
	return bRet;
}

void RatingNode::initNodeWithType(int starNum)
{
	if (starNum>3||starNum<0)
	{
		this->removeAllChildrenWithCleanup(true);
		return;
	}
	m_StarNum=starNum;
	this->removeAllChildrenWithCleanup(true);
	if (starNum==0)return;
	else if (starNum==1)
	{
		CCSprite* spStar=CCSprite::create(PVE_FIELD_PIC_STAR_1);
		this->addChild(spStar);
		CCSize starSize=spStar->getContentSize();
		spStar->setPosition(ccp(-starSize.width,0));
	}
	else if (starNum=2)
	{
		CCSprite* spStar1=CCSprite::create(PVE_FIELD_PIC_STAR_1);
		this->addChild(spStar1);
		CCSprite* spStar2=CCSprite::create(PVE_FIELD_PIC_STAR_1);
		this->addChild(spStar2);
		CCSize size=spStar2->getContentSize();
		spStar1->setPosition(ccp(-size.width,0));
	}
	else if (starNum==3)
	{
		CCSprite* spStar1=CCSprite::create(PVE_FIELD_PIC_STAR_1);
		this->addChild(spStar1);
		CCSprite* spStar2=CCSprite::create(PVE_FIELD_PIC_STAR_1);
		this->addChild(spStar2);
		CCSprite* spStar3=CCSprite::create(PVE_FIELD_PIC_STAR_1);
		this->addChild(spStar3);
		CCSize size=spStar2->getContentSize();
		spStar1->setPosition(ccp(-size.width,0));
		spStar3->setPosition(ccp(size.width,0));
	}
	else
		return ;
}

//////////////////////////////////////////////////////////////////////////
//GameRoom_PlayerNode

GameRoom_PlayerNode::GameRoom_PlayerNode()
{
	m_SpBackground=0;
	m_SpPlayer=0;
	m_SpMaster=0;
	m_SpGetReady=0;
	m_LbPlayerNickName=0;
	m_LbPlayerLevel=0;
	m_NodeType=GameRoom_PlayerNodeType_Empty;
	m_IsReady=false;
}

GameRoom_PlayerNode::~GameRoom_PlayerNode()
{

}

bool GameRoom_PlayerNode::init()
{
	bool bRet=false;
	do 
	{
		initNode();
		bRet=true;
	} while (0);
	return bRet;
}

void GameRoom_PlayerNode::initNode()
{
	m_SpBackground=CCSprite::create(PVE_FIELD_BUTTON_SEAT_1);
	this->addChild(m_SpBackground);
	m_SpPlayer=CCSprite::create(PVE_FIELD_PIC_PLAYER);
	this->addChild(m_SpPlayer);
	m_SpMaster=CCSprite::create(PVE_FIELD_GAMEROOM_MASTER);
	this->addChild(m_SpMaster);
	m_SpGetReady=CCSprite::create(PVE_FIELD_GAMEROOM_READY);
	this->addChild(m_SpGetReady);
	m_SpGetReady->setVisible(false);
}

void GameRoom_PlayerNode::setNodeType( GameRoom_PlayerNodeType nodeType )
{
	m_NodeType=nodeType;
	if (m_NodeType==GameRoom_PlayerNodeType_Empty)
	{
		this->removeAllChildrenWithCleanup(true);
		m_SpPlayer=m_SpMaster=m_SpGetReady=m_LbPlayerNickName=m_LbPlayerLevel=0;
		ToolsFun::changeSpriteFrame(m_SpBackground,PVE_FIELD_BUTTON_SEAT_1);
	}
	else if (m_NodeType==GameRoom_PlayerNodeType_Closed)
	{
		this->removeAllChildrenWithCleanup(true);
		m_SpPlayer=m_SpMaster=m_SpGetReady=m_LbPlayerNickName=m_LbPlayerLevel=0;
		ToolsFun::changeSpriteFrame(m_SpBackground,PVE_FIELD_BUTTON_SEAT_2);
	}
	else if (m_NodeType==GameRoom_PlayerNodeType_Master)
	{
		ToolsFun::changeSpriteFrame(m_SpBackground,PVE_FIELD_BUTTON_SEAT_1);
		if (NULL==m_SpMaster)
		{
			m_SpMaster=CCSprite::create(PVE_FIELD_GAMEROOM_MASTER);
			this->addChild(m_SpMaster);
		}
	}
	else if (m_NodeType==GameRoom_PlayerNodeType_CommonPlayer)
	{
		ToolsFun::changeSpriteFrame(m_SpBackground,PVE_FIELD_BUTTON_SEAT_1);
		if (m_SpMaster!=NULL)
		{
			this->removeChild(m_SpMaster,true);
			m_SpPlayer=NULL;
		}
	}
}

//////////////////////////////////////////////////////////////////////////
//GameRoom_MapInfoNode

GameRoom_MapInfoNode::GameRoom_MapInfoNode()
{
	m_SpBackground=NULL;
	m_SpMapName=NULL;
	m_RatingNode=NULL;
}

GameRoom_MapInfoNode::~GameRoom_MapInfoNode()
{

}

GameRoom_MapInfoNode* GameRoom_MapInfoNode::create()
{
	GameRoom_MapInfoNode* pRet=new GameRoom_MapInfoNode();
	if (pRet&&pRet->init())
	{
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return NULL;
}

bool GameRoom_MapInfoNode::init()
{
	bool bRet=false;
	do 
	{
		initNode();
		bRet=true;
	} while (0);
	return bRet;
}

void GameRoom_MapInfoNode::initNode()
{
	m_SpBackground=CCSprite::create(PVE_FIELD_PIC_STAGE);
	this->addChild(m_SpBackground);
	CCSize backgroundSize=m_SpBackground->getContentSize();

	m_SpMapName=CCSprite::create(PVE_FIELD_LABEL_STAGEAME);
	this->addChild(m_SpMapName);
	m_SpMapName->setPosition(ccp(-89,88));

	m_RatingNode=RatingNode::create();
	this->addChild(m_RatingNode);
	m_RatingNode->initNodeWithType(2);
	m_RatingNode->setPosition(ccp(112,-87));
}