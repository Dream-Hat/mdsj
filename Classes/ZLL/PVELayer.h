#ifndef __MDSJ_ZLL_PVELayer_H__
#define __MDSJ_ZLL_PVELayer_H__
#include "cocos2d.h"
#include "Define.h"

class CCMenuP;
class ScrollViewModel;
class PVEMediator;
class PVEUILayer;
class PVEMapLayer;
class PVELayer:public cocos2d::CCLayer
{

public:
	PVELayer();
	~PVELayer();
	virtual bool init();
	CREATE_FUNC(PVELayer);
	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);

	/*//监听Android返回事件
	virtual void keyBackClicked();
	virtual void keyMenuClicked();*/
protected:
	void initLayer();
public:
	PVEMediator* m_PVEMediator;
	PVEUILayer* m_UILayer;
	PVEMapLayer* m_MapLayer;
};

/*
 * PVE野外界面的UI层
 */
class PVEUILayer:public cocos2d::CCLayer
{
public:
	PVEUILayer();
	~PVEUILayer();
	virtual bool init();
	static PVEUILayer* create(int r);
	virtual void onEnter();
	//监听Android返回事件
	virtual void keyBackClicked();
	virtual void keyMenuClicked();
protected:
	void initLayer();
	void createDropList();
protected:
	void OnBtnGoBack(cocos2d::CCObject* sender);
	void OnBtnGoLeft(cocos2d::CCObject* sender);
	void OnBtnGoRight(cocos2d::CCObject* sender);
	void OnBtnOpenLevel(cocos2d::CCObject* sender);
	void OnBtnOpenPlaceNameScrollView(cocos2d::CCObject* sender);
	void OnBtnGotoTargetPage(cocos2d::CCObject* sender);
public:/*对外接口*/
	void setBtnsState(int page);
	void refreshDropListData();
protected:
	int m_Priority;
	bool m_MapCanMove;
	cocos2d::CCMenuItemSprite* m_BtnGoLeft;
	cocos2d::CCMenuItemSprite* m_BtnGoRight;
	cocos2d::CCSprite* m_DropListBackground;
	ScrollViewModel* m_PlaceViewModel;
	CCMenuP* m_DropListMenu;
	cocos2d::CCMenuItemSprite* m_BtnPlaceName;
	
public:
	void setMapCanMove(bool canmove){m_MapCanMove=canmove;}
	void setBtnLeftCanClick(bool canClick){m_BtnGoLeft->setEnabled(canClick);}
	void setBtnRightCanClick(bool canClick){m_BtnGoRight->setEnabled(canClick);}
};

/*
 * PVE地图层
 */
class PVEMapLayer:public cocos2d::CCLayer
{
public:
	PVEMapLayer();
	~PVEMapLayer();
	virtual bool init();
	static PVEMapLayer* create(int r);
	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
protected:
	void initLayer();
	void createRoute(cocos2d::CCSprite* sprite);
	void createRoute(cocos2d::CCSprite* sprite,int targetPage);
	void LayerMoveOver();
	void resetPosOver();
	void moveToTargetPageOver();
	void createANewPage(cocos2d::CCPoint point);
	cocos2d::CCSprite* createAPage(cocos2d::CCPoint point);
public:
	void gotoTargetPage(int page);//切换到指定页面
protected:
	void OnBtnEnterLevel(cocos2d::CCObject* sender);
protected:
	cocos2d::CCSprite* m_MainBackground;
	cocos2d::CCSprite* m_LeftBackground;
	cocos2d::CCSprite* m_RightBackground;
	cocos2d::CCSprite* m_TempBackground;

	cocos2d::CCArray* m_MoveToTargetPageArray;
protected:
	int m_MaxPage;
	int m_CurrentPage;
	int m_Priority;
	bool m_MoveTouchLeft;
	bool m_CanDragMap;
	cocos2d::CCPoint m_MapPos;
	cocos2d::CCPoint m_StartTouchPoint;
public:
	void setMaxPage(int maxPage){m_MaxPage=maxPage;}
	int getMaxPage(){return m_MaxPage;}
	void setCurrentPage(int currentPage){m_CurrentPage=currentPage;}
	int getCurrentPage(){return m_CurrentPage;}
};


/*
 * PVE关卡层
 */
class PVELevelLayer:public cocos2d::CCLayer
{
public:
	PVELevelLayer();
	~PVELevelLayer();
	static PVELevelLayer* create(int r,PVEFightType _fightType);
	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	//监听Android返回事件
	virtual void onEnter();
	virtual void keyBackClicked();
	virtual void keyMenuClicked();
protected:
	void initLayer();
	void createLevelMenu();
protected:
	void OnBtnGoBack(cocos2d::CCObject* sender);
	void OnBtnObserve(cocos2d::CCObject* sender);
	void OnBtnFight(cocos2d::CCObject* sender);
	void OnBtnFindTeam(cocos2d::CCObject* sender);
	void OnBtnCreateTeam(cocos2d::CCObject* sender);
protected:
	int m_Priority;
	PVEFightType m_PVEFightType;
protected://strength
	cocos2d::CCLabelTTF* m_LbRecommendLevel;//推荐等级
	cocos2d::CCLabelTTF* m_LbExpendStrength;//消耗体力
	cocos2d::CCLabelTTF* m_LbLimitTimes;	//次数限制
	cocos2d::CCLabelTTF* m_LbPlaceName;		//地点名称
	cocos2d::CCLabelTTF* m_LbExperience;	//经验值
	cocos2d::CCLabelTTF* m_LbGold;			//元宝
	cocos2d::CCLabelTTF* m_LbMoney;			//铜钱
	cocos2d::CCSprite* m_SpReward[6];		//6个奖品
};


/*
 * 游戏房间
 */
class PVEGameRoomLayer:public cocos2d::CCLayer
{
public:
	PVEGameRoomLayer();
	~PVEGameRoomLayer();
	static PVEGameRoomLayer* create(int r);
	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	//监听Android返回事件
	virtual void onEnter();
	virtual void keyBackClicked();
	virtual void keyMenuClicked();
	void initLayer();
protected:
	void createGameRoomMenu();
protected:
	void OnBtnGoBack(cocos2d::CCObject* sender);
	void OnBtnInvite(cocos2d::CCObject* sender);//邀请
	void OnBtnStartGame(cocos2d::CCObject* sender);
	void OnBtnSetReady(cocos2d::CCObject* sender);

protected:
	int m_Priority;

protected:
	cocos2d::CCLabelTTF* m_LbRoomName;
	cocos2d::CCSprite* m_SpMap;
};

/*
 * 战斗翻牌
 */
class PVEFlopLayer:public cocos2d::CCLayer
{
public:
	PVEFlopLayer();
	~PVEFlopLayer();
	virtual bool init();
	static PVEFlopLayer* create(int r);
	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);//监听Android返回事件
// 	virtual void keyBackClicked();
// 	virtual void keyMenuClicked();
protected:
	void initLayer();
	void createFlopMenu();
	void createCard();
protected:
	void OnBtnOK(cocos2d::CCObject* sender);

protected:
	int m_Priority;

protected:
	cocos2d::CCLabelTTF* m_LbFreeFlop;
	cocos2d::CCLabelTTF* m_LbGoldFlop;
};
#endif