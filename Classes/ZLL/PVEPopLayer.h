#ifndef __MDSJ_ZLL_PVEPOPLAYER_H__
#define __MDSJ_ZLL_PVEPOPLAYER_H__
#include "cocos2d.h"

class ScrollViewModel;

/*
 * 观战列表
 */
class ObserveLayer:public cocos2d::CCLayerColor
{
public:
	ObserveLayer();
	~ObserveLayer();
	static ObserveLayer* create(int r);
	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	void initLayer();
protected:
	void createMenu();
protected:
	void OnBtnGoBack(cocos2d::CCObject* sender);
	void OnBtnFight(cocos2d::CCObject* sender);
	void OnBtnObserve(cocos2d::CCObject* sender);
protected:
	int m_Priority;
};

/*
 * 创建队伍
 */
class CreateTeamLayer:public cocos2d::CCLayerColor
{
public:
	CreateTeamLayer();
	~CreateTeamLayer();
	static CreateTeamLayer* create(int r);
	virtual void onEnter();
	virtual void keyBackClicked();
	virtual void keyMenuClicked();
	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	void initLayer();
protected:
	void createMenu();
protected:
	void OnBtnGoback(cocos2d::CCObject* sender);
	void OnBtnCreate(cocos2d::CCObject* sender);
protected:
	int m_Priority;
protected:
	cocos2d::CCTextFieldTTF* m_TeamName;
	cocos2d::CCTextFieldTTF* m_TeamPassword;
	cocos2d::CCPoint m_beginPos;
};
#endif

/*
 * 查找队伍界面
 */
class FindTeamLayer:public cocos2d::CCLayerColor
{
public:
	FindTeamLayer();
	~FindTeamLayer();
	static FindTeamLayer* create(int r);
	virtual void onEnter();
	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void keyBackClicked();
	virtual void keyMenuClicked();
	void initLayer();
protected:
	void createMenu();
	void createScrollView();
protected:
	void OnBtnGoback(cocos2d::CCObject* sender);
	void OnBtnSearch(cocos2d::CCObject* sender);
	void OnBtnJoin(cocos2d::CCObject* sender);

protected:
	int m_Priority;
protected:
	cocos2d::CCTextFieldTTF* m_TeadID;
	cocos2d::CCPoint m_beginPos;
protected:
	ScrollViewModel* m_ScrollView;

};

/*
 * 查找队伍结果界面
 */
class SearchTeamResultLayer:public cocos2d::CCLayerColor
{
public:
	SearchTeamResultLayer();
	~SearchTeamResultLayer();
	static SearchTeamResultLayer* create(int r);
	virtual void onEnter();
	virtual void keyBackClicked();
	virtual void keyMenuClicked();
	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	void initLayer();
protected:
	void createMenu();
protected:
	void OnBtnCancel(cocos2d::CCObject* sender);
	void OnBtnJoin(cocos2d::CCObject* sender);
protected:
	int m_Priority;
protected:
	cocos2d::CCLabelTTF* m_LbTeamID;
	cocos2d::CCLabelTTF* m_LbTeamName;
	cocos2d::CCLabelTTF* m_LbPlayerNum;
};

/*
 * 战斗结束结果界面
 */
class PVEFightResultLayer:public cocos2d::CCLayer
{
public:
	PVEFightResultLayer();
	~PVEFightResultLayer();
	virtual bool init();
	static PVEFightResultLayer* create(int r);
	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
protected:
	void initLayer();
	void createLayerMenu();
protected:
	void OnBtnGoBack(cocos2d::CCObject* sender);
protected:
	int m_Priority;
};
