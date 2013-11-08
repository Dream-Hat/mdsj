#include "ArenaLayer.h"
#include "IniParser.h"
#include "Define.h"
#include "CMyMenu.h"
#include "TextChange.h"
#include "ToolsFun.h"
#include "ArenaPopLayer.h"
#include "ScrollViewModel.h"
#include "ArenaNode.h"

#include "CfgManager.h"
#include "ArenaNode.h"
#include "EventMSG.h"

#include "LanguageManager.h"

#include "../ZMQ/MessageCenter.h"

//#include "../proto_files/AthleticProto.pb.h"

#define SCROLLVIEWMENU 1		//滚动条按钮Tag



//层次
#define TARGETMODEROOMLAYER 2  //具体游戏模式层
#define GAMEROOMLAYER 3//游戏房间层
#define POPLAYER 10//弹出菜单层次

#define LAYERPOPLAYER 3	//各层上的弹出菜单层
USING_NS_CC;
//////////////////////////////////////////////////////////////////////////
//ArenaLayer
ArenaLayer::ArenaLayer()
{
	m_ArenaMadiator=NULL;
	m_iniParser=NULL;
}

ArenaLayer::~ArenaLayer()
{

}

bool ArenaLayer::init()
{
	bool bRet=false;
	do 
	{
		initLayer();
		bRet=true;
	} while (0);
	return bRet;
}

void ArenaLayer::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,-131,true);
}

bool ArenaLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	return true;
}

void ArenaLayer::onEnter()
{
	CCLayer::onEnter();
	this->setKeypadEnabled(true);
}

void ArenaLayer::keyBackClicked()
{
	SEND_EVENT(this,ArenaEvent::ARENAVIEW_CLOSE,NULL);
}

void ArenaLayer::keyMenuClicked()
{

}

void ArenaLayer::setLayerKeyPad(int endTag)
{

}

void ArenaLayer::refreshModeList(com::tiange::mdsj::proto::ModeListResponse &_modeList)
{
	CCLayer* scrollLayer=(CCLayer*)m_ScrollView->getContainer();
	if (NULL==scrollLayer)return;

// 	m_GameRoomMenu=CCMenuP::create(-132,NULL);
// 	scrollLayer->addChild(m_GameRoomMenu);
// 	m_GameRoomMenu->setPosition(CCPointZero);

	int index=0;
	int heightStep=110;

	int modeLen=_modeList.modes_size();
	for (int i=0;i<modeLen;i++)
	{
		com::tiange::mdsj::proto::ModeListResponse_Mode* modeNode=_modeList.mutable_modes(i);

		GameModeNode* spModel=GameModeNode::create();
		scrollLayer->addChild(spModel,1);
	
		//spModel->setPosition(ccp(340,500-index*heightStep));
		//CCSprite* selectedImg=CCSprite::create(ATHLETIC_LIST_TYPE);CCMenuItemSprite* btn=CCMenuItemSprite::create(CCSprite::create(ATHLETIC_LIST_TYPE),CCSprite::create(ATHLETIC_LIST_TYPE),CCSprite::create(ATHLETIC_LIST_TYPE),this,menu_selector(ArenaLayer::OnBtnFindRoom));
		//m_GameRoomMenu->addChild(btn);
		//btn->setPosition(spModel->getPosition());
		index++;
	}
}

void ArenaLayer::initLayer()
{
	m_iniParser=new INIParser("ui/Arema/configfile/Arema.ini");
	if (!m_iniParser)return;//需要发送退出竞技场界面的协议
	//背景
	CCSprite* spBackground=CCSprite::create(ATHLETIC_BACKGROUND);
	this->addChild(spBackground);
	spBackground->setPosition(m_iniParser->getPoint("ArenaLayer_LayerBackground","Position",ccp(0,0)));
	spBackground->setAnchorPoint(m_iniParser->getPoint("ArenaLayer_LayerBackground","AnchorPoint"));
	
	createModeSelectView();

	//菜单按钮
	createModeSelectMenu();
	
	//刷新模式数据
	//OnRefreshGameModeData();
	this->setTouchEnabled(true);
	delete m_iniParser;
	m_iniParser=NULL;
}

