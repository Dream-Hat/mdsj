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

USING_NS_CC;
USING_NS_CC_EXT;

class ShopMediator;
class ShopLayer : public CCLayer,public cocos2d::CCIMEDelegate
{
public:
	ShopMediator* m_Mediator;
	ShopLayer(){m_pUILayer=NULL;m_layerLayout=NULL;m_buyLayout=NULL;}
	~ShopLayer(){}

	bool init();

	
	void keyBackClicked();
	virtual void onEnter();
	virtual void registerWithTouchDispatcher(void);
	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	cocos2d::CCPoint  m_beginPos;

	CREATE_FUNC(ShopLayer);


private:
	//充值按钮回调
	void payBtnCallBack(CCObject* pSender);
	//购买按钮回调
	void buyBtnCallBack(CCObject* pSender);
	//返回按钮回调
	void closeBtnCallBack(CCObject* pSender);
	//滚动层内按钮回调
	void scroCallBack(CCObject* pSender);
	//顶部按钮回调
	void tapMenuCallBack(CCObject* pSender);
	//对话框内 返回按钮回调
	void closeBtnDlgCallBack(CCObject* pSender);
	//加号按钮回调
	void subBtnCallBack(CCObject* pSender);
	//减号按钮回调
	void addBtnCallBack(CCObject* pSender);
	//数字输入键盘
	void callForNumInput(CCObject* pSender);
	//数字键盘结束回调
	void numInputCallBack(CCObject* pSender);
	//更新滚动层
	void updateScroV(bool isVis);
	//更新购买层,isVis是否打折商品
	void updateBuyLayout(CCObject* pSender,bool isVis);
	
protected:
	UILayer* m_pUILayer;
	Layout* m_layerLayout;
	Layout* m_buyLayout;
	//总价
	UILabel* m_totalPriLabel;
	//单价
	int m_onePri;
	UILabel* m_onePriLabel;
	//数量
	int m_buyNum;
	UILabel* m_buyNumLabel;

	//当前选着的界面
	int m_curTapMenu;

};

class ShopMediator:public CCObject
{
	AutoPtr<ShopLayer> _scene;
public:
	ShopMediator();
	~ShopMediator();
	void OnPackage(short xy,char* pack,int len);
	void OnShopOpen(CCObject* sender,int msgid,cocos2d::CCObject* obj);
	void dispose();//关界面
};