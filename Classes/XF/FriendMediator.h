#pragma once

#include "cocos2d.h"
#include "cocos-ext.h"
#include "../ZMQ/GameDef.h"
#include "../ZMQ/MessageCenter.h"


#define SHOP_LAYOUT_TAG_ROOT							    1000
#define SHOP_LAYOUT_TAG_EQUIP                              1001
#define SHOP_LAYOUT_TAG_TEJIA								1002
#define SHOP_LAYOUT_TAG_DIAMOND						    1003
#define SHOP_LAYOUT_TAG_YAOSHUI                            1004
#define SHOP_LAYOUT_TAG_OTHER								   1005

	
#define FRIENDLAYER_TAG									   500
#define FRIENDLAYER_TAG_LAYER							FRIENDLAYER_TAG+1
#define FRIENDLAYER_TAG_SEARCH						FRIENDLAYER_TAG+2
#define FRIENDLAYER_TAG_TIPS							FRIENDLAYER_TAG+3
#define FRIENDLAYER_TAG_NEIRONG						FRIENDLAYER_TAG+4
#define FRIENDLAYER_TAG_YAOQING						FRIENDLAYER_TAG+5

USING_NS_CC;
USING_NS_CC_EXT;

class FriendMediator;
class FriendLayer : public CCLayer,public cocos2d::CCIMEDelegate
{
public:
	FriendMediator* m_Mediator;
	FriendLayer(){m_pUILayer=NULL;m_pLayout=NULL;m_tipsLayout=NULL;m_layerLayout=NULL;}
	~FriendLayer(){}

	bool init();

	void keyBackClicked();
	virtual void onEnter();
	virtual void registerWithTouchDispatcher(void);
	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	cocos2d::CCPoint  m_beginPos;

	CREATE_FUNC(FriendLayer);


private:
	void yesBtnCallBack(CCObject* pSender);
	void closeBtnCallBack(CCObject* pSender);
	void noBtnCallBack(CCObject* pSender);
	void scroCallBack(CCObject* pSender);
	void tapMenuCallBack(CCObject* pSender);
	void writeBtnCallBack(CCObject* pSender);
	void delBtnCallBack(CCObject* pSender);
	void updateLayer(int num);
protected:
	UILayer* m_pUILayer;
	Layout* m_pLayout;
	Layout* m_tipsLayout;
	Layout* m_layerLayout;

	int layerNum;

	UITextButton* m_yesBtn;  //过程中会替换文字,下同
	UITextButton* m_noBtn;
	UITextButton* m_writeBtn;
	UITextButton* m_delBtn;
	UITextButton* m_topBtn[3];
};

class FriendMediator:public CCObject
{
	AutoPtr<FriendLayer> _scene;
public:
	FriendMediator();
	~FriendMediator();
	void OnPackage(short xy,char* pack,int len);
	void OnFriendOpen(CCObject* sender,int msgid,cocos2d::CCObject* obj);
	void dispose();//关界面

};
