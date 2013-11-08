#include "ArenaPopLayer.h"
#include "Define.h"
#include "TextChange.h"
#include "ToolsFun.h"
#include "CMyMenu.h"
#include "ScrollViewModel.h"
#include "ArenaNode.h"
#include "ArenaLayer.h"
#include "LanguageManager.h"
USING_NS_CC;
ArenaFindPlayer::ArenaFindPlayer():m_Priority(0),m_InputPlayerName(NULL)
{
}

ArenaFindPlayer* ArenaFindPlayer::create(int r)
{
	ArenaFindPlayer* pRet=new ArenaFindPlayer();
	pRet->m_Priority=r;
	if (pRet&&pRet->initWithColor(ccc4(0,0,0,200)))
	{
		pRet->initLayer();
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	pRet=NULL;
	return NULL;
}

void ArenaFindPlayer::initLayer()
{
	CCSprite* background=CCSprite::create(ATHLETIC_POPWINBACKGROUND_2);
	background->setPosition(ccp(480,320));
	this->addChild(background);

	CCLabelTTF* lbFindPlayer=CCLabelTTF::create(LanguageManager::shareManager()->getContentByKey("FIND_PLAYER").c_str(),DEF_FONT_NAME,26);
	this->addChild(lbFindPlayer);
	lbFindPlayer->setHorizontalAlignment(kCCTextAlignmentCenter);
	lbFindPlayer->setPosition(ccp(480,450));

	CCLabelTTF* lbPlayerName=CCLabelTTF::create(LanguageManager::shareManager()->getContentByKey("INPUT_PLAYER_ID").c_str(),DEF_FONT_NAME,20);
	this->addChild(lbPlayerName);
	lbPlayerName->setPosition(ccp(280,340));

	CCSprite* spPlayerName=CCSprite::create(ATHLETIC_TEXTINPUTS_ROOMCODE);
	this->addChild(spPlayerName);
	spPlayerName->setPosition(ccp(560,340));

	m_InputPlayerName = CCTextFieldTTF::textFieldWithPlaceHolder("111",CCSizeMake(300,30),kCCTextAlignmentCenter,DEF_FONT_NAME,20);
	m_InputPlayerName->setPosition(ccp(600,340));
	this->addChild(m_InputPlayerName);

	createMenu();
}

void ArenaFindPlayer::createMenu()
{
	CCMenuP* menu=CCMenuP::create(m_Priority-1,NULL);
	this->addChild(menu);
	menu->setPosition(CCPointZero);

	CCMenuItemSprite* btnOk=ToolsFun::createBTN(LanguageManager::shareManager()->getContentByKey("BUTTON_OK").c_str(),ButtomType_Blue2,this,menu_selector(ArenaFindPlayer::OnBtnOk));
	menu->addChild(btnOk);
	btnOk->setPosition(ccp(350,200));

	CCMenuItemSprite* btnCancel=ToolsFun::createBTN(LanguageManager::shareManager()->getContentByKey("BUTTON_CANCEL").c_str(),ButtomType_Blue2,this,menu_selector(ArenaFindPlayer::OnBtnCanCel));
	menu->addChild(btnCancel);
	btnCancel->setPosition(ccp(610,200));
}

void ArenaFindPlayer::onEnter()
{
	CCLayerColor::onEnter();
	setTouchEnabled(true);
	setKeypadEnabled(true);
}

void ArenaFindPlayer::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,m_Priority,true);
}

bool ArenaFindPlayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	m_beginPos = pTouch->getLocation(); 
	return true;
}

void ArenaFindPlayer::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	CCPoint endPos = pTouch->getLocation();    

	float delta = 5.0f;
	if (::abs(endPos.x - m_beginPos.x) > delta
		|| ::abs(endPos.y - m_beginPos.y) > delta)
	{
		// not click
		m_beginPos.x = m_beginPos.y = -1;
		return;
	}

	// decide the trackNode is clicked.
	CCPoint point = convertTouchToNodeSpace(pTouch);

	CCRect rect;
	rect.origin = m_InputPlayerName->getPosition();
	rect.size = m_InputPlayerName->getDimensions();
	rect.origin.x -= m_InputPlayerName->getAnchorPointInPoints().x;
	rect.origin.y -= m_InputPlayerName->getAnchorPointInPoints().y;

	if (rect.containsPoint(point))
	{
		m_InputPlayerName->attachWithIME();
	}
	else
	{
		m_InputPlayerName->detachWithIME();
	}
}

void ArenaFindPlayer::OnBtnOk( cocos2d::CCObject* sender )
{

}

