#pragma once

#include "cocos2d.h"
#include "cocos-ext.h"
#include "GameDef.h"
#include "MessageCenter.h"

#define SHIWUSUOLAYER_TAG									   500
#define SHIWUSUOLAYER_TAG_LAYER							SHIWUSUOLAYER_TAG+1
#define SHIWUSUOLAYER_TAG_XX							SHIWUSUOLAYER_TAG+2

USING_NS_CC;
USING_NS_CC_EXT;

class ZhujueMediator;
class ZhujueLayer : public CCLayer
{
public:
	ZhujueMediator* m_Mediator;
	ZhujueLayer(){ m_pUILayer=NULL;m_layerLayout=NULL;}
	~ZhujueLayer(){}

	bool init();

	
	void keyBackClicked();
	virtual void onEnter();
	virtual void registerWithTouchDispatcher(void);
	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	cocos2d::CCPoint  m_beginPos;

	CREATE_FUNC(ZhujueLayer);


private:
	void yesBtnCallBack(CCObject* pSender);
	void closeBtnCallBack(CCObject* pSender);


protected:
	UILayer* m_pUILayer;
	Layout* m_layerLayout;

	int layerNum;

};

class ZhujueMediator:public CCObject
{
	AutoPtr<ZhujueLayer> _scene;
public:
	ZhujueMediator();
	~ZhujueMediator();
	void OnPackage(short xy,char* pack,int len);
	void OnZhujueOpen(CCObject* sender,int msgid,cocos2d::CCObject* obj);
	void dispose();//πÿΩÁ√Ê
};
