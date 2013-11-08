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
	//��ֵ��ť�ص�
	void payBtnCallBack(CCObject* pSender);
	//����ť�ص�
	void buyBtnCallBack(CCObject* pSender);
	//���ذ�ť�ص�
	void closeBtnCallBack(CCObject* pSender);
	//�������ڰ�ť�ص�
	void scroCallBack(CCObject* pSender);
	//������ť�ص�
	void tapMenuCallBack(CCObject* pSender);
	//�Ի����� ���ذ�ť�ص�
	void closeBtnDlgCallBack(CCObject* pSender);
	//�ӺŰ�ť�ص�
	void subBtnCallBack(CCObject* pSender);
	//���Ű�ť�ص�
	void addBtnCallBack(CCObject* pSender);
	//�����������
	void callForNumInput(CCObject* pSender);
	//���ּ��̽����ص�
	void numInputCallBack(CCObject* pSender);
	//���¹�����
	void updateScroV(bool isVis);
	//���¹����,isVis�Ƿ������Ʒ
	void updateBuyLayout(CCObject* pSender,bool isVis);
	
protected:
	UILayer* m_pUILayer;
	Layout* m_layerLayout;
	Layout* m_buyLayout;
	//�ܼ�
	UILabel* m_totalPriLabel;
	//����
	int m_onePri;
	UILabel* m_onePriLabel;
	//����
	int m_buyNum;
	UILabel* m_buyNumLabel;

	//��ǰѡ�ŵĽ���
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
	void dispose();//�ؽ���
};