#include "SoulMediator.h"
#include "../ZMQ/GameDef.h"
#include "../ZMQ/AllCommandSignal.h"
#include "../ZMQ/layerManager.h"
#include "ZLL/LanguageManager.h"
#include "../ZMQ/SceneCover.h"
#include "../ZMQ/UIPageCircle.h"


SoulMediator::SoulMediator()
{
	_scene = NULL;

	ADD_EVENT_LISTENER(OnSoulOpen,NULL,this,Event::SOUL_OPEN,SoulMediator)
}

SoulMediator::~SoulMediator()
{
	if (_scene)
	{
		REMOVE_SCENE_FROM_LAYER(_scene)
	}
}

void SoulMediator::OnPackage( short xy,char* pack,int len )
{

}

void SoulMediator::OnSoulOpen( CCObject* sender,int msgid,cocos2d::CCObject* obj)
{
	if (_scene == NULL)
	{
		_scene = SoulLayer::create();
		//_scene->retain();
		_scene->m_Mediator = this;
		ADD_SCENE_TO_LAYER(_scene.obj(),LayerManager::sceneUILayer);
	}
}

void SoulMediator::dispose()
{
	if (_scene)
	{
		_scene->setKeypadEnabled(false);
		REMOVE_SCENE_FROM_LAYER(_scene)
			//_scene->release();
			_scene = NULL;
	}
}

bool SoulLayer::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!CCLayer::init());

		m_pUILayer = UILayer::create();
		m_pUILayer->setTouchPriority(-200);
		//m_pUILayer->scheduleUpdate();
		addChild(m_pUILayer);
		m_curLayerNum = SOULLAYER_TAG_LAYER;

		for (int i = 0;i<4;i++)
		{
			m_soulPage[i] = NULL;
		}
		m_layerLayout = dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile("ui/SoulUI/SoulUI.json"));
		m_pUILayer->addWidget(m_layerLayout);


		UITextButton* returnBtn = dynamic_cast<UITextButton*>(m_layerLayout->getChildByName("returnBtn"));
		returnBtn->addReleaseEvent(this, coco_releaseselector(SoulLayer::closeBtnCallBack));

		Layout* lay = dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile("ui/SoulUI/SoulUI_EX.json"));
		
		m_pageView = UIPageCircle::create();
		m_pageView->setTouchEnable(true,true);
		m_pageView->setSize(lay->getSize());
		m_pageView->setAnchorPoint(ccp(0,0));
		m_pageView->setPosition(lay->getPosition());
		
		for (int i = 0;i <4;i++)
		{
			Layout* layer = dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile("ui/SoulUI/SoulUI_EX.json"));
			
			for (int j = 0;j<8;j++)
			{
				Layout* panel = dynamic_cast<Layout*>(layer->getChildByName(CCString::createWithFormat("Panel_%d",j)->getCString()));
				UIImageView* soulImg = dynamic_cast<UIImageView*>(panel->getChildByName("soulImg"));
				soulImg->addReleaseEvent(this,coco_releaseselector(SoulLayer::soulImgBtnCallBack));
			}
			m_pageView->addPage(layer);
		}
		m_pageView->addEventListener(this,pagecircleeventselector(SoulLayer::pageViewCallBack));
		m_layerLayout->addChild(m_pageView);
		bRet = true;

	} while (0);

	return bRet;
}



void SoulLayer::yesBtnCallBack(CCObject* pSender)
{

}

void SoulLayer::closeBtnCallBack(CCObject* pSender)
{
	switch(m_curLayerNum)
	{
	case SOULLAYER_TAG_LAYER:
		{
			m_Mediator->dispose();
		}break;
	case SOULLAYER_TAG_JJ:
	case SOULLAYER_TAG_XL:
	case SOULLAYER_TAG_WY:
	case SOULLAYER_TAG_HC:
		{
			changeState(SOULLAYER_TAG_LAYER);
		}break;
	case SOULLAYER_TAG_XL_DLG:
		{
			m_xl_dlg_layout->setVisible(false);
			m_xl_dlg_layout->setTouchEnable(false,true);
			changeState(SOULLAYER_TAG_XL);
		}break;
	case SOULLAYER_TAG_WY_RESULT_DLG:
		{

		}break;
	case  SOULLAYER_TAG_HC_DLG:
		{
			m_hc_dlg_layout->setVisible(false);
			m_hc_dlg_layout->setTouchEnable(false,true);
			changeState(SOULLAYER_TAG_HC);
		}break;
	default:
		break;
	}
	
}


