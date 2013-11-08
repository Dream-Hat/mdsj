#include "AppDelegate.h"
#include "ZMQ/GameLogo.h"
#include "XF/ChatMediator.h"
#include "XF/ClubMediator.h"
#include "XF/FriendMediator.h"
#include "ZMQ/layerManager.h"
#include "ZMQ/MailMediator.h"
#include "XF/ShopMediator.h"
#include "ZMQ/PacksackMediator.h"
#include "ZMQ/RichangMediator.h"
#include "ZMQ/ShiwusuoMediator.h"
#include "ZMQ/TaskMediator.h"
#include "XF/TiejiangpuMediator.h"
#include "ZMQ/VipMediator.h"
#include "ZMQ/ZhujueMediator.h"
#include "XF/SoulMediator.h"
#include "ZMQ/Facade.h"
#include "ZMQ/DlgLogin.h"
/*#include "vld.h"*/
#include "CocoStudio/GUI/System/UIHelper.h"

#include "ZXL/SportMediator.h"
#include "ZLL/ArenaMediator.h"
#include "ZLL/LanguageManager.h"
#include "ZLL/CfgManager.h"
#include "ZLL/PVEMediator.h"
#include "ZLL/FightMediator.h"

#include "google/protobuf/stubs/common.h"
USING_NS_CC;

AppDelegate::AppDelegate() {
	MessageCenter::instance= new MessageCenter();
	LanguageManager::shareManager()->setLanguageFile("language/CN.xml");
}

AppDelegate::~AppDelegate() 
{
	// 	cocos2d::extension::CCArmatureDataManager::purge();
	cocos2d::extension::CCSSceneReader::sharedSceneReader()->purgeSceneReader();
	cocos2d::extension::ActionManager::shareManager()->purgeActionManager();
	cocos2d::extension::UIHelper::instance()->purgeUIHelper();
	MessageCenter::purgeMessageCenter();
	Facade::purgeFacade();
	CfgManger::pure();
	LanguageManager::shareManager()->purge();
	google::protobuf::ShutdownProtobufLibrary();
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();
    pDirector->setOpenGLView(pEGLView);

    CCSize designSize = CCSizeMake(800,480);
    CCSize resourceSize = CCSizeMake(960,640);
    CCSize screenSize = CCEGLView::sharedOpenGLView()->getFrameSize();

    std::vector<std::string> resDirOrders;

    TargetPlatform platform = CCApplication::sharedApplication()->getTargetPlatform();
    if (platform == kTargetIphone || platform == kTargetIpad)
    {
        std::vector<std::string> searchPaths = CCFileUtils::sharedFileUtils()->getSearchPaths();
        searchPaths.insert(searchPaths.begin(), "Published-iOS");
        CCFileUtils::sharedFileUtils()->setSearchPaths(searchPaths);
        if (screenSize.height == 1536)//iPad-hd
        {
            CCLog("resources-ipadhd");
            resourceSize = CCSizeMake(2048, 1536);
            resDirOrders.push_back("resources-ipadhd");
        }
        else if (screenSize.height == 768)//iPad
        {
            CCLog("resources-ipad");
            resourceSize = CCSizeMake(1024, 768);
            resDirOrders.push_back("resources-ipad");
        }
        else if (screenSize.height == 640)//iPhone 4/4s/5
        {
            CCLog("resources-iphonehd");
            resourceSize = CCSizeMake( 960,640);
            resDirOrders.push_back("resources-iphonehd");
        }
        else//iPhone 3GS
        {
            CCLog("resources-iphone");
            resourceSize = CCSizeMake(480, 320);
            resDirOrders.push_back("resources-iphone");
        }
    }
    else if (platform == kTargetAndroid || platform == kTargetWindows)
    {
        std::vector<std::string> searchPaths = CCFileUtils::sharedFileUtils()->getSearchPaths();
        searchPaths.insert(searchPaths.begin(), "Published-Android");
        CCFileUtils::sharedFileUtils()->setSearchPaths(searchPaths);
        if (screenSize.height > 720)
        {
            CCLog("resources-large");
            resourceSize = CCSizeMake( 960,640);
            resDirOrders.push_back("resources-large");
        }
        else if (screenSize.height > 568)
        {
            CCLog("resources-medium");
            resourceSize = CCSizeMake(480, 720);
            resDirOrders.push_back("resources-medium");
        }
        else
        {
            CCLog("resources-small");
            resourceSize = CCSizeMake(320, 568);
            resDirOrders.push_back("resources-small");
        }
    }

    CCFileUtils::sharedFileUtils()->setSearchResolutionsOrder(resDirOrders);
   // pDirector->setContentScaleFactor(resourceSize.width/designSize.width);
   // CCEGLView::sharedOpenGLView()->setDesignResolutionSize(designSize.width, designSize.height, kResolutionNoBorder);
	CCEGLView::sharedOpenGLView()->setDesignResolutionSize(screenSize.width, screenSize.height, kResolutionNoBorder);

    // turn on display FPS
    pDirector->setDisplayStats(true);
	pDirector->getOpenGLView()->setDesignResolutionSize(960, 640, kResolutionExactFit);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    CCScene *pScene = GameLogo::scene();

// 	LayerManager::loginLayer->addChild(LoadingLayer::create());
	ReStartupGame();
    // run
    pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    CCDirector::sharedDirector()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}

void AppDelegate::ReStartupGame()
{
	MessageCenter::instance->clear();
	Facade::instance()->clear();
// 	CDManger::pure();
// 	RoleManager::purgeFacade();
// 	RoleManager::reborn();

	Facade::instance()->addMediator(AppDelegate::ChatMediatorMark, new ChatMediator());
	Facade::instance()->addMediator(AppDelegate::ClubMediatorMark, new ClubMediator());
	Facade::instance()->addMediator(AppDelegate::FriendMediatorMark, new FriendMediator());
	Facade::instance()->addMediator(AppDelegate::MailMediatorMark, new MailMediator());
	Facade::instance()->addMediator(AppDelegate::ShopMediatorMark, new ShopMediator());
	Facade::instance()->addMediator(AppDelegate::PacksackMediatorMark, new PacksackMediator());
	Facade::instance()->addMediator(AppDelegate::RichangMediatorMark, new RichangMediator());
	Facade::instance()->addMediator(AppDelegate::ShiwusuoMediatorMark, new ShiwusuoMediator());
	Facade::instance()->addMediator(AppDelegate::TaskMediatorMark, new TaskMediator());
	Facade::instance()->addMediator(AppDelegate::TiejiangpuMediatorMark, new TiejiangpuMediator());
	Facade::instance()->addMediator(AppDelegate::VipMediatorMark, new VipMediator());
	Facade::instance()->addMediator(AppDelegate::ZhujueMediatorMark, new ZhujueMediator());
	Facade::instance()->addMediator(AppDelegate::DlgLoginMediatorMark, new DlgLoginMediator());

	Facade::instance()->addMediator(AppDelegate::ArenaMediatorMark,new ArenaMediator());
	Facade::instance()->addMediator(AppDelegate::PVEMediatorMark,new PVEMediator());
	Facade::instance()->addMediator(AppDelegate::FightMediatorMark,new FightMediator());
	Facade::instance()->addMediator(AppDelegate::SoulMediatorMark, new SoulMediator());
	Facade::instance()->addMediator(AppDelegate::SportMediatorMark, new SportMediator());

 	MessageCenter::instance->connectGame();

}
