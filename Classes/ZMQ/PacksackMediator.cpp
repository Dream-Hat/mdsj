#include "PacksackMediator.h"
#include "GameDef.h"
#include "AllCommandSignal.h"
#include "layerManager.h"


PacksackMediator::PacksackMediator()
{
	_scene = NULL;

	ADD_EVENT_LISTENER(OnPacksackOpen,NULL,this,Event::PACKSACK_OPEN,PacksackMediator)
}

PacksackMediator::~PacksackMediator()
{
	if (_scene)
	{
		REMOVE_SCENE_FROM_LAYER(_scene)
	}
}

void PacksackMediator::OnPackage( short xy,char* pack,int len )
{

}

void PacksackMediator::OnPacksackOpen( CCObject* sender,int msgid,cocos2d::CCObject* obj)
{
	if (_scene == NULL)
	{
		_scene = PacksackLayer::create();
		//_scene->retain();
		_scene->m_Mediator = this;
		ADD_SCENE_TO_LAYER(_scene.obj(),LayerManager::sceneUILayer);
	}
}

void PacksackMediator::dispose()
{
	if (_scene)
	{
		_scene->setKeypadEnabled(false);
		REMOVE_SCENE_FROM_LAYER(_scene)
			//_scene->release();
			_scene = NULL;
	}
}

bool PacksackLayer::init()
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

		Layout* lay = dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile("ui/packsackUI/packsackUI.json"));
		m_pUILayer->addWidget(lay);

		m_layerLayout = dynamic_cast<Layout*>(lay->getChildByName("layerPanel"));
		m_rootLayout = dynamic_cast<Layout*>(lay->getChildByName("rootPanel"));
		m_rootLayout->setTouchEnable(false,true);
		m_rootLayout->setVisible(false);
		m_curLayerNum = PACKSACK_LAYOUT_TAG_LAYER;
		m_curGoodsID = 1;

		UIButton* returnBtn = dynamic_cast<UIButton*>(m_layerLayout->getChildByName("returnBtn"));
		returnBtn->addReleaseEvent(this, coco_releaseselector(PacksackLayer::closeBtnCallBack));

		UIButton* returnBtn1 = dynamic_cast<UIButton*>(m_rootLayout->getChildByName("returnBtn"));
		returnBtn1->addReleaseEvent(this, coco_releaseselector(PacksackLayer::closeBtnCallBack));
		UITextButton* sureBtn = dynamic_cast<UITextButton*>(m_rootLayout->getChildByName("sureBtn"));
		sureBtn->addReleaseEvent(this,coco_releaseselector(PacksackLayer::sureBtnCallBack));

		for (int i = 0 ; i < 3; i++)
		{
			UIImageView* checkBg = dynamic_cast<UIImageView*>(m_rootLayout->getChildByName(CCString::createWithFormat("checkBg_%d",i)->getCString()));
			checkBg->addReleaseEvent(this,coco_releaseselector(PacksackLayer::checkboxBtnCallBack));

			checkImg[i] = dynamic_cast<UIImageView*>(m_rootLayout->getChildByName(CCString::createWithFormat("checkBg_img_%d",i)->getCString()));
			checkImg[i]->addReleaseEvent(this,coco_releaseselector(PacksackLayer::checkboxBtnCallBack));
			checkImg[i]->setVisible(false);

			UILabel* lab = dynamic_cast<UILabel*>(checkBg->getChildByName("Label"));
			lab->addReleaseEvent(this,coco_releaseselector(PacksackLayer::checkboxLabCallBack));
		}
		m_checkNum = 0;
		checkImg[m_checkNum]->setVisible(true);

		UIScrollView* scroV = dynamic_cast<UIScrollView*>(m_layerLayout->getChildByName("ScrollView"));
		for (int i = 0; i < 2; i++)
		{
			UIButton* scroPanel = dynamic_cast<UIButton*>(scroV->getChildByName(CCString::createWithFormat("Panel_%d", i)->getCString()));
			scroPanel->addReleaseEvent(this, coco_releaseselector(PacksackLayer::scroCallBack));
		}

		UIButton* payBtn = dynamic_cast<UIButton*>(m_layerLayout->getChildByName("payBtn"));
		payBtn->addReleaseEvent(this, coco_releaseselector(PacksackLayer::buyBtnCallBack));

		Layout* tapbtn_panel = dynamic_cast<Layout*>(m_layerLayout->getChildByName("tapbtn_Panel"));
		tapbtn_panel->setWidgetTag(PACKSACK_LAYOUT_TAG_ROOT);

		UIButton* equipBtn = dynamic_cast<UIButton*>(tapbtn_panel->getChildByName("equipBtn"));
		equipBtn->addReleaseEvent(this, coco_releaseselector(PacksackLayer::tapMenuCallBack));
		equipBtn->setWidgetTag(PACKSACK_LAYOUT_TAG_EQUIP);

		UIButton* tejiaBtn = dynamic_cast<UIButton*>(tapbtn_panel->getChildByName("tejiaBtn"));
		tejiaBtn->addReleaseEvent(this, coco_releaseselector(PacksackLayer::tapMenuCallBack));
		tejiaBtn->setWidgetTag(PACKSACK_LAYOUT_TAG_TEJIA);
		tejiaBtn->disable();

		UIButton* diamondBtn = dynamic_cast<UIButton*>(tapbtn_panel->getChildByName("diamondBtn"));
		diamondBtn->addReleaseEvent(this, coco_releaseselector(PacksackLayer::tapMenuCallBack));
		diamondBtn->setWidgetTag(PACKSACK_LAYOUT_TAG_DIAMOND);

		UIButton* yaoshuiBtn = dynamic_cast<UIButton*>(tapbtn_panel->getChildByName("yaoshuiBtn"));
		yaoshuiBtn->addReleaseEvent(this, coco_releaseselector(PacksackLayer::tapMenuCallBack));
		yaoshuiBtn->setWidgetTag(PACKSACK_LAYOUT_TAG_YAOSHUI);

		UIButton* otherBtn = dynamic_cast<UIButton*>(tapbtn_panel->getChildByName("otherBtn"));
		otherBtn->addReleaseEvent(this, coco_releaseselector(PacksackLayer::tapMenuCallBack));
		otherBtn->setWidgetTag(PACKSACK_LAYOUT_TAG_OTHER);

		bRet = true;

	} while (0);

	return bRet;
}



