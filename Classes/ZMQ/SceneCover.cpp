#include "SceneCover.h"
#include "GameDef.h"
#include "SceneString.h"
#include "MessageCenter.h"
#include "AllCommandSignal.h"
#include "layerManager.h"

#include "../XF/ChatMediator.h"
#include "../XF/ShopMediator.h"
#include "PacksackMediator.h"
#include "TaskMediator.h"
#include "RichangMediator.h"
#include "../XF/ClubMediator.h"
#include "../XF/FriendMediator.h"
#include "../XF/TiejiangpuMediator.h"
#include "VipMediator.h"
#include "ShiwusuoMediator.h"
#include "ZhujueMediator.h"
#include "MailMediator.h"
#include "KeyboardLayer.h"
#include "UI_ModalDialogue_Layer.h"

#include "ZXL/SportMediator.h"
//#include "../ZLL/ArenaLayer.h"
#include "../ZLL/EventMSG.h"
using namespace cocos2d;

SceneCoverMediator::SceneCoverMediator()
{
	_scene = NULL;

	ADD_EVENT_LISTENER(OnSceneCoverOpen,NULL,this,Event::SceneCover_OPEN,SceneCoverMediator)
}

SceneCoverMediator::~SceneCoverMediator()
{
	if (_scene)
	{
		REMOVE_SCENE_FROM_LAYER(_scene)
	}
}

void SceneCoverMediator::OnPackage( short xy,char* pack,int len )
{

}

void SceneCoverMediator::OnSceneCoverOpen( CCObject* sender,int msgid,cocos2d::CCObject* obj)
{
	if (_scene == NULL)
	{
		_scene = SceneCover::create();
		//_scene->retain();
		_scene->m_Mediator = this;
		ADD_SCENE_TO_LAYER(_scene.obj(),LayerManager::sceneLayer);
	}
}

void SceneCoverMediator::dispose()
{
	if (_scene)
	{
		REMOVE_SCENE_FROM_LAYER(_scene)
			//_scene->release();
			_scene = NULL;
	}
}

CCScene* SceneCover::scene()
{
    CCScene * scene = NULL;
    do 
    {
        scene = CCScene::create();
        CC_BREAK_IF(! scene);
         SceneCover *layer = SceneCover::create();
         CC_BREAK_IF(! layer);
        scene->addChild(layer);
    } while (0);

    return scene;
}

// void SceneCover::show()
// {
// 	CCScene* scene = CCScene::create();
// 
// 	SceneCover* layer = SceneCover::create();
// 	scene->addChild(layer);
// 
// 	CCScene* pScene = CCDirector::sharedDirector()->getRunningScene();
// 	if (!pScene)
// 	{s
// 		CCDirector::sharedDirector()->runWithScene(scene);
// 	}
// 	else
// 	{
// 		CCDirector::sharedDirector()->replaceScene(scene);
// 	}
// }


