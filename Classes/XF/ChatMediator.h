#pragma once

#include "cocos2d.h"
#include "cocos-ext.h"
#include "../ZMQ/GameDef.h"
#include "../ZMQ/MessageCenter.h"

USING_NS_CC;
USING_NS_CC_EXT;

class ChatMediator;
class ChatLayer : public CCLayer,public cocos2d::CCIMEDelegate
{
public:

	ChatMediator* m_Mediator;
	ChatLayer(){}
	~ChatLayer(){}
	CREATE_FUNC(ChatLayer);
	bool init();
	void keyBackClicked();
	virtual void onEnter();
	virtual void registerWithTouchDispatcher(void);
	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	cocos2d::CCPoint  m_beginPos;

private:
	void sendBtnCallBack(CCObject* pSender);
	void closeBtnCallBack(CCObject* pSender);
	void curBtnCallBack(CCObject* pSender);
	void menuBtnCallBack(CCObject* pSender);
	void keyPBtnCallBack(CCObject* pSender);


protected:
	UILayer* m_pUILayer;
	Layout* m_pLayout;
	UITextField* m_shuruK;
	UIScrollView* m_scro;
	UILabel* shurulable[12];
	int shuruNum;
	UITextButton* m_menuBtn[3];
};

class ChatMediator:public CCObject
{
	AutoPtr<ChatLayer> _scene;
public:
	ChatMediator();
	~ChatMediator();
	void OnPackage(short xy,char* pack,int len);
	void OnChatOpen(CCObject* sender,int msgid,cocos2d::CCObject* obj);
	void dispose();//πÿΩÁ√Ê

};

