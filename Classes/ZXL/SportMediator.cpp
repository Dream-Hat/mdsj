#include "SportMediator.h"
#include "ZMQ/GameDef.h"
#include "ZMQ/AllCommandSignal.h"
#include "ZMQ/layerManager.h"
#include "ZXL/tools/DataPackageManager.h"
//#include "proto_files/Land.pb.h"

#pragma comment(lib,"libprotobuf.lib") //加入链接库
#pragma comment(lib,"libprotoc.lib") //加入链接库
//using namespace com::tiange::mdsj::proto;

SportMediator::SportMediator()
{
	_scene = NULL;

	ADD_EVENT_LISTENER(OnSportOpen,NULL,this,Event::SPORT_OPEN,SportMediator)
}

SportMediator::~SportMediator()
{
	if (_scene)
	{
		REMOVE_SCENE_FROM_LAYER(_scene)
	}
}

void SportMediator::OnPackage( int xy,void* pack)
{
	
}

void SportMediator::OnSportOpen( CCObject* sender,int msgid,cocos2d::CCObject* obj)
{
	if (_scene == NULL)
	{
		_scene = SportLayer::create();
		//_scene->retain();
		_scene->m_Mediator = this;
		ADD_SCENE_TO_LAYER(_scene.obj(),LayerManager::sceneUILayer);
	}
}

void SportMediator::dispose()
{
	if (_scene)
	{
		REMOVE_SCENE_FROM_LAYER(_scene)
			//_scene->release();
			_scene = NULL;
	}
}
void SportLayer::onExit()
{
	CCLayer::onExit();
	CC_SAFE_RELEASE(m_allPanelNames);
}

