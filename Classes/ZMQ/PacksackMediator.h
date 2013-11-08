#pragma once

#include "cocos2d.h"
#include "cocos-ext.h"
#include "GameDef.h"
#include "MessageCenter.h"


#define PACKSACK_LAYOUT_TAG_ROOT							    1000
#define PACKSACK_LAYOUT_TAG_EQUIP                              1001
#define PACKSACK_LAYOUT_TAG_TEJIA								1002
#define PACKSACK_LAYOUT_TAG_DIAMOND						    1003
#define PACKSACK_LAYOUT_TAG_YAOSHUI                            1004
#define PACKSACK_LAYOUT_TAG_OTHER								 1005

typedef enum
{
	PACKSACK_LAYOUT_TAG_LAYER,
	PACKSACK_LAYOUT_TAG_KUORONG,
	PACKSACK_LAYOUT_TAG_GOODS,
	PACKSACK_LAYOUT_TAG_SALEDLG
}PacksackLayerType;

USING_NS_CC;
USING_NS_CC_EXT;

class PacksackMediator;
class PacksackLayer : public CCLayer,public cocos2d::CCIMEDelegate
{
public:
	PacksackMediator* m_Mediator;
	PacksackLayer(){ m_pUILayer=NULL;m_layerLayout=NULL;m_rootLayout=NULL;m_goodsLayout = NULL;m_saleLayout=NULL;}
	~PacksackLayer(){}

	bool init();

	void keyBackClicked();
	virtual void onEnter();
	virtual void registerWithTouchDispatcher(void);
	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	cocos2d::CCPoint  m_beginPos;

	CREATE_FUNC(PacksackLayer);

private:
	//扩容按钮回调
	void buyBtnCallBack(CCObject* pSender);
	//返回按钮回调
	void closeBtnCallBack(CCObject* pSender);
	//滚动层内回调
	void scroCallBack(CCObject* pSender);
	//顶部按钮组回调
	void tapMenuCallBack(CCObject* pSender);
	//单选按钮回调
	void checkboxBtnCallBack(CCObject* pSender);
	void checkboxLabCallBack(CCObject* pSender);
	//打开商品详细内容
	void openGoods();
	//出售按钮回调
	void saleBtnCallBack(CCObject* pSender);
	//使用按钮回调
	void useBtnCallBack(CCObject* pSender);
	//扩容 按钮回调
	void sureBtnCallBack(CCObject* pSender);


protected:
	UILayer* m_pUILayer;
	Layout* m_layerLayout;
	Layout* m_rootLayout;
	Layout* m_goodsLayout;
	//出售布局
	Layout* m_saleLayout;
	UIImageView* checkImg[3];
	//当前点击的单选框
	int m_checkNum;
	//当前所处编号
	PacksackLayerType m_curLayerNum;
	//当前点击的商品ID
	int m_curGoodsID;
};

class PacksackMediator:public CCObject
{
	AutoPtr<PacksackLayer> _scene;
public:
	PacksackMediator();
	~PacksackMediator();
	void OnPackage(short xy,char* pack,int len);
	void OnPacksackOpen(CCObject* sender,int msgid,cocos2d::CCObject* obj);
	void dispose();//关界面

};
