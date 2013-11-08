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
	static CCLayer* sceneLayer;				/*����*/
	static CCLayer* sceneCoverLayer;		/*��������ĸ�������*/
	static CCLayer* buttonLayer;
	static CCLayer* resourceFieldLayer;		/*��Դ��*/
	static CCLayer* otherUILayer;			/*�ͽ���塪����լ*/
	static CCLayer* sceneUILayer;			/*����scene�򿪵����*/
	static CCLayer* windowLayer;				/*������*/
	static CCLayer* chongzhiUILayer;			/*��ֵ*/
	static CCLayer* sectionLayer;

	static CCLayer* fightLayer;				/*ս������*/
	static CCLayer* chatLayer;				/*����*/
	static CCLayer* resLoadingLayer;			/*������Դ*/
	
	static CCLayer* loginLayer;				/*��¼*/
	static CCLayer* registLayer;			/*������ɫ*/
	
	static CCLayer* noticeLayer;				/*֪ͨ*/
	static CCLayer* worldLayer;				/*�����*/
	static CCLayer* newhandLayer;			/*����������*/

	static CCLayer* effectLayer;				/*�㶯��Ч��*/
	static CCLayer* storyUILayer;			/*�����������*/

	static CCLayer* topLayer;				/*��ʾ����*/
	static CCLayer* tipsLayer;				/*��ʾTIP*/
	static CCLayer* broadcastLayer;			/*���洰��*/
	static CCLayer* loadingLayer;			/*����*/
	static CCLayer* videoLayer;				/*��Ƶ��*/
	static CCLayer* mouseLayer;				/*����*/
	static CCLayer* centerBCLayer;			/* ���빫���*/

	static void createAllLayer(CCScene* pScene);

	static	layerEffect* createLayerEffect();
};