void SoulLayer::onEnter()
{
	CCLayer::onEnter();
	setTouchEnabled(true);
	setKeypadEnabled(true);
}

void SoulLayer::registerWithTouchDispatcher( void )
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -190, true);
}

bool SoulLayer::ccTouchBegan( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent )
{
	return true;
}

void SoulLayer::ccTouchEnded( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent )
{

}

void SoulLayer::pageViewCallBack(CCObject *pSender, PageCircleEventType type)
{
// 	switch (type)
// 	{
// 	case PAGEVIEW_EVENT_TURNING:
// 		{
// 			UIPageView* pageView = dynamic_cast<UIPageView*>(pSender);
// 			CCLog("pagenum= %d",pageView->getCurPageIndex());
// 		}
// 		break;
// 
// 	default:
// 		break;
// 	}
}

void SoulLayer::soulImgBtnCallBack( CCObject* pSender )
{
	if (NULL == m_soulLayout)
	{
		m_soulLayout = dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile("ui/SoulUI/SoulUI_1.json"));
		m_pUILayer->addWidget(m_soulLayout);

		UITextButton* returnBtn = dynamic_cast<UITextButton*>(m_soulLayout->getChildByName("returnBtn"));
		returnBtn->addReleaseEvent(this, coco_releaseselector(SoulLayer::closeBtnCallBack));

		Layout* menuPanel = dynamic_cast<Layout*>(m_soulLayout->getChildByName("menuPanel"));

		UITextButton* jjBtn = dynamic_cast<UITextButton*>(menuPanel->getChildByName("jjBtn"));
		jjBtn->addReleaseEvent(this, coco_releaseselector(SoulLayer::tapMenuCallBack));
		jjBtn->setWidgetTag(SOUL_BTN_JJ);
		jjBtn->disable();

		UITextButton* xlBtn = dynamic_cast<UITextButton*>(menuPanel->getChildByName("xlBtn"));
		xlBtn->addReleaseEvent(this, coco_releaseselector(SoulLayer::tapMenuCallBack));
		xlBtn->setWidgetTag(SOUL_BTN_XL);

		UITextButton* wyBtn = dynamic_cast<UITextButton*>(menuPanel->getChildByName("wyBtn"));
		wyBtn->addReleaseEvent(this, coco_releaseselector(SoulLayer::tapMenuCallBack));
		wyBtn->setWidgetTag(SOUL_BTN_WY);

		UITextButton* hcBtn = dynamic_cast<UITextButton*>(menuPanel->getChildByName("hcBtn"));
		hcBtn->addReleaseEvent(this, coco_releaseselector(SoulLayer::tapMenuCallBack));
		hcBtn->setWidgetTag(SOUL_BTN_HC);
	}
	if (NULL == m_soulPage[0])
	{
		Layout* lay = dynamic_cast<Layout*>(m_soulLayout->getChildByName("basePanel"));
		for (int i = 0; i <4;i++)
		{
			m_soulPage[i] = UIPageView::create();
			m_soulPage[i]->setTouchEnable(false);
			m_soulPage[i]->setSize(lay->getSize());
			m_soulPage[i]->setAnchorPoint(ccp(0,0));
			m_soulPage[i]->setPosition(lay->getPosition());
			m_soulPage[i]->setVisible(false);
			m_pUILayer->addWidget(m_soulPage[i]);

			m_isInputPage[i] = false;
		}
		for (int i = 0;i<3;i++)
		{
			Layout* lay = dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile("ui/SoulUI/SoulUI_1_JJ.json"));
			m_soulPage[0]->addPage(lay);
			//m_soulPage[0]->addWidgetToPage(lay,i,true);
		}
		m_isInputPage[0] = true;
		m_soulPage[0]->addEventListener(this,pagevieweventselector(SoulLayer::soulPageCallBack));
	}
	changeState(SOULLAYER_TAG_JJ);
	Layout* root = dynamic_cast<Layout*>(m_soulLayout->getChildByName("menuPanel"));
	UITextButton* jjBtn = dynamic_cast<UITextButton*>(root->getChildByTag(SOUL_BTN_JJ));
	UITextButton* xlBtn = dynamic_cast<UITextButton*>(root->getChildByTag(SOUL_BTN_XL));
	UITextButton* wyBtn = dynamic_cast<UITextButton*>(root->getChildByTag(SOUL_BTN_WY));
	UITextButton* hcBtn = dynamic_cast<UITextButton*>(root->getChildByTag(SOUL_BTN_HC));
	jjBtn->disable();
	xlBtn->active();
	wyBtn->active();
	hcBtn->active();
}

