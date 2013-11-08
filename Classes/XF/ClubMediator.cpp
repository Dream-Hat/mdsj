#include "ClubMediator.h"
#include "../ZMQ/GameDef.h"
#include "../ZMQ/MessageCenter.h"
#include "../ZMQ/layerManager.h"
#include "../ZLL/LanguageManager.h"

ClubMediator::ClubMediator()
{
	_scene = NULL;

	ADD_EVENT_LISTENER(OnClubOpen,NULL,this,Event::CLUB_OPEN,ClubMediator)
}

ClubMediator::~ClubMediator()
{
	if (_scene)
	{
		REMOVE_SCENE_FROM_LAYER(_scene)
	}
}

void ClubMediator::OnPackage( short xy,char* pack,int len )
{

}

void ClubMediator::OnClubOpen( CCObject* sender,int msgid,cocos2d::CCObject* obj)
{
	if (_scene == NULL)
	{
		_scene = ClubLayer::create();
		//_scene->retain();
		_scene->m_Mediator = this;
		ADD_SCENE_TO_LAYER(_scene.obj(),LayerManager::sceneUILayer);
	}
}

void ClubMediator::dispose()
{
	if (_scene)
	{
		_scene->setKeypadEnabled(false);
		REMOVE_SCENE_FROM_LAYER(_scene)
			//_scene->release();
			_scene = NULL;
	}
}


bool ClubLayer::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!CCLayer::init());
		m_Mediator = NULL;
		m_isFirstloadPage = true;

		m_pUILayer = UILayer::create();
		m_pUILayer->setTouchPriority(-200);
		m_pUILayer->scheduleUpdate();
		addChild(m_pUILayer);

		m_pLayout = dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile("ui/ClubUI/ClubUI.json"));
		m_pUILayer->addWidget(m_pLayout);

		m_layerLayout = dynamic_cast<Layout*>(m_pLayout->getChildByName("layerPanel"));
		m_layerLayout->setVisible(true);
		m_jjLayout = dynamic_cast<Layout*>(m_layerLayout->getChildByName("jjPanel"));
		m_jjLayout->setVisible(false);
		m_jjLayout->setTouchEnable(false,true);
		m_jsLayout = dynamic_cast<Layout*>(m_layerLayout->getChildByName("jsPanel"));
		m_jsLayout->setVisible(false);
		m_jsLayout->setTouchEnable(false,true);
		m_cyLayout = dynamic_cast<Layout*>(m_layerLayout->getChildByName("cyPanel"));
		m_cyLayout->setVisible(true);
		m_cyLayout->setTouchEnable(true,true);
		layerNum = CLUBLAYER_TAG_LAYER;
		m_searchLayout = dynamic_cast<Layout*>(m_pLayout->getChildByName("rootPanel"));
		m_searchLayout->setTouchEnable(false,true);
		m_searchLayout->setVisible(false);
		m_tipsLayout = dynamic_cast<Layout*>(m_pLayout->getChildByName("tips_Panel"));
		m_tipsLayout->setTouchEnable(false,true);
		m_tipsLayout->setVisible(false);

		UITextButton* returnBtn = dynamic_cast<UITextButton*>(m_layerLayout->getChildByName("returnBtn"));
		returnBtn->addReleaseEvent(this, coco_releaseselector(ClubLayer::closeBtnCallBack));
		UITextButton* returnBtn1 = dynamic_cast<UITextButton*>(m_searchLayout->getChildByName("returnBtn"));
		returnBtn1->addReleaseEvent(this, coco_releaseselector(ClubLayer::closeBtnCallBack));
		UITextButton* returnBtn2 = dynamic_cast<UITextButton*>(m_tipsLayout->getChildByName("returnBtn"));
		returnBtn2->addReleaseEvent(this, coco_releaseselector(ClubLayer::closeBtnCallBack));

		UIScrollView* scroV = dynamic_cast<UIScrollView*>(m_layerLayout->getChildByName("ScrollView"));

		Layout* tapbtn_panel = dynamic_cast<Layout*>(m_layerLayout->getChildByName("tapbtn_Panel"));
		for (int i = 0; i < 4; i++)
		{
			Layout* scroPanel = dynamic_cast<Layout*>(scroV->getChildByName(CCString::createWithFormat("Panel_%d", i)->getCString()));
			scroPanel->addReleaseEvent(this, coco_releaseselector(ClubLayer::scroCallBack));

			m_topBtn[i] = dynamic_cast<UITextButton*>(tapbtn_panel->getChildByName(CCString::createWithFormat("topBtn_%d", i)->getCString()));
			m_topBtn[i]->addReleaseEvent(this, coco_releaseselector(ClubLayer::tapMenuCallBack));
		}
		m_topBtn[1]->disable();
		m_topBtn[2]->disable();
		m_topBtn[3]->disable();
		m_topBtn[2]->setVisible(false);
		m_topBtn[3]->setVisible(false);
		UIImageView* newImg = dynamic_cast<UIImageView*>(m_layerLayout->getChildByName("newImg"));
		newImg->setVisible(false);
		m_joinBtn = dynamic_cast<UITextButton*>(m_layerLayout->getChildByName("joinBtn"));
		m_joinBtn->addReleaseEvent(this, coco_releaseselector(ClubLayer::joinBtnCallBack));

		m_searchBtn= dynamic_cast<UITextButton*>(m_layerLayout->getChildByName("searchBtn"));
		m_searchBtn->addReleaseEvent(this, coco_releaseselector(ClubLayer::searchBtnCallBack));

		m_yesBtn= dynamic_cast<UITextButton*>(m_tipsLayout->getChildByName("yesBtn"));
		m_yesBtn->addReleaseEvent(this, coco_releaseselector(ClubLayer::yesBtnCallBack));

		m_noBtn= dynamic_cast<UITextButton*>(m_tipsLayout->getChildByName("noBtn"));
		m_noBtn->addReleaseEvent(this, coco_releaseselector(ClubLayer::noBtnCallBack));
		
		bRet = true;

	} while (0);

	return bRet;
}



