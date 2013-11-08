#include "FriendMediator.h"
#include "../ZMQ/GameDef.h"
#include "../ZMQ/AllCommandSignal.h"
#include "../ZMQ/layerManager.h"
#include "../ZLL/LanguageManager.h"


FriendMediator::FriendMediator()
{
	_scene = NULL;

	ADD_EVENT_LISTENER(OnFriendOpen,NULL,this,Event::FRIEND_OPEN,FriendMediator)
}

FriendMediator::~FriendMediator()
{
	if (_scene)
	{
		REMOVE_SCENE_FROM_LAYER(_scene)
	}
}

void FriendMediator::OnPackage( short xy,char* pack,int len )
{

}

void FriendMediator::OnFriendOpen( CCObject* sender,int msgid,cocos2d::CCObject* obj)
{
	if (_scene == NULL)
	{
		_scene = FriendLayer::create();
		//_scene->retain();
		_scene->m_Mediator = this;
		ADD_SCENE_TO_LAYER(_scene.obj(),LayerManager::sceneUILayer);
	}
}

void FriendMediator::dispose()
{
	if (_scene)
	{
		_scene->setKeypadEnabled(false);
		REMOVE_SCENE_FROM_LAYER(_scene)
			//_scene->release();
			_scene = NULL;
	}
}

bool FriendLayer::init()
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

		m_pLayout = dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile("ui/FriendUI/FriendUI.json"));
		m_pUILayer->addWidget(m_pLayout);

		m_layerLayout = dynamic_cast<Layout*>(m_pLayout->getChildByName("layerPanel"));
		m_layerLayout->setVisible(true);
		layerNum = FRIENDLAYER_TAG_LAYER;
		m_tipsLayout = dynamic_cast<Layout*>(m_pLayout->getChildByName("tips_Panel"));
		m_tipsLayout->setTouchEnable(false,true);
		m_tipsLayout->setVisible(false);

		UITextButton* returnBtn = dynamic_cast<UITextButton*>(m_layerLayout->getChildByName("returnBtn"));
		returnBtn->addReleaseEvent(this, coco_releaseselector(FriendLayer::closeBtnCallBack));
		UITextButton* returnBtn2 = dynamic_cast<UITextButton*>(m_tipsLayout->getChildByName("returnBtn"));
		returnBtn2->addReleaseEvent(this, coco_releaseselector(FriendLayer::closeBtnCallBack));

		UIScrollView* scroV = dynamic_cast<UIScrollView*>(m_layerLayout->getChildByName("ScrollView"));

		Layout* tapbtn_panel = dynamic_cast<Layout*>(m_layerLayout->getChildByName("tapbtn_Panel"));
		for (int i = 0; i <5; i++)
		{
			Layout* scroPanel = dynamic_cast<Layout*>(scroV->getChildByName(CCString::createWithFormat("Panel_%d", i)->getCString()));
			scroPanel->addReleaseEvent(this, coco_releaseselector(FriendLayer::scroCallBack));

			if (i < 3)
			{
				m_topBtn[i] = dynamic_cast<UITextButton*>(tapbtn_panel->getChildByName(CCString::createWithFormat("topBtn_%d", i)->getCString()));
				m_topBtn[i]->addReleaseEvent(this, coco_releaseselector(FriendLayer::tapMenuCallBack));
			}
			
		}
		m_topBtn[0]->disable();


		m_yesBtn = dynamic_cast<UITextButton*>(m_tipsLayout->getChildByName("yesBtn"));
		m_yesBtn->addReleaseEvent(this, coco_releaseselector(FriendLayer::yesBtnCallBack));

		m_noBtn= dynamic_cast<UITextButton*>(m_tipsLayout->getChildByName("noBtn"));
		m_noBtn->addReleaseEvent(this, coco_releaseselector(FriendLayer::noBtnCallBack));

		m_writeBtn= dynamic_cast<UITextButton*>(m_tipsLayout->getChildByName("writeBtn"));
		m_writeBtn->addReleaseEvent(this, coco_releaseselector(FriendLayer::writeBtnCallBack));

		m_delBtn= dynamic_cast<UITextButton*>(m_tipsLayout->getChildByName("delBtn"));
		m_delBtn->addReleaseEvent(this, coco_releaseselector(FriendLayer::delBtnCallBack));

		
		bRet = true;

	} while (0);

	return bRet;
}



