#include "GameLoading.h"
#include "GameResource.h"
#include "GameDef.h"
#include "DlgLogin.h"
#include "MessageCenter.h"
#include "AllCommandSignal.h"



GameLoading::GameLoading() : m_scale(0.0f)
{
}

GameLoading::~GameLoading()
{

}
void GameLoading::show()
{
	//³¡¾°ÇÐ»»
	CCTransitionScene *reScene = NULL;

	float t = 1.2f;

	CCScene* scene = CCScene::create();
   reScene = CCTransitionJumpZoom ::create(t , scene);
   CCDirector::sharedDirector()->replaceScene(reScene);
	GameLoading* layer = GameLoading::create();

	scene->addChild(layer);

	CCScene* pScene = CCDirector::sharedDirector()->getRunningScene();
	if (!pScene)
	{
		CCDirector::sharedDirector()->runWithScene(reScene);
	}
	else
	{
		CCDirector::sharedDirector()->replaceScene(reScene);
	}
}

bool GameLoading::init()
{
	bool bRet = false;

	do 
	{
		CC_BREAK_IF(!CCLayer::init());

		CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
		CCLog("[CCLog]->init Gameloading!");
		// bg
		CCSprite* bg = CCSprite::create(res_game_loading);
		bg->setPosition(ccp(screenSize.width/2, screenSize.height/2));
		this->addChild(bg);

		bRet = true;

	} while (0);

	return bRet;
}

void GameLoading::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();

	this->schedule(schedule_selector(GameLoading::tickLoadGameRes));
}


void GameLoading::tickLoadGameRes( float dt )
{
	this->unschedule(schedule_selector(GameLoading::tickLoadGameRes));

	CCSpriteFrameCache* sharedSpriteFrameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
	sharedSpriteFrameCache->addSpriteFramesWithFile(SO_LOGIN_Texture_Plist);
	sharedSpriteFrameCache->addSpriteFramesWithFile(SO_COVER_Texture_Plist);


	// µÇÂ¼¶Ô»°¿ò
// 	DlgLogin* dlg = DlgLogin::create();
// 	dlg->setPosition(CCPointZero);
// 	this->addChild(dlg, Z_Max);
	SEND_EVENT(NULL,Event::DLGLOGIN_OPEN,NULL)

}
