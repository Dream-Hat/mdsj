#ifndef __MDSJ_ZLL_FIGHTLAYER_H__
#define __MDSJ_ZLL_FIGHTLAYER_H__
#include "cocos2d.h"
#include "FightNode.h"
#include "CMyContact.h"
#include "GLES-Render.h"
#include "Box2D/Box2D.h"
#include "FightNode.h"
#define FIGHTLAYER_EFFECT 5		//战斗特效层
#define FIGHTLAYER_TIPLAYER 6   //战斗信息提示层
#define FIGHTLAYER_ICONLAYER 7	//图标层
#define FIGHTLAYER_UILAYER 10	//战斗UI层

class FightMediator;
class FightMainLayer;
class FightUILayer;
class FightIconLayer;
class FightEffectLayer;
class FightTipLayer;
/*
 * 战斗界面层
 * 战斗界面层包含5个层次
 * 战斗层 1
 * 特效层5
 * 提示信息层 6
 * 界面图标层 7
 * UI层 10
 */
class FightLayer:public cocos2d::CCLayerColor
{
public:
	FightLayer();
	~FightLayer();
	static FightLayer* create(int r);
	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	void DrawLocusMask(cocos2d::CCPoint point);
	void HideLocusMask();

	//通知客户端
	void NotifyMsg(char* _msg,int _value);
	void NotifyMsg(char* _msg);
	void NotifyElementAct(int _turnID);
	void checkLayerMovingBouding(cocos2d::CCPoint &endPoint);
	void setMainLayerPosition(cocos2d::CCPoint endPoint);
	void setViewToNextPlayer(int nextPlayerID);

	void showTip(cocos2d::CCPoint _showPos,FightTipType _type,int _value=0);
	void changeViewToNextPlayer();
protected:
	void initLayer();
	void panForTranslation(cocos2d::CCPoint transitonPoint);
	void checkLayerMovingBouding(cocos2d::CCPoint transitionPoint,cocos2d::CCPoint &endPont);
	void checkWorldFrameBox(cocos2d::CCPoint &_point);
public:
	FightMediator* m_FightMediator;
	FightMainLayer* m_MainLayer;
	FightEffectLayer* m_EffectLayer;
	FightTipLayer* m_TipLayer;
	FightIconLayer*  m_IconLayer;
	FightUILayer* m_UILayer;
	int m_Priority;
	cocos2d::CCSize m_MapContentSize;

	float m_MaxLayerMoveX;
	float m_MaxLayerMoveY;
	float m_MinLayerMoveX;
	float m_MinLayerMoveY;
};

/*
 * 战斗主界面
 */
class FightMainLayer:public cocos2d::CCLayer
{
public:
	FightMainLayer();
	~FightMainLayer();
	virtual bool init();
	static FightMainLayer* create(int r);
	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	void update(float dt);
	void draw();

public:
	void addPlayer(FightElementDataNode& _node);
	void notifyElementAct(int _turnID);
	cocos2d::CCPoint findTargetPlayerPosInParent(int turnIndex);
	void showTip(cocos2d::CCPoint _showPoint,FightTipType _type,int _value=0);
protected:
	void initLayer();
	void checkMapSize();
	void createWorld();
	b2Body* createPlayerBody(FightElementNode* _node);
	b2Body* createBullet(cocos2d::CCPoint point);
	b2Body* createCopyBullet(cocos2d::CCPoint point);
protected:
	//检查是否点击在玩家身上
	bool checkTouchInElement(FightElementNode* _node,cocos2d::CCPoint _point);
	//获取模拟子弹的轨迹坐标
	void setCopyPosPoint();

	bool checkCanPushBackDestoryList(std::vector<b2Body*> _destroyList,b2Body* _body);
	
	void checkFightResult(FightElementNode* _node);

	void bulletTick(float dt);

	void CallBack_ObjRemoveFromParent(cocos2d::CCNode* sender);
public:
	FightMediator* m_FightMediator;
	std::vector<cocos2d::CCPoint> m_CopyPointList;
protected:
	int m_Priority;
	float m_BulletHeight;
	cocos2d::CCArray* m_FightElementDic;
	cocos2d::CCSize m_MapSize;
	cocos2d::CCPoint m_LeftDownPoint;
	cocos2d::CCPoint m_RightTopPoint;
	FightElementNode* m_CurrentSelectElement;
	cocos2d::CCPoint m_LastFrameBulletPos;
protected:
	b2World* m_b2World;
	b2Body* m_WorldBody;
	GLESDebugDraw *debugDraw;
	CMyContactListener* m_ContactListener;
	b2Body* m_CopyBullet;
public:
	bool m_CanAtk;
	int m_MinDistance;
	int m_MaxDistance;
	bool m_GameStarted;
	
	//int m_TurnIndex;//当前轮到哪位玩家行动
public:
	cocos2d::CCSize getLayerContentSize(){return m_MapSize;}
};

/*
 * 战斗界面UI层
 */
class FightUILayer:public cocos2d::CCLayer
{
public:
	FightUILayer();
	~FightUILayer();
	virtual bool init();
	static FightUILayer* create(int r);
	virtual void onEnter();
	virtual void keyBackClicked();
	virtual void keyMenuClicked();
	void setNextPlayerView();
protected:
	void initLayer();
protected:
	void OnBtnExit(cocos2d::CCObject* sender);
	void OnBtnOpenChat(cocos2d::CCObject* sender);
	void OnBtnUseSoul(cocos2d::CCObject* sender);
	void OnBtnUseTools(cocos2d::CCObject* sender);
	void OnBtnViewToNextPlayer(cocos2d::CCObject* sender);
protected:
	int m_Priority;
	cocos2d::CCMenuItemSprite* m_BtnSoul[4];
	cocos2d::CCMenuItemSprite* m_BtnTools[4];

public:
	cocos2d::CCMenuItemSprite* mBtnViewToNextPlayer;
};

/*
 * 图标层
 */
class FightIconLayer:public cocos2d::CCLayer
{
public:
	FightIconLayer();
	~FightIconLayer();
	virtual bool init();
	CREATE_FUNC(FightIconLayer);
protected:
	void initLayer();
protected:
	cocos2d::CCLabelAtlas* m_LbTime;
};

/*
 * 特效层
 */
class FightEffectLayer:public cocos2d::CCLayer
{
public:
	FightEffectLayer();
	~FightEffectLayer();
	virtual bool init();
	CREATE_FUNC(FightEffectLayer);
	virtual void draw();
protected:
	void initLayer();
public:
	FightMediator* mFightMediator;
};

/*
 * 提示信息层
 */
class FightTipLayer:public cocos2d::CCLayer
{
public:
	FightTipLayer();
	~FightTipLayer();
	virtual bool init();
	CREATE_FUNC(FightTipLayer);
	
protected:
	void initLayer();
	void showMsgOver(cocos2d::CCObject* obj);
	void CallBack_ObjRemoveFromParent(cocos2d::CCNode* sender);
public:
	void showMsg(char* msg);

	//提示战斗信息，如扣血，闪避等
	void showTip(cocos2d::CCPoint _showPoint,FightTipType _type,int _value=0);
};
#endif