bool SportLayer::init()
{

	bool bRet = false;
	do 
	{
		CCLog("sport init start");
		CC_BREAK_IF(!CCLayer::init());
		CC_BREAK_IF(! this->initUI());

		this->hideAllPanels();
		this->showPanelAt(panelSport);
		

		m_Mediator = NULL;
		bRet = true;
	} while (0);

	return bRet;
}
bool SportLayer::initUI()
{
	bool bRet = false;
	do 
	{
		///////////////////////////		UI control			/////////////////////////////
		m_pUILayer = UILayer::create();
		m_pUILayer->setTouchPriority(-200);
		m_pUILayer->scheduleUpdate();
		this->addChild(m_pUILayer);
		m_allPanelNames = CCDictionary::create();
		m_allPanelNames->setObject(CCString::create("panel_sport"), panelSport);
		m_allPanelNames->setObject(CCString::create("panel_sport_friend"), panelSportFriend);
		m_allPanelNames->setObject(CCString::create("panel_sport_top"), panelSportTop);
		m_allPanelNames->setObject(CCString::create("panel_sport_rule"), panelSportRule);
		m_allPanelNames->setObject(CCString::create("panel_sport_countdown"), panelSportCountdown);
		m_allPanelNames->retain();

		m_allListItemNames = CCDictionary::create();
		m_allListItemNames->setObject(CCString::create("panel_sport_friend_list_item"), friendListItem);
		m_allListItemNames->setObject(CCString::create("panel_sport_top_list_item"), topListItem);
		m_allListItemNames->retain();
		bRet = true;
	} while (0);
	return bRet;
}
bool SportLayer::initWidgets4PanelSport(Layout* _sportLay)
{
	bool bRet = false;
	do 
	{
		//btn back
		UIWidget* bgSport = _sportLay->getChildByName("bg_sport");
		UITextButton* txtBtnSportBack = dynamic_cast<UITextButton*>(bgSport->getChildByName("txtBtn_sport_back"));
		txtBtnSportBack->addReleaseEvent(this, coco_releaseselector(SportLayer::closeBtnCallBack));
		//btn rule
		UITextButton* txtBtnSportRule = dynamic_cast<UITextButton*>(bgSport->getChildByName("txtBtn_sport_rule"));
		txtBtnSportRule->addReleaseEvent(this, coco_releaseselector(SportLayer::panelSportCallback));
		txtBtnSportRule->setWidgetTag(sportRuleBtnTag);
		//btn start
		UITextButton* txtBtnSportStart = dynamic_cast<UITextButton*>(bgSport->getChildByName("txtBtn_sport_start"));
		txtBtnSportStart->addReleaseEvent(this, coco_releaseselector(SportLayer::panelSportCallback));
		txtBtnSportStart->setWidgetTag(sportStartBtnTag);
		//btn top
		UITextButton* txtBtnSportTop = dynamic_cast<UITextButton*>(bgSport->getChildByName("txtBtn_sport_top"));
		txtBtnSportTop->addReleaseEvent(this, coco_releaseselector(SportLayer::panelSportCallback));
		txtBtnSportTop->setWidgetTag(sportTopBtnTag);
		//btn clear
		UITextButton* txtBtnSportClear = dynamic_cast<UITextButton*>(bgSport->getChildByName("txtBtn_sport_clear"));
		txtBtnSportClear->addReleaseEvent(this, coco_releaseselector(SportLayer::panelSportCallback));
		txtBtnSportClear->setWidgetTag(sportClearBtnTag);
		//btn sport reward obtain
		UIWidget* bgSportReward = bgSport->getChildByName("bg_sport_reward");
		UITextButton* txtBtnRewardObtain = dynamic_cast<UITextButton*>(bgSportReward->getChildByName("txtBtn_reward_obtain"));
		txtBtnRewardObtain->addReleaseEvent(this, coco_releaseselector(SportLayer::panelSportCallback));
		txtBtnRewardObtain->setWidgetTag(sportRewardObtainBtnTag);
		//btn sport player seat invite 
		UIWidget* bgSportPlayerSeat = bgSport->getChildByName("bg_sport_player_seat");
		UIButton* txtBtnSeatInvite = dynamic_cast<UIButton*>(bgSportPlayerSeat->getChildByName("btn_seat_invite"));
		txtBtnSeatInvite->addReleaseEvent(this, coco_releaseselector(SportLayer::panelSportCallback));
		txtBtnSeatInvite->setWidgetTag(sportPlayerSeatInivteBtnTag);
		bRet = true;
	} while (0);
	return bRet;
}
bool SportLayer::initWidgets4PanelSportFriend(Layout* _sportFriendLay)
{
	bool bRet = false;
	do 
	{
		UIWidget* bgSportFriend = _sportFriendLay->getChildByName("bg_friend");
		UITextButton* txtBtnSportFriendBack = dynamic_cast<UITextButton*>(bgSportFriend->getChildByName("txtBtn_friend_back"));
		txtBtnSportFriendBack->addReleaseEvent(this, coco_releaseselector(SportLayer::panelSportFriendCallback));
		txtBtnSportFriendBack->setWidgetTag(sportFriendBackBtnTag);

		UITextButton* txtBtnSportFriendOLPlayerTag = dynamic_cast<UITextButton*>(bgSportFriend->getChildByName("txtBtn_friend_olplayer_tag"));
		txtBtnSportFriendOLPlayerTag->addReleaseEvent(this, coco_releaseselector(SportLayer::panelSportFriendCallback));
		txtBtnSportFriendOLPlayerTag->setWidgetTag(sportFriendOLPlayerTagBtnTag);

		UITextButton* txtBtnSportFriendClubTag = dynamic_cast<UITextButton*>(bgSportFriend->getChildByName("txtBtn_friend_club_tag"));
		txtBtnSportFriendClubTag->addReleaseEvent(this, coco_releaseselector(SportLayer::panelSportFriendCallback));
		txtBtnSportFriendClubTag->setWidgetTag(sportFriendClubTagBtnTag);

		UITextButton* txtBtnSportFriendFriendTag = dynamic_cast<UITextButton*>(bgSportFriend->getChildByName("txtBtn_friend_friend_tag"));
		txtBtnSportFriendFriendTag->addReleaseEvent(this, coco_releaseselector(SportLayer::panelSportFriendCallback));
		txtBtnSportFriendFriendTag->setWidgetTag(sportFriendFriendTagBtnTag);

		//friend list
		UIScrollView* scvwFriendList = dynamic_cast<UIScrollView*>(bgSportFriend->getChildByName("scvw_friend_list"));
		
		//scvwFriendList->scrollToTop();
		//listitem 
		int itemCount = 10;
		CCString* name = CCString::createWithFormat("ui/SportUI/%s.json",m_allListItemNames->valueForKey(friendListItem)->getCString() );

		Layout* pListItem = dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile(name->getCString()	));
		CC_BREAK_IF(! pListItem);
		pListItem->setPosition(CCPointZero);
		scvwFriendList->addChild(pListItem);
		CCSize scvwSize = scvwFriendList->getInnerContainerSize();
		scvwFriendList->setInnerContainerSize(CCSizeMake(scvwSize.width, pListItem->getContentSize().height * itemCount));
		for(int i=1; i<itemCount; i++){
			pListItem = dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile(name->getCString()	));
			CC_BREAK_IF(! pListItem);
			pListItem->setPosition(ccp(0,i*(pListItem->getContentSize().height)));
			scvwFriendList->addChild(pListItem);
		}
		

		bRet = true;
	} while (0);
	return bRet;
}
bool SportLayer::initWidgets4PanelSportTop(Layout* _sportTopLay)
{
	bool bRet = false;
	do 
	{
		UIWidget* bgSportRule = _sportTopLay->getChildByName("bg_top");
		UITextButton* txtBtnSportTopWinRatetag = dynamic_cast<UITextButton*>(bgSportRule->getChildByName("txtBtn_top_win_rate_tag"));
		txtBtnSportTopWinRatetag->addReleaseEvent(this, coco_releaseselector(SportLayer::panelSportTopCallback));
		txtBtnSportTopWinRatetag->setWidgetTag(sportTopWinRateTagBtnTag);

		UITextButton* txtBtnSportTopWinCnttag = dynamic_cast<UITextButton*>(bgSportRule->getChildByName("txtBtn_top_win_cnt_tag"));
		txtBtnSportTopWinCnttag->addReleaseEvent(this, coco_releaseselector(SportLayer::panelSportTopCallback));
		txtBtnSportTopWinCnttag->setWidgetTag(sportTopWinCntTagBtnTag);

		UITextButton* txtBtnSportTopScoreTag = dynamic_cast<UITextButton*>(bgSportRule->getChildByName("txtBtn_top_score_tag"));
		txtBtnSportTopScoreTag->addReleaseEvent(this, coco_releaseselector(SportLayer::panelSportTopCallback));
		txtBtnSportTopScoreTag->setWidgetTag(sportTopScoreTagBtnTag);

		UITextButton* txtBtnSportTopBack = dynamic_cast<UITextButton*>(bgSportRule->getChildByName("txtBtn_top_back"));
		txtBtnSportTopBack->addReleaseEvent(this, coco_releaseselector(SportLayer::panelSportTopCallback));
		txtBtnSportTopBack->setWidgetTag(sportTopBackBtnTag);

		UITextButton* txtBtnSportTopPlayerNicknameTag = dynamic_cast<UITextButton*>(bgSportRule->getChildByName("txtBtn_player_nickname_tag"));
		txtBtnSportTopPlayerNicknameTag->addReleaseEvent(this, coco_releaseselector(SportLayer::panelSportTopCallback));
		txtBtnSportTopPlayerNicknameTag->setWidgetTag(sportTopPlayerNicknameBtnTag);

		//friend list
		UIScrollView* scvwTopList = dynamic_cast<UIScrollView*>(bgSportRule->getChildByName("scvw_top_list"));
		CC_BREAK_IF(! scvwTopList);
		int itemCount = 10;
		//listitem 
		CCString* name = CCString::createWithFormat("ui/SportUI/%s.json",m_allListItemNames->valueForKey(topListItem)->getCString() );
		Layout* pListItem = dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile(name->getCString()	));
		CC_BREAK_IF(! pListItem);
		pListItem->setPosition(CCPointZero);
		scvwTopList->addChild(pListItem);

		CCSize scvwSize = scvwTopList->getInnerContainerSize();
		scvwTopList->setInnerContainerSize(CCSizeMake(scvwSize.width, pListItem->getContentSize().height * itemCount));

		for(int i=1; i<itemCount; i++){
			pListItem = dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile(name->getCString()	));
			CC_BREAK_IF(! pListItem);
			pListItem->setPosition(ccp(0,i*(pListItem->getContentSize().height)));
			scvwTopList->addChild(pListItem);
		}

		bRet = true;
	} while (0);
	return bRet;
}
bool SportLayer::initWidgets4PanelSportRule(Layout* _sportRuleLay)
{
	bool bRet = false;
	do 
	{
		UIWidget* bgSportRule = _sportRuleLay->getChildByName("bg_rule");
		UITextButton* txtBtnSportRuleBack = dynamic_cast<UITextButton*>(bgSportRule->getChildByName("txtBtn_rule_back"));
		txtBtnSportRuleBack->addReleaseEvent(this, coco_releaseselector(SportLayer::panelSportRuleCallback));
		txtBtnSportRuleBack->setWidgetTag(sportRuleBackBtnTag);

		bRet = true;
	} while (0);
	return bRet;
}
bool SportLayer::initWidgets4PanelSportCountdown(Layout* _sportCountdownLay)
{
	bool bRet = false;
	do 
	{

		bRet = true;
	} while (0);
	return bRet;
}
bool SportLayer::initPanelSportByType(Layout* _lay, PanelType _type)
{
	bool bRet = false;
	do 
	{
		switch(_type){
		case panelSport:
			bRet = initWidgets4PanelSport(_lay);
			break;
		case panelSportFriend:
			bRet = initWidgets4PanelSportFriend(_lay);
			break;
		case panelSportTop:
			bRet = initWidgets4PanelSportTop(_lay);
			break;
		case panelSportRule:
			bRet = initWidgets4PanelSportRule(_lay);
			break;
		case panelSportCountdown:
			bRet = initWidgets4PanelSportCountdown(_lay);
			break;
		default:
			bRet = true;
			break;
		}
	} while (0);
	return bRet;
}