void ArenaFindPlayer::OnBtnCanCel( cocos2d::CCObject* sender )
{
	this->removeFromParentAndCleanup(true);
	ArenaLayer* layer=(ArenaLayer*)this->getParent();
	if (layer)
	{
		layer->setKeypadEnabled(true);
	}
}

void ArenaFindPlayer::keyBackClicked()
{
	ArenaLayer* layer=(ArenaLayer*)this->getParent();
	if (layer)
	{
		layer->setKeypadEnabled(true);
	}
	this->removeFromParentAndCleanup(true);
}

void ArenaFindPlayer::keyMenuClicked()
{

}

//////////////////////////////////////////////////////////////////////////
//ArenaCreateRoom
ArenaCreateRoom::ArenaCreateRoom()
{
	m_RoomName=NULL;
	m_RoomPassword=NULL;
	m_Btn1V1=NULL;
	m_Btn2V2=NULL;
	m_BtnRandom=NULL;
	m_BtnFreedom=NULL;
	m_BtnOK=NULL;
	m_BtnCancel=NULL;
}

ArenaCreateRoom* ArenaCreateRoom::create(int r)
{
	ArenaCreateRoom* pRet=new ArenaCreateRoom();
	pRet->m_Priority=r;
	if (pRet&&pRet->initWithColor(ccc4(0,0,0,180)))
	{
		pRet->autorelease();
		pRet->initLayer();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	pRet=NULL;
	return NULL;
}

void ArenaCreateRoom::initLayer()
{
	//±³¾°
	CCSprite* background=CCSprite::create(ATHLETIC_BACKGROUNDSMALL);
	background->setPosition(ccp(480,320));
	this->addChild(background);
	//±êÇ©
	CCLabelTTF* lbTitle=CCLabelTTF::create(LanguageManager::shareManager()->getContentByKey("CREATE_ROOM").c_str(),DEF_FONT_NAME,20);
	this->addChild(lbTitle);
	lbTitle->setPosition(ccp(480,530));

	CCLabelTTF* lbRoomName=CCLabelTTF::create(LanguageManager::shareManager()->getContentByKey("ROOM_NAME").c_str(),DEF_FONT_NAME,20);
	this->addChild(lbRoomName);
	lbRoomName->setPosition(ccp(240,470));

	CCLabelTTF* lbRoomPassword=CCLabelTTF::create(LanguageManager::shareManager()->getContentByKey("ROOM_PASSWORD").c_str(),DEF_FONT_NAME,20);
	this->addChild(lbRoomPassword);
	lbRoomPassword->setPosition(ccp(240,380));

	CCSprite* spRoomName=CCSprite::create(ATHLETIC_TEXTINPUTS_ROOMCODE);
	this->addChild(spRoomName);
	spRoomName->setPosition(ccp(520,470));

	CCSprite* spRoomPassword=CCSprite::create(ATHLETIC_TEXTINPUTS_ROOMCODE);
	this->addChild(spRoomPassword);
	spRoomPassword->setPosition(ccp(520,380));

	m_RoomName = CCTextFieldTTF::textFieldWithPlaceHolder("111",CCSizeMake(300,30),kCCTextAlignmentCenter,DEF_FONT_NAME,20);
	m_RoomName->setPosition(ccp(520,470));
	addChild(m_RoomName);

	m_RoomPassword = CCTextFieldTTF::textFieldWithPlaceHolder("222",CCSizeMake(300,30),kCCTextAlignmentCenter,DEF_FONT_NAME,20);
	m_RoomPassword->setPosition(ccp(520,380));
	addChild(m_RoomPassword);
	
	//±êÇ©
	CCLabelTTF* lbPlayerNum=CCLabelTTF::create(LanguageManager::shareManager()->getContentByKey("FIGHT_PLAYER_NUM").c_str(),DEF_FONT_NAME,20);
	this->addChild(lbPlayerNum);
	lbPlayerNum->setPosition(ccp(300,300));

	CCLabelTTF* lb1V1=CCLabelTTF::create("1V1",DEF_FONT_NAME,20);
	this->addChild(lb1V1);
	lb1V1->setPosition(ccp(480,300));

	CCLabelTTF* lb2V2=CCLabelTTF::create("2V2",DEF_FONT_NAME,20);
	this->addChild(lb2V2);
	lb2V2->setPosition(ccp(660,300));

	CCLabelTTF* lbGameMode=CCLabelTTF::create(LanguageManager::shareManager()->getContentByKey("PLAY_GAME_MODE").c_str(),DEF_FONT_NAME,20);
	this->addChild(lbGameMode);
	lbGameMode->setPosition(ccp(300,200));

	CCLabelTTF* lbRamdon=CCLabelTTF::create(LanguageManager::shareManager()->getContentByKey("RANDOM").c_str(),DEF_FONT_NAME,20);
	this->addChild(lbRamdon);
	lbRamdon->setPosition(ccp(480,200));

	CCLabelTTF* lbFreedom=CCLabelTTF::create(LanguageManager::shareManager()->getContentByKey("FREEDOM").c_str(),DEF_FONT_NAME,20);
	this->addChild(lbFreedom);
	lbFreedom->setPosition(ccp(660,200));

	createLayerMenu();
}

void ArenaCreateRoom::createLayerMenu()
{
	m_Btn1V1=ToolsFun::createOnePicBtn(ATHLETIC_1V1,this,menu_selector(ArenaCreateRoom::OnBtn1V1));
	m_Btn2V2=ToolsFun::createOnePicBtn(ATHLETIC_1V1,this,menu_selector(ArenaCreateRoom::OnBtn2V2));
	m_BtnRandom=ToolsFun::createOnePicBtn(ATHLETIC_1V1,this,menu_selector(ArenaCreateRoom::OnBtnRandom));
	m_BtnFreedom=ToolsFun::createOnePicBtn(ATHLETIC_1V1,this,menu_selector(ArenaCreateRoom::OnBtnFreedom));

	m_Btn1V1->setPosition(ccp(380,300));
	m_Btn2V2->setPosition(ccp(560,300));
	m_BtnRandom->setPosition(ccp(380,200));
	m_BtnFreedom->setPosition(ccp(560,200));

	m_BtnOK=ToolsFun::createBTN(LanguageManager::shareManager()->getContentByKey("BUTTON_OK").c_str(),ButtomType_Blue2,this,menu_selector(ArenaCreateRoom::OnBtnOk));
	m_BtnCancel=ToolsFun::createBTN(LanguageManager::shareManager()->getContentByKey("BUTTON_CANCEL").c_str(),ButtomType_Blue2,this,menu_selector(ArenaCreateRoom::OnBtnCancel));
	m_BtnOK->setPosition(ccp(240,100));
	m_BtnCancel->setPosition(ccp(720,100));

	CCMenuP* menu=CCMenuP::create(m_Priority-1,m_Btn1V1,m_Btn2V2,m_BtnRandom,m_BtnFreedom,m_BtnOK,m_BtnCancel,NULL);
	this->addChild(menu);
	menu->setPosition(CCPointZero);
}

void ArenaCreateRoom::onEnter()
{
	CCLayerColor::onEnter();
	setTouchEnabled(true);
	setKeypadEnabled(true);
}

void ArenaCreateRoom::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, m_Priority, true);
}