void ArenaLayer::createModeSelectView()
{
	CCSprite* background=CCSprite::create(ATHLETIC_TEXTURE_2);
	//CCRect rt=CCRectMake(0,0,680,620);
	CCRect rt=m_iniParser->getRect("ArenaLayer_ModeScrollViewBackground","BoundingBox");
	background->setTextureRect(rt);
	ccTexParams tp={GL_LINEAR,GL_LINEAR,GL_REPEAT,GL_REPEAT};
	background->getTexture()->setTexParameters(&tp);
	this->addChild(background);
	background->setAnchorPoint(m_iniParser->getPoint("ArenaLayer_ModeScrollViewBackground","AnchorPoint"));
	background->setPosition(m_iniParser->getPoint("ArenaLayer_ModeScrollViewBackground","Position"));

	CCLayer* scrollLayer=CCLayer::create();
	m_ScrollView=ScrollViewModel::createP(m_iniParser->getInt("ArenaLayer_ScrollView","Priority",-128),
		m_iniParser->getContentSize("ArenaLayer_ScrollView","ViewSize"),
		scrollLayer);
	this->addChild(m_ScrollView);
	m_ScrollView->setContentSize(m_iniParser->getContentSize("ArenaLayer_ScrollView","ContentSize"));
	m_ScrollView->setPosition(m_iniParser->getPoint("ArenaLayer_ScrollView","Position"));
	m_ScrollView->setDirection(kCCScrollViewDirectionVertical);
	//scrollView->setContentOffset(ccp(0,-600));
	//模式选择
	CCLabelTTF* lbModeSelect=CCLabelTTF::create(LanguageManager::shareManager()->getContentByKey("MODE_SELECT").c_str(),DEF_FONT_NAME,30);
	this->addChild(lbModeSelect);
	lbModeSelect->setPosition(ccp(300,590));

	CCMenuP* scrollMenu=CCMenuP::create(-201,NULL);
	scrollLayer->addChild(scrollMenu,0,SCROLLVIEWMENU);
	scrollMenu->setPosition(CCPointZero);
}

void ArenaLayer::createModeSelectMenu()
{
	CCMenuP* menu=CCMenuP::create(-135,NULL);
	this->addChild(menu);
	menu->setPosition(CCPointZero);

	CCMenuItemSprite* btnGoBack=ToolsFun::createBTN(LanguageManager::shareManager()->getContentByKey("GOBACK").c_str(),ButtomType_Red,this,menu_selector(ArenaLayer::OnBtnGOBack));
	btnGoBack->setPosition(ccp(840,570));
	menu->addChild(btnGoBack);

	CCMenuItemSprite* btnJoin=ToolsFun::createBTN(LanguageManager::shareManager()->getContentByKey("RANDOM_JOIN").c_str(),ButtomType_Blue1,this,menu_selector(ArenaLayer::OnBtnRandomJoin));
	btnJoin->setPosition(ccp(820,420));
	menu->addChild(btnJoin);

	CCMenuItemSprite* btnFindPlayer=ToolsFun::createBTN(LanguageManager::shareManager()->getContentByKey("FIND_PLAYER").c_str(),ButtomType_Blue1,this,menu_selector(ArenaLayer::OnBtnFindPlayer));
	btnFindPlayer->setPosition(ccp(820,270));
	menu->addChild(btnFindPlayer);

	CCLayer* scrollLayer=(CCLayer*)m_ScrollView->getContainer();
	m_GameRoomMenu=CCMenuP::create(-132,NULL);
	if (NULL!=scrollLayer)
	{
		scrollLayer->addChild(m_GameRoomMenu);
		m_GameRoomMenu->setPosition(CCPointZero);
	}
}

