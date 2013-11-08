#include "PVEPopLayer.h"
#include "Define.h"
#include "TextChange.h"
#include "CMyMenu.h"
#include "ToolsFun.h"
#include "ScrollViewModel.h"
#include "LanguageManager.h"
#include "PVELayer.h"

#include "EventMSG.h"

#include "../ZMQ/MessageCenter.h"
USING_NS_CC;


ObserveLayer::ObserveLayer():m_Priority(0)
{

}

ObserveLayer::~ObserveLayer()
{

}

ObserveLayer* ObserveLayer::create( int r )
{
	ObserveLayer* pRet=new ObserveLayer();
	pRet->m_Priority=r;
	if (pRet&&pRet->initWithColor(ccc4(0,0,0,180)))
	{
		pRet->autorelease();
		pRet->initLayer();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return NULL;
}

void ObserveLayer::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,m_Priority,true);
}

bool ObserveLayer::ccTouchBegan( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent )
{
	return true;
}

void ObserveLayer::initLayer()
{
	createMenu();
	this->setTouchEnabled(true);
}

void ObserveLayer::createMenu()
{

}

void ObserveLayer::OnBtnGoBack( cocos2d::CCObject* sender )
{

}

void ObserveLayer::OnBtnFight( cocos2d::CCObject* sender )
{

}

void ObserveLayer::OnBtnObserve( cocos2d::CCObject* sender )
{

}

//////////////////////////////////////////////////////////////////////////
//CreateTeamLayer
CreateTeamLayer::CreateTeamLayer():m_Priority(0),m_TeamName(0),m_TeamPassword(0)
{
}

CreateTeamLayer::~CreateTeamLayer()
{

}

CreateTeamLayer* CreateTeamLayer::create( int r )
{
	CreateTeamLayer* pRet=new CreateTeamLayer();
	pRet->m_Priority=r;
	if (pRet&&pRet->initWithColor(ccc4(0,0,0,180)))
	{
		pRet->autorelease();
		pRet->initLayer();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return NULL;
}

void CreateTeamLayer::onEnter()
{
	CCLayerColor::onEnter();
	setTouchEnabled(true);
	setKeypadEnabled(true);
}

void CreateTeamLayer::keyBackClicked()
{
	PVELevelLayer* parentLayer=(PVELevelLayer*)getParent();
	if (parentLayer)
	{
		parentLayer->setKeypadEnabled(true);
	}
	this->removeFromParentAndCleanup(true);
}

void CreateTeamLayer::keyMenuClicked()
{

}

void CreateTeamLayer::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,m_Priority,true);
}

bool CreateTeamLayer::ccTouchBegan( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent )
{
	m_beginPos=pTouch->getLocation();
	return true;
}

void CreateTeamLayer::ccTouchEnded( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent )
{
	CCPoint endPos=pTouch->getLocation();

	float delta = 5.0f;
	if (::abs(endPos.x - m_beginPos.x) > delta
		|| ::abs(endPos.y - m_beginPos.y) > delta)
	{
		// not click
		m_beginPos.x = m_beginPos.y = -1;
		return;
	}

	CCPoint point = convertTouchToNodeSpace(pTouch);

	CCRect rect;
	rect.origin = m_TeamName->getPosition();
	rect.size = m_TeamName->getDimensions();
	rect.origin.x -= m_TeamName->getAnchorPointInPoints().x;
	rect.origin.y -= m_TeamName->getAnchorPointInPoints().y;

	CCRect rect1;
	rect1.origin = m_TeamPassword->getPosition();
	rect1.size = m_TeamPassword->getDimensions();
	rect1.origin.x -= m_TeamPassword->getAnchorPointInPoints().x;
	rect1.origin.y -= m_TeamPassword->getAnchorPointInPoints().y;

	if (rect.containsPoint(point))
	{
		m_TeamName->attachWithIME();
	}
	else if (rect1.containsPoint(point))
	{
		m_TeamPassword->attachWithIME();
	}
	else
	{
		m_TeamName->detachWithIME();
		m_TeamPassword->detachWithIME();
	}
}