void SoulLayer::soulPageCallBack( CCObject *pSender, PageViewEventType type )
{
	switch (type)
	{
	case PAGEVIEW_EVENT_TURNING:
		{
			UIPageView* pageView = dynamic_cast<UIPageView*>(pSender);
			CCLog("pagenuaaaaam= %d",pageView->getCurPageIndex());
		}
		break;

	default:
		break;
	}
}

void SoulLayer::changeState(SoulLayerType state)
{
	m_curLayerNum = state;
	setVis();
	if (SOULLAYER_TAG_LAYER == state)
	{
		m_soulLayout->setVisible(false);
		m_soulLayout->setTouchEnable(false,true);
		m_layerLayout->setVisible(true);
		m_layerLayout->setTouchEnable(true,true);
		return;
	}
	else
	{
		m_soulLayout->setVisible(true);
		m_soulLayout->setTouchEnable(true,true);
		m_layerLayout->setVisible(false);
		m_layerLayout->setTouchEnable(false,true);
	}

	switch(state)
	{
	case SOULLAYER_TAG_JJ:
		{
			m_soulPage[0]->setVisible(true);
			m_soulPage[0]->setTouchEnable(true,true);
		}break;
	case SOULLAYER_TAG_XL:
		{
			m_soulPage[1]->setVisible(true);
			m_soulPage[1]->setTouchEnable(true,true);
		}break;
	case SOULLAYER_TAG_WY:
		{
			m_soulPage[2]->setVisible(true);
			m_soulPage[2]->setTouchEnable(true,true);
		}break;
	case SOULLAYER_TAG_HC:
		{
			m_soulPage[3]->setVisible(true);
			m_soulPage[3]->setTouchEnable(true,true);
		}break;
	default:
		break;
	}
}

void SoulLayer::setVis()
{
	for (int i = 0;i<4;i++)
	{
		if (NULL == m_soulPage[i])continue;
		m_soulPage[i]->setVisible(false);
		m_soulPage[i]->setTouchEnable(false,true);
	}
}

void SoulLayer::tapMenuCallBack(CCObject* pSender)
{
	UITextButton* button = dynamic_cast<UITextButton*>(pSender);

	Layout* root = dynamic_cast<Layout*>(m_soulLayout->getChildByName("menuPanel"));
	UITextButton* jjBtn = dynamic_cast<UITextButton*>(root->getChildByTag(SOUL_BTN_JJ));
	UITextButton* xlBtn = dynamic_cast<UITextButton*>(root->getChildByTag(SOUL_BTN_XL));
	UITextButton* wyBtn = dynamic_cast<UITextButton*>(root->getChildByTag(SOUL_BTN_WY));
	UITextButton* hcBtn = dynamic_cast<UITextButton*>(root->getChildByTag(SOUL_BTN_HC));

	jjBtn->active();
	xlBtn->active();
	wyBtn->active();
	hcBtn->active();

	switch (button->getWidgetTag())
	{
	case SOUL_BTN_JJ:
		{
			jjBtn->disable();
		}break;
	case SOUL_BTN_XL:
		{
			if (false == m_isInputPage[1])
			{
				for (int i = 0;i<3;i++)
				{
					Layout* lay = dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile("ui/SoulUI/SoulUI_1_XL.json"));
					
					UITextButton* xlBtn = dynamic_cast<UITextButton*>(lay->getChildByName("xlBtn"));
					xlBtn->addReleaseEvent(this,coco_releaseselector(SoulLayer::openSelXLCallBack));
					Layout* cjLayout = dynamic_cast<Layout*>(lay->getChildByName("cjPanel"));
					cjLayout->setVisible(false);
					cjLayout->setTouchEnable(false,true);
					UITextButton* sureBtn = dynamic_cast<UITextButton*>(cjLayout->getChildByName("sureBtn"));
					sureBtn->addReleaseEvent(this,coco_releaseselector(SoulLayer::sureBtnCallBack));

					m_soulPage[1]->addPage(lay);
				}
				m_isInputPage[1] = true;
				m_soulPage[1]->addEventListener(this,pagevieweventselector(SoulLayer::soulPageCallBack));
			}
			xlBtn->disable();
			changeState(SOULLAYER_TAG_XL);
		}break;
	case SOUL_BTN_WY:
		{
			if (false == m_isInputPage[2])
			{
				for (int i = 0;i<3;i++)
				{
					Layout* lay = dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile("ui/SoulUI/SoulUI_1_WY.json"));

					UITextButton* sureBtn =dynamic_cast<UITextButton*>(lay->getChildByName("sureBtn"));
					sureBtn->addReleaseEvent(this,coco_releaseselector(SoulLayer::sureBtnCallBack));

					Layout* wyPanel = dynamic_cast<Layout*>(lay->getChildByName("wyPanel"));
					for (int j = 0;j<6;j++)
					{
						UIImageView* img = dynamic_cast<UIImageView*>(wyPanel->getChildByName(CCString::createWithFormat("ImageView_%d",j)->getCString()));
						img->addReleaseEvent(this,coco_releaseselector(SoulLayer::wyImgCallBack));
						m_wySoulHas[i][j] = false;
					}
					m_soulPage[2]->addPage(lay);
				}
				m_isInputPage[2] = true;
				m_soulPage[2]->addEventListener(this,pagevieweventselector(SoulLayer::soulPageCallBack));
			}
			wyBtn->disable();
			changeState(SOULLAYER_TAG_WY);
		}break;
	case SOUL_BTN_HC:
		{
			if (false == m_isInputPage[3])
			{
				for (int i = 0;i<3;i++)
				{
					Layout* lay = dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile("ui/SoulUI/SoulUI_1_HC.json"));
					Layout* wyPanel = dynamic_cast<Layout*>(lay->getChildByName("wyPanel"));
					UITextButton* sureBtn = dynamic_cast<UITextButton*>(wyPanel->getChildByName("sureBtn"));
					sureBtn->addReleaseEvent(this,coco_releaseselector(SoulLayer::sureBtnCallBack));
					sureBtn->disable();
					Layout* unSelPanel = dynamic_cast<Layout*>(wyPanel->getChildByName("unSelPanel"));
					unSelPanel->addReleaseEvent(this,coco_releaseselector(SoulLayer::openSelHCCallBack));

					m_soulPage[3]->addPage(lay);
				}
				m_isInputPage[3] = true;
				m_soulPage[3]->addEventListener(this,pagevieweventselector(SoulLayer::soulPageCallBack));
			}
			hcBtn->disable();
			changeState(SOULLAYER_TAG_HC);
		}break;
	default:
		break;
	}
}