void ArenaLayer::OnRefreshGameModeData()
{
	CCLayer* scrollLayer=(CCLayer*)m_ScrollView->getContainer();
	if (NULL==scrollLayer)return;

	m_GameRoomMenu=CCMenuP::create(-132,NULL);
	scrollLayer->addChild(m_GameRoomMenu);
	m_GameRoomMenu->setPosition(CCPointZero);
	std::map<int,GameModeStepVo*> gameModeDic=CfgManger::getGameMode();
	int index=0;
	int heightStep=110;
	std::map<int,GameModeStepVo*>::iterator it;
	for (it=gameModeDic.begin();it!=gameModeDic.end();++it)
	{
		GameModeNode* spModel=GameModeNode::create();
		scrollLayer->addChild(spModel,1);
		spModel->setPosition(ccp(340,500-index*heightStep));
		CCSprite* selectedImg=CCSprite::create(ATHLETIC_LIST_TYPE);
		selectedImg->setScale(1.1f);
		CCMenuItemSprite* btn=CCMenuItemSprite::create(
			CCSprite::create(ATHLETIC_LIST_TYPE),
			selectedImg,
			CCSprite::create(ATHLETIC_LIST_TYPE),this,menu_selector(ArenaLayer::OnBtnFindRoom));
		m_GameRoomMenu->addChild(btn);
		btn->setPosition(spModel->getPosition());
		index++;

// 		GameModeSprite* normal=GameModeSprite::create(ATHLETIC_LIST_TYPE,"XXXXXXXXXXXX",10);
// 		GameModeSprite* selected=GameModeSprite::create(ATHLETIC_LIST_TYPE,"XXXXXXXXXXXX",10);
// 		GameModeSprite* disible=GameModeSprite::create(ATHLETIC_LIST_TYPE,"XXXXXXXXXXXX",10);
// 		selected->setScale(1.1f);
// 		CCMenuItemSprite* btn=CCMenuItemSprite::create(normal,selected,disible,this,menu_selector(ArenaLayer::OnBtnFindRoom));
// 		m_GameRoomMenu->addChild(btn);
// 		btn->setPosition(ccp(340,500-index*heightStep));
// 		index++;
	}
}

void ArenaLayer::createMenu()
{
	CCMenuP* menu=CCMenuP::create(-130,NULL);
	this->addChild(menu);
	menu->setPosition(CCPointZero);

	CCMenuItemImage* btnGoBack=ToolsFun::createABtn("UI/Arema/GoBack.png",this,menu_selector(ArenaLayer::OnBtnGOBack));
	btnGoBack->setPosition(ccp(840,570));
	menu->addChild(btnGoBack);

	CCMenuItemSprite* btnJoin=ToolsFun::createBtn(LanguageManager::shareManager()->getContentByKey("RANDOM_JOIN").c_str(),this,menu_selector(ArenaLayer::OnBtnRandomJoin));
	btnJoin->setPosition(ccp(820,420));
	menu->addChild(btnJoin);

	CCMenuItemSprite* btnFindRoom=ToolsFun::createBtn(LanguageManager::shareManager()->getContentByKey("FIND_ROOM").c_str(),this,menu_selector(ArenaLayer::OnBtnFindRoom));
	btnFindRoom->setPosition(ccp(820,270));
	menu->addChild(btnFindRoom);

	CCMenuItemSprite* btnCreateRoom=ToolsFun::createBtn(LanguageManager::shareManager()->getContentByKey("CREATE_ROOM").c_str(),this,menu_selector(ArenaLayer::OnBtnCreateRoom));
	btnCreateRoom->setPosition(ccp(820,120));
	menu->addChild(btnCreateRoom);
}

void ArenaLayer::OnBtnGOBack( cocos2d::CCObject* sender )
{
	//this->removeFromParentAndCleanup(true);
	SEND_EVENT(this,ArenaEvent::ARENAVIEW_CLOSE,NULL);
}

