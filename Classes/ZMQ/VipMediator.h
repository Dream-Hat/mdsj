#pragma once

#include "cocos2d.h"
#include "cocos-ext.h"
#include "GameDef.h"
#include "MessageCenter.h"


#define VIPLAYER_TAG									   500
#define VIPLAYER_TAG_LAYER							VIPLAYER_TAG+1
#define VIPLAYER_TAG_XX								VIPLAYER_TAG+2
#define VIPLAYER_TAG_OPEN							VIPLAYER_TAG+3

USING_NS_CC;
USING_NS_CC_EXT;

class VipMediator;
class VipLayer : public CCLayer
{
public:
	VipMediator* m_Mediator;
	VipLayer(){ m_pUILayer=NULL;m_layerLayout=NULL;m_openLayout=NULL;m_xxLayout=NULL;}
	~VipLayer(){}

	bool init();

	void keyBackClicked();
	virtual void onEnter();
	virtual void registerWithTouchDispatcher(void);
	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);

	CREATE_FUNC(VipLayer);


private:
	void scroCallBack(CCObject* pSender);
	void closeBtnCallBack(CCObject* pSender);
	void openBtnCallBack(CCObject* pSender);
	void xxBtnCallBack(CCObject* pSender);


protected:
	UILayer* m_pUILayer;
	Layout* m_layerLayout;
	Layout* m_openLayout;
	Layout* m_xxLayout;

	int layerNum;
};

class VipMediator:public CCObject
{
	AutoPtr<VipLayer> _scene;
public:
	VipMediator();
	~VipMediator();
	void OnPackage(short xy,char* pack,int len);
	void OnVipOpen(CCObject* sender,int msgid,cocos2d::CCObject* obj);
	void dispose();//πÿΩÁ√Ê

};