void SportLayer::hidePanelAt(PanelType _index)
{
	CCAssert(m_allPanelNames != NULL , "m_allLayers is not init!");
	Layout* lay = dynamic_cast<Layout*>(m_pUILayer->getWidgetByName(  m_allPanelNames->valueForKey(_index)->getCString() ));
	if(! lay) return;
	lay->setVisible(false);
	lay->setTouchEnable(false,true);
}

void SportLayer::hideAllPanels()
{
	CCAssert(m_allPanelNames != NULL , "m_allPanelNames is not init!");
	Layout* lay = NULL;
	CCDictElement* elm = NULL;
	CCDICT_FOREACH(m_allPanelNames , elm){
		lay = dynamic_cast<Layout*>(m_pUILayer->getWidgetByName(((CCString* )elm->getObject())->getCString() ));
		if(! lay) continue;
		lay->setVisible(false);
		lay->setTouchEnable(false,true);
	}
}

void SportLayer::showPanelAt(PanelType _index)
{
	CCAssert(m_allPanelNames != NULL , "m_allLayers is not init!");
	Layout* lay = dynamic_cast<Layout*>(m_pUILayer->getWidgetByName(  m_allPanelNames->valueForKey(_index)->getCString() ));
	if(! lay){
		std::string name = "ui/SportUI/";
		name += m_allPanelNames->valueForKey(_index)->getCString();
		name += ".json";
		lay = dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile( name.c_str()  ));
		CCAssert(lay != NULL, "get panel error");
		m_pUILayer->addWidget(lay);
		CCAssert(initPanelSportByType(lay, _index), "lay init error");
	}
	lay->setVisible(true);
	lay->setTouchEnable(true,true);
}
void SportLayer::sinkPanelFromParent(PanelType _parentIndex, PanelType _subIndex)
{
	CCAssert(m_allPanelNames != NULL , "m_allLayers is not init!");
	Layout* pLay = dynamic_cast<Layout*>(m_pUILayer->getWidgetByName(  m_allPanelNames->valueForKey(_parentIndex)->getCString() ));
	Layout* subLayer = dynamic_cast<Layout*>(m_pUILayer->getWidgetByName(  m_allPanelNames->valueForKey(_subIndex)->getCString() ));
	CCAssert(pLay&&subLayer , "parent and child should not null");
	subLayer->setWidgetZOrder(pLay->getWidgetZOrder() - 1);
}

