#include "MailMediator.h"
#include "GameDef.h"
#include "AllCommandSignal.h"
#include "layerManager.h"
#include "../ZLL/LanguageManager.h"
#include "SceneCover.h"

MailMediator::MailMediator()
{
	_scene = NULL;

	ADD_EVENT_LISTENER(OnMailOpen,NULL,this,Event::MAIL_OPEN,MailMediator)
}

MailMediator::~MailMediator()
{
	if (_scene)
	{
		REMOVE_SCENE_FROM_LAYER(_scene)
	}
}

void MailMediator::OnPackage( short xy,char* pack,int len )
{

}

void MailMediator::OnMailOpen( CCObject* sender,int msgid,cocos2d::CCObject* obj)
{
	if (_scene == NULL)
	{
		_scene = MailLayer::create();
		//_scene->retain();
		_scene->m_Mediator = this;
		ADD_SCENE_TO_LAYER(_scene.obj(),LayerManager::sceneUILayer);
	}
}

void MailMediator::dispose()
{
	if (_scene)
	{
		_scene->setKeypadEnabled(false);
		REMOVE_SCENE_FROM_LAYER(_scene)
			//_scene->release();
			_scene = NULL;
	}
}

bool MailLayer::init()
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

		Layout* lay = dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile("ui/MailUI/MailUI.json"));
		m_pUILayer->addWidget(lay);

		m_mailLayout = dynamic_cast<Layout*>(lay->getChildByName("mailPanel"));
		layerNum = MAILLAYER_TAG_MAIL;
		m_writeLayout = dynamic_cast<Layout*>(lay->getChildByName("writePanel"));
		m_writeLayout->setTouchEnable(false,true);
		m_writeLayout->setVisible(false);
		m_fujianLayout = dynamic_cast<Layout*>(lay->getChildByName("fujianPanel"));
		m_fujianLayout->setTouchEnable(false,true);
		m_fujianLayout->setVisible(false);
		UITextButton* returnBtn = dynamic_cast<UITextButton*>(lay->getChildByName("returnBtn"));
		returnBtn->addReleaseEvent(this, coco_releaseselector(MailLayer::closeBtnCallBack));

		UIScrollView* scroV = dynamic_cast<UIScrollView*>(m_mailLayout->getChildByName("ScrollView"));

		for (int i = 0; i <5; i++)
		{
			UIButton* scroPanel = dynamic_cast<UIButton*>(scroV->getChildByName(CCString::createWithFormat("listBtn_%d", i)->getCString()));
			scroPanel->addReleaseEvent(this, coco_releaseselector(MailLayer::scroCallBack));		
		}
		m_leftBtn = dynamic_cast<UITextButton*>(m_writeLayout->getChildByName("leftBtn"));
		m_leftBtn->addReleaseEvent(this, coco_releaseselector(MailLayer::leftBtnCallBack));

		m_rightBtn = dynamic_cast<UITextButton*>(m_writeLayout->getChildByName("rightBtn"));
		m_rightBtn->addReleaseEvent(this, coco_releaseselector(MailLayer::rightBtnCallBack));

		UITextButton* writeBtn = dynamic_cast<UITextButton*>(m_mailLayout->getChildByName("writeBtn"));
		writeBtn->addReleaseEvent(this, coco_releaseselector(MailLayer::writeBtnCallBack));

		for (int i = 0; i < 2; i++)
		{
			UIImageView* img = dynamic_cast<UIImageView*>(m_writeLayout->getChildByName(CCString::createWithFormat("fujian_%d", i)->getCString()));
			img->addReleaseEvent(this,coco_releaseselector(MailLayer::fujianBtnCallBack));
		}
		bRet = true;

	} while (0);

	return bRet;
}



void MailLayer::leftBtnCallBack(CCObject* pSender)
{

}

void MailLayer::closeBtnCallBack(CCObject* pSender)
{
	switch(layerNum){
	case MAILLAYER_TAG_MAIL:
		{
			m_Mediator->dispose();
		}break;
	case MAILLAYER_TAG_WRITE:
	case MAILLAYER_TAG_RECEIVE:
	case MAILLAYER_TAG_FUJIAN:
		{
			layerNum = MAILLAYER_TAG_MAIL;
			updateLayer();
		}break;
	default:
		break;
	}

}


void MailLayer::onEnter()
{
	CCLayer::onEnter();
	setTouchEnabled(true);
	setKeypadEnabled(true);
}

void MailLayer::registerWithTouchDispatcher( void )
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -190, true);
}

bool MailLayer::ccTouchBegan( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent )
{
	return true;
}

void MailLayer::ccTouchEnded( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent )
{

}