bool ArenaCreateRoom::ccTouchBegan( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent )
{
	m_beginPos=pTouch->getLocation();
	return true;
}

void ArenaCreateRoom::ccTouchEnded( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent )
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
	rect.origin = m_RoomName->getPosition();
	rect.size = m_RoomName->getDimensions();
	rect.origin.x -= m_RoomName->getAnchorPointInPoints().x;
	rect.origin.y -= m_RoomName->getAnchorPointInPoints().y;

	CCRect rect1;
	rect1.origin = m_RoomPassword->getPosition();
	rect1.size = m_RoomPassword->getDimensions();
	rect1.origin.x -= m_RoomPassword->getAnchorPointInPoints().x;
	rect1.origin.y -= m_RoomPassword->getAnchorPointInPoints().y;

	if (rect.containsPoint(point))
	{
		m_RoomName->attachWithIME();
	}
	else if (rect1.containsPoint(point))
	{
		m_RoomPassword->attachWithIME();
	}
	else
	{
		m_RoomName->detachWithIME();
		m_RoomPassword->detachWithIME();
	}
}

void ArenaCreateRoom::keyBackClicked()
{
	ArenaModeRoom* parentLayer=(ArenaModeRoom*)getParent();
	if (parentLayer)
	{
		parentLayer->setKeypadEnabled(true);
	}
	this->removeFromParentAndCleanup(true);
}

void ArenaCreateRoom::keyMenuClicked()
{

}

void ArenaCreateRoom::OnBtn1V1( cocos2d::CCObject* sender )
{

}

void ArenaCreateRoom::OnBtn2V2( cocos2d::CCObject* sender )
{

}

void ArenaCreateRoom::OnBtnRandom( cocos2d::CCObject* sender )
{

}

void ArenaCreateRoom::OnBtnFreedom( cocos2d::CCObject* sender )
{

}

void ArenaCreateRoom::OnBtnOk( cocos2d::CCObject* sender )
{

}

void ArenaCreateRoom::OnBtnCancel( cocos2d::CCObject* sender )
{
	ArenaModeRoom* parentLayer=(ArenaModeRoom*)getParent();
	if (parentLayer)
	{
		parentLayer->setTouchEnabled(true);
	}
	this->removeFromParentAndCleanup(true);
}

