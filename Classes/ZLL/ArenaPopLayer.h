#ifndef __MDSJ_ZLL_ARENAPOPLAYER_H__
#define __MDSJ_ZLL_ARENAPOPLAYER_H__
#include "cocos2d.h"
class ScrollViewModel;
//查找玩家界面
class ArenaFindPlayer:public cocos2d::CCLayerColor,public cocos2d::CCIMEDelegate
{
public:
	ArenaFindPlayer();
	static ArenaFindPlayer* create(int r);
	void initLayer();
	virtual void onEnter();
	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void keyBackClicked();
	virtual void keyMenuClicked();
protected:
	void createMenu();
protected:
	void OnBtnOk(cocos2d::CCObject* sender);
	void OnBtnCanCel(cocos2d::CCObject* sender);
public:
	int m_Priority;
protected:
	cocos2d::CCTextFieldTTF* m_InputPlayerName;
	cocos2d::CCPoint m_beginPos;
};

//创建房间界面
class ArenaCreateRoom:public cocos2d::CCLayerColor,public cocos2d::CCIMEDelegate
{
public:
	ArenaCreateRoom();
	static ArenaCreateRoom* create(int r);//带触摸优先级
	void initLayer();

	virtual void onEnter();
	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void keyBackClicked();
	virtual void keyMenuClicked();
protected:
	void createLayerMenu();
protected:
	void OnBtn1V1(cocos2d::CCObject* sender);
	void OnBtn2V2(cocos2d::CCObject* sender);
	void OnBtnRandom(cocos2d::CCObject* sender);
	void OnBtnFreedom(cocos2d::CCObject* sender);
	void OnBtnOk(cocos2d::CCObject* sender);
	void OnBtnCancel(cocos2d::CCObject* sender);
public:
	int m_Priority;

protected:
	cocos2d::CCTextFieldTTF* m_RoomName;
	cocos2d::CCTextFieldTTF* m_RoomPassword;

	cocos2d::CCMenuItemSprite* m_Btn1V1;
	cocos2d::CCMenuItemSprite* m_Btn2V2;
	cocos2d::CCMenuItemSprite* m_BtnRandom;
	cocos2d::CCMenuItemSprite* m_BtnFreedom;
	cocos2d::CCMenuItemSprite* m_BtnOK;
	cocos2d::CCMenuItemSprite* m_BtnCancel;

	cocos2d::CCPoint m_beginPos;
};

//查找房间界面
class ArenaFindRoom:public cocos2d::CCLayerColor,public cocos2d::CCIMEDelegate
{
public:
	ArenaFindRoom();
	static ArenaFindRoom* create(int r);
	void initLayer();
	virtual void onEnter();
	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void keyBackClicked();
	virtual void keyMenuClicked();
protected:
	void createMenu();
protected:
	void OnBtnOk(cocos2d::CCObject* sender);
	void OnBtnCanCel(cocos2d::CCObject* sender);
public:
	int m_Priority;
protected:
	cocos2d::CCTextFieldTTF* m_InputPlayerName;
	cocos2d::CCPoint m_beginPos;
};

//竞技场魂魄界面
class ArenaSoulView:public cocos2d::CCLayerColor
{
public:
	ArenaSoulView();
	~ArenaSoulView();
	static ArenaSoulView* create(int r);
	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	void initLayer();
	virtual void onEnter();
	virtual void keyBackClicked();
	virtual void keyMenuClicked();
protected:
	void createSoulMenu();
	void createScrollView();
protected:
	void OnBtnGoBack(cocos2d::CCObject* sender);
protected:
	cocos2d::CCSprite* m_SpPlayerHeader;
	cocos2d::CCLabelTTF* m_LbPlayerName;
	cocos2d::CCLabelTTF* m_LbPlayerLevel;
	cocos2d::CCLabelTTF* m_LbPlayerPower;
public:
	int m_Priority;
};

//选择地图界面
class ArenaSelectMap:public cocos2d::CCLayerColor
{
public:
	ArenaSelectMap();
	~ArenaSelectMap();
	static ArenaSelectMap* create(int r);
	void initLayer();
	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void onEnter();
	virtual void keyBackClicked();
	virtual void keyMenuClicked();
protected:
	void createSelectMapMenu();
	void createScrollView();
protected:
	void OnBtnGoBack(cocos2d::CCObject* sender);
protected:
	int m_Priority;
};


//邀请队友界面
class ArenaInviteView:public cocos2d::CCLayerColor
{
public:
	ArenaInviteView();
	~ArenaInviteView();
	static ArenaInviteView* create(int r);
	void initLayer();
	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void onEnter();
	virtual void keyBackClicked();
	virtual void keyMenuClicked();
protected:
	void createInviteMenu();
	void createScrollView();
protected:
	void OnBtnGoBack(cocos2d::CCObject* sender);
	void OnBtnFriend(cocos2d::CCObject* sender);
	void OnBtnSocieties(cocos2d::CCObject* sender);	
	void OnBtnPlayerOnline(cocos2d::CCObject* sender);
protected:
	int m_Priority;
protected:
	ScrollViewModel* m_ScrollView;
};

class ArenaBagView:public cocos2d::CCLayerColor
{
public:
	ArenaBagView();
	~ArenaBagView();
	static ArenaBagView* create(int r);
	void initLayer();
	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void onEnter();
	virtual void keyBackClicked();
	virtual void keyMenuClicked();
protected:
	void createBagMenu();
	void createScrollView();
protected:
	void OnBtnGoBack(cocos2d::CCObject* sender);
	void OnBtnSwitchShopView(cocos2d::CCObject* sender);
	void OnBtnSwitchBagView(cocos2d::CCObject* sender);
protected:
	int m_Priority;
protected:
	ScrollViewModel* m_ScrollView;
};
#endif