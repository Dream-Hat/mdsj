#include "TiejiangpuMediator.h"
#include "../ZMQ/GameDef.h"
#include "../ZMQ/AllCommandSignal.h"
#include "../ZMQ/layerManager.h"
#include "../ZLL/LanguageManager.h"
#include "../proto_files//LandProto.pb.h"

using namespace com::tiange::mdsj::proto;

TiejiangpuMediator::TiejiangpuMediator()
{
	_scene = NULL;

	ADD_EVENT_LISTENER(OnTiejiangpuOpen,NULL,this,Event::TIEJIANGPU_OPEN,TiejiangpuMediator)
	//ADD_PACK_LISTENER(OnPackage,this,SocketCMDConst::SMSG_LOGIN,TiejiangpuMediator)
}

TiejiangpuMediator::~TiejiangpuMediator()
{
	if (_scene)
	{
		REMOVE_SCENE_FROM_LAYER(_scene)
	}
}

void TiejiangpuMediator::OnPackage(int xy,void* pack)
{
	switch(xy)
	{
	case SocketCMDConst::SMSG_LOGIN:
		{
			LoginResponse login;
			std::string str = *((std::string*)pack);
			login.ParseFromString(str);
			std::string a = login.version();
			int b = login.result();
			b = 0;
		}break;
	case SocketCMDConst::SMSG_LOGIN_GETROLELIST:
		{

		}break;
	case SocketCMDConst::SMSG_LOGIN_CREATEROLER:
		{

		}break;
	case SocketCMDConst::SMSG_LOGIN_DELETEROLER:
		{

		}break;
	default:
		break;
	}
}

void TiejiangpuMediator::OnTiejiangpuOpen( CCObject* sender,int msgid,cocos2d::CCObject* obj)
{
	if (_scene == NULL)
	{
		_scene = TiejiangpuLayer::create();
		//_scene->retain();
		_scene->m_Mediator = this;
		ADD_SCENE_TO_LAYER(_scene.obj(),LayerManager::sceneUILayer);
	}
}

void TiejiangpuMediator::dispose()
{
	if (_scene)
	{
		_scene->setKeypadEnabled(false);
		REMOVE_SCENE_FROM_LAYER(_scene)
			//_scene->release();
			_scene = NULL;
	}
}

bool TiejiangpuLayer::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!CCLayer::init());
		m_Mediator = NULL;
		m_isFirst = true;

		m_pUILayer = UILayer::create();
		m_pUILayer->setTouchPriority(-200);
		m_pUILayer->scheduleUpdate();
		addChild(m_pUILayer);

		m_pLayout = dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile("ui/tiejiangpuUI/tiejiangpuUI.json"));
		m_pUILayer->addWidget(m_pLayout);

		m_layerLayout = dynamic_cast<Layout*>(m_pLayout->getChildByName("layerPanel"));
		m_layerLayout->setVisible(true);
		m_layerNum = TJPLAYER_TAG_LAYER;
		m_tipsLayout = dynamic_cast<Layout*>(m_pLayout->getChildByName("tips_Panel"));
		m_tipsLayout->setTouchEnable(false,true);
		m_tipsLayout->setVisible(false);

		UITextButton* returnBtn = dynamic_cast<UITextButton*>(m_layerLayout->getChildByName("returnBtn"));
		returnBtn->addReleaseEvent(this, coco_releaseselector(TiejiangpuLayer::closeBtnCallBack));
		UITextButton* returnBtn2 = dynamic_cast<UITextButton*>(m_tipsLayout->getChildByName("returnBtn"));
		returnBtn2->addReleaseEvent(this, coco_releaseselector(TiejiangpuLayer::closeBtnCallBack));
		UIScrollView* scroV = dynamic_cast<UIScrollView*>(m_layerLayout->getChildByName("ScrollView"));

		Layout* tapbtn_panel = dynamic_cast<Layout*>(m_tipsLayout->getChildByName("tapbtn_Panel"));
		for (int i = 0; i <4; i++)
		{
			UIButton* scroPanel = dynamic_cast<UIButton*>(scroV->getChildByName(CCString::createWithFormat("btnList_%d", i)->getCString()));
			scroPanel->addReleaseEvent(this, coco_releaseselector(TiejiangpuLayer::scroCallBack));

			if (i < 2)
			{
				m_topBtn[i] = dynamic_cast<UITextButton*>(tapbtn_panel->getChildByName(CCString::createWithFormat("topBtn_%d", i)->getCString()));
				m_topBtn[i]->addReleaseEvent(this, coco_releaseselector(TiejiangpuLayer::tapMenuCallBack));
			}
			
		}
		m_topBtn[0]->disable();
		
		bRet = true;

	} while (0);

	return bRet;
}

