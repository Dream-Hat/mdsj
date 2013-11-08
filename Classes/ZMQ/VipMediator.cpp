#include "VipMediator.h"
#include "GameDef.h"
#include "AllCommandSignal.h"
#include "layerManager.h"
#include "AlertDialog.h"


VipMediator::VipMediator()
{
	_scene = NULL;

	ADD_EVENT_LISTENER(OnVipOpen,NULL,this,Event::VIP_OPEN,VipMediator)
}

VipMediator::~VipMediator()
{
	if (_scene)
	{
		REMOVE_SCENE_FROM_LAYER(_scene)
	}
}

void VipMediator::OnPackage( short xy,char* pack,int len )
{

}

void VipMediator::OnVipOpen( CCObject* sender,int msgid,cocos2d::CCObject* obj)
{
	if (_scene == NULL)
	{
		_scene = VipLayer::create();
		//_scene->retain();
		_scene->m_Mediator = this;
		ADD_SCENE_TO_LAYER(_scene.obj(),LayerManager::sceneUILayer);
	}
}

void VipMediator::dispose()
{
	if (_scene)
	{
		_scene->setKeypadEnabled(false);
		REMOVE_SCENE_FROM_LAYER(_scene)
			//_scene->release();
			_scene = NULL;
	}
}

bool VipLayer::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!CCLayer::init());


		CCSize scrSize = CCDirector::sharedDirector()->getWinSize();

		m_pUILayer = UILayer::create();
		m_pUILayer->setTouchPriority(-200);
		m_pUILayer->scheduleUpdate();
		addChild(m_pUILayer);

		Layout* layout = dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile("ui/VIPUI/VIPUI.json"));
		m_pUILayer->addWidget(layout);	
		
		m_layerLayout = dynamic_cast<Layout*>(layout->getChildByName("layerPanel"));
		m_layerLayout->setVisible(true);
		layerNum = VIPLAYER_TAG_LAYER;
		m_xxLayout = dynamic_cast<Layout*>(layout->getChildByName("xx_Panel"));
		m_xxLayout->setTouchEnable(false,true);
		m_xxLayout->setVisible(false);
		m_openLayout = dynamic_cast<Layout*>(layout->getChildByName("open_Panel"));
		m_openLayout->setTouchEnable(false,true);
		m_openLayout->setVisible(false);

		UITextButton* returnBtn = dynamic_cast<UITextButton*>(m_layerLayout->getChildByName("returnBtn"));
		returnBtn->addReleaseEvent(this, coco_releaseselector(VipLayer::closeBtnCallBack));
		UITextButton* returnBtn2 = dynamic_cast<UITextButton*>(m_xxLayout->getChildByName("returnBtn"));
		returnBtn2->addReleaseEvent(this, coco_releaseselector(VipLayer::closeBtnCallBack));
		UITextButton* returnBtn3 = dynamic_cast<UITextButton*>(m_openLayout->getChildByName("returnBtn"));
		returnBtn3->addReleaseEvent(this, coco_releaseselector(VipLayer::closeBtnCallBack));

		UIButton* oneselfBtn = dynamic_cast<UIButton*>(m_layerLayout->getChildByName("oneselfBtn"));

		UIScrollView* scroV = dynamic_cast<UIScrollView*>(m_xxLayout->getChildByName("ScrollView"));
		for (int i = 0; i <5; i++)
		{
			Layout* scroPanel = dynamic_cast<Layout*>(scroV->getChildByName(CCString::createWithFormat("Panel_%d", i)->getCString()));
			scroPanel->addReleaseEvent(this, coco_releaseselector(VipLayer::scroCallBack));
		}

		UITextButton* openBtn = dynamic_cast<UITextButton*>(m_layerLayout->getChildByName("openBtn"));
		openBtn->addReleaseEvent(this,coco_releaseselector(VipLayer::openBtnCallBack));

		UITextButton* xxBtn = dynamic_cast<UITextButton*>(m_layerLayout->getChildByName("xxBtn"));
		xxBtn->addReleaseEvent(this,coco_releaseselector(VipLayer::xxBtnCallBack));
		bRet = true;

	} while (0);

	return bRet;
}



void VipLayer::scroCallBack( CCObject* pSender )
{
}

void VipLayer::closeBtnCallBack( CCObject* pSender )
{
	switch(layerNum)
	{
	case VIPLAYER_TAG_LAYER:
		{
			m_Mediator->dispose();
		}break;
	case VIPLAYER_TAG_XX:
		{
			Pop::popText("ins",ccc3(0,255,0));
			m_layerLayout->setVisible(true);
			m_layerLayout->setTouchEnable(true,true);
			m_xxLayout->setTouchEnable(false,true);
			m_xxLayout->setVisible(false);
			layerNum = VIPLAYER_TAG_LAYER;
		}break;
	case VIPLAYER_TAG_OPEN:
		{
			m_layerLayout->setVisible(true);
			m_layerLayout->setTouchEnable(true,true);
			m_openLayout->setTouchEnable(false,true);
			m_openLayout->setVisible(false);
			layerNum = VIPLAYER_TAG_LAYER;
		}break;
	default:
		break;
	}
}

void VipLayer::onEnter()
{
	CCLayer::onEnter();
	setTouchEnabled(true);
	setKeypadEnabled(true);
}

void VipLayer::registerWithTouchDispatcher( void )
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -190, true);
}

bool VipLayer::ccTouchBegan( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent )
{
	return true;
}

void VipLayer::ccTouchEnded( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent )
{

}

void VipLayer::openBtnCallBack( CCObject* pSender )
{

	m_layerLayout->setVisible(false);
	m_layerLayout->setTouchEnable(false,true);
	m_openLayout->setTouchEnable(true,true);
	m_openLayout->setVisible(true);
	layerNum = VIPLAYER_TAG_OPEN;
}

void VipLayer::xxBtnCallBack( CCObject* pSender )
{
	m_layerLayout->setVisible(false);
	m_layerLayout->setTouchEnable(false,true);
	m_xxLayout->setTouchEnable(true,true);
	m_xxLayout->setVisible(true);
	layerNum = VIPLAYER_TAG_XX;
}

void VipLayer::keyBackClicked()
{
	closeBtnCallBack(NULL);
}