void CreateTeamLayer::initLayer()
{
	//±³¾°
	CCSprite* background=CCSprite::create(ATHLETIC_BACKGROUNDSMALL);
	this->addChild(background);
	background->setPosition(ccp(480,320));

	//±êÇ©
	CCLabelTTF* lbTeamName=CCLabelTTF::create(LanguageManager::shareManager()->getContentByKey("TEAM_NAME").c_str(),DEF_FONT_NAME,26);
	this->addChild(lbTeamName);
	lbTeamName->setPosition(ccp(260,390));
	CCLabelTTF* lbTeamPassword=CCLabelTTF::create(LanguageManager::shareManager()->getContentByKey("TEAM_PASSWORD").c_str(),DEF_FONT_NAME,26);
	this->addChild(lbTeamPassword);
	lbTeamPassword->setPosition(ccp(260,290));

	CCSprite* spTeamName=CCSprite::create(PVE_FIELD_BGPIC_TEAMNAMETEXT);
	this->addChild(spTeamName);
	spTeamName->setPosition(ccp(530,290));
	
	CCSprite* spTeamPassword=CCSprite::create(PVE_FIELD_BGPIC_TEAMNAMETEXT);
	this->addChild(spTeamPassword);
	spTeamPassword->setPosition(ccp(530,390));

	m_TeamName=CCTextFieldTTF::textFieldWithPlaceHolder("111",CCSizeMake(430,60),kCCTextAlignmentCenter,DEF_FONT_NAME,26);
	m_TeamName->setPosition(ccp(530,380));
	this->addChild(m_TeamName);

	m_TeamPassword=CCTextFieldTTF::textFieldWithPlaceHolder("222",CCSizeMake(430,60),kCCTextAlignmentCenter,DEF_FONT_NAME,26);
	m_TeamPassword->setPosition(ccp(530,280));
	this->addChild(m_TeamPassword);

	createMenu();
}

void CreateTeamLayer::createMenu()
{
	CCMenuP* menu=CCMenuP::create(m_Priority-1,NULL);
	this->addChild(menu);
	menu->setPosition(CCPointZero);

	CCMenuItemSprite* btnCreate=ToolsFun::createBTN(LanguageManager::shareManager()->getContentByKey("BUTTON_CREATE").c_str(),ButtomType_Blue2,this,menu_selector(CreateTeamLayer::OnBtnCreate));
	btnCreate->setPosition(ccp(490,130));
	menu->addChild(btnCreate);

	CCMenuItemSprite* btnGoBack=ToolsFun::createBTN(LanguageManager::shareManager()->getContentByKey("GOBACK").c_str(),ButtomType_Red,this,menu_selector(CreateTeamLayer::OnBtnGoback));
	btnGoBack->setPosition(ccp(840,560));
	menu->addChild(btnGoBack);
}

void CreateTeamLayer::OnBtnGoback( cocos2d::CCObject* sender )
{
	PVELevelLayer* parentLayer=(PVELevelLayer*)getParent();
	if (parentLayer)
	{
		parentLayer->setKeypadEnabled(true);
	}
	this->removeFromParentAndCleanup(true);
}

void CreateTeamLayer::OnBtnCreate( cocos2d::CCObject* sender )
{
	this->removeFromParentAndCleanup(true);
	EventParam* ep=new EventParam();
	ep->autorelease();
	ep->intParam=11;
	SEND_EVENT(this,PVEEvent::PVEVIEW_ENTERGAMEROOM,ep);
}

//////////////////////////////////////////////////////////////////////////
//FindTeamLayer
FindTeamLayer::FindTeamLayer():m_Priority(0),m_TeadID(0)
{
	m_ScrollView=NULL;
}

FindTeamLayer::~FindTeamLayer()
{

}

FindTeamLayer* FindTeamLayer::create( int r )
{
	FindTeamLayer* pRet=new FindTeamLayer();
	pRet->m_Priority=r;
	if (pRet&&pRet->initWithColor(ccc4(0,0,0,180)))
	{
		pRet->autorelease();
		pRet->initLayer();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return NULL;
}

void FindTeamLayer::onEnter()
{
	CCLayerColor::onEnter();
	setTouchEnabled(true);
	setKeypadEnabled(true);
}

void FindTeamLayer::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,m_Priority,true);
}

bool FindTeamLayer::ccTouchBegan( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent )
{
	m_beginPos=pTouch->getLocation();
	return true;
}