void SportLayer::comeupPanelFromParent(PanelType _parentIndex, PanelType _subIndex)
{
	CCAssert(m_allPanelNames != NULL , "m_allLayers is not init!");
	Layout* pLay = dynamic_cast<Layout*>(m_pUILayer->getWidgetByName(  m_allPanelNames->valueForKey(_parentIndex)->getCString() ));
	Layout* subLayer = dynamic_cast<Layout*>(m_pUILayer->getWidgetByName(  m_allPanelNames->valueForKey(_subIndex)->getCString() ));
	CCAssert(pLay&&subLayer , "parent and child should not null");
	subLayer->setWidgetZOrder(pLay->getWidgetZOrder() + 1);
}
Layout* SportLayer::getPanelAt(PanelType _index)
{
	CCAssert(m_allPanelNames != NULL , "m_allLayers is not init!");
	Layout* lay = dynamic_cast<Layout*>(m_pUILayer->getWidgetByName(  m_allPanelNames->valueForKey(_index)->getCString() ));
	CCAssert(lay != NULL, "get panel error");
	return lay;
}

void SportLayer::connectCallback4Target(void* data ,void* route)
{
 	CCLog("connect is callback");
// 	if(data == NULL) return;
// 	std::string val = *((std::string*)data);
// 	CCLog("data : %s",val.c_str());
}

