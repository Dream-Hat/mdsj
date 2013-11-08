#pragma once

#include "cocos2d.h"
#include "cocos-ext.h"
#include "GameDef.h"
#include "MessageCenter.h"


#define MAILLAYER_TAG									   500
#define MAILLAYER_TAG_MAIL							MAILLAYER_TAG+1
#define MAILLAYER_TAG_FUJIAN						MAILLAYER_TAG+2
#define MAILLAYER_TAG_WRITE							MAILLAYER_TAG+3
#define MAILLAYER_TAG_RECEIVE						MAILLAYER_TAG+4

USING_NS_CC;
USING_NS_CC_EXT;

class MailMediator;
class MailLayer : public CCLayer
{
public:
	MailMediator* m_Mediator;
	MailLayer(){m_pUILayer=NULL;m_writeLayout=NULL;m_mailLayout=NULL;m_fujianLayout=NULL;}
	~MailLayer(){}

	bool init();

	void keyBackClicked();
	virtual void onEnter();
	virtual void registerWithTouchDispatcher(void);
	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	cocos2d::CCPoint  m_beginPos;

	CREATE_FUNC(MailLayer);


private:
	void leftBtnCallBack(CCObject* pSender);
	void closeBtnCallBack(CCObject* pSender);
	void scroCallBack(CCObject* pSender);
	void rightBtnCallBack(CCObject* pSender);
	void writeBtnCallBack(CCObject* pSender);
	void fujianBtnCallBack(CCObject* pSender);
	void updateLayer();


protected:
	UILayer* m_pUILayer;
	Layout* m_writeLayout;
	Layout* m_fujianLayout;
	Layout* m_mailLayout;

	int layerNum;
	UITextButton* m_leftBtn;
	UITextButton* m_rightBtn;
};

class MailMediator:public CCObject
{
	AutoPtr<MailLayer> _scene;
public:
	MailMediator();
	~MailMediator();
	void OnPackage(short xy,char* pack,int len);
	void OnMailOpen(CCObject* sender,int msgid,cocos2d::CCObject* obj);
	void dispose();//πÿΩÁ√Ê

};