//////////////////////////////////////////////////////////////////////////
//ArenaFindRoom

ArenaFindRoom::ArenaFindRoom():m_Priority(0),m_InputPlayerName(NULL)
{
}

ArenaFindRoom* ArenaFindRoom::create(int r)
{
	ArenaFindRoom* pRet=new ArenaFindRoom();
	pRet->m_Priority=r;
	if (pRet&&pRet->initWithColor(ccc4(0,0,0,200)))
	{
		pRet->initLayer();
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	pRet=NULL;
	return NULL;
}

void ArenaFindRoom::initLayer()
{
	CCSprite* background=CCSprite::create(ATHLETIC_POPWINBACKGROUND_2);
	background->setPosition(ccp(480,320));
	this->addChild(background);

	CCLabelTTF* lbFindPlayer=CCLabelTTF::create(LanguageManager::shareManager()->getContentByKey("FIND_PLAYER").c_str(),DEF_FONT_NAME,26);
	this->addChild(lbFindPlayer);
	lbFindPlayer->setHorizontalAlignment(kCCTextAlignmentCenter);
	lbFindPlayer->setPosition(ccp(480,450));

	CCLabelTTF* lbPlayerName=CCLabelTTF::create(LanguageManager::shareManager()->getContentByKey("INPUT_PLAYER_ID").c_str(),DEF_FONT_NAME,20);
	this->addChild(lbPlayerName);
	lbPlayerName->setPosition(ccp(280,340));

	CCSprite* spPlayerName=CCSprite::create(ATHLETIC_TEXTINPUTS_ROOMCODE);
	this->addChild(spPlayerName);
	spPlayerName->setPosition(ccp(560,340));

	m_InputPlayerName = CCTextFieldTTF::textFieldWithPlaceHolder("111",CCSizeMake(300,30),kCCTextAlignmentCenter,DEF_FONT_NAME,20);
	m_InputPlayerName->setPosition(ccp(600,340));
	this->addChild(m_InputPlayerName);

	createMenu();
}

void ArenaFindRoom::createMenu()
{
	CCMenuP* menu=CCMenuP::create(m_Priority-1,NULL);
	this->addChild(menu);
	menu->setPosition(CCPointZero);

	CCMenuItemSprite* btnOk=ToolsFun::createBTN(LanguageManager::shareManager()->getContentByKey("BUTTON_OK").c_str(),ButtomType_Blue2,this,menu_selector(ArenaFindRoom::OnBtnOk));
	menu->addChild(btnOk);
	btnOk->setPosition(ccp(350,200));

	CCMenuItemSprite* btnCancel=ToolsFun::createBTN(LanguageManager::shareManager()->getContentByKey("BUTTON_CANCEL").c_str(),ButtomType_Blue2,this,menu_selector(ArenaFindRoom::OnBtnCanCel));
	menu->addChild(btnCancel);
	btnCancel->setPosition(ccp(610,200));
}

void ArenaFindRoom::onEnter()
{
	CCLayerColor::onEnter();
	setTouchEnabled(true);
	setKeypadEnabled(true);
}

void ArenaFindRoom::keyBackClicked()
{
	ArenaModeRoom* parentLayer=(ArenaModeRoom*)getParent();
	if (parentLayer)
	{
		parentLayer->setKeypadEnabled(true);
	}
	this->removeFromParentAndCleanup(true);
}

void ArenaFindRoom::keyMenuClicked()
{

}

void ArenaFindRoom::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,m_Priority,true);
}

bool ArenaFindRoom::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	m_beginPos = pTouch->getLocation(); 
	return true;
}

void ArenaFindRoom::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	CCPoint endPos = pTouch->getLocation();    

	float delta = 5.0f;
	if (::abs(endPos.x - m_beginPos.x) > delta
		|| ::abs(endPos.y - m_beginPos.y) > delta)
	{
		// not click
		m_beginPos.x = m_beginPos.y = -1;
		return;
	}

	// decide the trackNode is clicked.
	CCPoint point = convertTouchToNodeSpace(pTouch);

	CCRect rect;
	rect.origin = m_InputPlayerName->getPosition();
	rect.size = m_InputPlayerName->getDimensions();
	rect.origin.x -= m_InputPlayerName->getAnchorPointInPoints().x;
	rect.origin.y -= m_InputPlayerName->getAnchorPointInPoints().y;

	if (rect.containsPoint(point))
	{
		m_InputPlayerName->attachWithIME();
	}
	else
	{
		m_InputPlayerName->detachWithIME();
	}
}

void ArenaFindRoom::OnBtnOk( cocos2d::CCObject* sender )
{

}