void SoulLayer::openSelXLCallBack(CCObject* pSender)
{
	UITextButton* xlBtn = dynamic_cast<UITextButton*>(pSender);
	m_xl_cjPanel = xlBtn->getParent();
	if (NULL == m_xl_dlg_layout)
	{
		m_xl_dlg_layout = dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile("ui/SoulUI/SoulUI_1_XL_DLG.json"));
		m_pUILayer->addWidget(m_xl_dlg_layout);

		UITextButton* returnBtn = dynamic_cast<UITextButton*>(m_xl_dlg_layout->getChildByName("rerurnBtn"));
		returnBtn->addReleaseEvent(this,coco_releaseselector(SoulLayer::closeBtnCallBack));

		UIScrollView* scro = dynamic_cast<UIScrollView*>(m_xl_dlg_layout->getChildByName("ScrollView"));
		for (int i = 0;i<3;i++)
		{
			Layout* panel = dynamic_cast<Layout*>(scro->getChildByName(CCString::createWithFormat("Panel_%d",i)->getCString()));
			for (int j = 0; j<3;j++)
			{
				UIImageView* imgView = dynamic_cast<UIImageView*>(panel->getChildByName(CCString::createWithFormat("ImageView_%d",j)->getCString()));
				imgView->addReleaseEvent(this,coco_releaseselector(SoulLayer::closeSelXLCallBack));
			}
		}
		Layout* topPanel = dynamic_cast<Layout*>(m_xl_dlg_layout->getChildByName("topPanel"));
		UIPageView* pgView = UIPageView::create();
		pgView->setTouchEnable(true);
		pgView->setSize(topPanel->getSize());
		pgView->setAnchorPoint(ccp(0,0));
		pgView->setPosition(ccp(0,0));
		pgView->setZOrder(6);
		topPanel->addChild(pgView);
		for (int i = 0; i < 3;i++)
		{
			Layout* layout = Layout::create();
			layout->setSize(topPanel->getSize());

			UIImageView* imageView = UIImageView::create();
			imageView->setTouchEnable(true);
			imageView->loadTexture("ui/SoulUI/soul_pic_soulicon001.png");
			imageView->setPosition(ccp(134, 77));
			layout->addChild(imageView);

			UILabel* label = UILabel::create();
			label->setText(LanguageManager::shareManager()->getContentByKey("CLUB_CYNC").c_str());
			label->setFontSize(33);
			label->setColor(ccc3(192, 192, 192));
			label->setPosition(ccp(279,112));
			layout->addChild(label);

			UILabel* label1 = UILabel::create();
			label1->setText("28");
			label1->setFontSize(33);
			label1->setColor(ccc3(192, 192, 192));
			label1->setPosition(ccp(279,49));
			layout->addChild(label1);
			pgView->addPage(layout);
		}
	}
	m_curLayerNum = SOULLAYER_TAG_XL_DLG;
	m_xl_dlg_layout->setVisible(true);
	m_xl_dlg_layout->setTouchEnable(true,true);
	m_soulPage[1]->setTouchEnable(false,true);
	m_soulLayout->setTouchEnable(false,true);
}

