#include "GameLogo.h"
#include "GameLoading.h"
#include "GameResource.h"
#include "GameDef.h"

GameLogo::GameLogo(void)
{
}

GameLogo::~GameLogo(void)
{
}

bool GameLogo::init()
{	
	//���� init ����
	if (! CCLayer::init())
	{
		return false;
	}
	CCSize scrSize = CCDirector::sharedDirector()->getWinSize();		//����,��ȡ��Ļ����
	//this->setIsTouchEnabled(true);										//֧�ִ���
	//setIsKeypadEnabled(true);

	CCTexture2D *tex = CCTextureCache::sharedTextureCache()->addImage(res_game_logo);

	//logo
	CCSprite* bgMap = CCSprite::createWithTexture(tex);
	bgMap->setPosition(ccp(scrSize.width/2,scrSize.height/2));
	bgMap->setOpacity(0);
	this->addChild(bgMap, Z_00);
	bgMap->runAction(CCFadeIn::create(2));
	schedule(schedule_selector(GameLogo::ShowLogo), 3.0f);
/*	autorelease();*/

	return true;
}

//�˳�
void GameLogo::onExit()
{
	this->removeAllChildrenWithCleanup(true);
	CCTextureCache::sharedTextureCache()->removeAllTextures();

	CCLayer::onExit();

	CCLog("[CCLog]->Exit: GameLogo!");
}

//����
void GameLogo::ShowLogo(float dt)
{
	CCTexture2D* tex = CCTextureCache::sharedTextureCache()->addImage(res_game_logo);
	if(getChildren()->count() > 1)
	{
		removeAllChildrenWithCleanup(true);
		CCSprite* aSprite = CCSprite::createWithTexture(tex);
		CCSize size = CCDirector::sharedDirector()->getWinSize();
		aSprite->setPosition(ccp(size.width/2,size.height/2));
		aSprite->setOpacity(0);
		addChild(aSprite, 0);
		aSprite->runAction(CCFadeIn::create(2));
		return;
	}
	unschedule(schedule_selector(GameLogo::update));



	GameLoading::show();
	int a = 0;
	a = 9;
}


//�ص�����
void GameLogo::gameCallback(CCObject* pSender)
{
	CCLog("[CCLog]->Callback: GameLogo!");
}

//�������
CCScene* GameLogo::scene()
{
	CCScene *scene = CCScene::create();
	GameLogo *layer = GameLogo::create();
	scene->addChild(layer);

	return scene;
}