void ArenaFindRoom::OnBtnCanCel( cocos2d::CCObject* sender )
{
	ArenaModeRoom* parentLayer=(ArenaModeRoom*)getParent();
	if (parentLayer)
	{
		parentLayer->setKeypadEnabled(true);
	}
	this->removeFromParentAndCleanup(true);
}

//////////////////////////////////////////////////////////////////////////
//ArenaSoulView

ArenaSoulView::ArenaSoulView()
{
	m_SpPlayerHeader=NULL;
	m_LbPlayerName=NULL;
	m_LbPlayerLevel=NULL;
	m_LbPlayerPower=NULL;
	m_Priority=0;
}

ArenaSoulView::~ArenaSoulView()
{

}

ArenaSoulView* ArenaSoulView::create(int r)
{
	ArenaSoulView* pRet=new ArenaSoulView();
	pRet->m_Priority=r;
	if (pRet&&pRet->initWithColor(ccc4(0,0,0,180)))
	{
		pRet->autorelease();
		pRet->initLayer();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	pRet=NULL;
	return NULL;
}

void ArenaSoulView::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,m_Priority,true);
}

bool ArenaSoulView::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	return true;
}

void ArenaSoulView::onEnter()
{
	CCLayerColor::onEnter();
	this->setKeypadEnabled(true);
}

void ArenaSoulView::keyBackClicked()
{
	ArenaGameRoom* parentLayer=(ArenaGameRoom*)getParent();
	if (parentLayer)
	{
		parentLayer->setKeypadEnabled(true);
	}
	this->removeFromParentAndCleanup(true);
}

void ArenaSoulView::keyMenuClicked()
{

}

void ArenaSoulView::initLayer()
{
	//±³¾°
	CCSprite* background=CCSprite::create(ATHLETIC_BACKGROUNDSMALL);
	this->addChild(background);
	background->setPosition(ccp(480,320));

	//»êÆÇ¹ö¶¯È¥±³¾°,CCSizeMake(820,500)
	CCSprite* soulBackground=CCSprite::create(ATHLETIC_TEXTURE_2);
	CCRect rt=CCRectMake(0,0,820,400);
	soulBackground->setTextureRect(rt);
	ccTexParams tp={GL_LINEAR,GL_LINEAR,GL_REPEAT,GL_REPEAT};
	soulBackground->getTexture()->setTexParameters(&tp);
	this->addChild(soulBackground);
	soulBackground->setPosition(ccp(480,250));

	//Íæ¼ÒÐÅÏ¢
	m_SpPlayerHeader=CCSprite::create(ATHLETIC_PLAYERHEADER);
	this->addChild(m_SpPlayerHeader);
	m_SpPlayerHeader->setPosition(ccp(135,525));

	//Ãû×Ö£¬µÈ¼¶
	CCLabelTTF* lbPlayerName=CCLabelTTF::create(LanguageManager::shareManager()->getContentByKey("PLAYER_NICKNAME").c_str(),DEF_FONT_NAME,20);
	this->addChild(lbPlayerName);
	lbPlayerName->setAnchorPoint(ccp(0.0f,0.5f));
	lbPlayerName->setPosition(ccp(215,550));
	m_LbPlayerName=CCLabelTTF::create("XXXXXXXXXX",DEF_FONT_NAME,20);
	this->addChild(m_LbPlayerName);
	m_LbPlayerName->setAnchorPoint(ccp(0.0f,0.5f));
	m_LbPlayerName->setPosition(ccp(315,550));

	CCLabelTTF* lbPlayerLevel=CCLabelTTF::create(LanguageManager::shareManager()->getContentByKey("PLAYER_LEVEL").c_str(),DEF_FONT_NAME,20);
	this->addChild(lbPlayerLevel);
	lbPlayerLevel->setAnchorPoint(ccp(0.0f,0.5f));
	lbPlayerLevel->setPosition(ccp(215,500));
	m_LbPlayerLevel=CCLabelTTF::create("9999",DEF_FONT_NAME,20);
	this->addChild(m_LbPlayerLevel);
	m_LbPlayerLevel->setAnchorPoint(ccp(0.0f,0.5f));
	m_LbPlayerLevel->setPosition(ccp(315,500));

	//Õ½¶·Á¦
	CCLabelTTF* lbPlayerPower=CCLabelTTF::create(LanguageManager::shareManager()->getContentByKey("COMBAT_POWER").c_str(),DEF_FONT_NAME,30);
	this->addChild(lbPlayerPower);
	lbPlayerPower->setAnchorPoint(ccp(0.0f,0.5f));
	lbPlayerPower->setPosition(ccp(470,525));
	m_LbPlayerPower=CCLabelTTF::create("999999",DEF_FONT_NAME,30);
	this->addChild(m_LbPlayerPower);
	m_LbPlayerPower->setAnchorPoint(ccp(0.0f,0.5f));
	m_LbPlayerPower->setPosition(ccp(590,525));
	
	//¹ö¶¯ÇøÓò
	createScrollView();
	//°´Å¥²Ëµ¥
	createSoulMenu();
	this->setTouchEnabled(true);
}