void FriendLayer::yesBtnCallBack(CCObject* pSender)
{
/*	switch(layerNum){
	case FRIENDLAYER_TAG_LAYER:
		{
		}break;
	case FriendLayer_TAG_NEIRONG:
		{
			layerNum = FriendLayer_TAG_TIPS;
			m_layerLayout->setVisible(false);
			m_layerLayout->setTouchEnable(false,true);
			m_tipsLayout->setTouchEnable(true,true);
			m_tipsLayout->setVisible(true);
		}break;

	default:
		break;
	}
	*/
}

void FriendLayer::closeBtnCallBack(CCObject* pSender)
{
	switch(layerNum){
	case FRIENDLAYER_TAG_LAYER:
		{
			m_Mediator->dispose();
		}break;
/*	case FRIENDLAYER_TAG_TIPS:
		{
			layerNum = FriendLayer_TAG_SEARCH;
			m_layerLayout->setVisible(true);
			m_layerLayout->setTouchEnable(true,true);

			m_searchLayout->setTouchEnable(false,true);
			m_searchLayout->setVisible(false);
			m_tipsLayout->setTouchEnable(false,true);
			m_tipsLayout->setVisible(false);
		}break;
	case FriendLayer_TAG_TIPS:
		{
			layerNum = FriendLayer_TAG_LAYER;
			m_layerLayout->setVisible(true);
			m_layerLayout->setTouchEnable(true,true);

			m_searchLayout->setTouchEnable(false,true);
			m_searchLayout->setVisible(false);
			m_tipsLayout->setTouchEnable(false,true);
			m_tipsLayout->setVisible(false);
		}break;
	case FriendLayer_TAG_NEIRONG:
		{
			layerNum = FriendLayer_TAG_LAYER;
			updateLayer(layerNum);
		}break;
	case FriendLayer_TAG_YAOQING:
		{
			layerNum = FriendLayer_TAG_NEIRONG;
			updateLayer(layerNum);
		}break;
		*/
	default:
		break;
	}

}

void FriendLayer::noBtnCallBack( CCObject* pSender)
{
/*	switch(layerNum)
	{
	case FriendLayer_TAG_LAYER:
		{
			layerNum = FriendLayer_TAG_SEARCH;
			m_layerLayout->setVisible(true);
			m_layerLayout->setTouchEnable(false,true);

			m_searchLayout->setTouchEnable(true,true);
			m_searchLayout->setVisible(true);
			m_tipsLayout->setTouchEnable(false,true);
			m_tipsLayout->setVisible(false);
		}break;
	case FriendLayer_TAG_NEIRONG:
		{
			layerNum = FriendLayer_TAG_YAOQING;
			updateLayer(layerNum);
		}break;
	default:
		break;
	}
	*/
}
void FriendLayer::onEnter()
{
	CCLayer::onEnter();
	setTouchEnabled(true);
	setKeypadEnabled(true);
}

void FriendLayer::registerWithTouchDispatcher( void )
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -190, true);
}

bool FriendLayer::ccTouchBegan( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent )
{
	return true;
}

void FriendLayer::ccTouchEnded( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent )
{

}

void FriendLayer::scroCallBack( CCObject* pSender )
{
	Layout* tempPanel = dynamic_cast<Layout*>(pSender);
	int temp = tempPanel->getTag();


	UIScrollView* scroV = dynamic_cast<UIScrollView*>(m_pLayout->getChildByName("ScrollView"));
	Layout* scroPanel[5];
	for (int i = 0; i < 5; i++)
	{
		scroPanel[i] = dynamic_cast<Layout*>(scroV->getChildByName(CCString::createWithFormat("Panel_%d", i)->getCString()));
	}
	
	scroPanel[temp % 100]->setBackGroundColor(ccc3(255,20,255));
}

void FriendLayer::tapMenuCallBack( CCObject* pSender )
{
	 UIButton* button = dynamic_cast<UIButton*>(pSender);

	 int temp = button->getTag() %120;
	 for (int i = 0; i <3;i++)
	 {
		 m_topBtn[i]->active();
	 }
	 m_topBtn[temp]->disable();
	
	 /*if (layerNum == FriendLayer_TAG_LAYER && temp == 0)
	 {
		 layerNum = FriendLayer_TAG_NEIRONG;
		 updateLayer(layerNum);
	 }
	 */
}

void FriendLayer::writeBtnCallBack( CCObject* pSender )
{
	m_pUILayer->setVisible(true);
	m_pUILayer->setTouchEnabled(true);
}

