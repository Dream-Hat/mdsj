#include "ArenaNode.h"
#include "Define.h"
#include "TextChange.h"
#include "ToolsFun.h"
#include "../proto_files/AthleticProto.pb.h"

USING_NS_CC;

GameModeNode::GameModeNode()
{
	m_SpMode=NULL;
	m_SpLocked=NULL;
	m_LbContent=NULL;
	m_LbLimitLv=NULL;
}

GameModeNode::~GameModeNode()
{

}

bool GameModeNode::init()
{
	bool bRet=false;
	do 
	{
		initNode();
		bRet=true;
	} while (0);
	return bRet;
}

void GameModeNode::initNode()
{
	//±³¾°

	//CCSprite* spBackground=CCSprite::create("ui/Arema/athletic_list_type.png");
	//this->addChild(spBackground);

	CCSize size=CCSizeMake(653,98);

	m_SpMode=CCSprite::create(ATHLETIC_TYPE_ICON_1);
	this->addChild(m_SpMode);
	m_SpMode->setAnchorPoint(ccp(0.0f,0.5f));
	m_SpMode->setPosition(ccp(-size.width/2,0));	
	CCSize spModeSize=m_SpMode->getContentSize();
	CCPoint spModePoint=m_SpMode->getPosition();

 	m_LbContent=CCLabelTTF::create("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX",DEF_FONT_NAME,20,CCSizeMake(250,100),kCCTextAlignmentLeft);
 	this->addChild(m_LbContent);
	m_LbContent->setVerticalAlignment(kCCVerticalTextAlignmentCenter);
 	m_LbContent->setAnchorPoint(ccp(0.5f,0.5f));
 	m_LbContent->setPosition(ccp(0,0));

	m_LbLimitLv=CCLabelTTF::create("Lv.4",DEF_FONT_NAME,20);
	this->addChild(m_LbLimitLv);
	m_LbLimitLv->setAnchorPoint(ccp(0.0f,0.5f));
	m_LbLimitLv->setPosition(ccp(size.width/4,0));
}

void GameModeNode::changeContent( const char* content )
{
	if (NULL!=m_LbContent)
	{
		m_LbContent->setString(content);
	}
}

void GameModeNode::changeModeDisplay( const char* filePath )
{
	ToolsFun::changeSpriteFrame(m_SpMode,filePath);
}

void GameModeNode::setData(com::tiange::mdsj::proto::ModeListResponse_Mode* _mode)
{
	if (!_mode)return;
	CCString* iconStr=CCString::createWithFormat("%s%s.png",PICPATH_AREMAPATH,_mode->icon());
	ToolsFun::changeSpriteFrame(m_SpMode,iconStr->getCString());
}

// void GameModeNode::setData(ModeListResponse_Mode* _mode)
// {
// 	if (!_mode)return;
// 	//CCString* iconStr=CCString::createWithFormat("%s%s.png",PICPATH_AREMAPATH,_mode->icon_->c_str());
// 	//ToolsFun::changeSpriteFrame(m_SpMode,iconStr->getCString());
// 	//m_LbContent->setString();
// }

//////////////////////////////////////////////////////////////////////////
//GameRoomsNode
GameRoomsNode::GameRoomsNode():m_SpIcon(0),m_LbRoomName(0),m_LbLevel(0),m_LbPlayerNum(0),m_SpIsLock(0)
{

}

GameRoomsNode::~GameRoomsNode()
{

}

bool GameRoomsNode::init()
{
	bool bRet=false;
	do 
	{
		initNode();
		bRet=true;
	} while (0);
	return bRet;
}

void GameRoomsNode::initNode()
{
	m_SpIcon=CCSprite::create(ATHLETIC_LIST_ROOM);
	this->addChild(m_SpIcon);
}

//////////////////////////////////////////////////////////////////////////
//ÓÎÏ··¿¼äÄÚÍæ¼ÒÄ£¿é
TeamNodeInRoom::TeamNodeInRoom()
{
	m_SpTopPlayer=NULL;
	m_SpBottomPlayer=NULL;
	m_SpMasterTag=NULL;
}

TeamNodeInRoom::~TeamNodeInRoom()
{

}

bool TeamNodeInRoom::init()
{
	bool bRet=false;
	do 
	{
		initNode();
		bRet=true;
	} while (0);
	return bRet;
}