bool SceneCover::init()
{
    bool bRet = false;
    do 
    {
		CC_BREAK_IF(!CCLayer::init());
		m_Mediator = NULL;

		mKTArrays=CCArray::createWithCapacity(6);mKTArrays->retain();
		m_Aimate = NULL;
		m_isvis = true;
		//setKeypadEnabled(true);

		CCSize screenSize = CCDirector::sharedDirector()->getWinSize();

		m_pUILayer = UILayer::create();
		m_pUILayer->scheduleUpdate();
		addChild(m_pUILayer);
	
		m_pLayout = dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile("ui/GameCover/GameCover.json"));
		m_pUILayer->addWidget(m_pLayout);

		UIButton* chat = dynamic_cast<UIButton*>(m_pLayout->getChildByName("chat"));
		chat->addReleaseEvent(this, coco_releaseselector(SceneCover::callbackMenuChat));

		UIButton* zhujue = dynamic_cast<UIButton*>(m_pLayout->getChildByName("zhujue"));
		zhujue->addReleaseEvent(this, coco_releaseselector(SceneCover::callbackMenuZhujue));
		
		UIButton* soul = dynamic_cast<UIButton*>(m_pLayout->getChildByName("soul"));
		soul->addReleaseEvent(this, coco_releaseselector(SceneCover::callbackMenuSoul));

		UIButton* task = dynamic_cast<UIButton*>(m_pLayout->getChildByName("task"));
		task->addReleaseEvent(this, coco_releaseselector(SceneCover::callbackMenuTask));

		UIButton* packsack = dynamic_cast<UIButton*>(m_pLayout->getChildByName("packsack"));
		packsack->addReleaseEvent(this, coco_releaseselector(SceneCover::callbackMenuPacksack));

		UIButton* setting = dynamic_cast<UIButton*>(m_pLayout->getChildByName("setting"));
		setting->addReleaseEvent(this, coco_releaseselector(SceneCover::callbackMenuSetting));

		UIButton* menu = dynamic_cast<UIButton*>(m_pLayout->getChildByName("menu"));
		menu->addReleaseEvent(this, coco_releaseselector(SceneCover::callbackMenu));

		UIButton* mail = dynamic_cast<UIButton*>(m_pLayout->getChildByName("mail"));
		mail->addReleaseEvent(this, coco_releaseselector(SceneCover::callbackMenuMail));

		UIButton* haoyou = dynamic_cast<UIButton*>(m_pLayout->getChildByName("friend"));
		haoyou->addReleaseEvent(this, coco_releaseselector(SceneCover::callbackMenuFriend));

		UIButton* VIP = dynamic_cast<UIButton*>(m_pLayout->getChildByName("vip"));
		VIP->addReleaseEvent(this, coco_releaseselector(SceneCover::callbackMenuVIP));

		UIButton* richangrenwu = dynamic_cast<UIButton*>(m_pLayout->getChildByName("richangrenwu"));
		richangrenwu->addReleaseEvent(this, coco_releaseselector(SceneCover::callbackMenuRichang));

		UIButton* tiejiangpu = dynamic_cast<UIButton*>(m_pLayout->getChildByName("tiejiangpu"));
		tiejiangpu->addReleaseEvent(this, coco_releaseselector(SceneCover::callbackTiejiangpu));

		UIButton* soulCentre = dynamic_cast<UIButton*>(m_pLayout->getChildByName("soulCentre"));
		soulCentre->addReleaseEvent(this, coco_releaseselector(SceneCover::callbackSoul));

		UIButton* shop = dynamic_cast<UIButton*>(m_pLayout->getChildByName("shop"));
		shop->addReleaseEvent(this, coco_releaseselector(SceneCover::callbackShop));

		UIButton* pvp = dynamic_cast<UIButton*>(m_pLayout->getChildByName("pvp"));
		pvp->addReleaseEvent(this, coco_releaseselector(SceneCover::callbackJingjichang));

		UIButton* shiwusuo = dynamic_cast<UIButton*>(m_pLayout->getChildByName("shiwusuo"));
		shiwusuo->addReleaseEvent(this, coco_releaseselector(SceneCover::callbackShiwusuo));

		UIButton* club = dynamic_cast<UIButton*>(m_pLayout->getChildByName("club"));
		club->addReleaseEvent(this, coco_releaseselector(SceneCover::callbackClub));

		UIButton* yewai = dynamic_cast<UIButton*>(m_pLayout->getChildByName("yewai"));
		yewai->addReleaseEvent(this, coco_releaseselector(SceneCover::callbackYewai));

		UIButton* sport = dynamic_cast<UIButton*>(m_pLayout->getChildByName("sport"));
		sport->addReleaseEvent(this, coco_releaseselector(SceneCover::callbackMenuSport));

		createArrayByPlist();
		CCAnimation* animation=CCAnimation::createWithSpriteFrames(mKTArrays,0.3f);
		m_Aimate=CCAnimate::create(animation);
		m_Aimate->retain();
		




        bRet = true;
    } while (0);

    return bRet;
}

void SceneCover::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();
}

void SceneCover::callbackMenuChat( CCObject* pSender )
{
	SEND_EVENT(NULL,Event::CHAT_OPEN,NULL)
}

void SceneCover::callbackMenuFriend( CCObject* pSender )
{
	SEND_EVENT(NULL,Event::FRIEND_OPEN,NULL)
}

void SceneCover::callbackMenuMail( CCObject* pSender )
{
	SEND_EVENT(NULL,Event::MAIL_OPEN,NULL)
}

void SceneCover::callbackMenuPacksack( CCObject* pSender )
{
// 	CCSprite* sprite=CCSprite::create();
// 	this->addChild(sprite,10);
// 	sprite->setTag(110);
// 	sprite->setPosition(ccp(300,200));
// 	sprite->runAction(CCSequence::create(CCCallFunc::create(this,callfunc_selector(SceneCover::showKatoon)),CCCallFunc::create(this,callfunc_selector(SceneCover::callback11)),CCCallFunc::create(this,callfunc_selector(SceneCover::stst)),NULL));

	SEND_EVENT(NULL,Event::PACKSACK_OPEN,NULL)
}


void SceneCover::callbackMenuRichang( CCObject* pSender )
{
	SEND_EVENT(NULL,Event::RICHANG_OPEN,NULL)
}

void SceneCover::callbackMenuSetting( CCObject* pSender )
{
// 	SceneString *sen = SceneString::show();
// 	if (sen != NULL)
// 	{
// 		sen->setText("setting");
// 	}
//	UI_ModalDialogue_Layer::DoModal("321","4343",UI_ModalDialogue_Layer::DT_Yes_No,[&](){this->foo();} );
}

void SceneCover::callbackMenuSoul( CCObject* pSender )
{
	SEND_EVENT(NULL,Event::SOUL_OPEN,NULL)
}

void SceneCover::callbackMenuTask( CCObject* pSender )
{
	SEND_EVENT(NULL,Event::TASK_OPEN,NULL)
}

void SceneCover::callbackMenuZhujue( CCObject* pSender )
{
	SEND_EVENT(NULL,Event::ZHUJUE_OPEN,NULL)
}