void ClubLayer::joinBtnCallBack(CCObject* pSender)
{
	switch(layerNum){
	case CLUBLAYER_TAG_LAYER:
		{
		}break;
	case CLUBLAYER_TAG_NEIRONG_CY:
		{
			layerNum = CLUBLAYER_TAG_TIPS;
			updateLayer(layerNum);
		}break;

	default:
		break;
	}
}

void ClubLayer::closeBtnCallBack(CCObject* pSender)
{
	switch(layerNum){
	case CLUBLAYER_TAG_LAYER:
		{
			m_Mediator->dispose();
		}break;
	case CLUBLAYER_TAG_SEARCH:
		{
			layerNum = CLUBLAYER_TAG_LAYER;
			updateLayer(layerNum);
		}break;
	case CLUBLAYER_TAG_TIPS:
		{
			layerNum = CLUBLAYER_TAG_NEIRONG_CY;
			updateLayer(layerNum);
		}break;
	case CLUBLAYER_TAG_NEIRONG_JS:
	case CLUBLAYER_TAG_NEIRONG_JJ:
	case CLUBLAYER_TAG_NEIRONG_CY:
		{
			layerNum = CLUBLAYER_TAG_LAYER;
			updateLayer(layerNum);
		}break;
	case CLUBLAYER_TAG_YAOQING:
		{
			layerNum = CLUBLAYER_TAG_NEIRONG_CY;
			updateLayer(layerNum);
		}break;
	case CLUBLAYER_TAG_NEIRONG_XSQ:
		{
			layerNum = CLUBLAYER_TAG_NEIRONG_CY;
			updateLayer(layerNum);
		}break;
	default:
		break;
	}


}

void ClubLayer::searchBtnCallBack( CCObject* pSender)
{
	switch(layerNum)
	{
	case CLUBLAYER_TAG_LAYER:
		{
			layerNum = CLUBLAYER_TAG_SEARCH;
			setVis(false);
			m_searchLayout->setTouchEnable(true,true);
			m_searchLayout->setVisible(true);
		}break;
	case CLUBLAYER_TAG_NEIRONG_CY:
		{
			layerNum = CLUBLAYER_TAG_YAOQING;
			updateLayer(layerNum);
		}break;
	default:
		break;
	}

}
void ClubLayer::onEnter()
{
	CCLayer::onEnter();
	setTouchEnabled(true);
	setKeypadEnabled(true);
}

