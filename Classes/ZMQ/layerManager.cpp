#include "layerManager.h"
#include "AllCommandSignal.h"
#include "MessageCenter.h"
CCLayer* LayerManager::sceneLayer;				/*场景*/
CCLayer* LayerManager::sceneCoverLayer;
CCLayer* LayerManager::buttonLayer;
CCLayer* LayerManager::resourceFieldLayer;		/*资源田*/
CCLayer* LayerManager::otherUILayer;			/*演武场,跑商,屯田*/
CCLayer* LayerManager::sceneUILayer;			/*小地图。左上角。导航*/
CCLayer* LayerManager::chongzhiUILayer;			/*充值*/
CCLayer* LayerManager::storyUILayer;			/*单个剧情界面*/
CCLayer* LayerManager::fightLayer;				/*战斗场景*/
CCLayer* LayerManager::chatLayer;				/*聊天*/
CCLayer* LayerManager::resLoadingLayer;			/*加载资源*/
CCLayer* LayerManager::windowLayer;				/*弹出窗*/
CCLayer* LayerManager::sectionLayer;			/*选择章节*/
CCLayer* LayerManager::loginLayer;				/*登录*/
CCLayer* LayerManager::registLayer;				/*创建角色*/
CCLayer* LayerManager::noticeLayer;				/*通知*/
CCLayer* LayerManager::worldLayer;				/*世界层*/
CCLayer* LayerManager::newhandLayer;			/*新手引导层*/
CCLayer* LayerManager::effectLayer;				/*效果*/
CCLayer* LayerManager::topLayer;				/*提示窗口*/
CCLayer* LayerManager::tipsLayer;				/*提示TIP*/
CCLayer* LayerManager::broadcastLayer;			/*公告窗口*/
CCLayer* LayerManager::loadingLayer;			/*加载*/
CCLayer* LayerManager::videoLayer;				/*视频层*/
CCLayer* LayerManager::mouseLayer;				/*鼠标层*/
CCLayer* LayerManager::centerBCLayer;			/* 中央公告层*/

void LayerManager::createAllLayer(CCScene* pScene)
{
	LayerManager::sceneLayer = CCLayer::create();
	pScene->addChild(LayerManager::sceneLayer);		

	LayerManager::sceneCoverLayer = CCLayer::create();
	pScene->addChild(LayerManager::sceneCoverLayer);

	

	LayerManager::buttonLayer = CCLayer::create();
	pScene->addChild(LayerManager::buttonLayer);
	
			
	LayerManager::resourceFieldLayer=CCLayer::create();
	pScene->addChild(LayerManager::resourceFieldLayer);
			
	LayerManager::otherUILayer=CCLayer::create();
	pScene->addChild(LayerManager::otherUILayer);
			
	
	LayerManager::sceneUILayer= CCLayer::create();
	pScene->addChild(LayerManager::sceneUILayer);

	
	//弹出窗
	LayerManager::windowLayer=CCLayer::create();
	pScene->addChild(LayerManager::windowLayer);

	LayerManager::chongzhiUILayer= CCLayer::create();
	pScene->addChild(LayerManager::chongzhiUILayer);

	LayerManager::sectionLayer=CCLayer::create();
	pScene->addChild(LayerManager::sectionLayer);
			

			
	LayerManager::fightLayer=CCLayer::create();
	pScene->addChild(LayerManager::fightLayer);
			
	LayerManager::chatLayer=CCLayer::create();
	pScene->addChild(LayerManager::chatLayer);
			
	LayerManager::resLoadingLayer=CCLayer::create();
	pScene->addChild(LayerManager::resLoadingLayer);
			
			

	LayerManager::loginLayer=CCLayer::create();
	pScene->addChild(LayerManager::loginLayer);


	LayerManager::registLayer=CCLayer::create();
	pScene->addChild(LayerManager::registLayer);
	
			
	LayerManager::worldLayer=CCLayer::create();
	pScene->addChild(LayerManager::worldLayer);
			
	LayerManager::newhandLayer=CCLayer::create();
	pScene->addChild(LayerManager::newhandLayer);
			
	LayerManager::noticeLayer=CCLayer::create();
	pScene->addChild(LayerManager::noticeLayer);
			
	LayerManager::effectLayer = CCLayer::create();
	pScene->addChild(LayerManager::effectLayer);

	LayerManager::storyUILayer= CCLayer::create();
	pScene->addChild(LayerManager::storyUILayer);
			
	LayerManager::topLayer = CCLayer::create();
	pScene->addChild(LayerManager::topLayer);
			
	LayerManager::tipsLayer=CCLayer::create();
	pScene->addChild(LayerManager::tipsLayer);
			

			
	LayerManager::broadcastLayer=CCLayer::create();
	pScene->addChild(LayerManager::broadcastLayer);
			
	LayerManager::loadingLayer=CCLayer::create();
	pScene->addChild(LayerManager::loadingLayer);
			
	LayerManager::videoLayer=CCLayer::create();
	pScene->addChild(LayerManager::videoLayer);
			
	LayerManager::mouseLayer = CCLayer::create();
	pScene->addChild(LayerManager::mouseLayer);

	LayerManager::centerBCLayer = CCLayer::create();
	pScene->addChild(LayerManager::centerBCLayer);
}

