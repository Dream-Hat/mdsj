#include "ShiwusuoMediator.h"
#include "GameDef.h"
#include "AllCommandSignal.h"
#include "layerManager.h"


ShiwusuoMediator::ShiwusuoMediator()
{
	_scene = NULL;

	ADD_EVENT_LISTENER(OnShiwusuoOpen,NULL,this,Event::SHIWUSUO_OPEN,ShiwusuoMediator)
}

ShiwusuoMediator::~ShiwusuoMediator()
{
	if (_scene)
	{
		REMOVE_SCENE_FROM_LAYER(_scene)
	}
}

void ShiwusuoMediator::OnPackage( short xy,char* pack,int len )
{

}

void ShiwusuoMediator::OnShiwusuoOpen( CCObject* sender,int msgid,cocos2d::CCObject* obj)
{
	if (_scene == NULL)
	{
		_scene = ShiwusuoLayer::create();
		//_scene->retain();
		_scene->m_Mediator = this;
		ADD_SCENE_TO_LAYER(_scene.obj(),LayerManager::sceneUILayer);
	}
}

void ShiwusuoMediator::dispose()
{
	if (_scene)
	{
		_scene->setKeypadEnabled(false);
		REMOVE_SCENE_FROM_LAYER(_scene)
			//_scene->release();
			_scene = NULL;
	}
}

bool ShiwusuoLayer::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!CCLayer::init());
		m_Mediator = NULL;
		m_pUILayer = UILayer::create();
		m_pUILayer->setTouchPriority(-200);
		m_pUILayer->scheduleUpdate();
		addChild(m_pUILayer);

		Layout* lay = dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile("ui/shiwusuoUI/shiwusuoUI.json"));
		m_pUILayer->addWidget(lay);

		m_layerLayout = dynamic_cast<Layout*>(lay->getChildByName("layerPanel"));
		layerNum = SHIWUSUOLAYER_TAG_LAYER;
		m_xxLayout = dynamic_cast<Layout*>(lay->getChildByName("xxPanel"));
		m_xxLayout->setTouchEnable(false,true);
		m_xxLayout->setVisible(false);

		UITextButton* returnBtn = dynamic_cast<UITextButton*>(lay->getChildByName("returnBtn"));
		returnBtn->addReleaseEvent(this, coco_releaseselector(ShiwusuoLayer::closeBtnCallBack));

		UIScrollView* scroV = dynamic_cast<UIScrollView*>(m_layerLayout->getChildByName("ScrollView"));

		for (int i = 0; i <5; i++)
		{
			Layout* scroPanel = dynamic_cast<Layout*>(scroV->getChildByName(CCString::createWithFormat("Panel_%d", i)->getCString()));
			scroPanel->addReleaseEvent(this, coco_releaseselector(ShiwusuoLayer::scroCallBack));		
		}
		UITextButton* yesBtn = dynamic_cast<UITextButton*>(m_xxLayout->getChildByName("yesBtn"));
		yesBtn->addReleaseEvent(this, coco_releaseselector(ShiwusuoLayer::yesBtnCallBack));

		bRet = true;

	} while (0);

	return bRet;
}



void ShiwusuoLayer::yesBtnCallBack(CCObject* pSender)
{

}

void ShiwusuoLayer::closeBtnCallBack(CCObject* pSender)
{
	switch(layerNum){
	case SHIWUSUOLAYER_TAG_LAYER:
		{
			m_Mediator->dispose();
		}break;
	case SHIWUSUOLAYER_TAG_XX:
		{
			m_layerLayout->setVisible(true);
			m_layerLayout->setTouchEnable(true,true);
			m_xxLayout->setTouchEnable(false,true);
			m_xxLayout->setVisible(false); 
			layerNum = SHIWUSUOLAYER_TAG_LAYER;
		}break;
	default:
		break;
	}

}


void ShiwusuoLayer::onEnter()
{
	CCLayer::onEnter();
	setTouchEnabled(true);
	setKeypadEnabled(true);
}

void ShiwusuoLayer::registerWithTouchDispatcher( void )
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -190, true);
}

bool ShiwusuoLayer::ccTouchBegan( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent )
{
	return true;
}

void ShiwusuoLayer::ccTouchEnded( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent )
{

}

void ShiwusuoLayer::scroCallBack( CCObject* pSender )
{
	Layout* tempPanel = dynamic_cast<Layout*>(pSender);
	int temp = tempPanel->getTag();


	UIScrollView* scroV = dynamic_cast<UIScrollView*>(m_layerLayout->getChildByName("ScrollView"));
	Layout* scroPanel[5];
	for (int i = 0; i < 5; i++)
	{
		scroPanel[i] = dynamic_cast<Layout*>(scroV->getChildByName(CCString::createWithFormat("Panel_%d", i)->getCString()));
		scroPanel[i]->setBackGroundColor(ccc3(150,200,255));
	}
	
	scroPanel[temp % 100]->setBackGroundColor(ccc3(255,20,255));

	m_xxLayout->setVisible(true);
	m_xxLayout->setTouchEnable(true,true);
	m_layerLayout->setTouchEnable(false,true);
	m_layerLayout->setVisible(false);
	layerNum = SHIWUSUOLAYER_TAG_XX;
}

void ShiwusuoLayer::keyBackClicked()
{
	closeBtnCallBack(NULL);
}