void ArenaLayer::OnBtnRandomJoin( cocos2d::CCObject* sender )
{
	ArenaModeRoom* modeRoom=ArenaModeRoom::create(-141);
	this->addChild(modeRoom,TARGETMODEROOMLAYER);
	this->setKeypadEnabled(false);
}

void ArenaLayer::OnBtnFindRoom( cocos2d::CCObject* sender )
{

}

void ArenaLayer::OnBtnCreateRoom( cocos2d::CCObject* sender )
{
	ArenaFindPlayer* layer=ArenaFindPlayer::create(-181);
	this->addChild(layer,2);
}

void ArenaLayer::OnBtnFindPlayer(cocos2d::CCObject* sender)
{
	ArenaFindPlayer* layer=ArenaFindPlayer::create(-150);
	this->addChild(layer);
	layer->setTag(FINDPLAYERTAG);
	this->setKeypadEnabled(false);
}

//////////////////////////////////////////////////////////////////////////
//ArenaModeRoom
ArenaModeRoom::ArenaModeRoom()
{

}

ArenaModeRoom::~ArenaModeRoom()
{

}

bool ArenaModeRoom::init()
{
	bool bRet=false;
	do 
	{
		initLayer();
		bRet=true;
	} while (0);
	return bRet;
}

ArenaModeRoom* ArenaModeRoom::create(int r)
{
	ArenaModeRoom* pRet=new ArenaModeRoom();
	pRet->m_Priority=r;
	if (pRet&&pRet->init())
	{
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	pRet=NULL;
	return pRet;
}

void ArenaModeRoom::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,m_Priority,true);
}

bool ArenaModeRoom::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	return true;
}

void ArenaModeRoom::onEnter()
{
	CCLayer::onEnter();
	this->setKeypadEnabled(true);
}

void ArenaModeRoom::keyBackClicked()
{
	ArenaLayer* parentLayer=(ArenaLayer*)getParent();
	if (parentLayer)
	{
		parentLayer->setKeypadEnabled(true);
	}
	this->removeFromParentAndCleanup(true);
}

void ArenaModeRoom::keyMenuClicked()
{

}

void ArenaModeRoom::initLayer()
{
	CCSprite* spBackground=CCSprite::create(ATHLETIC_BACKGROUND);
	this->addChild(spBackground);
	spBackground->setPosition(ccp(480,320));
	spBackground->setAnchorPoint(ccp(0.5,0.5));

	createModeSelectView();
	createMenu();

	OnRefreshGameRoomsData();
	this->setTouchEnabled(true);
}

void ArenaModeRoom::createModeSelectView()
{
	CCSprite* background=CCSprite::create(ATHLETIC_TEXTURE_2);
	CCRect rt=CCRectMake(0,0,680,620);
	background->setTextureRect(rt);
	ccTexParams tp={GL_LINEAR,GL_LINEAR,GL_REPEAT,GL_REPEAT};
	background->getTexture()->setTexParameters(&tp);
	this->addChild(background);
	background->setAnchorPoint(ccp(0,0));
	background->setPosition(ccp(10,10));

	CCLayer* scrollLayer=CCLayer::create();
	m_ScrollView=ScrollViewModel::createP(m_Priority-5,CCSizeMake(680,530),scrollLayer);
	this->addChild(m_ScrollView);
	m_ScrollView->setContentSize(CCSizeMake(680,800));
	m_ScrollView->setPosition(ccp(10,10));
	m_ScrollView->setDirection(kCCScrollViewDirectionVertical);

	CCLabelTTF* lbModeSelect=CCLabelTTF::create(LanguageManager::shareManager()->getContentByKey("XX_GAMEMODE").c_str(),DEF_FONT_NAME,30);
	this->addChild(lbModeSelect);
	lbModeSelect->setPosition(ccp(300,590));

	CCMenuP* scrollMenu=CCMenuP::create(m_Priority-1,NULL);
	scrollLayer->addChild(scrollMenu,0,SCROLLVIEWMENU);
	scrollMenu->setPosition(CCPointZero);
}