void ArenaSoulView::createSoulMenu()
{
	CCMenuItemSprite* btnGoBack=ToolsFun::createBTN(LanguageManager::shareManager()->getContentByKey("GOBACK").c_str(),ButtomType_Red,this,menu_selector(ArenaSoulView::OnBtnGoBack));
	btnGoBack->setPosition(ccp(830,550));

	CCMenuP* menu=CCMenuP::create(m_Priority-1,btnGoBack,NULL);
	this->addChild(menu);
	menu->setPosition(CCPointZero);
}

void ArenaSoulView::createScrollView()
{
	CCLayer* scrollLayer=CCLayer::create();
	ScrollViewModel* scrollView=ScrollViewModel::createP(m_Priority-5,CCSizeMake(820,400),scrollLayer);
	this->addChild(scrollView);
	scrollView->setContentSize(CCSizeMake(820,800));
	scrollView->setPosition(ccp(75,50));
	scrollView->setDirection(kCCScrollViewDirectionVertical);

	CommonNode* soulNode=CommonNode::create(CommonNodeType_Soul);
	scrollLayer->addChild(soulNode);
	soulNode->setPosition(ccp(205,335));
}

void ArenaSoulView::OnBtnGoBack( cocos2d::CCObject* sender )
{
	ArenaGameRoom* parentLayer=(ArenaGameRoom*)getParent();
	if (parentLayer)
	{
		parentLayer->setKeypadEnabled(true);
	}
	this->removeFromParentAndCleanup(true);
}

//////////////////////////////////////////////////////////////////////////
//ArenaSelectMap

ArenaSelectMap::ArenaSelectMap():m_Priority(0)
{

}

ArenaSelectMap::~ArenaSelectMap()
{

}

ArenaSelectMap* ArenaSelectMap::create( int r )
{
	ArenaSelectMap* pRet=new ArenaSelectMap();
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

void ArenaSelectMap::initLayer()
{
	//±³¾°
	CCSprite* background=CCSprite::create(ATHLETIC_BACKGROUNDSMALL);
	this->addChild(background);
	background->setPosition(ccp(480,320));

	//¹ö¶¯ÇøÓò±³¾°
	CCSprite* soulBackground=CCSprite::create(ATHLETIC_TEXTURE_2);
	CCRect rt=CCRectMake(0,0,820,470);
	soulBackground->setTextureRect(rt);
	ccTexParams tp={GL_LINEAR,GL_LINEAR,GL_REPEAT,GL_REPEAT};
	soulBackground->getTexture()->setTexParameters(&tp);
	this->addChild(soulBackground);
	soulBackground->setPosition(ccp(480,285));

	CCLabelTTF* lbSelect=CCLabelTTF::create(LanguageManager::shareManager()->getContentByKey("SELECT_MAP").c_str(),DEF_FONT_NAME,25);
	this->addChild(lbSelect);
	lbSelect->setPosition(ccp(140,570));

	createScrollView();
	createSelectMapMenu();
	this->setTouchEnabled(true);
}

void ArenaSelectMap::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,m_Priority,true);
}

bool ArenaSelectMap::ccTouchBegan( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent )
{
	return true;
}

void ArenaSelectMap::onEnter()
{
	CCLayerColor::onEnter();
	this->setKeypadEnabled(true);
}

void ArenaSelectMap::keyBackClicked()
{
	ArenaGameRoom* parentLayer=(ArenaGameRoom*)getParent();
	if (parentLayer)
	{
		parentLayer->setKeypadEnabled(true);
	}
	this->removeFromParentAndCleanup(true);
}

void ArenaSelectMap::keyMenuClicked()
{

}

void ArenaSelectMap::createSelectMapMenu()
{
	CCMenuItemSprite* btnGoBack=ToolsFun::createBTN(LanguageManager::shareManager()->getContentByKey("GOBACK").c_str(),ButtomType_Red,this,menu_selector(ArenaSelectMap::OnBtnGoBack));
	btnGoBack->setPosition(ccp(830,565));

	CCMenuP* menu=CCMenuP::create(m_Priority-1,btnGoBack,NULL);
	this->addChild(menu);
	menu->setPosition(CCPointZero);
}

