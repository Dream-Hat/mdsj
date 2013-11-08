#include "SceneString.h"
#include "GameDef.h"
#include "GameResource.h"
#include "SceneCover.h"

using namespace cocos2d;

CCScene* SceneString::scene()
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



SceneString* SceneString::show()
{
	CCScene* scene = CCScene::create();

	SceneString* layer = SceneString::create();

	scene->addChild(layer);

	CCScene* pScene = CCDirector::sharedDirector()->getRunningScene();
	if (!pScene)
	{
		CCDirector::sharedDirector()->runWithScene(scene);
	}
	else
	{
		CCDirector::sharedDirector()->replaceScene(scene);
	}
	 return layer;
}



bool SceneString::init()
{
    bool bRet = false;
    do 
    {
		CC_BREAK_IF(!CCLayer::init());

		CCSize screenSize = CCDirector::sharedDirector()->getWinSize();

		// bg
		CCSprite* bg = CCSprite::create(res_game_string);
		bg->setPosition(ccp(screenSize.width/2, screenSize.height/2));
		this->addChild(bg,Z_00);


		m_lblText = CCLabelTTF::create("13465","Arial", 26, CCSizeMake(200, 100), kCCTextAlignmentCenter);
		m_lblText->setPosition(ccp(80, 86));
		
		m_lblText->setColor(ccc3(255,255,255));
		m_lblText->setAnchorPoint(CCPointZero);
		this->addChild(m_lblText);


		CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
			"CloseNormal.png",
			"CloseSelected.png",
			this,
			menu_selector(SceneString::menuCloseCallback));

		pCloseItem->setPosition(ccp(screenSize.width - pCloseItem->getContentSize().width/2 ,
			pCloseItem->getContentSize().height/2));

        CCMenu* pMenu = CCMenu::create(pCloseItem,NULL);
        pMenu->setPosition(CCPointZero);
        CC_BREAK_IF(! pMenu);

        this->addChild(pMenu, 1);




        bRet = true;
    } while (0);

    return bRet;
}

void SceneString::menuCloseCallback(CCObject* pSender)
{
 // SceneCover::show();
}

void SceneString::setText( const char* pContent )
{
	if (m_lblText)
	{
		m_lblText->setString(pContent);
	}
}





