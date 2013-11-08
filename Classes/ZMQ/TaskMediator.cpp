#include "TaskMediator.h"
#include "GameDef.h"
#include "AllCommandSignal.h"
#include "layerManager.h"


TaskMediator::TaskMediator()
{
	_scene = NULL;

	ADD_EVENT_LISTENER(OnTaskOpen,NULL,this,Event::TASK_OPEN,TaskMediator)
}

TaskMediator::~TaskMediator()
{
	if (_scene)
	{
		_scene->setKeypadEnabled(false);
		REMOVE_SCENE_FROM_LAYER(_scene)
	}
}

void TaskMediator::OnPackage( short xy,char* pack,int len )
{

}

void TaskMediator::OnTaskOpen( CCObject* sender,int msgid,cocos2d::CCObject* obj)
{
	if (_scene == NULL)
	{
		_scene = TaskLayer::create();
		//_scene->retain();
		_scene->m_Mediator = this;
		ADD_SCENE_TO_LAYER(_scene.obj(),LayerManager::sceneUILayer);
	}
}

void TaskMediator::dispose()
{
	if (_scene)
	{
		_scene->setKeypadEnabled(false);
		REMOVE_SCENE_FROM_LAYER(_scene)
			//_scene->release();
			_scene = NULL;
	}
}

bool TaskLayer::init()
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

		m_pLayout = dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile("ui/taskUI/taskUI.json"));
		m_pUILayer->addWidget(m_pLayout);

		UIScrollView* scroV = dynamic_cast<UIScrollView*>(m_pLayout->getChildByName("ScrollView"));

		for (int i = 0; i < 6; i++)
		{
			UITextButton* scroPanel = dynamic_cast<UITextButton*>(scroV->getChildByName(CCString::createWithFormat("TextButton_%d", i)->getCString()));
			scroPanel->addReleaseEvent(this, coco_releaseselector(TaskLayer::scroCallBack));
			if (i==0)
			{
				scroPanel->active();
			}
			
		}

		UIButton* returnBtn = dynamic_cast<UIButton*>(m_pLayout->getChildByName("returnBtn"));
		returnBtn->addReleaseEvent(this, coco_releaseselector(TaskLayer::closeBtnCallBack));

		Layout* tapbtn_panel = dynamic_cast<Layout*>(m_pLayout->getChildByName("menubtn_Panel"));
		tapbtn_panel->setWidgetTag(SHOP_LAYOUT_TAG_ROOT);

		UIButton* couldBtn = dynamic_cast<UIButton*>(tapbtn_panel->getChildByName("couldBtn"));
		couldBtn->addReleaseEvent(this, coco_releaseselector(TaskLayer::tapMenuCallBack));
		couldBtn->setWidgetTag(SHOP_LAYOUT_TAG_EQUIP);

		UIButton* canBtn = dynamic_cast<UIButton*>(tapbtn_panel->getChildByName("canBtn"));
		canBtn->addReleaseEvent(this, coco_releaseselector(TaskLayer::tapMenuCallBack));
		canBtn->setWidgetTag(SHOP_LAYOUT_TAG_TEJIA);
		canBtn->disable();

		bRet = true;

	} while (0);

	return bRet;
}



void TaskLayer::buyBtnCallBack( CCObject* pSender )
{

}

void TaskLayer::closeBtnCallBack( CCObject* pSender )
{
	m_Mediator->dispose();
}

void TaskLayer::curBtnCallBack( CCObject* pSender )
{
	
}
void TaskLayer::onEnter()
{
	CCLayer::onEnter();
	setTouchEnabled(true);
	setKeypadEnabled(true);
}

void TaskLayer::registerWithTouchDispatcher( void )
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -190, true);
}

bool TaskLayer::ccTouchBegan( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent )
{
	return true;
}

void TaskLayer::ccTouchEnded( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent )
{

}

void TaskLayer::scroCallBack( CCObject* pSender )
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

void TaskLayer::tapMenuCallBack( CCObject* pSender )
{
	 UIButton* button = dynamic_cast<UIButton*>(pSender);

	 Layout* root = dynamic_cast<Layout*>(m_pUILayer->getWidgetByTag(SHOP_LAYOUT_TAG_ROOT));

	 UIButton* couldBtn = dynamic_cast<UIButton*>(root->getChildByTag(SHOP_LAYOUT_TAG_EQUIP));

	 UIButton* canBtnBtn = dynamic_cast<UIButton*>(root->getChildByTag(SHOP_LAYOUT_TAG_TEJIA));

	 couldBtn->active();
	 canBtnBtn->active();

	 switch (button->getWidgetTag())
	 {
	 case SHOP_LAYOUT_TAG_EQUIP:
		 {
			 couldBtn->disable();
		 }break;
	 case SHOP_LAYOUT_TAG_TEJIA:
		 {
			 canBtnBtn->disable();
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

void TaskLayer::closeBtnCallBack1( CCObject* pSender )
{

}

void TaskLayer::keyBackClicked()
{
	closeBtnCallBack(NULL);
}
