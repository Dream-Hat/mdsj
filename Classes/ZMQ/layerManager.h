#pragma once
#include "cocos2d.h"
#include "AllCommandSignal.h"
USING_NS_CC;

#define ADD_SCENE_TO_LAYER(scene,layer)\
	layer->removeAllChildrenWithCleanup(true);	\
	layer->addChild(scene);


#define REMOVE_SCENE_FROM_LAYER(scene)\
	scene->removeFromParentAndCleanup(true);\
	SEND_EVENT(NULL,Event::CANCEL_HELP,NULL)
class layerEffect:public CCLayer
{
	CCSprite* movieSprite[10][6];
	CCArray* arrays;
public:
	layerEffect();
	~layerEffect();
	void showCoverEffect();
	void showPassEffect();
	void destory();
	void createOK();
};

class LayerManager
{
public:
	static CCLayer* sceneLayer;				/*场景*/
	static CCLayer* sceneCoverLayer;		/*场景上面的浮动物体*/
	static CCLayer* buttonLayer;
	static CCLayer* resourceFieldLayer;		/*资源田*/
	static CCLayer* otherUILayer;			/*低阶面板——家宅*/
	static CCLayer* sceneUILayer;			/*所有scene打开的面板*/
	static CCLayer* windowLayer;				/*弹出窗*/
	static CCLayer* chongzhiUILayer;			/*充值*/
	static CCLayer* sectionLayer;

	static CCLayer* fightLayer;				/*战斗场景*/
	static CCLayer* chatLayer;				/*聊天*/
	static CCLayer* resLoadingLayer;			/*加载资源*/
	
	static CCLayer* loginLayer;				/*登录*/
	static CCLayer* registLayer;			/*创建角色*/
	
	static CCLayer* noticeLayer;				/*通知*/
	static CCLayer* worldLayer;				/*世界层*/
	static CCLayer* newhandLayer;			/*新手引导层*/

	static CCLayer* effectLayer;				/*层动画效果*/
	static CCLayer* storyUILayer;			/*单个剧情界面*/

	static CCLayer* topLayer;				/*提示窗口*/
	static CCLayer* tipsLayer;				/*提示TIP*/
	static CCLayer* broadcastLayer;			/*公告窗口*/
	static CCLayer* loadingLayer;			/*加载*/
	static CCLayer* videoLayer;				/*视频层*/
	static CCLayer* mouseLayer;				/*鼠标层*/
	static CCLayer* centerBCLayer;			/* 中央公告层*/

	static void createAllLayer(CCScene* pScene);

	static	layerEffect* createLayerEffect();
};