void SportLayer::panelSportCallback(CCObject* pSender)
{
	UIWidget* pWidget = dynamic_cast<UIWidget*>(pSender);
	int widgetTag = pWidget->getWidgetTag();
	//LoginRequest login;
	//std::string strDat("");
	switch(widgetTag){
	case sportStartBtnTag:
		//通信测试
		//DataPackageManager::shareDataPackageManager()->requestHandshake(datapackage_selector(SportLayer::connectCallback4Target),this);
		//DataPackageManager::shareDataPackageManager()->requestData("this is a body of data.", 0 ,datapackage_selector(SportLayer::connectCallback4Target),this);
		break;
	case sportTopBtnTag:
		getPanelAt(panelSport)->setTouchEnable(false,true);
		showPanelAt(panelSportTop);
		comeupPanelFromParent(panelSport, panelSportTop);
		break;
	case sportRuleBtnTag:
		getPanelAt(panelSport)->setTouchEnable(false,true);
		showPanelAt(panelSportRule);
		comeupPanelFromParent(panelSport, panelSportRule);
		break;
	case sportClearBtnTag:
		
		//login.set_user("123");
	//	login.set_key("123");
		//login.set_version("123");
		//login.SerializeToString(&strDat);

		//DataPackageManager::shareDataPackageManager()->requestData(strDat, 1 ,datapackage_selector(SportLayer::connectCallback4Target),this);
		break;
	case sportPlayerSeatInivteBtnTag:
		getPanelAt(panelSport)->setTouchEnable(false,true);
		showPanelAt(panelSportFriend);
		comeupPanelFromParent(panelSport, panelSportFriend);
		break;
	case sportRewardObtainBtnTag:
		break;
	default:	break;
	}
}
void SportLayer::panelSportFriendCallback(CCObject* pSender)
{
	UIWidget* pWidget = dynamic_cast<UIWidget*>(pSender);
	int widgetTag = pWidget->getWidgetTag();
	switch(widgetTag){
	case sportFriendOLPlayerTagBtnTag:
		break;
	case sportFriendClubTagBtnTag:
		break;
	case sportFriendBackBtnTag:
		getPanelAt(panelSport)->setTouchEnable(true,true);
		hidePanelAt(panelSportFriend);
		break;
	case sportFriendFriendTagBtnTag:
		break;
	default:break;
	}

}
void SportLayer::panelSportTopCallback(CCObject* pSender)
{
	UIWidget* pWidget = dynamic_cast<UIWidget*>(pSender);
	int widgetTag = pWidget->getWidgetTag();
	switch(widgetTag){
	case sportTopBackBtnTag:
		getPanelAt(panelSport)->setTouchEnable(true,true);
		hidePanelAt(panelSportTop);
		break;
	case sportTopPlayerNicknameBtnTag:
		break;
	case sportTopWinRateTagBtnTag:
		break;
	case sportTopWinCntTagBtnTag:
		break;
	case sportTopScoreTagBtnTag:
		break;
	default:break;
	}


}
void SportLayer::panelSportRuleCallback(CCObject* pSender)
{
	UIWidget* pWidget = dynamic_cast<UIWidget*>(pSender);
	int widgetTag = pWidget->getWidgetTag();
	switch(widgetTag){
	case sportRuleBackBtnTag:
		getPanelAt(panelSport)->setTouchEnable(true,true);
		hidePanelAt(panelSportRule);
		break;
	}
}
void SportLayer::panelSportCountdownCallback(CCObject* pSender)
{

}


void SportLayer::closeBtnCallBack( CCObject* pSender )
{
	m_Mediator->dispose();
}

void SportLayer::onEnter()
{
	CCLayer::onEnter();
	setTouchEnabled(true);
}

void SportLayer::registerWithTouchDispatcher( void )
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -190, true);
}

bool SportLayer::ccTouchBegan( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent )
{
	CCLog("ccTouchBegan");
	return true;
}

void SportLayer::ccTouchEnded( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent )
{
	CCLog("ccTouchEnded");
}