void ArenaModeRoom::createMenu()
{
	CCMenuP* menu=CCMenuP::create(m_Priority-1,NULL);
	this->addChild(menu);
	menu->setPosition(CCPointZero);

	//返回按钮
	CCMenuItemSprite* btnGoBack=ToolsFun::createBTN(LanguageManager::shareManager()->getContentByKey("GOBACK").c_str(),ButtomType_Red,this,menu_selector(ArenaModeRoom::OnBtnGoBack));
	menu->addChild(btnGoBack);
	btnGoBack->setPosition(ccp(840,570));

	CCMenuItemSprite* btnJoin=ToolsFun::createBTN(LanguageManager::shareManager()->getContentByKey("RANDOM_JOIN").c_str(),ButtomType_Blue1,this,menu_selector(ArenaModeRoom::OnBtnRandomJoin));
	btnJoin->setPosition(ccp(820,420));
	menu->addChild(btnJoin);

	CCMenuItemSprite* btnFindRoom=ToolsFun::createBTN(LanguageManager::shareManager()->getContentByKey("FIND_ROOM").c_str(),ButtomType_Blue1,this,menu_selector(ArenaModeRoom::OnBtnFindRoom));
	btnFindRoom->setPosition(ccp(820,270));
	menu->addChild(btnFindRoom);

	CCMenuItemSprite* btnCreateRoom=ToolsFun::createBTN(LanguageManager::shareManager()->getContentByKey("CREATE_ROOM").c_str(),ButtomType_Blue1,this,menu_selector(ArenaModeRoom::OnBtnCreateRoom));
	btnCreateRoom->setPosition(ccp(820,120));
	menu->addChild(btnCreateRoom);
}

void ArenaModeRoom::OnRefreshGameRoomsData()
{
	CCLayer* scrollLayer=(CCLayer*)m_ScrollView->getContainer();
	if (NULL==scrollLayer)return;

	std::map<int,GameRoomsStepVo*> gameRoomsDic=CfgManger::getRoomsDic();
	int index=0;
	int heightStep=90;
	std::map<int,GameRoomsStepVo*>::iterator it;
	for (it=gameRoomsDic.begin();it!=gameRoomsDic.end();++it)
	{
 		GameRoomsNode* roomNode=GameRoomsNode::create();
		scrollLayer->addChild(roomNode);
 		roomNode->setPosition(ccp(340,490-index*heightStep));
 		GameRoomsStepVo* vo=it->second;
// 		roomNode->setData(vo);
 		index++;
	}
}

void ArenaModeRoom::OnBtnGoBack( cocos2d::CCObject* sender )
{
	this->removeFromParentAndCleanup(true);
	//SEND_EVENT(this,ArenaEvent::ARENAVIEW_CLOSE,NULL);
}

void ArenaModeRoom::OnBtnRandomJoin( cocos2d::CCObject* sender )
{
	//test
	ArenaGameRoom* gameRoom=ArenaGameRoom::create(m_Priority-10);
	this->addChild(gameRoom,GAMEROOMLAYER,GAMEMODETAG);
	this->setKeypadEnabled(false);
	gameRoom->RefreshTeamData();
}

void ArenaModeRoom::OnBtnFindRoom( cocos2d::CCObject* sender )
{
	ArenaFindRoom* findRoom=ArenaFindRoom::create(m_Priority-10);
	this->addChild(findRoom,POPLAYER);
	this->setKeypadEnabled(false);
}

void ArenaModeRoom::OnBtnCreateRoom( cocos2d::CCObject* sender )
{
	ArenaCreateRoom* createRoom=ArenaCreateRoom::create(m_Priority-10);
	this->addChild(createRoom);
	createRoom->setTag(POPLAYER);
	this->setKeypadEnabled(false);

	
}

