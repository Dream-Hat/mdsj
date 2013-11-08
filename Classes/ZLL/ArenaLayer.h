#ifndef __MDSJ_ZLL_ARENALAYER_H__
#define __MDSJ_ZLL_ARENALAYER_H__

#include "cocos2d.h"
class ScrollViewModel;
class ArenaMediator;
class CCMenuP;
class INIParser;

#include "proto_files/AthleticProto.pb.h"


#define FINDPLAYERTAG 10		//查找玩家界面Tag
#define GAMEMODETAG 11			//游戏模式选择界面Tag
#define FINDGAMEROOMTAG 12
#define CREATEGAMEROOMTAG 13
#define GAMEROOMTAG 14
#define YAOQINGTAG  16
#define FIGHTTOOLSVIEWTAG 17
#define SOULVIEWTAG 18
#define SELECTMAPTAG 19
//竞技场界面
class ArenaLayer:public cocos2d::CCLayer
{
public:
	ArenaLayer();
	~ArenaLayer();
	virtual bool init();
	CREATE_FUNC(ArenaLayer);
	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);

	//监听Android返回按钮
	virtual void onEnter();
	virtual void keyBackClicked();
	virtual void keyMenuClicked();

	void setLayerKeyPad(int endTag);
	void refreshModeList(com::tiange::mdsj::proto::ModeListResponse &_modeList);
protected:
	void initLayer();
	void createModeSelectView();
	void createModeSelectMenu();
	void createMenu();

	void OnRefreshGameModeData();
protected:
	void OnBtnGOBack(cocos2d::CCObject* sender);
	void OnBtnRandomJoin(cocos2d::CCObject* sender);
	void OnBtnFindRoom(cocos2d::CCObject* sender);
	void OnBtnCreateRoom(cocos2d::CCObject* sender);
	void OnBtnFindPlayer(cocos2d::CCObject* sender);
public:
	ArenaMediator* m_ArenaMadiator;
	CCMenuP* m_GameRoomMenu;
protected:
	ScrollViewModel* m_ScrollView;
	INIParser* m_iniParser;
};

//游戏模式选择界面
class ArenaModeRoom:public cocos2d::CCLayer
{
public:
	ArenaModeRoom();
	~ArenaModeRoom();
	virtual bool init();
	static ArenaModeRoom* create(int r);
	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	//监听Android返回按钮
	virtual void onEnter();
	virtual void keyBackClicked();
	virtual void keyMenuClicked();
protected:
	void initLayer();
	void createModeSelectView();
	void createMenu();
	void OnRefreshGameRoomsData();
protected:
	void OnBtnGoBack(cocos2d::CCObject* sender);
	void OnBtnRandomJoin(cocos2d::CCObject* sender);
	void OnBtnFindRoom(cocos2d::CCObject* sender);
	void OnBtnCreateRoom(cocos2d::CCObject* sender);

public:
	int m_Priority;
	ScrollViewModel* m_ScrollView;
};

//游戏房间界面
class ArenaGameRoom:public cocos2d::CCLayer
{
public:
	ArenaGameRoom();
	~ArenaGameRoom();
	virtual bool init();
	static ArenaGameRoom* create(int r);
	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	//监听Android返回按钮
	virtual void onEnter();
	virtual void keyBackClicked();
	virtual void keyMenuClicked();
protected:
	void initLayer();
	void createGameRoomMenu();
protected:
	void OnBtnGoBack(cocos2d::CCObject* sender);
	void OnBtnInvite(cocos2d::CCObject* sender);
	void OnBtnFightTools(cocos2d::CCObject* sender);
	void OnBtnSetReady(cocos2d::CCObject* sender);
	void OnBtnSetSoul(cocos2d::CCObject* sender);
	void OnBtnSelectMap(cocos2d::CCObject* sender);

public:
	void RefreshTeamData();
protected:
	cocos2d::CCLabelTTF* m_LbRoomID;
	cocos2d::CCSprite* m_SpMap;
	int m_Priority;
};
#endif