layerEffect* LayerManager::createLayerEffect()
{
	LayerManager::effectLayer->removeAllChildrenWithCleanup(true);
	if (LayerManager::effectLayer->getChildrenCount() == 0)
	{
		layerEffect* l = new layerEffect();
		LayerManager::effectLayer->addChild(l);
		l->release();
		l->setVisible(false);
		return l;
	}
	return NULL;
}

layerEffect::layerEffect()
{
	arrays=CCArray::createWithCapacity(5);
	for (int i=1;i<6;i++)
	{
		CCString* fileName=CCString::createWithFormat("./effect/zhandouloading_1/%d.png",i);
		CCTexture2D* texture=CCTextureCache::sharedTextureCache()->addImage(fileName->getCString());
		CCSize texSize=texture->getContentSize();
		CCRect texRect=CCRectMake(0,0,texSize.width,texSize.height);
		CCSpriteFrame* frame=CCSpriteFrame::createWithTexture(texture,texRect);
		arrays->addObject(frame);
	}
	
	//animate2 = CCAnimate::create(animation);
	//animate2->reverse();
	arrays->retain();
	//animate2->retain();

	for (int i = 0; i < 10; i ++)
	{
		for (int j = 0; j < 6; j ++)
		{
			movieSprite[i][j] = CCSprite::create();
			this->addChild(movieSprite[i][j]);
			CCSize picSize=movieSprite[i][j]->getContentSize();
			movieSprite[i][j]->setPosition(ccp(40+80*i,40+80*j));
		}
	}
}
layerEffect::~layerEffect()
{
	arrays->release();
	//animate2->release();
}

void layerEffect::showCoverEffect()
{
	setVisible(true);
	
	for (int i = 0; i < 10; i ++)
	{
		for (int j = 0; j < 6; j ++)
		{
			float startdelay = 0;
			if (j < 2)
				startdelay= 2 - j;
			if (j > 3)
				startdelay = j -3;
			startdelay+=i;


			CCAnimation* animation=CCAnimation::createWithSpriteFrames(arrays,0.1f);
			CCAnimate* animate=CCAnimate::create(animation);
			CCDelayTime* d = CCDelayTime::create(startdelay*0.05f);
		
			movieSprite[i][j]->runAction(CCSequence::create(d,animate->reverse(),NULL));
		}
	}
	CCDelayTime* d = CCDelayTime::create(20*0.05f+0.1f*5);
	CCCallFunc* f= CCCallFunc::create(this,callfunc_selector(layerEffect::createOK));
	this->runAction(CCSequence::create(d,f,NULL));
	
}
void layerEffect::showPassEffect()
{

	for (int i = 0; i < 10; i ++)
	{
		for (int j = 0; j < 6; j ++)
		{
			float startdelay = 0;
			if (j < 2)
				startdelay= 2 - j;
			if (j > 3)
				startdelay = j -3;
			startdelay+=i;


			CCAnimation* animation=CCAnimation::createWithSpriteFrames(arrays,0.1f);
			CCAnimate* animate=CCAnimate::create(animation);
			CCDelayTime* d = CCDelayTime::create(startdelay*0.05f);
			movieSprite[i][j]->runAction(CCSequence::create(d,animate,NULL));
		}
	}
	CCDelayTime* d = CCDelayTime::create(20*0.05f+0.1f*5);
	CCCallFunc* f= CCCallFunc::create(this,callfunc_selector(layerEffect::destory));
	this->runAction(CCSequence::create(d,f,NULL));

}
void layerEffect::createOK()
{

	SEND_EVENT(NULL,Event::EFFECT_HALF,NULL);
}
void layerEffect::destory()
{
	SEND_EVENT(NULL,Event::EFFECT_OVER,NULL);
	removeFromParentAndCleanup(true);
}