void FindTeamLayer::ccTouchEnded( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent )
{
	CCPoint endPos=pTouch->getLocation();

	float delta = 5.0f;
	if (::abs(endPos.x - m_beginPos.x) > delta
		|| ::abs(endPos.y - m_beginPos.y) > delta)
	{
		// not click
		m_beginPos.x = m_beginPos.y = -1;
		return;
	}

	CCPoint point = convertTouchToNodeSpace(pTouch);

	CCRect rect;
	rect.origin = m_TeadID->getPosition();
	rect.size = m_TeadID->getDimensions();
	rect.origin.x -= m_TeadID->getAnchorPointInPoints().x;
	rect.origin.y -= m_TeadID->getAnchorPointInPoints().y;


	if (rect.containsPoint(point))
	{
		m_TeadID->attachWithIME();
	}
	else
	{
		m_TeadID->detachWithIME();
	}
}

void FindTeamLayer::keyBackClicked()
{
	PVELevelLayer* parentLayer=(PVELevelLayer*)getParent();
	if (parentLayer)
	{
		parentLayer->setKeypadEnabled(true);
	}
	this->removeFromParentAndCleanup(true);
}

void FindTeamLayer::keyMenuClicked()
{

}

void FindTeamLayer::initLayer()
{
	CCSprite* background=CCSprite::create(ATHLETIC_BACKGROUND);
	this->addChild(background);
	background->setPosition(ccp(480,320));
	//±êÇ©
	CCLabelTTF* lbTeamID=CCLabelTTF::create(LanguageManager::shareManager()->getContentByKey("TEAM_ID").c_str(),DEF_FONT_NAME,30);
	this->addChild(lbTeamID);
	lbTeamID->setPosition(ccp(150,600));

	CCSprite* spTeamIDBackground=CCSprite::create(PVE_FIELD_FIELD_SEARCHTEAM_INPUTID);
	this->addChild(spTeamIDBackground);
	spTeamIDBackground->setPosition(ccp(395,600));

	m_TeadID=CCTextFieldTTF::textFieldWithPlaceHolder("123",CCSizeMake(248,82),kCCTextAlignmentCenter,DEF_FONT_NAME,30);
	this->addChild(m_TeadID);
	m_TeadID->setPosition(ccp(395,590));

	CCSprite* spTeamListBackground=ToolsFun::createSpriteWithRepeatTexture(REPEATTEXTURE_1,CCSizeMake(926,528));
	this->addChild(spTeamListBackground);
	spTeamListBackground->setPosition(ccp(480,270));

	createScrollView();
	createMenu();
}

void FindTeamLayer::createMenu()
{
	CCMenuP* menu=CCMenuP::create(m_Priority-1,NULL);
	this->addChild(menu);
	menu->setPosition(CCPointZero);

	CCMenuItemSprite* btnSearch=ToolsFun::createBTN(LanguageManager::shareManager()->getContentByKey("SEARCHING").c_str(),ButtomType_Blue2,this,menu_selector(FindTeamLayer::OnBtnSearch));
	btnSearch->setPosition(ccp(613,600));
	menu->addChild(btnSearch);

	CCMenuItemSprite* btnGoback=ToolsFun::createBTN(LanguageManager::shareManager()->getContentByKey("GOBACK").c_str(),ButtomType_Red,this,menu_selector(FindTeamLayer::OnBtnGoback));
	btnGoback->setPosition(ccp(900,600));
	menu->addChild(btnGoback);

	CCMenuItemSprite* btnJoin=ToolsFun::createBTN(LanguageManager::shareManager()->getContentByKey("TOJOIN").c_str(),ButtomType_Blue2,this,menu_selector(FindTeamLayer::OnBtnJoin));
	btnJoin->setPosition(ccp(900,50));
	menu->addChild(btnJoin);
}

void FindTeamLayer::createScrollView()
{
	CCLayer* scrollLayer=CCLayer::create();

	//CCLayerColor* scrollLayer=CCLayerColor::create(ccc4(255,255,255,255));
	ScrollViewModel* scrollView=ScrollViewModel::createP(m_Priority-10,CCSizeMake(918,520),scrollLayer);
	this->addChild(scrollView);
	scrollView->setContentSize(CCSizeMake(918,800));
	scrollView->setPosition(ccp(20,5));
	scrollView->setDirection(kCCScrollViewDirectionVertical);

	CCSprite* testNode=CCSprite::create(PVE_FIELD_BGPIC_PLAYERLIST);
	scrollLayer->addChild(testNode);
	testNode->setPosition(ccp(459,400));
}

void FindTeamLayer::OnBtnGoback( cocos2d::CCObject* sender )
{
	PVELevelLayer* parentLayer=(PVELevelLayer*)getParent();
	if (parentLayer)
	{
		parentLayer->setKeypadEnabled(true);
	}
	this->removeFromParentAndCleanup(true);

}

