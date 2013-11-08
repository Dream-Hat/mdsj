#include "ShopMediator.h"
#include "../ZMQ/GameDef.h"
#include "../ZMQ/AllCommandSignal.h"
#include "../ZMQ/layerManager.h"
#include "../ZMQ/UIScrollViewP.h"
#include "../ZMQ/KeyboardLayer.h"
#include "../ZMQ/Facade.h"



ShopMediator::ShopMediator()
{
	_scene = NULL;

	ADD_EVENT_LISTENER(OnShopOpen,NULL,this,Event::Shop_OPEN,ShopMediator)
}

ShopMediator::~ShopMediator()
{
	if (_scene)
	{
		REMOVE_SCENE_FROM_LAYER(_scene)
	}
}

void ShopMediator::OnPackage( short xy,char* pack,int len )
{

}

void ShopMediator::OnShopOpen( CCObject* sender,int msgid,cocos2d::CCObject* obj)
{
	if (_scene == NULL)
	{
		_scene = ShopLayer::create();
		//_scene->retain();
		_scene->m_Mediator = this;
		ADD_SCENE_TO_LAYER(_scene.obj(),LayerManager::sceneUILayer);
	}
}

void ShopMediator::dispose()
{
	if (_scene)
	{
		_scene->setKeypadEnabled(false);
		REMOVE_SCENE_FROM_LAYER(_scene)
			//_scene->release();
			_scene = NULL;
	}
}

bool ShopLayer::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!CCLayer::init());
		m_Mediator = NULL;
		m_buyNum = 1;
		m_onePri = 5000;
		m_curTapMenu = SHOP_LAYOUT_TAG_TEJIA;

		m_pUILayer = UILayer::create();
		m_pUILayer->setTouchPriority(-200);
		m_pUILayer->scheduleUpdate();
		addChild(m_pUILayer);

		Layout* lay;
		lay = dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile("ui/ShopUI/ShopUI.json"));
		m_pUILayer->addWidget(lay);

		m_layerLayout = dynamic_cast<Layout*>(lay->getChildByName("layerPanel"));
		m_buyLayout = dynamic_cast<Layout*>(lay->getChildByName("buyRootPanel"));


		UIButton* returnBtn1 = dynamic_cast<UIButton*>(m_buyLayout->getChildByName("returnBtn"));
		returnBtn1->addReleaseEvent(this, coco_releaseselector(ShopLayer::closeBtnDlgCallBack));

		UIScrollView* scroV = dynamic_cast<UIScrollView*>(m_layerLayout->getChildByName("ScrollView"));
// 		UIScrollViewP* scroV = dynamic_cast<UIScrollViewP*>(m_layerLayout->getChildByName("ScrollView"));
// 		UIImageView* spr = dynamic_cast<UIImageView*>(m_layerLayout->getChildByName("slideImge"));
// 		CCSize a  = scroV->getInnerContainerSize();
// 		CCSize b  =scroV->getSize();
// 		float scale = b.height/a.height;
// 		spr->setScaleY(scale);
// 		scroV->setSlideSprite(spr,scale);

		for (int i = 0; i < 8; i++)
		{
			UIButton* scroPanel = dynamic_cast<UIButton*>(scroV->getChildByName(CCString::createWithFormat("Panel_%d", i)->getCString()));
			scroPanel->addReleaseEvent(this, coco_releaseselector(ShopLayer::scroCallBack));
		}


		UIButton* returnBtn = dynamic_cast<UIButton*>(m_layerLayout->getChildByName("returnBtn"));
		returnBtn->addReleaseEvent(this, coco_releaseselector(ShopLayer::closeBtnCallBack));

		UIButton* payBtn = dynamic_cast<UIButton*>(m_layerLayout->getChildByName("payBtn"));
		payBtn->addReleaseEvent(this, coco_releaseselector(ShopLayer::payBtnCallBack));

		UIButton* subBtn = dynamic_cast<UIButton*>(m_buyLayout->getChildByName("subBtn"));
		subBtn->addReleaseEvent(this, coco_releaseselector(ShopLayer::subBtnCallBack));

		UIButton* addBtn = dynamic_cast<UIButton*>(m_buyLayout->getChildByName("addBtn"));
		addBtn->addReleaseEvent(this, coco_releaseselector(ShopLayer::addBtnCallBack));

		Layout* buyNumPanel = dynamic_cast<Layout*>(m_buyLayout->getChildByName("buyNumPanel"));
		buyNumPanel->addReleaseEvent(this,coco_releaseselector(ShopLayer::callForNumInput));

		m_buyNumLabel = dynamic_cast<UILabel*>(buyNumPanel->getChildByName("Label"));
		m_totalPriLabel = dynamic_cast<UILabel*>(m_buyLayout->getChildByName("totalPriLabel"));
		m_onePriLabel = dynamic_cast<UILabel*>(m_buyLayout->getChildByName("onePriLabel"));

		UITextButton* buyBtn = dynamic_cast<UITextButton*>(m_buyLayout->getChildByName("buyBtn"));
		buyBtn->addReleaseEvent(this, coco_releaseselector(ShopLayer::buyBtnCallBack));

		Layout* tapbtn_panel = dynamic_cast<Layout*>(m_layerLayout->getChildByName("tapbtn_Panel"));
		tapbtn_panel->setWidgetTag(SHOP_LAYOUT_TAG_ROOT);

		UIButton* equipBtn = dynamic_cast<UIButton*>(tapbtn_panel->getChildByName("equipBtn"));
		equipBtn->addReleaseEvent(this, coco_releaseselector(ShopLayer::tapMenuCallBack));
		equipBtn->setWidgetTag(SHOP_LAYOUT_TAG_EQUIP);

		UIButton* tejiaBtn = dynamic_cast<UIButton*>(tapbtn_panel->getChildByName("tejiaBtn"));
		tejiaBtn->addReleaseEvent(this, coco_releaseselector(ShopLayer::tapMenuCallBack));
		tejiaBtn->setWidgetTag(SHOP_LAYOUT_TAG_TEJIA);
		tejiaBtn->disable();

		UIButton* diamondBtn = dynamic_cast<UIButton*>(tapbtn_panel->getChildByName("diamondBtn"));
		diamondBtn->addReleaseEvent(this, coco_releaseselector(ShopLayer::tapMenuCallBack));
		diamondBtn->setWidgetTag(SHOP_LAYOUT_TAG_DIAMOND);

		UIButton* yaoshuiBtn = dynamic_cast<UIButton*>(tapbtn_panel->getChildByName("yaoshuiBtn"));
		yaoshuiBtn->addReleaseEvent(this, coco_releaseselector(ShopLayer::tapMenuCallBack));
		yaoshuiBtn->setWidgetTag(SHOP_LAYOUT_TAG_YAOSHUI);

		UIButton* otherBtn = dynamic_cast<UIButton*>(tapbtn_panel->getChildByName("otherBtn"));
		otherBtn->addReleaseEvent(this, coco_releaseselector(ShopLayer::tapMenuCallBack));
		otherBtn->setWidgetTag(SHOP_LAYOUT_TAG_OTHER);


		bRet = true;

	} while (0);

	return bRet;
}



