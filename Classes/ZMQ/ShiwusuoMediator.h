#pragma once

#include "cocos2d.h"
#include "cocos-ext.h"
#include "GameDef.h"
#include "MessageCenter.h"

typedef enum
{
	SHIWUSUOLAYER_TAG_LAYER,
	SHIWUSUOLAYER_TAG_XX
}SWSLayerType;

USING_NS_CC;
USING_NS_CC_EXT;

class ShiwusuoMediator;
class ShiwusuoLayer : public CCLayer
{
public:
	ShiwusuoMediator* m_Mediator;
	ShiwusuoLayer(){ m_pUILayer=NULL;m_xxLayout=NULL;m_layerLayout=NULL;}
	~ShiwusuoLayer(){}

	bool init();

	void keyBackClicked();
	virtual void onEnter();
	virtual void registerWithTouchDispatcher(void);
	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	cocos2d::CCPoint  m_beginPos;

	CREATE_FUNC(ShiwusuoLayer);


private:
	void yesBtnCallBack(CCObject* pSender);
	void closeBtnCallBack(CCObject* pSender);
	void scroCallBack(CCObject* pSender);


protected:
	UILayer* m_pUILayer;
	Layout* m_xxLayout;
	Layout* m_layerLayout;

	SWSLayerType layerNum;
};

class ShiwusuoMediator:public CCObject
{
	AutoPtr<ShiwusuoLayer> _scene;
public:
	ShiwusuoMediator();
	~ShiwusuoMediator();
	void OnPackage(short xy,char* pack,int len);
	void OnShiwusuoOpen(CCObject* sender,int msgid,cocos2d::CCObject* obj);
	void dispose();//πÿΩÁ√Ê
};