void ClubLayer::registerWithTouchDispatcher( void )
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -190, true);
}

bool ClubLayer::ccTouchBegan( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent )
{
	return true;
}

void ClubLayer::ccTouchEnded( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent )
{

}

void ClubLayer::scroCallBack( CCObject* pSender )
{
	Layout* tempPanel = dynamic_cast<Layout*>(pSender);
	int temp = tempPanel->getTag();


	UIScrollView* scroV = dynamic_cast<UIScrollView*>(m_pLayout->getChildByName("ScrollView"));
	Layout* scroPanel[4];
	for (int i = 0; i < 4; i++)
	{
		scroPanel[i] = dynamic_cast<Layout*>(scroV->getChildByName(CCString::createWithFormat("Panel_%d", i)->getCString()));
		scroPanel[i]->setBackGroundColor(ccc3(150,200,255));
	}
	
	scroPanel[temp % 100]->setBackGroundColor(ccc3(255,20,255));
}

void ClubLayer::tapMenuCallBack( CCObject* pSender )
{
	 UIButton* button = dynamic_cast<UIButton*>(pSender);

	 int temp = button->getTag() %120;
	 for (int i = 0; i <4;i++)
	 {
		 m_topBtn[i]->active();
	 }

	 if (layerNum == CLUBLAYER_TAG_LAYER && temp == 0)
	 {
		 layerNum = CLUBLAYER_TAG_NEIRONG_JJ;
		 updateLayer(layerNum);
	 }
	 else
	 {
		 switch(temp)
		 {
		 case 0:
			 {
				 layerNum = CLUBLAYER_TAG_NEIRONG_JJ;
				 updateLayer(layerNum);
			 }break;
		 case 1:
			 {
				 layerNum = CLUBLAYER_TAG_NEIRONG_CY;
				 updateLayer(layerNum);
			 }break;
		 case 2:
			 {
				 layerNum = CLUBLAYER_TAG_NEIRONG_JS;
				 updateLayer(layerNum);
			 }break;
		 case 3:
			 {
				 layerNum= CLUBLAYER_TAG_NEIRONG_XSQ;
				 updateLayer(layerNum);
			 }break;
		 default:
			 break;
		 }
	 }
}

void ClubLayer::closeBtnCallBack1(CCObject* pSender)
{
	m_pUILayer->setVisible(true);
	m_pUILayer->setTouchEnabled(true);
}