void FriendLayer::updateLayer(int num)
{
/*	switch(num){
	case FriendLayer_TAG_LAYER:
		{
			m_topBtn[2]->disable();
			m_topBtn[3]->disable();
			m_topBtn[2]->setVisible(false);
			m_topBtn[3]->setVisible(false);
			m_topBtn[0]->setText(LanguageManager::shareManager()->getContentByKey("CLUB_STNC").c_str());
			m_topBtn[1]->setText(LanguageManager::shareManager()->getContentByKey("CLUB_QBST").c_str());
			m_topBtn[1]->disable();

			Layout* lablepanel = dynamic_cast<Layout*>(m_layerLayout->getChildByName("topLabelPanel"));
			UILabel* lable[5];
			for (int i = 0 ; i < 5; i++)
			{
				lable[i] = dynamic_cast<UILabel*>(lablepanel->getChildByName(CCString::createWithFormat("Label_%d", i)->getCString()));
			}
			lable[0]->setText(LanguageManager::shareManager()->getContentByKey("CLUB_STNC").c_str());
			lable[1]->setText(LanguageManager::shareManager()->getContentByKey("CLUB_TZNC").c_str());
			lable[2]->setText(LanguageManager::shareManager()->getContentByKey("CLUB_DJ").c_str());
			lable[3]->setText(LanguageManager::shareManager()->getContentByKey("CLUB_RS").c_str());
			lable[4]->setText(LanguageManager::shareManager()->getContentByKey("CLUB_YSQ").c_str());

			m_joinBtn->setText(LanguageManager::shareManager()->getContentByKey("CLUB_JR").c_str());
			m_searchBtn->setText(LanguageManager::shareManager()->getContentByKey("CLUB_SS").c_str());
		}break;
	case FriendLayer_TAG_SEARCH:
		{

		}break;
	case FriendLayer_TAG_TIPS:
		{

		}break;
	case FriendLayer_TAG_NEIRONG:
		{
			m_topBtn[2]->active();
			m_topBtn[3]->active();
			m_topBtn[2]->setVisible(true);
			m_topBtn[3]->setVisible(true);
			m_topBtn[0]->setText(LanguageManager::shareManager()->getContentByKey("CLUB_JJ").c_str());
			m_topBtn[1]->setText(LanguageManager::shareManager()->getContentByKey("CLUB_CY").c_str());
			m_topBtn[1]->disable();

			Layout* lablepanel = dynamic_cast<Layout*>(m_layerLayout->getChildByName("topLabelPanel"));
			UILabel* lable[5];
			for (int i = 0 ; i < 5; i++)
			{
				lable[i] = dynamic_cast<UILabel*>(lablepanel->getChildByName(CCString::createWithFormat("Label_%d", i)->getCString()));
			}
			lable[0]->setText("VIP");
			lable[1]->setText(LanguageManager::shareManager()->getContentByKey("CLUB_CYNC").c_str());
			lable[2]->setText(LanguageManager::shareManager()->getContentByKey("CLUB_ZWM").c_str());
			lable[3]->setText(LanguageManager::shareManager()->getContentByKey("CLUB_DJ").c_str());
			lable[4]->setText(LanguageManager::shareManager()->getContentByKey("CLUB_ZT").c_str());

			m_joinBtn->setText(LanguageManager::shareManager()->getContentByKey("CLUB_XX").c_str());
			m_joinBtn->setVisible(true);
			m_searchBtn->setText(LanguageManager::shareManager()->getContentByKey("CLUB_YQ").c_str());
		}break;
	case FriendLayer_TAG_YAOQING:
		{
			m_joinBtn->setVisible(false);
			m_searchBtn->setText(LanguageManager::shareManager()->getContentByKey("CLUB_SS").c_str());
			m_topBtn[2]->setVisible(false);
			m_topBtn[3]->setVisible(false);
			m_topBtn[0]->setText(LanguageManager::shareManager()->getContentByKey("CLUB_HY").c_str());
			m_topBtn[1]->setText(LanguageManager::shareManager()->getContentByKey("CLUB_ZJLX").c_str());
			m_topBtn[1]->disable();
		}break;
	default:
		break;
	}
	*/
}

void FriendLayer::delBtnCallBack( CCObject* pSender )
{

}

void FriendLayer::keyBackClicked()
{
	closeBtnCallBack(NULL);
}