void PacksackLayer::buyBtnCallBack( CCObject* pSender )
{
	m_curLayerNum = PACKSACK_LAYOUT_TAG_KUORONG;
	m_layerLayout->setTouchEnable(false,true);
	m_rootLayout->setTouchEnable(true,true);
	m_rootLayout->setVisible(true);
}

void PacksackLayer::closeBtnCallBack( CCObject* pSender )
{
	switch(m_curLayerNum)
	{
	case PACKSACK_LAYOUT_TAG_LAYER:
		{
			m_Mediator->dispose();
		}break;
	case PACKSACK_LAYOUT_TAG_KUORONG:
		{
			m_curLayerNum = PACKSACK_LAYOUT_TAG_LAYER;
			m_layerLayout->setTouchEnable(true,true);
			m_rootLayout->setTouchEnable(false,true);
			m_rootLayout->setVisible(false);
		}
		break;
	case PACKSACK_LAYOUT_TAG_GOODS:
		{
			m_curLayerNum = PACKSACK_LAYOUT_TAG_LAYER;
			m_layerLayout->setTouchEnable(true,true);
			m_goodsLayout->setTouchEnable(false,true);
			m_goodsLayout->setVisible(false);
		}
		break;
	case PACKSACK_LAYOUT_TAG_SALEDLG:
		{
			m_curLayerNum = PACKSACK_LAYOUT_TAG_GOODS;
			m_goodsLayout->setTouchEnable(true,true);
			m_saleLayout->setVisible(false);
			m_saleLayout->setTouchEnable(false,false);
		}break;
	default:
		break;
	}
}

void PacksackLayer::onEnter()
{
	CCLayer::onEnter();
	setTouchEnabled(true);
	setKeypadEnabled(true);
}

void PacksackLayer::registerWithTouchDispatcher( void )
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -190, true);
}

bool PacksackLayer::ccTouchBegan( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent )
{
	return true;
}

void PacksackLayer::ccTouchEnded( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent )
{

}

void PacksackLayer::scroCallBack( CCObject* pSender )
{
	UIButton* tempPanel = dynamic_cast<UIButton*>(pSender);
	m_curGoodsID = tempPanel->getTag();

	openGoods();
}

void PacksackLayer::tapMenuCallBack( CCObject* pSender )
{
	 UIButton* button = dynamic_cast<UIButton*>(pSender);

	 Layout* root = dynamic_cast<Layout*>(m_pUILayer->getWidgetByTag(PACKSACK_LAYOUT_TAG_ROOT));

	 UIButton* equipBtn = dynamic_cast<UIButton*>(root->getChildByTag(PACKSACK_LAYOUT_TAG_EQUIP));

	 UIButton* tejiaBtn = dynamic_cast<UIButton*>(root->getChildByTag(PACKSACK_LAYOUT_TAG_TEJIA));

	 UIButton* diamondBtn = dynamic_cast<UIButton*>(root->getChildByTag(PACKSACK_LAYOUT_TAG_DIAMOND));

	 UIButton* yaoshuiBtn = dynamic_cast<UIButton*>(root->getChildByTag(PACKSACK_LAYOUT_TAG_YAOSHUI));

	 UIButton* otherBtn = dynamic_cast<UIButton*>(root->getChildByTag(PACKSACK_LAYOUT_TAG_OTHER));

	 equipBtn->active();
	 tejiaBtn->active();
	 diamondBtn->active();
	 yaoshuiBtn->active();
	 otherBtn->active();

	 switch (button->getWidgetTag())
	 {
	 case PACKSACK_LAYOUT_TAG_EQUIP:
		 {
			 equipBtn->disable();
		 }break;
	 case PACKSACK_LAYOUT_TAG_TEJIA:
		 {
			 tejiaBtn->disable();
		 }break;
	 case PACKSACK_LAYOUT_TAG_DIAMOND:
		 {
			 diamondBtn->disable();
		 }break;
	 case PACKSACK_LAYOUT_TAG_YAOSHUI:
		 {
			 yaoshuiBtn->disable();
		 }break;
	 case PACKSACK_LAYOUT_TAG_OTHER:
		 {
			 otherBtn->disable();
		 }break;
	 }
}