void FindTeamLayer::OnBtnSearch( cocos2d::CCObject* sender )
{
	SearchTeamResultLayer* resultLayer=SearchTeamResultLayer::create(m_Priority-10);
	this->addChild(resultLayer);
	this->setKeypadEnabled(false);
}

void FindTeamLayer::OnBtnJoin( cocos2d::CCObject* sender )
{

}

//////////////////////////////////////////////////////////////////////////
//SearchTeamResultLayer

SearchTeamResultLayer::SearchTeamResultLayer():m_Priority(0)
{
	m_LbTeamID=NULL;
	m_LbTeamName=NULL;
	m_LbPlayerNum=NULL;
}

SearchTeamResultLayer::~SearchTeamResultLayer()
{

}

SearchTeamResultLayer* SearchTeamResultLayer::create( int r )
{
	SearchTeamResultLayer* pRet=new SearchTeamResultLayer();
	pRet->m_Priority=r;
	if (pRet&&pRet->initWithColor(ccc4(0,0,0,180)))
	{
		pRet->autorelease();
		pRet->initLayer();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return NULL;
}

void SearchTeamResultLayer::onEnter()
{
	CCLayerColor::onEnter();
	setKeypadEnabled(true);
}

void SearchTeamResultLayer::keyBackClicked()
{
	FindTeamLayer* parentLayer=(FindTeamLayer*)getParent();
	if (parentLayer)
	{
		parentLayer->setKeypadEnabled(true);
	}
	this->removeFromParentAndCleanup(true);
}

void SearchTeamResultLayer::keyMenuClicked()
{

}

void SearchTeamResultLayer::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,m_Priority,true);
}

bool SearchTeamResultLayer::ccTouchBegan( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent )
{
	return true;
}

void SearchTeamResultLayer::initLayer()
{
	//±³¾°
	CCSprite* background=CCSprite::create(PVE_FIELD_POPWIN_BACKGROUND);
	this->addChild(background);
	background->setPosition(ccp(480,320));

	CCLabelTTF* lbResult=ToolsFun::createLabel(LanguageManager::shareManager()->getContentByKey("SEARCH_RESULT").c_str(),DEF_FONT_NAME,30,ccp(495,525),this);
	CCLabelTTF* lbTeamID=ToolsFun::createLabel(LanguageManager::shareManager()->getContentByKey("TEAM_ID").c_str(),DEF_FONT_NAME,28,ccp(421,440),this);
	CCLabelTTF* lbTeamName=ToolsFun::createLabel(LanguageManager::shareManager()->getContentByKey("TEAM_NAME").c_str(),DEF_FONT_NAME,28,ccp(421,368),this);
	CCLabelTTF* lbPlayerNum=ToolsFun::createLabel(LanguageManager::shareManager()->getContentByKey("PLAYER_NUM").c_str(),DEF_FONT_NAME,28,ccp(388,297),this);

	m_LbTeamID=ToolsFun::createLabel("111",DEF_FONT_NAME,30,ccp(490,440),this);
	m_LbTeamName=ToolsFun::createLabel("111",DEF_FONT_NAME,30,ccp(490,368),this);
	m_LbPlayerNum=ToolsFun::createLabel("11/11",DEF_FONT_NAME,30,ccp(435,297),this);
	m_LbTeamID->setAnchorPoint(ccp(0.0f,0.5f));
	m_LbTeamName->setAnchorPoint(ccp(0.0f,0.5f));
	m_LbPlayerNum->setAnchorPoint(ccp(0.0f,0.5f));

	createMenu();
	this->setTouchEnabled(true);
}

void SearchTeamResultLayer::createMenu()
{
	CCMenuP* menu=CCMenuP::create(m_Priority-1,NULL);
	this->addChild(menu);
	menu->setPosition(CCPointZero);

	CCMenuItemSprite* btnJoin=ToolsFun::createBTN(LanguageManager::shareManager()->getContentByKey("TOJOIN").c_str(),ButtomType_Blue2,this,menu_selector(SearchTeamResultLayer::OnBtnJoin));
	btnJoin->setPosition(ccp(350,167));
	menu->addChild(btnJoin);

	CCMenuItemSprite* btnCancel=ToolsFun::createBTN(LanguageManager::shareManager()->getContentByKey("GOBACK").c_str(),ButtomType_Blue2,this,menu_selector(SearchTeamResultLayer::OnBtnCancel));
	btnCancel->setPosition(ccp(650,167));
	menu->addChild(btnCancel);
}

