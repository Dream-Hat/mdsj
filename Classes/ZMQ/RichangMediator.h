#pragma once

#include "cocos2d.h"
#include "cocos-ext.h"
#include "GameDef.h"
#include "MessageCenter.h"


#define SHOP_LAYOUT_TAG_ROOT							    1000
#define SHOP_LAYOUT_TAG_EQUIP                              1001
#define SHOP_LAYOUT_TAG_TEJIA								1002
#define SHOP_LAYOUT_TAG_DIAMOND						    1003
#define SHOP_LAYOUT_TAG_YAOSHUI                            1004
#define SHOP_LAYOUT_TAG_OTHER								   1005

USING_NS_CC;
USING_NS_CC_EXT;

class RichangMediator;
class RichangLayer : public CCLayer,public cocos2d::CCIMEDelegate
{
public:
	RichangMediator* m_Mediator;
	RichangLayer(){}
	~RichangLayer(){}

	bool init();

	void keyBackClicked();
	virtual void onEnter();
	virtual void registerWithTouchDispatcher(void);
	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	cocos2d::CCPoint  m_beginPos;

	CREATE_FUNC(RichangLayer);


private:
	void buyBtnCallBack(CCObject* pSender);
	void closeBtnCallBack(CCObject* pSender);
	void curBtnCallBack(CCObject* pSender);
	void scroCallBack(CCObject* pSender);
	void tapMenuCallBack(CCObject* pSender);
	void closeBtnCallBack1(CCObject* pSender);


protected:
	UILayer* m_pUILayer;
	Layout* m_pLayout;
};

class RichangMediator:public CCObject
{
	AutoPtr<RichangLayer> _scene;
public:
	RichangMediator();
	~RichangMediator();
	void OnPackage(short xy,char* pack,int len);
	void OnRichangOpen(CCObject* sender,int msgid,cocos2d::CCObject* obj);
	void dispose();//πÿΩÁ√Ê

};