void SceneCover::callbackClub( CCObject* pSender )
{
// 	ClubLayer* dlg = ClubLayer::create();
// 	dlg->setPosition(CCPointZero);
// 	this->addChild(dlg, Z_Max);
	SEND_EVENT(NULL,Event::CLUB_OPEN,NULL)
}

void SceneCover::callbackYewai( CCObject* pSender )
{
	SEND_EVENT(NULL,PVEEvent::PVEVIEW_OPEN,NULL);
}

void SceneCover::callbackJingjichang( CCObject* pSender )
{
// 	ArenaLayer* layer=ArenaLayer::create();
// 	this->addChild(layer,11);	
	//SEND_EVENT(NULL,Event::EFFECT_HALF,NULL);
	SEND_EVENT(NULL,ArenaEvent::ARENAVIEW_OPEN,NULL);
}

void SceneCover::callbackShiwusuo( CCObject* pSender )
{
	SEND_EVENT(NULL,Event::SHIWUSUO_OPEN,NULL)
}
void SceneCover::callbackShop( CCObject* pSender )
{
	SEND_EVENT(NULL,Event::Shop_OPEN,NULL)
}

void SceneCover::callbackSoul( CCObject* pSender )
{
	SEND_EVENT(NULL,Event::SOUL_OPEN,NULL)
// 	SceneString *sen = SceneString::show();
// 	if (sen != NULL)
// 	{
// 		sen->setText("soul");
	// 	}
	//addChild(KeyboardLayer::create(-160,this,callfuncO_selector(SceneCover::callbackTiejiangpu),1,9999,0),Z_Max+3);
}

void SceneCover::stst()
{
	this->removeChildByTag(110,true);
}

void SceneCover::callbackTiejiangpu( CCObject* pSender )
{
	SEND_EVENT(NULL,Event::TIEJIANGPU_OPEN,NULL)
	
	//CCTextureCache::sharedTextureCache()->dumpCachedTextureInfo();
}

void SceneCover::createArrayByPlist()
{
	if (mKTArrays->count()>0)return;
	CCString* plistFileName=CCString::createWithFormat("so_cover_katoon.plist");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(plistFileName->getCString());
	mKTArrays->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("1.png"));
	mKTArrays->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("2.png"));
	mKTArrays->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("3.png"));
	mKTArrays->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("4.png"));
	mKTArrays->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("5.png"));
	mKTArrays->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("6.png"));
	CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile(plistFileName->getCString());
}

void SceneCover::showKatoon()
{
	CCSprite* sprite=CCSprite::create();
	this->addChild(sprite,10);
	sprite->setTag(110);
	sprite->setPosition(ccp(300,200));
	//sprite->runAction(CCSequence::create(m_Aimate,CCCallFunc::create(this,callfunc_selector(SceneCover::stst)),NULL));
	sprite ->runAction(m_Aimate);
}

void SceneCover::callback11()
{
	PacksackLayer* dlg = PacksackLayer::create();
	dlg->setPosition(CCPointZero);
	this->addChild(dlg, 1);
}

void SceneCover::callbackMenu( CCObject* pSender )
{
	m_isvis = !m_isvis;
	setBtnVis(m_isvis);	
}

void SceneCover::callbackMenuVIP( CCObject* pSender )
{
// 	VipLayer* dlg = VipLayer::create();
// 	dlg->setPosition(CCPointZero);
// 	this->addChild(dlg, 1);
	SEND_EVENT(NULL,Event::VIP_OPEN,NULL)
}

void SceneCover::setBtnVis(bool isVis)
{
	UIButton* zhujue = dynamic_cast<UIButton*>(m_pLayout->getChildByName("zhujue"));
	//zhujue->setVisible(isVis);
	zhujue->setEnabled(isVis);
	UIButton* soul = dynamic_cast<UIButton*>(m_pLayout->getChildByName("soul"));
	soul->setEnabled(isVis);
	UIButton* task = dynamic_cast<UIButton*>(m_pLayout->getChildByName("task"));
	task->setEnabled(isVis);
	UIButton* packsack = dynamic_cast<UIButton*>(m_pLayout->getChildByName("packsack"));
	packsack->setEnabled(isVis);
	UIButton* setting = dynamic_cast<UIButton*>(m_pLayout->getChildByName("setting"));
	setting->setEnabled(isVis);
	UIButton* mail = dynamic_cast<UIButton*>(m_pLayout->getChildByName("mail"));
	mail->setEnabled(isVis);
	UIButton* haoyou = dynamic_cast<UIButton*>(m_pLayout->getChildByName("friend"));
	haoyou->setEnabled(isVis);
// 	UIButton* chat = dynamic_cast<UIButton*>(m_pLayout->getChildByName("chat"));
// 	chat->setEnabled(isVis);
	UIButton* vipBtn = dynamic_cast<UIButton*>(m_pLayout->getChildByName("vip"));
	vipBtn->setEnabled(isVis);
}

void SceneCover::callbackMenuSport( CCObject* pSender )
{
	SEND_EVENT(NULL,Event::SPORT_OPEN,NULL)
}

void SceneCover::keyBackClicked()
{
	//CCDirector::sharedDirector()->end();
}

void SceneCover::foo()
{

}




