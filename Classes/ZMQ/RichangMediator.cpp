#include "RichangMediator.h"
#include "GameDef.h"
#include "AllCommandSignal.h"
#include "layerManager.h"


RichangMediator::RichangMediator()
{
	_scene = NULL;

	ADD_EVENT_LISTENER(OnRichangOpen,NULL,this,Event::RICHANG_OPEN,RichangMediator)
}

RichangMediator::~RichangMediator()
{
	if (_scene)
	{
		REMOVE_SCENE_FROM_LAYER(_scene)
	}
}

void RichangMediator::OnPackage( short xy,char* pack,int len )
{

}

void RichangMediator::OnRichangOpen( CCObject* sender,int msgid,cocos2d::CCObject* obj)
{
	if (_scene == NULL)
	{
		_scene = RichangLayer::create();
		//_scene->retain();
		_scene->m_Mediator = this;
		ADD_SCENE_TO_LAYER(_scene.obj(),LayerManager::sceneUILayer);
	}
}

void RichangMediator::dispose()
{
	if (_scene)
	{
		_scene->setKeypadEnabled(false);
		REMOVE_SCENE_FROM_LAYER(_scene)
			//_scene->release();
			_scene = NULL;
	}
}

bool RichangLayer::init()
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

		m_pLayout = dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile("ui/richangUI/richangUI_1.json"));
		m_pUILayer->addWidget(m_pLayout);

		UIScrollView* scroV = dynamic_cast<UIScrollView*>(m_pLayout->getChildByName("ScrollView"));

		for (int i = 0; i < 6; i++)
		{
			UITextButton* scroPanel = dynamic_cast<UITextButton*>(scroV->getChildByName(CCString::createWithFormat("TextButton_%d", i)->getCString()));
			scroPanel->addReleaseEvent(this, coco_releaseselector(RichangLayer::scroCallBack));
			if (i==0)
			{
				scroPanel->active();
			}
			
		}

		UIButton* returnBtn = dynamic_cast<UIButton*>(m_pLayout->getChildByName("returnBtn"));
		returnBtn->addReleaseEvent(this, coco_releaseselector(RichangLayer::closeBtnCallBack));

		Layout* tapbtn_panel = dynamic_cast<Layout*>(m_pLayout->getChildByName("menubtn_Panel"));
		tapbtn_panel->setWidgetTag(SHOP_LAYOUT_TAG_ROOT);

		UIButton* richangBtn = dynamic_cast<UIButton*>(tapbtn_panel->getChildByName("richangBtn"));
		richangBtn->addReleaseEvent(this, coco_releaseselector(RichangLayer::tapMenuCallBack));
		richangBtn->setWidgetTag(SHOP_LAYOUT_TAG_EQUIP);

		UIButton* activityBtn = dynamic_cast<UIButton*>(tapbtn_panel->getChildByName("activityBtn"));
		activityBtn->addReleaseEvent(this, coco_releaseselector(RichangLayer::tapMenuCallBack));
		activityBtn->setWidgetTag(SHOP_LAYOUT_TAG_TEJIA);
		activityBtn->disable();

		bRet = true;

	} while (0);

	return bRet;
}



void RichangLayer::buyBtnCallBack( CCObject* pSender )
{

}

void RichangLayer::closeBtnCallBack( CCObject* pSender )
{
	m_Mediator->dispose();
}

void RichangLayer::curBtnCallBack( CCObject* pSender )
{
	
}
void RichangLayer::onEnter()
{
	CCLayer::onEnter();
	setTouchEnabled(true);
	setKeypadEnabled(true);
}

void RichangLayer::registerWithTouchDispatcher( void )
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -190, true);
}

bool RichangLayer::ccTouchBegan( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent )
{
	return true;
}

void RichangLayer::ccTouchEnded( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent )
{

}

void RichangLayer::scroCallBack( CCObject* pSender )
{
	UITextButton* tempBtn = dynamic_cast<UITextButton*>(pSender);
	int temp = tempBtn->getTag();
	UIScrollView* scroV = dynamic_cast<UIScrollView*>(m_pLayout->getChildByName("ScrollView"));
	UITextButton* scroBtn[6];
	for (int i = 0; i < 6; i++)
	{
		scroBtn[i] = dynamic_cast<UITextButton*>(scroV->getChildByName(CCString::createWithFormat("TextButton_%d", i)->getCString()));
		scroBtn[i]->active();
	}
	
	scroBtn[temp % 100]->disable();
}

void RichangLayer::tapMenuCallBack( CCObject* pSender )
{
	 UIButton* button = dynamic_cast<UIButton*>(pSender);

	 Layout* root = dynamic_cast<Layout*>(m_pUILayer->getWidgetByTag(SHOP_LAYOUT_TAG_ROOT));

	 UIButton* ricBtn = dynamic_cast<UIButton*>(root->getChildByTag(SHOP_LAYOUT_TAG_EQUIP));

	 UIButton* activityBtn = dynamic_cast<UIButton*>(root->getChildByTag(SHOP_LAYOUT_TAG_TEJIA));

	 ricBtn->active();
	 activityBtn->active();

	 switch (button->getWidgetTag())
	 {
	 case SHOP_LAYOUT_TAG_EQUIP:
		 {
			 ricBtn->disable();
		 }break;
	 case SHOP_LAYOUT_TAG_TEJIA:
		 {
			 activityBtn->disable();
		 }break;
	 }

	 UIScrollView* scroV = dynamic_cast<UIScrollView*>(m_pLayout->getChildByName("ScrollView"));
	 UITextButton* scroBtn[6];
	 for (int i = 0; i < 6; i++)
	 {
		 scroBtn[i] = dynamic_cast<UITextButton*>(scroV->getChildByName(CCString::createWithFormat("TextButton_%d", i)->getCString()));
		 scroBtn[i]->active();
	 }
}

void RichangLayer::closeBtnCallBack1( CCObject* pSender )
{

}

void RichangLayer::keyBackClicked()
{
	closeBtnCallBack(NULL);
}