void SoulLayer::xlDlgDSrovCallBack( CCObject* pSender )
{

}

void SoulLayer::closeSelXLCallBack(CCObject* pSender)
{
	m_xl_dlg_layout->setVisible(false);
	m_xl_dlg_layout->setTouchEnable(false,true);
	changeState(SOULLAYER_TAG_XL);
	UITextButton* xlBtn = dynamic_cast<UITextButton*>(m_xl_cjPanel->getChildByName("xlBtn"));
	xlBtn->disable();
	Layout* lay = dynamic_cast<Layout*>(m_xl_cjPanel->getChildByName("cjPanel"));
	lay->setVisible(true);
}

void SoulLayer::sureBtnCallBack( CCObject* pSender )
{
	switch(m_curLayerNum)
	{
	case SOULLAYER_TAG_XL:
		{
			if (NULL == m_xl_result_dlg_layout)
			{
				m_xl_result_dlg_layout = dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile("ui/SoulUI/SoulUI_1_XL_DLG_0.json"));
				m_pUILayer->addWidget(m_xl_result_dlg_layout);

				UITextButton* sureBtn = dynamic_cast<UITextButton*>(m_xl_result_dlg_layout->getChildByName("sureBtn"));
				sureBtn->addReleaseEvent(this,coco_releaseselector(SoulLayer::sureBtnCallBack));
			}
			m_curLayerNum = SOULLAYER_TAG_XL_RESULT_DLG;
			m_xl_result_dlg_layout->setVisible(true);
			m_xl_result_dlg_layout->setTouchEnable(true,true);
			m_soulPage[1]->setTouchEnable(false,true);
			m_soulLayout->setTouchEnable(false,true);
		}break;
	case SOULLAYER_TAG_XL_RESULT_DLG:
		{
			m_xl_result_dlg_layout->setVisible(false);
			m_xl_result_dlg_layout->setTouchEnable(false,true);	
			changeState(SOULLAYER_TAG_XL);
			UITextButton* xlBtn = dynamic_cast<UITextButton*>(m_xl_cjPanel->getChildByName("xlBtn"));
			xlBtn->active();
			Layout* lay = dynamic_cast<Layout*>(m_xl_cjPanel->getChildByName("cjPanel"));
			lay->setVisible(false);
		}break;
	case SOULLAYER_TAG_WY_DLG:
		{
			if (NULL ==m_wy_result_dlg_layout)
			{
				m_wy_result_dlg_layout = dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile("ui/SoulUI/SoulUI_1_WY_DLG_1.json"));
				m_pUILayer->addWidget(m_wy_result_dlg_layout);

				UITextButton* sureBtn = dynamic_cast<UITextButton*>(m_wy_result_dlg_layout->getChildByName("sureBtn"));
				sureBtn->addReleaseEvent(this,coco_releaseselector(SoulLayer::sureBtnCallBack));
				UITextButton* cancelBtn = dynamic_cast<UITextButton*>(m_wy_result_dlg_layout->getChildByName("cancelBtn"));
				cancelBtn->addReleaseEvent(this,coco_releaseselector(SoulLayer::closeBtnCallBack));
			}
			m_curLayerNum = SOULLAYER_TAG_WY_RESULT_DLG;
			m_wy_result_dlg_layout->setVisible(true);
			m_wy_result_dlg_layout->setTouchEnable(true,true);
			m_soulPage[2]->setTouchEnable(false,true);
			m_soulLayout->setTouchEnable(false,true);
		}break;
	case SOULLAYER_TAG_WY_RESULT_DLG:
		{
			m_wy_result_dlg_layout->setVisible(false);
			m_wy_result_dlg_layout->setTouchEnable(false,true);	
			changeState(SOULLAYER_TAG_WY);
		}break;
	case SOULLAYER_TAG_HC_DLG:
		{
			if (1 == m_checkNum)
			{
				UIWidget* curPage = dynamic_cast<UIWidget*>(m_soulPage[3]->m_pages->objectAtIndex(m_soulPage[3]->getCurPageIndex()));
				Layout* unSelPanel = dynamic_cast<Layout*>(curPage->getChildByName("unSelPanel"));
				unSelPanel->setVisible(false);
				unSelPanel->setTouchEnable(false,true);
				Layout* selPanel = dynamic_cast<Layout*>(curPage->getChildByName("selPanel"));
				selPanel->setVisible(true);
				selPanel->setTouchEnable(true,true);
				Layout* wyPanel = dynamic_cast<Layout*>(curPage->getChildByName("wyPanel"));
				UITextButton* sureBtn = dynamic_cast<UITextButton*>(wyPanel->getChildByName("sureBtn"));
				sureBtn->active();

				m_hc_dlg_layout->setVisible(false);
				m_hc_dlg_layout->setTouchEnable(false,true);
				m_curLayerNum = SOULLAYER_TAG_HC;
				m_soulPage[3]->setTouchEnable(true,true);
				m_soulLayout->setTouchEnable(true,true);
			}
		}break;
	case SOULLAYER_TAG_HC:
		{
			openHCResult();
		}break;
	case SOULLAYER_TAG_HC_RESULT_DLG:
		{
			if (4 == m_curHCSkillNum)
			{
				UIWidget* curPage = dynamic_cast<UIWidget*>(m_soulPage[3]->m_pages->objectAtIndex(m_soulPage[3]->getCurPageIndex()));
				Layout* unSelPanel = dynamic_cast<Layout*>(curPage->getChildByName("unSelPanel"));
				unSelPanel->setVisible(true);
				unSelPanel->setTouchEnable(true,true);
				Layout* selPanel = dynamic_cast<Layout*>(curPage->getChildByName("selPanel"));
				selPanel->setVisible(false);
				selPanel->setTouchEnable(false,true);
				Layout* wyPanel = dynamic_cast<Layout*>(curPage->getChildByName("wyPanel"));
				UITextButton* sureBtn = dynamic_cast<UITextButton*>(wyPanel->getChildByName("sureBtn"));
				sureBtn->disable();

				m_hc_result_dlg_layout->setVisible(false);
				m_hc_result_dlg_layout->setTouchEnable(false,true);
				m_curLayerNum = SOULLAYER_TAG_HC;
				m_soulPage[3]->setTouchEnable(true);
				m_soulLayout->setTouchEnable(true,true);
			}
		}break;
	default:
		break;
	}
}

