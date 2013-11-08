#ifndef __SceneCoverMediator_H__
#define __SceneCoverMediator_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "GameDef.h"
#include "MessageCenter.h"

USING_NS_CC;
USING_NS_CC_EXT;
#include "SimpleAudioEngine.h"

class SceneCoverMediator;
class SceneCover : public cocos2d::CCLayer
{
public:
	SceneCoverMediator* m_Mediator;
	SceneCover(){}
	~SceneCover(){}
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();

	//static void show();
	void keyBackClicked();
	//static void show();
	void foo();
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
	void callbackMenu(CCObject* pSender);
	void callbackMenuChat(CCObject* pSender);
	void callbackMenuFriend(CCObject* pSender);
	void callbackMenuMail(CCObject* pSender);
	void callbackMenuPacksack(CCObject* pSender);
	void callbackMenuRichang(CCObject* pSender);
	void callbackMenuSetting(CCObject* pSender);
	void callbackMenuSoul(CCObject* pSender);
	void callbackMenuTask(CCObject* pSender);
	void callbackMenuZhujue(CCObject* pSender);
	void callbackMenuVIP(CCObject* pSender);
	void callbackClub(CCObject* pSender);
	void callbackYewai(CCObject* pSender);
	void callbackJingjichang(CCObject* pSender);
	void callbackShiwusuo(CCObject* pSender);
	void callbackShop(CCObject* pSender);
	void callbackSoul(CCObject* pSender);
	void callbackTiejiangpu(CCObject* pSender);
	void callbackMenuSport(CCObject* pSender);
	void createArrayByPlist();

	void setBtnVis(bool isVis);


    // implement the "static node()" method manually
    CREATE_FUNC(SceneCover);
	void stst();
	void showKatoon();//播放动画
	void callback11();



protected:
	cocos2d::CCArray* mKTArrays;
	cocos2d::CCAnimate* m_Aimate;

	UILayer* m_pUILayer;
	Layout* m_pLayout;
	bool m_isvis;
};

class SceneCoverMediator:public CCObject
{
	AutoPtr<SceneCover> _scene;
public:
	SceneCoverMediator();
	~SceneCoverMediator();
	void OnPackage(short xy,char* pack,int len);
	void OnSceneCoverOpen(CCObject* sender,int msgid,cocos2d::CCObject* obj);
	void dispose();//关界面
};
#endif  // __SceneCover_H__