//////////////////////////////////////////////////////////////////////////
//ArenaGameRoom
ArenaGameRoom::ArenaGameRoom()
{
	m_LbRoomID=NULL;
	m_SpMap=NULL;
	m_Priority=0;
}

ArenaGameRoom::~ArenaGameRoom()
{

}

bool ArenaGameRoom::init()
{
	bool bRet=false;
	do 
	{
		initLayer();
		bRet=true;
	} while (0);
	return bRet;
}

ArenaGameRoom* ArenaGameRoom::create(int r)
{
	ArenaGameRoom* pRet=new ArenaGameRoom();
	pRet->m_Priority=r;
	if (pRet&&pRet->init())
	{
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return NULL;
}

void ArenaGameRoom::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,m_Priority,true);
}

bool ArenaGameRoom::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	return true;
}

void ArenaGameRoom::onEnter()
{
	CCLayer::onEnter();
	this->setKeypadEnabled(true);
}

void ArenaGameRoom::keyBackClicked()
{
	ArenaModeRoom* parentLayer=(ArenaModeRoom*)getParent();
	if (parentLayer)
	{
		parentLayer->setKeypadEnabled(true);
	}
	this->removeFromParentAndCleanup(true);
}

void ArenaGameRoom::keyMenuClicked()
{

}

void ArenaGameRoom::initLayer()
{
	//背景
	CCSprite* background=CCSprite::create(ATHLETIC_BACKGROUND);
	this->addChild(background);
	background->setPosition(ccp(480,320));

	CCSprite* spRoomID=CCSprite::create(ATHLETIC_ROOM_ID);
	this->addChild(spRoomID);
	spRoomID->setPosition(ccp(415,590));

	CCLabelTTF* lbRoomID=CCLabelTTF::create(LanguageManager::shareManager()->getContentByKey("ROOM_ID").c_str(),DEF_FONT_NAME,20);
	this->addChild(lbRoomID);
	lbRoomID->setPosition(ccp(70,590));

	m_LbRoomID=CCLabelTTF::create(LanguageManager::shareManager()->getContentByKey("ROOM_ID").c_str(),DEF_FONT_NAME,20);
	this->addChild(m_LbRoomID);
	m_LbRoomID->setHorizontalAlignment(kCCTextAlignmentLeft);
	m_LbRoomID->setPosition(ccp(160,590));

	//地图
	m_SpMap=CCSprite::create(ATHLETIC_ROOM_MAP);
	this->addChild(m_SpMap);
	m_SpMap->setPosition(ccp(700,320));

	createGameRoomMenu();
	this->setTouchEnabled(true);
}

void ArenaGameRoom::createGameRoomMenu()
{
	CCMenuItemSprite* btnGoBack=ToolsFun::createBTN(LanguageManager::shareManager()->getContentByKey("GOBACK").c_str(),ButtomType_Red,this,menu_selector(ArenaGameRoom::OnBtnGoBack));
	CCMenuItemSprite* btnInvite=ToolsFun::createBTN(LanguageManager::shareManager()->getContentByKey("INVITE_PLAYER").c_str(),ButtomType_Blue2,this,menu_selector(ArenaGameRoom::OnBtnInvite));
	CCMenuItemSprite* btnFightTools=ToolsFun::createBTN(LanguageManager::shareManager()->getContentByKey("FIGHT_PROPS").c_str(),ButtomType_Blue2,this,menu_selector(ArenaGameRoom::OnBtnFightTools));
	CCMenuItemSprite* btnSetReady=ToolsFun::createBTN(LanguageManager::shareManager()->getContentByKey("GETREADGAME").c_str(),ButtomType_Blue2,this,menu_selector(ArenaGameRoom::OnBtnSetReady));
	CCMenuItemSprite* btnSetSoul=ToolsFun::createBTN(LanguageManager::shareManager()->getContentByKey("SOUL_SETTING").c_str(),ButtomType_Blue2,this,menu_selector(ArenaGameRoom::OnBtnSetSoul));
	CCMenuItemSprite* btnSelectMap=ToolsFun::createBTN(LanguageManager::shareManager()->getContentByKey("SELECT_MAP").c_str(),ButtomType_Blue2,this,menu_selector(ArenaGameRoom::OnBtnSelectMap));

	btnGoBack->setPosition(ccp(880,590));
	btnInvite->setPosition(ccp(160,50));
	btnFightTools->setPosition(ccp(320,50));
	btnSetReady->setPosition(ccp(480,50));
	btnSetSoul->setPosition(ccp(640,50));
	btnSelectMap->setPosition(ccp(800,50));

	CCMenuP* menu=CCMenuP::create(m_Priority-10,btnGoBack,btnInvite,btnFightTools,btnSetReady,btnSetSoul,btnSelectMap,NULL);
	this->addChild(menu);
	menu->setPosition(CCPointZero);
}

