#pragma once

#include "cocos2d.h"
#include "cocos-ext.h"
#include "../ZMQ/GameDef.h"
#include "../ZMQ/MessageCenter.h"

#define TJP_LAYOUT_TAG_ROOT							    1000

typedef enum
{
	TJPLAYER_TAG_LAYER,
	TJPLAYER_TAG_TIPS_QH,
	TJPLAYER_TAG_TIPS_XQ
}TJPLayerType;
USING_NS_CC;
USING_NS_CC_EXT;

class TiejiangpuMediator;
class TiejiangpuLayer : public CCLayer,public cocos2d::CCIMEDelegate
{
public:
	TiejiangpuMediator* m_Mediator;
	TiejiangpuLayer(){m_pUILayer=NULL;m_pLayout=NULL;m_tipsLayout=NULL;m_layerLayout=NULL;}
	~TiejiangpuLayer(){}

	bool init();

	
	void keyBackClicked();
	virtual void onEnter();
	virtual void registerWithTouchDispatcher(void);
	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	cocos2d::CCPoint  m_beginPos;

	CREATE_FUNC(TiejiangpuLayer);


private:
	void closeBtnCallBack(CCObject* pSender);
	void scroCallBack(CCObject* pSender);
	void tapMenuCallBack(CCObject* pSender);

	void updateLayer();
	//是否是强化界面，不然就是镶嵌界面
	void initTipsLayer(bool isQH);


protected:
	UILayer* m_pUILayer;
	Layout* m_pLayout;
	Layout* m_tipsLayout;
	Layout* m_layerLayout;

	TJPLayerType m_layerNum;

	UITextButton* m_topBtn[3];

	//第一次加载page
	bool m_isFirst;
};

class TiejiangpuMediator:public CCObject
{
	AutoPtr<TiejiangpuLayer> _scene;
public:
	TiejiangpuMediator();
	~TiejiangpuMediator();
	void OnPackage(int xy,void* pack);
	void OnTiejiangpuOpen(CCObject* sender,int msgid,cocos2d::CCObject* obj);
	void dispose();//关界面

};