void SoulLayer::wyImgCallBack(CCObject* pSender)
{
	UIImageView* img = dynamic_cast<UIImageView*>(pSender);
	int tag = img->getTag()%110;

	if (NULL == m_wy_dlg_layout)
	{
		m_wy_dlg_layout = dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile("ui/SoulUI/SoulUI_1_WY_DLG.json"));
		m_pUILayer->addWidget(m_wy_dlg_layout);
		UITextButton* returnBtn = dynamic_cast<UITextButton*>(m_wy_dlg_layout->getChildByName("returnBtn"));
		returnBtn->addReleaseEvent(this,coco_releaseselector(SoulLayer::closeSelWYCallBack));
		UITextButton* sureBtn = dynamic_cast<UITextButton*>(m_wy_dlg_layout->getChildByName("sureBtn"));
		sureBtn->addReleaseEvent(this,coco_releaseselector(SoulLayer::sureBtnCallBack));

		m_curWYSoulNum=0;

		Layout* lay = dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile("ui/SoulUI/SoulUI_1_WY_DLG_PAGE.json"));
		UIPageView* pgView = UIPageView::create();
		pgView->setTouchEnable(true);
		pgView->setSize(lay->getSize());
		pgView->setAnchorPoint(ccp(0,0));
		pgView->setPosition(lay->getPosition());
		pgView->setZOrder(1);
		for (int i =0;i<3;i++)
		{
			Layout* lay1 = dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile("ui/SoulUI/SoulUI_1_WY_DLG_PAGE.json"));

			for (int j=0;j<6;j++)
			{
				Layout* panel = dynamic_cast<Layout*>(lay1->getChildByName(CCString::createWithFormat("Panel_%d",j)->getCString()));
				UICheckBox* box = dynamic_cast<UICheckBox*>(panel->getChildByName("CheckBox"));
				box->addEventListener(this,checkboxselectedeventselector(SoulLayer::checkBoxWYCallBack));
			}
			
			pgView->addPage(lay1);
		}
		m_wy_dlg_layout->addChild(pgView);
	}

	if (m_wySoulHas[m_soulPage[2]->getCurPageIndex()][tag])
	{
		img->loadTexture("ui/SoulUI/soul_pic_souliflute.png",UI_TEX_TYPE_LOCAL);
		m_wySoulHas[m_soulPage[2]->getCurPageIndex()][tag] = false;
	}
	else
	{
		m_curLayerNum = SOULLAYER_TAG_WY_DLG;
		m_wy_dlg_layout->setVisible(true);
		m_wy_dlg_layout->setTouchEnable(true,true);
		m_soulPage[2]->setTouchEnable(false,true);
		m_soulLayout->setTouchEnable(false,true);
	}
}