void ArenaSelectMap::createScrollView()
{
	CCLayer* scrollLayer=CCLayer::create();
	ScrollViewModel* scrollView=ScrollViewModel::createP(m_Priority-5,CCSizeMake(820,470),scrollLayer);
	this->addChild(scrollView);
	scrollView->setContentSize(CCSizeMake(820,470));
	scrollView->setPosition(ccp(70,50));
	scrollView->setDirection(kCCScrollViewDirectionVertical);

	CommonNode* soulNode=CommonNode::create(CommonNodeType_Map);
	scrollLayer->addChild(soulNode);
	soulNode->setPosition(ccp(405,380));
}

void ArenaSelectMap::OnBtnGoBack( cocos2d::CCObject* sender )
{
	ArenaGameRoom* parentLayer=(ArenaGameRoom*)getParent();
	if (parentLayer)
	{
		parentLayer->setKeypadEnabled(true);
	}
	this->removeFromParentAndCleanup(true);
}

//////////////////////////////////////////////////////////////////////////
//ArenaInviteView
ArenaInviteView::ArenaInviteView():m_Priority(0),m_ScrollView(NULL)
{

}

ArenaInviteView::~ArenaInviteView()
{

}

ArenaInviteView* ArenaInviteView::create( int r )
{
	ArenaInviteView* pRet=new ArenaInviteView();
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

void ArenaInviteView::initLayer()
{
	//±³¾°
	CCSprite* background=CCSprite::create(ATHLETIC_BACKGROUNDSMALL);
	this->addChild(background);
	background->setPosition(ccp(480,320));

	//¹ö¶¯ÇøÓò±³¾°
	CCSprite* soulBackground=CCSprite::create(ATHLETIC_TEXTURE_2);
	CCRect rt=CCRectMake(0,0,820,490);
	soulBackground->setTextureRect(rt);
	ccTexParams tp={GL_LINEAR,GL_LINEAR,GL_REPEAT,GL_REPEAT};
	soulBackground->getTexture()->setTexParameters(&tp);
	this->addChild(soulBackground);
	soulBackground->setPosition(ccp(480,290));

	createScrollView();
	createInviteMenu();
	this->setTouchEnabled(true);
}

void ArenaInviteView::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,m_Priority,true);
}

bool ArenaInviteView::ccTouchBegan( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent )
{
	return true;
}

void ArenaInviteView::onEnter()
{
	CCLayer::onEnter();
	setKeypadEnabled(true);
}

void ArenaInviteView::keyBackClicked()
{
	ArenaGameRoom* parentLayer=(ArenaGameRoom*)getParent();
	if (parentLayer)
	{
		parentLayer->setKeypadEnabled(true);
	}
	this->removeFromParentAndCleanup(true);
}

void ArenaInviteView::keyMenuClicked()
{

}

void ArenaInviteView::createInviteMenu()
{
	CCMenuItemSprite* btnGoBack=ToolsFun::createBTN(LanguageManager::shareManager()->getContentByKey("GOBACK").c_str(),ButtomType_Red,this,menu_selector(ArenaInviteView::OnBtnGoBack));
	btnGoBack->setPosition(ccp(830,572));

	CCMenuItemSprite* btnFriend=ToolsFun::createBTN(LanguageManager::shareManager()->getContentByKey("FRIEND").c_str(),ButtomType_Blue2,this,menu_selector(ArenaInviteView::OnBtnFriend));
	btnFriend->setPosition(ccp(130,572));

	CCMenuItemSprite* btnSocieties=ToolsFun::createBTN(LanguageManager::shareManager()->getContentByKey("SOCIETIES").c_str(),ButtomType_Blue2,this,menu_selector(ArenaInviteView::OnBtnSocieties));
	btnSocieties->setPosition(ccp(255,572));

	CCMenuItemSprite* btnPlayerOnline=ToolsFun::createBTN(LanguageManager::shareManager()->getContentByKey("PLAYER_INLINE").c_str(),ButtomType_Blue2,this,menu_selector(ArenaInviteView::OnBtnPlayerOnline));
	btnPlayerOnline->setPosition(ccp(380,572));

	CCMenuP* menu=CCMenuP::create(m_Priority-1,btnGoBack,NULL);
	this->addChild(menu);
	menu->setPosition(CCPointZero);

	CCRadioMenuP* radioMenu=CCRadioMenuP::createWithP(m_Priority-1,false,btnFriend,btnSocieties,btnPlayerOnline,NULL);
	this->addChild(radioMenu);
	radioMenu->setPosition(CCPointZero);
	radioMenu->setSelectedItem(btnFriend);
}

void ArenaInviteView::createScrollView()
{
	CCLayer* scrollLayer=CCLayer::create();
	//CCLayerColor* scrollLayer=CCLayerColor::create(ccc4(255,255,255,255));
	ScrollViewModel* scrollView=ScrollViewModel::createP(m_Priority-5,CCSizeMake(820,490),scrollLayer);
	this->addChild(scrollView);
	scrollView->setContentSize(CCSizeMake(820,490));
	scrollView->setPosition(ccp(70,45));
	scrollView->setDirection(kCCScrollViewDirectionVertical);
}

