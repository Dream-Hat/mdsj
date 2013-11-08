#pragma once

#include "cocos2d.h"
#include "cocos-ext.h"
#include "ZMQ/GameDef.h"
#include "ZMQ/MessageCenter.h"

USING_NS_CC;
USING_NS_CC_EXT;

class SportMediator;
class SportLayer : public CCLayer
{
public:

	SportMediator* m_Mediator;
	SportLayer(){}
	~SportLayer(){}
	CREATE_FUNC(SportLayer);
	bool init();
	virtual void onEnter();
	virtual void onExit();
	virtual void registerWithTouchDispatcher(void);
	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);

protected:
	enum PanelType{
		panelSport = 0,
		panelSportFriend,
		panelSportTop,
		panelSportRule,
		panelSportCountdown
	};
	enum ListItemType{
		friendListItem = 0,
		topListItem
	};
	enum PanelSportTag{
		sportStartBtnTag = 10,
		sportTopBtnTag,
		sportRuleBtnTag,
		sportClearBtnTag,
		sportPlayerSeatInivteBtnTag,
		sportRewardObtainBtnTag,
		sportBackBtnTag,
	};
	enum PanelSportRuleTag{
		sportRuleBackBtnTag = 20,
	};
	enum PanelSportTopTag{
		sportTopBackBtnTag = 30,
		sportTopPlayerNicknameBtnTag,
		sportTopWinRateTagBtnTag,
		sportTopWinCntTagBtnTag,
		sportTopScoreTagBtnTag,
	};
	enum PanelSportFriendTag{
		sportFriendOLPlayerTagBtnTag = 40,
		sportFriendClubTagBtnTag,
		sportFriendBackBtnTag,
		sportFriendFriendTagBtnTag,
	};
	void panelSportCallback(CCObject* pSender);
	void panelSportFriendCallback(CCObject* pSender);
	void panelSportTopCallback(CCObject* pSender);
	void panelSportRuleCallback(CCObject* pSender);
	void panelSportCountdownCallback(CCObject* pSender);
	void connectCallback4Target(void* data ,void* route);

private:
	bool initUI();
	bool initWidgets4PanelSport(Layout* _sportLay);
	bool initWidgets4PanelSportFriend(Layout* _sportFriendLay);
	bool initWidgets4PanelSportTop(Layout* _sportTopLay);
	bool initWidgets4PanelSportRule(Layout* _sportRuleLay);
	bool initWidgets4PanelSportCountdown(Layout* _sportCountdownLay);
	bool initPanelSportByType(Layout* _lay, PanelType _type);

	void closeBtnCallBack(CCObject* pSender);
	void showPanelAt(PanelType _index);
	void hidePanelAt(PanelType _index);
	void hideAllPanels();
	void comeupPanelFromParent(PanelType _parentIndex, PanelType _subIndex);
	void sinkPanelFromParent(PanelType _parentIndex, PanelType _subIndex);
	Layout* getPanelAt(PanelType _index);
private:
	UILayer* m_pUILayer;
	CCDictionary* m_allPanelNames;
	CCDictionary* m_allListItemNames;
};

class SportMediator:public CCObject
{
	AutoPtr<SportLayer> _scene;
public:
	SportMediator();
	~SportMediator();
	void OnPackage( int xy,void* pack);
	void OnSportOpen(CCObject* sender,int msgid,cocos2d::CCObject* obj);
	void dispose();//πÿΩÁ√Ê
};