void ArenaGameRoom::OnBtnGoBack( cocos2d::CCObject* sender )
{
	ArenaModeRoom* parentLayer=(ArenaModeRoom*)getParent();
	if (parentLayer)
	{
		parentLayer->setKeypadEnabled(true);
	}
	this->removeFromParentAndCleanup(true);
}

void ArenaGameRoom::OnBtnInvite( cocos2d::CCObject* sender )
{
	ArenaInviteView* inviteView=ArenaInviteView::create(m_Priority-10);
	this->addChild(inviteView,LAYERPOPLAYER);
	this->setKeypadEnabled(false);
}

void ArenaGameRoom::OnBtnFightTools( cocos2d::CCObject* sender )
{
	ArenaBagView* bagView=ArenaBagView::create(m_Priority-10);
	this->addChild(bagView,LAYERPOPLAYER);
	this->setKeypadEnabled(false);
}

void ArenaGameRoom::OnBtnSetReady( cocos2d::CCObject* sender )
{

}

void ArenaGameRoom::OnBtnSetSoul( cocos2d::CCObject* sender )
{
	ArenaSoulView* soulLayer=ArenaSoulView::create(m_Priority-10);
	this->addChild(soulLayer,LAYERPOPLAYER);
	this->setKeypadEnabled(false);
}

void ArenaGameRoom::OnBtnSelectMap( cocos2d::CCObject* sender )
{
	ArenaSelectMap* selectMapLayer=ArenaSelectMap::create(m_Priority-10);
	this->addChild(selectMapLayer,LAYERPOPLAYER);
	this->setKeypadEnabled(false);
}

void ArenaGameRoom::RefreshTeamData()
{
	std::map<int,GameRoomPlayerStepVo*> playerDic=CfgManger::getRoomPlayerDicc();
	PlayerVoInRoom leftPlayerTop;
	PlayerVoInRoom leftPlayerBottom;
	PlayerVoInRoom rightPlayerTop;
	PlayerVoInRoom rightPlayerBottom;
	leftPlayerTop.copyFromVo(playerDic[1]);
	leftPlayerBottom.copyFromVo(CfgManger::getPlayerStep(2));
	rightPlayerTop.copyFromVo(CfgManger::getPlayerStep(3));
	rightPlayerBottom.copyFromVo(CfgManger::getPlayerStep(4));
	TeamNodeInRoom* leftTeam=TeamNodeInRoom::createWithPlayer(1,leftPlayerTop,leftPlayerBottom);
	this->addChild(leftTeam);
	leftTeam->setPosition(ccp(120,320));

	TeamNodeInRoom* rightTeam=TeamNodeInRoom::createWithPlayer(2,rightPlayerTop,rightPlayerBottom);
	this->addChild(rightTeam);
	rightTeam->setPosition(ccp(340,320));
}