void SoulLayer::closeSelWYCallBack(CCObject* pSender)
{
	m_wy_dlg_layout->setVisible(false);
	m_wy_dlg_layout->setTouchEnable(false,true);
	m_soulPage[2]->setTouchEnable(true,true);
	m_soulLayout->setTouchEnable(true,true);
}

void SoulLayer::checkBoxWYCallBack(CCObject* pSender, CheckBoxEventType type)
{
	UICheckBox* box = dynamic_cast<UICheckBox*>(pSender);
	switch (type)
	{
	case CHECKBOX_STATE_EVENT_UNSELECTED:
		{
			m_curWYSoulNum--;
		}
		break;
	case CHECKBOX_STATE_EVENT_SELECTED:
		{
			
			if (5<m_curWYSoulNum)
			{
				box->setSelectedState(false);
			}
			else
			{
				m_curWYSoulNum++;
			}
			
		}
		break;
	default:
		break;
	}
	UILabel* lab = dynamic_cast<UILabel*>(m_wy_dlg_layout->getChildByName("curLabel"));
	lab->setText(CCString::createWithFormat("%d",m_curWYSoulNum)->getCString());
}

int SoulLayer::getCurWYSoulNum()
{
	int temp=0;
	for (int i =0;i<6;i++)
	{
		if (m_wySoulHas[m_soulPage[2]->getCurPageIndex()][i])
		{
			temp++;
		}
	}
	return temp;
}

void SoulLayer::setCurWYSoulNum(int soulIndex,bool isSel)
{
	m_wySoulHas[m_soulPage[2]->getCurPageIndex()][soulIndex] = isSel;
}

void SoulLayer::keyBackClicked()
{
	closeBtnCallBack(NULL);
}

void SoulLayer::openSelHCCallBack( CCObject* pSender )
{
	if (NULL == m_hc_dlg_layout)
	{
		m_hc_dlg_layout = dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile("ui/SoulUI/SoulUI_1_HC_DLG_0.json"));
		m_pUILayer->addWidget(m_hc_dlg_layout);

		UITextButton* returnBtn = dynamic_cast<UITextButton*>(m_hc_dlg_layout->getChildByName("returnBtn"));
		returnBtn->addReleaseEvent(this,coco_releaseselector(SoulLayer::closeBtnCallBack));
		UITextButton* sureBtn = dynamic_cast<UITextButton*>(m_hc_dlg_layout->getChildByName("sureBtn"));
		sureBtn->addReleaseEvent(this,coco_releaseselector(SoulLayer::sureBtnCallBack));


		Layout* pagePanel = dynamic_cast<Layout*>(m_hc_dlg_layout->getChildByName("pagePanel"));
		UIPageView* pgView = UIPageView::create();
		pgView->setTouchEnable(true);
		pgView->setSize(pagePanel->getSize());
		pgView->setAnchorPoint(ccp(0,0));
		pgView->setPosition(ccp(0,0));
		pgView->setZOrder(1);
		pgView->setWidgetTag(SOUL_BTN_HC_DLG_PAGE);
		pagePanel->addChild(pgView);
		for (int i = 0; i < 3;i++)
		{
			Layout* pglayout = dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile("ui/SoulUI/SoulUI_1_HC_DLG_0_PAGE.json"));

			for (int j = 0 ; j < 6; j++)
			{
				Layout* panel = dynamic_cast<Layout*>(pglayout->getChildByName(CCString::createWithFormat("Panel_%d",j)->getCString()));
				UIImageView* checkBg = dynamic_cast<UIImageView*>(panel->getChildByName("checkBg"));
				checkBg->addReleaseEvent(this,coco_releaseselector(SoulLayer::checkboxBgHCBtnCallBack));

				UIImageView* checkImg= dynamic_cast<UIImageView*>(checkBg->getChildByName("checkBg_img"));
				checkImg->addReleaseEvent(this,coco_releaseselector(SoulLayer::checkboxImgHCBtnCallBack));
			}
			pgView->addPage(pglayout);
		}
	}
	m_curLayerNum = SOULLAYER_TAG_HC_DLG;
	initCheckboxImgHC();
	m_checkNum =0;
	m_hc_dlg_layout->setVisible(true);
	m_hc_dlg_layout->setTouchEnable(true,true);
	m_soulPage[3]->setTouchEnable(false,true);
	m_soulLayout->setTouchEnable(false,true);
}