void ArenaInviteView::OnBtnGoBack( cocos2d::CCObject* sender )
{
	ArenaGameRoom* parentLayer=(ArenaGameRoom*)getParent();
	if (parentLayer)
	{
		parentLayer->setKeypadEnabled(true);
	}
	this->removeFromParentAndCleanup(true);
}

void ArenaInviteView::OnBtnFriend( cocos2d::CCObject* sender )
{

}

void ArenaInviteView::OnBtnSocieties( cocos2d::CCObject* sender )
{

}

void ArenaInviteView::OnBtnPlayerOnline( cocos2d::CCObject* sender )
{

}

//////////////////////////////////////////////////////////////////////////
//ArenaBagView


ArenaBagView::ArenaBagView():m_Priority(0),m_ScrollView(0)
{

}

ArenaBagView::~ArenaBagView()
{

}

ArenaBagView* ArenaBagView::create( int r )
{
	ArenaBagView* pRet=new ArenaBagView();
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

void ArenaBagView::initLayer()
{
	//±³¾°
	CCSprite* background=CCSprite::create(ATHLETIC_BACKGROUNDSMALL);
	this->addChild(background);
	background->setPosition(ccp(480,320));

	//¹ö¶¯ÇøÓò±³¾°
	CCSprite* soulBackground=CCSprite::create(ATHLETIC_TEXTURE_2);
	CCRect rt=CCRectMake(0,0,820,490);
	soulBackground->setTextureRect(rt);
	ccTexParams tp={GL_LINEAR,GL_LINEAR,GL_REPEAT,GL_REPEAT};
	soulBackground->getTexture()->setTexParameters(&tp);
	this->addChild(soulBackground);
	soulBackground->setPosition(ccp(480,290));

	createScrollView();
	createBagMenu();
	this->setTouchEnabled(true);
}

void ArenaBagView::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,m_Priority,true);
}

bool ArenaBagView::ccTouchBegan( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent )
{
	return true;
}

void ArenaBagView::onEnter()
{
	CCLayerColor::onEnter();
	this->setKeypadEnabled(true);
}

void ArenaBagView::keyBackClicked()
{
	ArenaGameRoom* parentLayer=(ArenaGameRoom*)getParent();
	if (parentLayer)
	{
		parentLayer->setKeypadEnabled(true);
	}
	this->removeFromParentAndCleanup(true);
}

void ArenaBagView::keyMenuClicked()
{

}

void ArenaBagView::createBagMenu()
{
	CCMenuItemSprite* btnGoBack=ToolsFun::createBTN(LanguageManager::shareManager()->getContentByKey("GOBACK").c_str(),ButtomType_Red,this,menu_selector(ArenaBagView::OnBtnGoBack));
	btnGoBack->setPosition(ccp(830,572));

	CCMenuP* menu=CCMenuP::create(m_Priority-1,btnGoBack,NULL);
	this->addChild(menu);
	menu->setPosition(CCPointZero);

	CCMenuItemSprite* btnShopView=ToolsFun::createBTN(LanguageManager::shareManager()->getContentByKey("PROPS_BUY").c_str(),ButtomType_Blue2,this,menu_selector(ArenaBagView::OnBtnSwitchShopView));
	btnShopView->setPosition(ccp(130,572));

	CCMenuItemSprite* btnBagView=ToolsFun::createBTN(LanguageManager::shareManager()->getContentByKey("BAG").c_str(),ButtomType_Blue2,this,menu_selector(ArenaBagView::OnBtnSwitchBagView));
	btnBagView->setPosition(ccp(255,572));

	CCRadioMenuP* radioMenu=CCRadioMenuP::createWithP(m_Priority-1,false,btnShopView,btnBagView,NULL);
	this->addChild(radioMenu);
	radioMenu->setPosition(CCPointZero);
	radioMenu->setSelectedItem(btnShopView);
}

void ArenaBagView::createScrollView()
{

}

void ArenaBagView::OnBtnGoBack( cocos2d::CCObject* sender )
{
	ArenaGameRoom* parentLayer=(ArenaGameRoom*)getParent();
	if (parentLayer)
	{
		parentLayer->setKeypadEnabled(true);
	}
	this->removeFromParentAndCleanup(true);
}

void ArenaBagView::OnBtnSwitchShopView( cocos2d::CCObject* sender )
{

}

void ArenaBagView::OnBtnSwitchBagView( cocos2d::CCObject* sender )
{

}