void PacksackLayer::checkboxBtnCallBack( CCObject* pSender )
{
	UIImageView* click1 = dynamic_cast<UIImageView*>(pSender);
	checkImg[m_checkNum]->setVisible(false);
	m_checkNum = click1->getTag() %80;
	checkImg[m_checkNum]->setVisible(true);
}

void PacksackLayer::openGoods()
{
	if (NULL == m_goodsLayout)
	{
		m_goodsLayout = dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile("ui/packsackUI/packsackUI_1.json"));
		m_pUILayer->addWidget(m_goodsLayout);

		UIButton* returnBtn1 = dynamic_cast<UIButton*>(m_goodsLayout->getChildByName("returnBtn"));
		returnBtn1->addReleaseEvent(this, coco_releaseselector(PacksackLayer::closeBtnCallBack));

		UITextButton* saleBtn = dynamic_cast<UITextButton*>(m_goodsLayout->getChildByName("saleBtn"));
		saleBtn->addReleaseEvent(this,coco_releaseselector(PacksackLayer::saleBtnCallBack));

		UITextButton* useBtn = dynamic_cast<UITextButton*>(m_goodsLayout->getChildByName("useBtn"));
		useBtn->addReleaseEvent(this,coco_releaseselector(PacksackLayer::useBtnCallBack));
	}
	m_curLayerNum = PACKSACK_LAYOUT_TAG_GOODS;
	m_layerLayout->setTouchEnable(false,true);
	m_goodsLayout->setTouchEnable(true,true);
	m_goodsLayout->setVisible(true);


	
}

void PacksackLayer::saleBtnCallBack(CCObject* pSender)
{
	switch (m_curLayerNum)
	{
	case PACKSACK_LAYOUT_TAG_GOODS:
		{
			if (NULL == m_saleLayout)
			{
				m_saleLayout = dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile("ui/packsackUI/packsackUI_Dlg.json"));
				m_pUILayer->addWidget(m_saleLayout);
				UITextButton* returnBtn = dynamic_cast<UITextButton*>(m_saleLayout->getChildByName("returnBtn"));
				returnBtn->addReleaseEvent(this,coco_releaseselector(PacksackLayer::closeBtnCallBack));
				UITextButton* saleBtn = dynamic_cast<UITextButton*>(m_saleLayout->getChildByName("saleBtn"));
				saleBtn->addReleaseEvent(this,coco_releaseselector(PacksackLayer::saleBtnCallBack));
			}
			m_curLayerNum = PACKSACK_LAYOUT_TAG_SALEDLG;
			m_goodsLayout->setTouchEnable(false,true);
			m_saleLayout->setVisible(true);
			m_saleLayout->setTouchEnable(true,false);
		}break;
	case PACKSACK_LAYOUT_TAG_SALEDLG:
		{
			m_saleLayout->setVisible(false);
			m_saleLayout->setTouchEnable(false,false);
			m_curLayerNum = PACKSACK_LAYOUT_TAG_LAYER;
			m_layerLayout->setTouchEnable(true,true);
			m_goodsLayout->setTouchEnable(false,true);
			m_goodsLayout->setVisible(false);
		}break;
	default:
		break;
	}
}

void PacksackLayer::useBtnCallBack(CCObject* pSender)
{
	m_curLayerNum = PACKSACK_LAYOUT_TAG_LAYER;
	m_layerLayout->setTouchEnable(true,true);
	m_goodsLayout->setTouchEnable(false,true);
	m_goodsLayout->setVisible(false);

	m_curGoodsID %=100;
	UIImageView* helmetImg = dynamic_cast<UIImageView*>(m_layerLayout->getChildByName("helmetImg"));
	helmetImg->loadTexture(CCString::createWithFormat("ui/packsackUI/bag_helmet%dtex.png",m_curGoodsID+1)->getCString(),UI_TEX_TYPE_LOCAL);

}

void PacksackLayer::keyBackClicked()
{
	closeBtnCallBack(NULL);
}

void PacksackLayer::sureBtnCallBack( CCObject* pSender )
{
	m_curLayerNum = PACKSACK_LAYOUT_TAG_LAYER;
	m_layerLayout->setTouchEnable(true,true);
	m_rootLayout->setTouchEnable(false,true);
	m_rootLayout->setVisible(false);
}

void PacksackLayer::checkboxLabCallBack( CCObject* pSender )
{
	UILabel* click1 = dynamic_cast<UILabel*>(pSender);
	checkImg[m_checkNum]->setVisible(false);
	m_checkNum = click1->getTag() %80;
	checkImg[m_checkNum]->setVisible(true);
}