void SearchTeamResultLayer::OnBtnCancel( cocos2d::CCObject* sender )
{
	FindTeamLayer* parentLayer=(FindTeamLayer*)getParent();
	if (parentLayer)
	{
		parentLayer->setKeypadEnabled(true);
	}
	this->removeFromParentAndCleanup(true);
}

void SearchTeamResultLayer::OnBtnJoin( cocos2d::CCObject* sender )
{

}

//////////////////////////////////////////////////////////////////////////
//PVEFightResultLayer

PVEFightResultLayer::PVEFightResultLayer():m_Priority(0)
{

}

PVEFightResultLayer::~PVEFightResultLayer()
{

}

bool PVEFightResultLayer::init()
{
	bool bRet=false;
	do 
	{
		initLayer();
		bRet=true;
	} while (0);
	return bRet;
}

PVEFightResultLayer* PVEFightResultLayer::create( int r )
{
	PVEFightResultLayer* pRet=new PVEFightResultLayer();
	pRet->m_Priority=r;
	if (pRet&&pRet->init())
	{
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return NULL;
}

void PVEFightResultLayer::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,m_Priority,true);
}

bool PVEFightResultLayer::ccTouchBegan( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent )
{
	return true;
}

void PVEFightResultLayer::initLayer()
{
	CCSprite* background=CCSprite::create(ATHLETIC_BACKGROUND);
	this->addChild(background);
	background->setPosition(ccp(480,320));
	CCLabelTTF* lbTitle=CCLabelTTF::create(LanguageManager::shareManager()->getContentByKey("FIGHT_OVER").c_str(),DEF_FONT_NAME,30);
	this->addChild(lbTitle);
	lbTitle->setPosition(ccp(480,600));

	//ÈËÎïÃû×Ö±³¾°
	CCSprite* player_Win_1_NameBackground=ToolsFun::createSprite(PVE_FIELD_BGPIC_PLAYERNAME_LOSE,ccp(0.5,0.5),ccp(270,500),this);
	CCSprite* player_Win_2_NameBackground=ToolsFun::createSprite(PVE_FIELD_BGPIC_PLAYERNAME_LOSE,ccp(0.5,0.5),ccp(450,500),this);
	CCSprite* player_Lose_1_NameBackground=ToolsFun::createSprite(PVE_FIELD_BGPIC_PLAYERNAME_WIN,ccp(0.5,0.5),ccp(650,500),this);
	CCSprite* player_Lose_2_NameBackground=ToolsFun::createSprite(PVE_FIELD_BGPIC_PLAYERNAME_WIN,ccp(0.5,0.5),ccp(830,500),this);
	CCSprite* spInfoBackground=ToolsFun::createSprite(PVE_FIELD_BGPIC_BATTLEEND,ccp(0.5,0.5),ccp(470,350),this);

	//
	CCSprite* spLoseBackground=ToolsFun::createSprite(PVE_FIELD_BGPIC_LOSE,ccp(0.5f,0.5f),ccp(240,43),this);
	CCSprite* spWinBackground=ToolsFun::createSprite(PVE_FIELD_BGPIC_WIN,ccp(0.5f,0.5f),ccp(760,43),this);
	CCSprite* spLoser=ToolsFun::createSprite(PVE_FIELD_PIC_MALEPLAYER_1_LOSE,ccp(0.5f,0.0f),ccp(240,43),this);
	CCSprite* spWiner=ToolsFun::createSprite(PVE_FIELD_PIC_MALEPLAYER_1_WIN,ccp(0.5f,0.0f),ccp(760,43),this);
	
	createLayerMenu();
	this->setTouchEnabled(true);
}

void PVEFightResultLayer::createLayerMenu()
{
	CCMenuP* menu=CCMenuP::create(m_Priority-1,NULL);
	this->addChild(menu,3);
	menu->setPosition(CCPointZero);

	CCMenuItemSprite* btnGoback=ToolsFun::createBTN(LanguageManager::shareManager()->getContentByKey("GOBACK").c_str(),ButtomType_Red,this,menu_selector(PVEFightResultLayer::OnBtnGoBack));
	btnGoback->setPosition(ccp(880,600));
	menu->addChild(btnGoback);

}

void PVEFightResultLayer::OnBtnGoBack( cocos2d::CCObject* sender )
{
	this->removeFromParentAndCleanup(true);
}