TeamNodeInRoom* TeamNodeInRoom::createWithPlayer(int teamId,const PlayerVoInRoom &player1,const PlayerVoInRoom &player2)
{
	TeamNodeInRoom* pRet=new TeamNodeInRoom();
	pRet->m_TeamID=teamId;
	pRet->m_PlayerTop=player1;
	pRet->m_PlayerBottom=player2;
	if (pRet&&pRet->init())
	{
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	pRet=NULL;
	return NULL;
}

void TeamNodeInRoom::initNode()
{
	//µ×°å±³¾°
	CCSprite* background=CCSprite::create(ATHLETIC_LABEL_PLAYERMESSAGE);
	this->addChild(background);
	
	int masterPos=0;
	//Í·Ïñ
	if (m_PlayerTop.isCopy)
	{
		m_SpTopPlayer=CCSprite::create(ATHLETIC_PIC_MALEPLAYER);
		this->addChild(m_SpTopPlayer);
		m_SpTopPlayer->setScale(0.5f);
		m_SpTopPlayer->setPosition(ccp(0,76));
		if (m_PlayerTop.roomMaster)
			masterPos=1;
	}
	if (m_PlayerBottom.isCopy)
	{
		m_SpBottomPlayer=CCSprite::create(ATHLETIC_PIC_FEMALEPLAYER);
		this->addChild(m_SpBottomPlayer);
		m_SpBottomPlayer->setScale(0.5f);
		m_SpBottomPlayer->setPosition(ccp(0,-96));
		if (m_PlayerBottom.roomMaster)
			masterPos=2;
	}
	
}

//////////////////////////////////////////////////////////////////////////
//CommonNode
CommonNode::CommonNode():m_NodeType(CommonNodeType_Null),m_SpHeader(NULL),m_BtnCall(NULL)
{

}

CommonNode::~CommonNode()
{

}

bool CommonNode::init()
{
	bool bRet=false;
	do 
	{
		initNode();
		bRet=true;
	} while (0);
	return bRet;
}

CommonNode* CommonNode::create( CommonNodeType nodeType )
{
	CommonNode* pRet=new CommonNode();
	pRet->m_NodeType=nodeType;
	if (pRet&&pRet->init())
	{
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	pRet=NULL;
	return NULL;
}

void CommonNode::initNode()
{
	if (m_NodeType==CommonNodeType_Soul)
	{
		//±³¾°
		CCSprite* background=CCSprite::create(ATHLETIC_TEXTURE);
		CCRect rt=CCRectMake(0,0,404,110);
		background->setTextureRect(rt);
		ccTexParams tp={GL_LINEAR,GL_LINEAR,GL_REPEAT,GL_REPEAT};
		background->getTexture()->setTexParameters(&tp);
		this->addChild(background);

		m_SpHeader=CCSprite::create(ATHLETIC_PLAYERHEADER);
		this->addChild(m_SpHeader);
		m_SpHeader->setPosition(ccp(-149,0));

		m_BtnCall=ToolsFun::createSpriteBtn(ATHLETIC_BUTTON_REPLACE_1,ATHLETIC_BUTTON_REPLACE_2,ATHLETIC_BUTTON_REPLACE_3);
		this->addChild(m_BtnCall);
		m_BtnCall->setPosition(ccp(134,0));
	}
	else if (m_NodeType==CommonNodeType_Map)
	{
		//±³¾°
		CCSprite* background=CCSprite::create(ATHLETIC_TEXTURE_2);
		CCRect rt=CCRectMake(0,0,810,160);
		background->setTextureRect(rt);
		ccTexParams tp={GL_LINEAR,GL_LINEAR,GL_REPEAT,GL_REPEAT};
		background->getTexture()->setTexParameters(&tp);
		this->addChild(background);

		m_SpHeader=CCSprite::create(ATHLETIC_ICON_MAP_001);
		this->addChild(m_SpHeader);
		m_SpHeader->setPosition(ccp(-270,0));

		m_BtnCall=ToolsFun::createSpriteBtn(ATHLETIC_BUTTON_REPLACE_1,ATHLETIC_BUTTON_REPLACE_2,ATHLETIC_BUTTON_REPLACE_3);
		this->addChild(m_BtnCall);
		m_BtnCall->setPosition(ccp(270,0));
	}
}

//////////////////////////////////////////////////////////////////////////
//GameModeSprite


GameModeSprite::GameModeSprite():m_LbContent(0),m_LbLimiteLV(0)
{

}

GameModeSprite::~GameModeSprite()
{

}

GameModeSprite* GameModeSprite::create( const char* filePath,const char* content,int limiteLv )
{
	GameModeSprite* pRet=new GameModeSprite();
	if (pRet&&pRet->initWithFile(filePath))
	{
		pRet->autorelease();
		pRet->initSprite();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return NULL;
}

void GameModeSprite::initSprite()
{
	CCSize size=getContentSize();
	CCSprite* m_SpMode=CCSprite::create(ATHLETIC_TYPE_ICON_1);
	this->addChild(m_SpMode);
	m_SpMode->setAnchorPoint(ccp(0.0f,0.5f));
	m_SpMode->setPosition(ccp(-size.width/2,0));
	CCSize spModeSize=m_SpMode->getContentSize();
	CCPoint spModePoint=m_SpMode->getPosition();

	m_LbContent=CCLabelTTF::create("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX",DEF_FONT_NAME,20,CCSizeMake(200,90),kCCTextAlignmentLeft);
	m_SpMode->addChild(m_LbContent);
	m_LbContent->setAnchorPoint(ccp(0.0f,0.0f));
	m_LbContent->setPosition(ccp(spModeSize.width,-size.height/2));
}