void ShopLayer::payBtnCallBack( CCObject* pSender )
{
}

void ShopLayer::closeBtnCallBack( CCObject* pSender )
{
	m_Mediator->dispose();
}

void ShopLayer::onEnter()
{
	CCLayer::onEnter();
	setTouchEnabled(true);
	setKeypadEnabled(true);
}

void ShopLayer::registerWithTouchDispatcher( void )
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -190, true);
}

bool ShopLayer::ccTouchBegan( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent )
{
	return true;
}

void ShopLayer::ccTouchEnded( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent )
{

}

void ShopLayer::scroCallBack( CCObject* pSender )
{
	UIButton* tempPanel = dynamic_cast<UIButton*>(pSender);
	int temp = tempPanel->getTag();
	if (SHOP_LAYOUT_TAG_TEJIA == m_curTapMenu)
	{
		updateBuyLayout(pSender,true);
	}
	else
	{
		updateBuyLayout(pSender,false);
	}
	
	m_layerLayout->setTouchEnable(false,true);
	m_buyLayout->setVisible(true);
	m_buyLayout->setTouchEnable(true,true);
}

void ShopLayer::tapMenuCallBack( CCObject* pSender )
{
	 UIButton* button = dynamic_cast<UIButton*>(pSender);

	 Layout* root = dynamic_cast<Layout*>(m_pUILayer->getWidgetByTag(SHOP_LAYOUT_TAG_ROOT));

	 UIButton* equipBtn = dynamic_cast<UIButton*>(root->getChildByTag(SHOP_LAYOUT_TAG_EQUIP));

	 UIButton* tejiaBtn = dynamic_cast<UIButton*>(root->getChildByTag(SHOP_LAYOUT_TAG_TEJIA));

	 UIButton* diamondBtn = dynamic_cast<UIButton*>(root->getChildByTag(SHOP_LAYOUT_TAG_DIAMOND));

	 UIButton* yaoshuiBtn = dynamic_cast<UIButton*>(root->getChildByTag(SHOP_LAYOUT_TAG_YAOSHUI));

	 UIButton* otherBtn = dynamic_cast<UIButton*>(root->getChildByTag(SHOP_LAYOUT_TAG_OTHER));

	 equipBtn->active();
	 tejiaBtn->active();
	 diamondBtn->active();
	 yaoshuiBtn->active();
	 otherBtn->active();

	 switch (button->getWidgetTag())
	 {
	 case SHOP_LAYOUT_TAG_EQUIP:
		 {
			 m_curTapMenu = SHOP_LAYOUT_TAG_EQUIP;
			 equipBtn->disable();
			 updateScroV(false);
		 }break;
	 case SHOP_LAYOUT_TAG_TEJIA:
		 {
			 m_curTapMenu = SHOP_LAYOUT_TAG_TEJIA;
			 tejiaBtn->disable();
			 updateScroV(true);
		 }break;
	 case SHOP_LAYOUT_TAG_DIAMOND:
		 {
			 m_curTapMenu = SHOP_LAYOUT_TAG_DIAMOND;
			 diamondBtn->disable();
			 updateScroV(false);
		 }break;
	 case SHOP_LAYOUT_TAG_YAOSHUI:
		 {
			 m_curTapMenu = SHOP_LAYOUT_TAG_YAOSHUI;
			 yaoshuiBtn->disable();
			 updateScroV(false);
		 }break;
	 case SHOP_LAYOUT_TAG_OTHER:
		 {
			 m_curTapMenu = SHOP_LAYOUT_TAG_OTHER;
			 otherBtn->disable();
			 updateScroV(false);
		 }break;
	 }
// 	 UIScrollView* scroV = dynamic_cast<UIScrollView*>(m_layerLayout->getChildByName("ScrollView"));
// 	 Layout* scroPanel[6];
// 	 for (int i = 0; i < 6; i++)
// 	 {
// 		 scroPanel[i] = dynamic_cast<UIButton*>(scroV->getChildByName(CCString::createWithFormat("Panel_%d", i)->getCString()));
// 		 scroPanel[i]->setBackGroundColor(ccc3(150,200,255));
// 	 }
}