void TiejiangpuLayer::closeBtnCallBack(CCObject* pSender)
{
	switch(m_layerNum){
	case TJPLAYER_TAG_LAYER:
		{
			m_Mediator->dispose();
		}break;
	case TJPLAYER_TAG_TIPS_QH:
	case TJPLAYER_TAG_TIPS_XQ:
		{
			m_layerLayout->setTouchEnable(true,true);
			m_layerLayout->setVisible(true);
			m_tipsLayout->setTouchEnable(false,true);
			m_tipsLayout->setVisible(false);
			m_layerNum = TJPLAYER_TAG_LAYER;
		}break;
	default:
		break;
	}

}
void TiejiangpuLayer::onEnter()
{
	CCLayer::onEnter();
	setTouchEnabled(true);
	setKeypadEnabled(true);
}

void TiejiangpuLayer::registerWithTouchDispatcher( void )
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -190, true);
}

bool TiejiangpuLayer::ccTouchBegan( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent )
{
	return true;
}

void TiejiangpuLayer::ccTouchEnded( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent )
{

}

void TiejiangpuLayer::scroCallBack( CCObject* pSender )
{
	UITextButton* tempBtn = dynamic_cast<UITextButton*>(pSender);


	Layout* textPanel = dynamic_cast<Layout*>(m_tipsLayout->getChildByName("textPanel"));
	if (m_isFirst)
	{
		m_isFirst =false;
		UIPageView* pageView = UIPageView::create();
		pageView->setTouchEnable(true);
		pageView->setSize(textPanel->getSize());
		pageView->setAnchorPoint(ccp(0,0));
		pageView->setPosition(ccp(0,0));
		pageView->setWidgetTag(TJP_LAYOUT_TAG_ROOT);
		textPanel->addChild(pageView);
		for (int i = 0;i<3;i++)
		{
			Layout* pgLayout = dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile("ui/tiejiangpuUI/tiejiangpuUI_Page.json"));
			pgLayout->setWidgetTag(TJP_LAYOUT_TAG_ROOT+i+1);
			pageView->addPage(pgLayout);
		}
	}
	m_layerNum = TJPLAYER_TAG_TIPS_QH;
	m_layerLayout->setTouchEnable(false,true);
	m_layerLayout->setVisible(false);
	m_tipsLayout->setTouchEnable(true,true);
	m_tipsLayout->setVisible(true);
	m_topBtn[0]->disable();
	m_topBtn[1]->active();
	initTipsLayer(true);

}

void TiejiangpuLayer::tapMenuCallBack(CCObject* pSender)
{
	 UIButton* button = dynamic_cast<UIButton*>(pSender);

	 int temp = button->getTag() %120;
	 for (int i = 0; i <2;i++)
	 {
		 m_topBtn[i]->active();
	 }
	 m_topBtn[temp]->disable();
	if (0 == temp)
	{
		m_layerNum = TJPLAYER_TAG_TIPS_QH;
	}
	else
	{
		m_layerNum = TJPLAYER_TAG_TIPS_XQ;
	}
	updateLayer();
}

void TiejiangpuLayer::updateLayer()
{
	switch(m_layerNum)
	{
	case TJPLAYER_TAG_TIPS_QH:
		{
			initTipsLayer(true);
			
		}break;
	case TJPLAYER_TAG_TIPS_XQ:
		{
			initTipsLayer(false);
		}break;
	default:
		break;
	}
}

void TiejiangpuLayer::keyBackClicked()
{
	closeBtnCallBack(NULL);
}

void TiejiangpuLayer::initTipsLayer(bool isQH)
{
	for (int i = 0;i<3;i++)
	{
		Layout* page = dynamic_cast<Layout*>(m_tipsLayout->getChildByTag(TJP_LAYOUT_TAG_ROOT+i+1));
		Layout* qhPanel = dynamic_cast<Layout*>(page->getChildByName("qhPanel")); 
		Layout* xqPanel =dynamic_cast<Layout*>(page->getChildByName("xqPanel"));
		UITextButton* qhBtn = dynamic_cast<UITextButton*>(page->getChildByName("qhBtn"));
		if (isQH)
		{
			qhBtn->setText(LanguageManager::shareManager()->getContentByKey("TJP_QH").c_str());
		}
		else
		{
			qhBtn->setText(LanguageManager::shareManager()->getContentByKey("TJP_XQ").c_str());
		}
		
		qhPanel->setVisible(isQH);
		xqPanel->setVisible(!isQH);
	}
}
