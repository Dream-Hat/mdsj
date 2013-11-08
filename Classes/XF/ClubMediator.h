#pragma once

#include "cocos2d.h"
#include "cocos-ext.h"
#include "../ZMQ/GameDef.h"



#define CLUBLAYER_TAG_ROOT								   1000

typedef enum
{
	CLUBLAYER_TAG_LAYER,
	CLUBLAYER_TAG_SEARCH,
	CLUBLAYER_TAG_TIPS,
	CLUBLAYER_TAG_NEIRONG_CY,
	CLUBLAYER_TAG_YAOQING,
	CLUBLAYER_TAG_NEIRONG_XSQ,
	CLUBLAYER_TAG_NEIRONG_JJ,
	CLUBLAYER_TAG_NEIRONG_JS
}ClubLayerType;
USING_NS_CC;
USING_NS_CC_EXT;

class ClubMediator;
class ClubLayer : public CCLayer,public cocos2d::CCIMEDelegate
{
public:
	ClubMediator* m_Mediator;
	ClubLayer(){  m_pUILayer=NULL;m_pLayout=NULL;m_tipsLayout=NULL;m_layerLayout=NULL;m_searchLayout=NULL;m_jsLayout=NULL;
		m_jjLayout=NULL;m_cyLayout=NULL;}
	~ClubLayer(){}

	bool init();

	
	void keyBackClicked();
	virtual void onEnter();
	virtual void registerWithTouchDispatcher(void);
	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	cocos2d::CCPoint  m_beginPos;

	CREATE_FUNC(ClubLayer);


private:
	void joinBtnCallBack(CCObject* pSender);
	void closeBtnCallBack(CCObject* pSender);
	void searchBtnCallBack(CCObject* pSender);
	void scroCallBack(CCObject* pSender);
	void tapMenuCallBack(CCObject* pSender);
	void closeBtnCallBack1(CCObject* pSender);
	void yesBtnCallBack(CCObject* pSender);
	void noBtnCallBack(CCObject* pSender);

	void updateLayer(ClubLayerType num);
	void setVis(bool isvis);


protected:
	UILayer* m_pUILayer;
	Layout* m_pLayout;
	Layout* m_tipsLayout;
	Layout* m_layerLayout;
	Layout* m_searchLayout;
	Layout* m_jsLayout;
	Layout* m_jjLayout;
	Layout* m_cyLayout;

	ClubLayerType layerNum;
	//是否第一次加载
	bool m_isFirstloadPage;

	UITextButton* m_joinBtn;  //过程中会替换文字,下同
	UITextButton* m_topBtn[4];
	UITextButton* m_searchBtn;
	UITextButton* m_yesBtn;
	UITextButton* m_noBtn;
};


class ClubMediator:public CCObject
{
	AutoPtr<ClubLayer> _scene;
public:
	ClubMediator();
	~ClubMediator();
	void OnPackage(short xy,char* pack,int len);
	void OnClubOpen(CCObject* sender,int msgid,cocos2d::CCObject* obj);
	void dispose();//关界面

};
