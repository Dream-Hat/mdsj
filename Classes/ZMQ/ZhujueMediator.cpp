#include "ZhujueMediator.h"
#include "GameDef.h"
#include "AllCommandSignal.h"
#include "layerManager.h"


ZhujueMediator::ZhujueMediator()
{
	_scene = NULL;

	ADD_EVENT_LISTENER(OnZhujueOpen,NULL,this,Event::ZHUJUE_OPEN,ZhujueMediator)
}

ZhujueMediator::~ZhujueMediator()
{
	if (_scene)
	{
		REMOVE_SCENE_FROM_LAYER(_scene)
	}
}

void ZhujueMediator::OnPackage( short xy,char* pack,int len )
{

}

void ZhujueMediator::OnZhujueOpen( CCObject* sender,int msgid,cocos2d::CCObject* obj)
{
	if (_scene == NULL)
	{
		_scene = ZhujueLayer::create();
		//_scene->retain();
		_scene->m_Mediator = this;
		ADD_SCENE_TO_LAYER(_scene.obj(),LayerManager::sceneUILayer);
	}
}

void ZhujueMediator::dispose()
{
	if (_scene)
	{
		_scene->setKeypadEnabled(false);
		REMOVE_SCENE_FROM_LAYER(_scene)
			//_scene->release();
			_scene = NULL;
	}
}

bool ZhujueLayer::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!CCLayer::init());

		m_pUILayer = UILayer::create();
		m_pUILayer->setTouchPriority(-200);
		m_pUILayer->scheduleUpdate();
		addChild(m_pUILayer);

		Layout* m_layerLayout = dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile("ui/ZhujueUI/ZhujueUI.json"));
		m_pUILayer->addWidget(m_layerLayout);

		UITextButton* returnBtn = dynamic_cast<UITextButton*>(m_layerLayout->getChildByName("returnBtn"));
		returnBtn->addReleaseEvent(this, coco_releaseselector(ZhujueLayer::closeBtnCallBack));

		

		bRet = true;

	} while (0);

	return bRet;
}



void ZhujueLayer::yesBtnCallBack(CCObject* pSender)
{

}

void ZhujueLayer::closeBtnCallBack(CCObject* pSender)
{
	m_Mediator->dispose();
}


void ZhujueLayer::onEnter()
{
	CCLayer::onEnter();
	setTouchEnabled(true);
	setKeypadEnabled(true);
}

void ZhujueLayer::registerWithTouchDispatcher( void )
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -190, true);
}

bool ZhujueLayer::ccTouchBegan( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent )
{
	return true;
}

void ZhujueLayer::ccTouchEnded( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent )
{

}

void ZhujueLayer::keyBackClicked()
{
	closeBtnCallBack(NULL);
}