void ClubLayer::updateLayer(ClubLayerType num)
{
	if (CLUBLAYER_TAG_TIPS == num || CLUBLAYER_TAG_NEIRONG_XSQ == num)
	{
		if (m_isFirstloadPage)
		{
			Layout* nrPanel = dynamic_cast<Layout*>(m_tipsLayout->getChildByName("nrPanel"));
			m_isFirstloadPage = false;
			UIPageView* pageView = UIPageView::create();
			pageView->setTouchEnable(true);
			pageView->setSize(nrPanel->getSize());
			pageView->setAnchorPoint(ccp(0,0));
			pageView->setPosition(ccp(0,0));
			pageView->setWidgetTag(CLUBLAYER_TAG_ROOT);
			nrPanel->addChild(pageView);
			for (int i = 0;i<3;i++)
			{
				Layout* pgLayout = dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile("ui/ClubUI/ClubUI_Page.json"));
				pgLayout->setWidgetTag(CLUBLAYER_TAG_ROOT+i+1);
				pageView->addPage(pgLayout);
			}
		}
	}
	switch(num){
	case CLUBLAYER_TAG_LAYER:
		{
			m_topBtn[2]->disable();
			m_topBtn[3]->disable();
			m_topBtn[2]->setVisible(false);
			m_topBtn[3]->setVisible(false);
			UIImageView* newImg = dynamic_cast<UIImageView*>(m_layerLayout->getChildByName("newImg"));
			newImg->setVisible(false);
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

			setVis(false);
			m_cyLayout->setVisible(true);
			m_cyLayout->setTouchEnable(true,true);
		}break;
	case CLUBLAYER_TAG_SEARCH:
		{

		}break;
	case CLUBLAYER_TAG_TIPS:
		{
			setVis(false);
			m_tipsLayout->setTouchEnable(true,true);
			m_tipsLayout->setVisible(true);
			m_yesBtn->setText(LanguageManager::shareManager()->getContentByKey("CLUB_KC").c_str());
			m_noBtn->setText(LanguageManager::shareManager()->getContentByKey("CLUB_TZ").c_str());
		}break;
	case CLUBLAYER_TAG_NEIRONG_CY:
		{
			m_topBtn[2]->active();
			m_topBtn[3]->active();
			m_topBtn[2]->setVisible(true);
			m_topBtn[3]->setVisible(true);
			UIImageView* newImg = dynamic_cast<UIImageView*>(m_layerLayout->getChildByName("newImg"));
			newImg->setVisible(true);
			m_topBtn[0]->setText(LanguageManager::shareManager()->getContentByKey("CLUB_JJ").c_str());
			m_topBtn[1]->setText(LanguageManager::shareManager()->getContentByKey("CLUB_CY").c_str());
			m_topBtn[1]->disable();

			setVis(false);
			m_cyLayout->setVisible(true);
			m_cyLayout->setTouchEnable(true,true);

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
	case CLUBLAYER_TAG_YAOQING:
		{
			m_joinBtn->setVisible(false);
			m_searchBtn->setText(LanguageManager::shareManager()->getContentByKey("CLUB_SS").c_str());
			m_topBtn[2]->setVisible(false);
			m_topBtn[3]->setVisible(false);
			UIImageView* newImg = dynamic_cast<UIImageView*>(m_layerLayout->getChildByName("newImg"));
			newImg->setVisible(false);
			m_topBtn[0]->setText(LanguageManager::shareManager()->getContentByKey("CLUB_HY").c_str());
			m_topBtn[1]->setText(LanguageManager::shareManager()->getContentByKey("CLUB_ZJLX").c_str());
			m_topBtn[1]->disable();
		}break;
	case CLUBLAYER_TAG_NEIRONG_XSQ:
		{
			setVis(false);
			m_tipsLayout->setTouchEnable(true,true);
			m_tipsLayout->setVisible(true);
			m_yesBtn->setText(LanguageManager::shareManager()->getContentByKey("CLUB_TY").c_str());
			m_noBtn->setText(LanguageManager::shareManager()->getContentByKey("CLUB_JUJUE").c_str());
		}break;
	case CLUBLAYER_TAG_NEIRONG_JJ:
		{
			m_topBtn[2]->active();
			m_topBtn[3]->active();
			m_topBtn[2]->setVisible(true);
			m_topBtn[3]->setVisible(true);
			UIImageView* newImg = dynamic_cast<UIImageView*>(m_layerLayout->getChildByName("newImg"));
			newImg->setVisible(true);
			m_topBtn[0]->setText(LanguageManager::shareManager()->getContentByKey("CLUB_JJ").c_str());
			m_topBtn[1]->setText(LanguageManager::shareManager()->getContentByKey("CLUB_CY").c_str());
			m_topBtn[0]->disable();
			setVis(false);
			m_jjLayout->setTouchEnable(true,true);
			m_jjLayout->setVisible(true);
		}break;
	case CLUBLAYER_TAG_NEIRONG_JS:
		{
			m_topBtn[2]->disable();
			setVis(false);
			m_jsLayout->setTouchEnable(true,true);
			m_jsLayout->setVisible(true);
		}break;
	default:
		break;
	}
}

void ClubLayer::yesBtnCallBack( CCObject* pSender )
{

}

void ClubLayer::noBtnCallBack( CCObject* pSender )
{

}

void ClubLayer::setVis( bool isvis )
{
	m_jsLayout->setVisible(isvis);
	m_jsLayout->setTouchEnable(isvis,true);
	m_jjLayout->setVisible(isvis);
	m_jjLayout->setTouchEnable(isvis,true);
	m_cyLayout->setVisible(isvis);
	m_cyLayout->setTouchEnable(isvis,true);
	m_searchLayout->setTouchEnable(isvis,true);
	m_searchLayout->setVisible(isvis);
	m_tipsLayout->setTouchEnable(isvis,true);
	m_tipsLayout->setVisible(isvis);
}

void ClubLayer::keyBackClicked()
{
	closeBtnCallBack(NULL);
}