void MailLayer::scroCallBack( CCObject* pSender )
{
	UIButton* tempPanel = dynamic_cast<UIButton*>(pSender);
	int temp = tempPanel->getTag();

// 	UIScrollView* scroV = dynamic_cast<UIScrollView*>(m_mailLayout->getChildByName("ScrollView"));
// 	UIButton* scroPanel[5];
// 	for (int i = 0; i < 5; i++)
// 	{
// 		scroPanel[i] = dynamic_cast<Layout*>(scroV->getChildByName(CCString::createWithFormat("Panel_%d", i)->getCString()));
// 		scroPanel[i]->setBackGroundColor(ccc3(150,200,255));
// 	}
// 	
// 	scroPanel[temp % 100]->setBackGroundColor(ccc3(255,20,255));

	layerNum = MAILLAYER_TAG_RECEIVE;
	updateLayer();
}

void MailLayer::updateLayer()
{
	switch(layerNum)
	{
	case MAILLAYER_TAG_MAIL:
		{
			m_mailLayout->setVisible(true);
			m_mailLayout->setTouchEnable(true,true);
			m_writeLayout->setVisible(false);
			m_writeLayout->setTouchEnable(false,true);
			m_fujianLayout->setVisible(false);
			m_fujianLayout->setTouchEnable(false,true);
		}break;
	case MAILLAYER_TAG_RECEIVE:
		{
			m_mailLayout->setVisible(true);
			m_mailLayout->setTouchEnable(true,true);
			m_writeLayout->setVisible(true);
			m_writeLayout->setTouchEnable(true,true);
			m_fujianLayout->setVisible(false);
			m_fujianLayout->setTouchEnable(false,true);

			m_leftBtn->setText(LanguageManager::shareManager()->getContentByKey("CLUB_LQ").c_str());
			m_rightBtn->setText(LanguageManager::shareManager()->getContentByKey("CLUB_HF").c_str());
			m_leftBtn->setVisible(true);
		}break;
	case MAILLAYER_TAG_FUJIAN:
		{
			m_mailLayout->setVisible(false);
			m_mailLayout->setTouchEnable(false,true);
			m_writeLayout->setVisible(true);
			m_writeLayout->setTouchEnable(true,true);
			m_fujianLayout->setVisible(true);
			m_fujianLayout->setTouchEnable(true,true);
		}break;
	case MAILLAYER_TAG_WRITE:
		{
			m_mailLayout->setVisible(true);
			m_mailLayout->setTouchEnable(true,true);
			m_writeLayout->setVisible(true);
			m_writeLayout->setTouchEnable(true,true);
			m_fujianLayout->setVisible(false);
			m_fujianLayout->setTouchEnable(false,true);

			m_leftBtn->setText(LanguageManager::shareManager()->getContentByKey("CLUB_LQ").c_str());
			m_rightBtn->setText(LanguageManager::shareManager()->getContentByKey("CLUB_FS").c_str());
			m_leftBtn->setVisible(false);
		}
	default:
		break;
	}
}

void MailLayer::rightBtnCallBack( CCObject* pSender )
{
	switch(layerNum)
	{
	case MAILLAYER_TAG_RECEIVE:
		{
			m_mailLayout->setVisible(true);
			m_mailLayout->setTouchEnable(true,true);
			m_writeLayout->setVisible(true);
			m_writeLayout->setTouchEnable(true,true);
			m_fujianLayout->setVisible(false);
			m_fujianLayout->setTouchEnable(false,true);

			m_leftBtn->setText(LanguageManager::shareManager()->getContentByKey("CLUB_LQ").c_str());
			m_rightBtn->setText(LanguageManager::shareManager()->getContentByKey("CLUB_FS").c_str());
			m_leftBtn->setVisible(false);

			layerNum = MAILLAYER_TAG_WRITE;
		}break;
	case MAILLAYER_TAG_FUJIAN:
	case MAILLAYER_TAG_WRITE:
		{
			m_mailLayout->setVisible(true);
			m_mailLayout->setTouchEnable(true,true);
			m_writeLayout->setVisible(false);
			m_writeLayout->setTouchEnable(false,true);
			m_fujianLayout->setVisible(false);
			m_fujianLayout->setTouchEnable(false,true);

			layerNum = MAILLAYER_TAG_MAIL;
		}break;
	default:
		break;
	}
}

void MailLayer::writeBtnCallBack( CCObject* pSender )
{
	if (layerNum == MAILLAYER_TAG_MAIL)
	{
		layerNum = MAILLAYER_TAG_WRITE;
		updateLayer();
	}
}

void MailLayer::fujianBtnCallBack( CCObject* pSender )
{
	if (layerNum == MAILLAYER_TAG_WRITE)
	{
		layerNum = MAILLAYER_TAG_FUJIAN;
		updateLayer();
	}
}

void MailLayer::keyBackClicked()
{
	closeBtnCallBack(NULL);
}