void SoulLayer::checkboxBgHCBtnCallBack( CCObject* pSender )
{
	initCheckboxImgHC();
	UIImageView* checkBg1 = dynamic_cast<UIImageView*>(pSender);
	UIImageView* checkImg1 = dynamic_cast<UIImageView*>(checkBg1->getChildByName("checkBg_img"));
	checkImg1->active();
	checkImg1->setVisible(true);
	m_checkNum = 1;
}

void SoulLayer::checkboxImgHCBtnCallBack( CCObject* pSender )
{
	initCheckboxImgHC();
	if (0 == m_checkNum)
	{
		UIImageView* checkImg1 = dynamic_cast<UIImageView*>(pSender);
		checkImg1->active();
		checkImg1->setVisible(true);
		m_checkNum = 1;
		return;
	}
	m_checkNum = 0;
}

void SoulLayer::initCheckboxImgHC()
{
	UIPageView* pageView = dynamic_cast<UIPageView*>(m_hc_dlg_layout->getChildByTag(SOUL_BTN_HC_DLG_PAGE));
	for (int k =0;k<3;k++)
	{
		UIWidget* curPage = dynamic_cast<UIWidget*>(pageView->m_pages->objectAtIndex(k));
		for (int i = 0;i<6;i++)
		{
			Layout* panel = dynamic_cast<Layout*>(curPage->getChildByName(CCString::createWithFormat("Panel_%d",i)->getCString()));
			UIImageView* checkBg = dynamic_cast<UIImageView*>(panel->getChildByName("checkBg"));
			UIImageView* checkImg = dynamic_cast<UIImageView*>(checkBg->getChildByName("checkBg_img"));
			checkImg->disable();
			checkImg->setVisible(false);
		}
	}
}

void SoulLayer::openHCResult()
{
	if (NULL == m_hc_result_dlg_layout)
	{
		m_hc_result_dlg_layout = dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile("ui/SoulUI/SoulUI_1_HC_DLG_1.json"));
		m_pUILayer->addWidget(m_hc_result_dlg_layout);
		m_curHCSkillNum = 0;

		UITextButton* sureBtn = dynamic_cast<UITextButton*>(m_hc_result_dlg_layout->getChildByName("sureBtn"));
		sureBtn->addReleaseEvent(this,coco_releaseselector(SoulLayer::sureBtnCallBack));
		UIScrollView* scrov = dynamic_cast<UIScrollView*>(m_hc_result_dlg_layout->getChildByName("ScrollView"));
		for (int j=0;j<8;j++)
		{
			Layout* panel = dynamic_cast<Layout*>(scrov->getChildByName(CCString::createWithFormat("Panel_%d",j)->getCString()));
			UICheckBox* box = dynamic_cast<UICheckBox*>(panel->getChildByName("CheckBox"));
			box->addEventListener(this,checkboxselectedeventselector(SoulLayer::checkBoxHCCallBack));
		}
	}
	m_curLayerNum = SOULLAYER_TAG_HC_RESULT_DLG;
	m_hc_result_dlg_layout->setVisible(true);
	m_hc_result_dlg_layout->setTouchEnable(true,true);
	m_soulPage[3]->setTouchEnable(false,true);
	m_soulLayout->setTouchEnable(false,true);
}

void SoulLayer::checkBoxHCCallBack( CCObject* pSender, CheckBoxEventType type )
{
	UICheckBox* box = dynamic_cast<UICheckBox*>(pSender);
	switch (type)
	{
	case CHECKBOX_STATE_EVENT_UNSELECTED:
		{
			m_curHCSkillNum--;
		}
		break;
	case CHECKBOX_STATE_EVENT_SELECTED:
		{

			if (3<m_curHCSkillNum)
			{
				box->setSelectedState(false);
			}
			else
			{
				m_curHCSkillNum++;
			}
		}
		break;
	default:
		break;
	}
	UILabel* lab = dynamic_cast<UILabel*>(m_hc_result_dlg_layout->getChildByName("curLabel"));
	lab->setText(CCString::createWithFormat("%d",m_curHCSkillNum)->getCString());
}