void ShopLayer::closeBtnDlgCallBack( CCObject* pSender )
{
	m_buyLayout->setVisible(false);
	m_buyLayout->setTouchEnable(false,true);
	m_layerLayout->setTouchEnable(true,true);
}

void ShopLayer::subBtnCallBack( CCObject* pSender )
{
	m_buyNum--;
	m_buyNumLabel->setText(CCString::createWithFormat("%d",m_buyNum)->getCString());
	m_totalPriLabel->setText(CCString::createWithFormat("%d",m_buyNum*m_onePri)->getCString());
}

void ShopLayer::addBtnCallBack( CCObject* pSender )
{
	m_buyNum++;
	m_buyNumLabel->setText(CCString::createWithFormat("%d",m_buyNum)->getCString());
	m_totalPriLabel->setText(CCString::createWithFormat("%d",m_buyNum*m_onePri)->getCString());
}

void ShopLayer::callForNumInput( CCObject* pSender )
{
	addChild(KeyboardLayer::create(-210,this,callfuncO_selector(ShopLayer::numInputCallBack),m_buyNum,9999,0),Z_10);
}

void ShopLayer::numInputCallBack( CCObject* pSender )
{
	KeyboardLayer* keyboard=(KeyboardLayer*)pSender;
	m_buyNum= keyboard->getInputValue();
	m_buyNumLabel->setText(CCString::createWithFormat("%d",m_buyNum)->getCString());
	m_totalPriLabel->setText(CCString::createWithFormat("%d",m_buyNum*m_onePri)->getCString());
}

void ShopLayer::updateScroV(bool isVis)
{		
	UIScrollView* scroV = dynamic_cast<UIScrollView*>(m_layerLayout->getChildByName("ScrollView"));
	for (int i = 0; i < 8; i++)
	{
		UIButton* scroPanel = dynamic_cast<UIButton*>(scroV->getChildByName(CCString::createWithFormat("Panel_%d", i)->getCString()));
		UIImageView* discountImg = dynamic_cast<UIImageView*>(scroPanel->getChildByName("discountImg"));
		discountImg->setVisible(isVis);
	}
}

void ShopLayer::updateBuyLayout(CCObject* pSender,bool isVis)
{
	UIButton* btn = dynamic_cast<UIButton*>(pSender);
	UILabel* nameLab = dynamic_cast<UILabel*>(m_buyLayout->getChildByName("propNameLabel"));
	nameLab->setText(dynamic_cast<UILabel*>(btn->getChildByName("nameLabel"))->getStringValue());

	UIImageView* discountImg = dynamic_cast<UIImageView*>(m_buyLayout->getChildByName("discountImg"));
	discountImg->setVisible(isVis);
	m_onePri = atoi(dynamic_cast<UILabel*>(btn->getChildByName("priLabel"))->getStringValue());
	m_onePriLabel->setText(CCString::createWithFormat("%d",m_onePri)->getCString());
	m_buyNum = 1;
	m_totalPriLabel->setText(CCString::createWithFormat("%d",m_onePri*m_buyNum)->getCString());
}

void ShopLayer::buyBtnCallBack( CCObject* pSender )
{
	m_buyLayout->setVisible(false);
	m_buyLayout->setTouchEnable(false,true);
	m_layerLayout->setTouchEnable(true,true);
}

void ShopLayer::keyBackClicked()
{
	closeBtnCallBack(NULL);
}
