#include "ChatMediator.h"
#include "../ZMQ/GameDef.h"
#include "../ZMQ/AllCommandSignal.h"
#include "../ZMQ/layerManager.h"
#include "../ZLL/LanguageManager.h"


ChatMediator::ChatMediator()
{
	_scene = NULL;

	ADD_EVENT_LISTENER(OnChatOpen,NULL,this,Event::CHAT_OPEN,ChatMediator)
}

ChatMediator::~ChatMediator()
{
	if (_scene)
	{
		REMOVE_SCENE_FROM_LAYER(_scene)
	}
}

void ChatMediator::OnPackage( short xy,char* pack,int len )
{

}

void ChatMediator::OnChatOpen( CCObject* sender,int msgid,cocos2d::CCObject* obj)
{
	if (_scene == NULL)
	{
		_scene = ChatLayer::create();
		//_scene->retain();
		_scene->m_Mediator = this;
		ADD_SCENE_TO_LAYER(_scene.obj(),LayerManager::sceneUILayer);
	}
}

void ChatMediator::dispose()
{
	if (_scene)
	{
		_scene->setKeypadEnabled(false);
		REMOVE_SCENE_FROM_LAYER(_scene)
			//_scene->release();
			_scene = NULL;
	}
}


bool ChatLayer::init()
{

	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!CCLayer::init());

		m_Mediator = NULL;
		m_pLayout = NULL;
		m_pUILayer = NULL;

		m_pUILayer = UILayer::create();
		m_pUILayer->setTouchPriority(-200);
		m_pUILayer->scheduleUpdate();
		addChild(m_pUILayer);

		// register root from json
		m_pLayout = dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile("ui/ChatUI/ChatUI.json"));
		m_pUILayer->addWidget(m_pLayout);

		// register button
		Layout* button_panel = dynamic_cast<Layout*>(m_pLayout->getChildByName("Btn_Panel"));

		Layout* keyP = dynamic_cast<Layout*>(m_pLayout->getChildByName("keyPanel"));
		keyP->addReleaseEvent(this,coco_releaseselector(ChatLayer::keyPBtnCallBack));

		UIButton* closeBtn = dynamic_cast<UIButton*>(m_pLayout->getChildByName("closeBtn"));
		closeBtn->addReleaseEvent(this, coco_releaseselector(ChatLayer::closeBtnCallBack));

		UIButton* sendBtn = dynamic_cast<UIButton*>(m_pLayout->getChildByName("sendBtn"));
		sendBtn->addReleaseEvent(this, coco_releaseselector(ChatLayer::sendBtnCallBack));

		UIButton* curBtn = dynamic_cast<UIButton*>(m_pLayout->getChildByName("curBtn"));
		curBtn->addReleaseEvent(this, coco_releaseselector(ChatLayer::curBtnCallBack));

		m_shuruK = dynamic_cast<UITextField*>(m_pLayout->getChildByName("shuruK"));

		m_scro = dynamic_cast<UIScrollView*>(m_pLayout->getChildByName("ScrollView"));

		for (int i = 0; i < 12;i++)
		{
			shurulable[i] = dynamic_cast<UILabel*>(m_scro->getChildByName(CCString::createWithFormat("shuruLable_%d",i)->getCString()));
			shurulable[i]->setVisible(false);
		}
		shuruNum = 0;

		Layout* menuBtn= dynamic_cast<Layout*>(m_pLayout->getChildByName("menubtn_Panel"));
		for (int i = 0; i< 3;i++)
		{
			m_menuBtn[i] = dynamic_cast<UITextButton*>(menuBtn->getChildByName(CCString::createWithFormat("menuBtn_%d",i)->getCString()));
			m_menuBtn[i]->addReleaseEvent(this,coco_releaseselector(ChatLayer::menuBtnCallBack));
		}
		m_menuBtn[0]->disable();
		bRet = true;

	} while (0);

	return bRet;
}



void ChatLayer::sendBtnCallBack( CCObject* pSender )
{	

	if (shuruNum < 12)
	{
		shurulable[shuruNum%12]->setText(CCString::createWithFormat("%s:%s",LanguageManager::shareManager()->getContentByKey("CLUB_DQ").c_str(),m_shuruK->getStringValue())->getCString());
		shurulable[shuruNum]->setVisible(true);
	}
	else
	{
		for (int i = 0; i <11;i++)
		{
			shurulable[i]->setText(shurulable[i+1]->getStringValue());
		}
		shurulable[11]->setText(CCString::createWithFormat("%s:%s",LanguageManager::shareManager()->getContentByKey("CLUB_DQ").c_str(),m_shuruK->getStringValue())->getCString());
	}
	m_shuruK->setText("");
	shuruNum++;

	
}

void ChatLayer::closeBtnCallBack( CCObject* pSender )
{
	m_Mediator->dispose();
}

void ChatLayer::curBtnCallBack( CCObject* pSender )
{
	int a = 0 ;
	a = 0;
}
void ChatLayer::onEnter()
{
	CCLayer::onEnter();
	setTouchEnabled(true);
	setKeypadEnabled(true);
}

void ChatLayer::registerWithTouchDispatcher( void )
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -190, true);
}

bool ChatLayer::ccTouchBegan( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent )
{
	return true;
}

void ChatLayer::ccTouchEnded( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent )
{

}

void ChatLayer::menuBtnCallBack( CCObject* pSender )
{
	UITextButton* temp = dynamic_cast<UITextButton*>(pSender);
	int tempNum = temp->getTag() %40;
	for (int i = 0; i< 3;i++)
	{
		m_menuBtn[i]->active();
	}
	m_menuBtn[tempNum]->disable();
	if (tempNum >0)
	{
		for (int i = 0; i < shuruNum%12;i++)
		{
			shurulable[i]->setVisible(false);
		}
	}
	else
	{
		for (int i = 0; i < shuruNum%12;i++)
		{
			shurulable[i]->setVisible(true);
		}
	}
	
}

void ChatLayer::keyPBtnCallBack( CCObject* pSender )
{
	//m_shuruK->attachWithIME();
}

void ChatLayer::keyBackClicked()
{
	closeBtnCallBack(NULL);
}

