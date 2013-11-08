#include "PVELayer.h"
#include "PVEMediator.h"
#include "ToolsFun.h"
#include "CMyMenu.h"
#include "EventMSG.h"
#include "TextChange.h"
#include "PVEPopLayer.h"
#include "LanguageManager.h"
#include "PVENode.h"
#include "ScrollViewModel.h"
#include "IniParser.h"
#include "../ZMQ/MessageCenter.h"
#include "../ZMQ/SceneCover.h"
#include <math.h>

USING_NS_CC;



PVELayer::PVELayer():m_PVEMediator(NULL),m_UILayer(NULL),m_MapLayer(NULL)
{

}

PVELayer::~PVELayer()
{

}

bool PVELayer::init()
{
	bool bRet=false;
	do 
	{
		initLayer();
		bRet=true;
	} while (0);
	return bRet;
}

void PVELayer::initLayer()
{
	//UI层
	m_UILayer=PVEUILayer::create(-150);
	this->addChild(m_UILayer,LAYER_UILAYER_ZINDEX);

	//游戏界面层
	m_MapLayer=PVEMapLayer::create(-140);
	this->addChild(m_MapLayer);
}

void PVELayer::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,-130,true);
}

bool PVELayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	return true;
}

//////////////////////////////////////////////////////////////////////////
//PVEUILayer
PVEUILayer::PVEUILayer():m_Priority(0),m_MapCanMove(true),m_BtnGoLeft(NULL),m_BtnGoRight(NULL),m_DropListBackground(NULL),m_PlaceViewModel(NULL),m_DropListMenu(NULL),m_BtnPlaceName(NULL)
{
}

PVEUILayer::~PVEUILayer()
{

}

bool PVEUILayer::init()
{
	bool bRet=false;
	do 
	{
		bRet=true;
	} while (0);
	return bRet;
}

PVEUILayer* PVEUILayer::create(int r)
{
	PVEUILayer* pRet=new PVEUILayer();
	pRet->m_Priority=r;
	if (pRet&&pRet->init())
	{
		pRet->autorelease();
		pRet->initLayer();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return NULL;
}

void PVEUILayer::onEnter()
{
	CCLayer::onEnter();
	this->setKeypadEnabled(true);
}

void PVEUILayer::keyBackClicked()
{
	SEND_EVENT(this,PVEEvent::PVEVIEW_CLOSE,NULL);
}

void PVEUILayer::keyMenuClicked()
{

}

void PVEUILayer::initLayer()
{
	//名字按钮背景
	CCSprite* placeNamebackground=CCSprite::create(PVE_FIELD_BUTTON_MAPNAME_1);
	this->addChild(placeNamebackground,2);
	placeNamebackground->setPosition(ccp(480,592));

	CCMenuP* menu=CCMenuP::create(m_Priority-5,NULL);
	this->addChild(menu,3);
	menu->setPosition(CCPointZero);

	CCMenuItemSprite* btnGoBack=ToolsFun::createBTN(LanguageManager::shareManager()->getContentByKey("GOBACK").c_str(),ButtomType_Red,this,menu_selector(PVEUILayer::OnBtnGoBack));
	m_BtnGoLeft=ToolsFun::createOnePicBtn(PVE_FIELD_BUTTON_ARROW,this,menu_selector(PVEUILayer::OnBtnGoLeft),true);
	m_BtnGoRight=ToolsFun::createOnePicBtn(PVE_FIELD_BUTTON_ARROW,this,menu_selector(PVEUILayer::OnBtnGoRight));
	menu->addChild(btnGoBack);
	//menu->addChild(m_BtnGoLeft);
	//menu->addChild(m_BtnGoRight);
	btnGoBack->setPosition(ccp(900,600));
	m_BtnGoLeft->setPosition(ccp(70,320));
	m_BtnGoRight->setPosition(ccp(890,320));
	m_BtnGoLeft->setEnabled(false);

	//CCMenuItemSprite* btnLevel=ToolsFun::createBTN(LanguageManager::shareManager()->getContentByKey("LEVELS").c_str(),ButtomType_Blue2,this,menu_selector(PVEUILayer::OnBtnOpenLevel));
	//menu->addChild(btnLevel);
	//btnLevel->setPosition(ccp(700,30));
	
	//关卡名字按钮
	m_BtnPlaceName=CCMenuItemSprite::create(
		CCSprite::create(PVE_FIELD_BUTTON_MAPNAME),
		CCSprite::create(PVE_FIELD_BUTTON_MAPNAME_SEL),
		CCSprite::create(PVE_FIELD_BUTTON_MAPNAME),
		this,menu_selector(PVEUILayer::OnBtnOpenPlaceNameScrollView));
	menu->addChild(m_BtnPlaceName);
	m_BtnPlaceName->setPosition(ccp(480,585));
	
	//下拉列表
	createDropList();
	m_BtnPlaceName->activate();
	refreshDropListData();
}

void PVEUILayer::createDropList()
{
	m_DropListBackground=CCSprite::create(PVE_FIELD_PULLDOWNLIST);
	this->addChild(m_DropListBackground,1);
	m_DropListBackground->setPosition(ccp(480,50));
	m_DropListBackground->setAnchorPoint(ccp(0.5f,0.0f));

	CCLayer* scrollLayer=CCLayer::create();
	//CCLayerColor* scrollLayer=CCLayerColor::create(ccc4(255,255,255,150));
	m_PlaceViewModel=ScrollViewModel::createP(m_Priority-2,CCSizeMake(367,496),scrollLayer);
	this->addChild(m_PlaceViewModel,2);
	m_PlaceViewModel->setContentSize(CCSizeMake(367,1000));
	m_PlaceViewModel->setPosition(ccp(297,50));
	m_PlaceViewModel->setDirection(kCCScrollViewDirectionVertical);
	
	m_DropListMenu=CCMenuP::create(m_Priority-4,NULL);
	scrollLayer->addChild(m_DropListMenu);
	m_DropListMenu->setPosition(CCPointZero);
}

void PVEUILayer::OnBtnGoBack( cocos2d::CCObject* sender )
{
	SEND_EVENT(this,PVEEvent::PVEVIEW_CLOSE,NULL);
}

void PVEUILayer::OnBtnGoLeft( cocos2d::CCObject* sender )
{
	if (m_MapCanMove)
	{
		SEND_EVENT(this,PVEEvent::PVEVIEW_MAPMOVELEFT,NULL);
		m_MapCanMove=!m_MapCanMove;
	}
}

void PVEUILayer::OnBtnGoRight( cocos2d::CCObject* sender )
{
	if (m_MapCanMove)
	{
		SEND_EVENT(this,PVEEvent::PVEVIEW_MAPMOVERIGHT,NULL);
		m_MapCanMove=!m_MapCanMove;
	}
}

void PVEUILayer::OnBtnOpenLevel(cocos2d::CCObject* sender)
{
	SEND_EVENT(this,PVEEvent::PVEVIEW_OPENLEVEL,NULL);
	this->setKeypadEnabled(false);
}

void PVEUILayer::OnBtnOpenPlaceNameScrollView(cocos2d::CCObject* sender)
{
	if (m_DropListBackground->isVisible()&&m_PlaceViewModel->isVisible())
	{
		m_DropListBackground->setVisible(false);
		m_PlaceViewModel->setVisible(false);
	}
	else if (!m_DropListBackground->isVisible()&&!m_PlaceViewModel->isVisible())
	{
		m_DropListBackground->setVisible(true);
		m_PlaceViewModel->setVisible(true);
	}

}

void PVEUILayer::OnBtnGotoTargetPage(cocos2d::CCObject* sender)
{
	CCMenuItemSprite* btn=(CCMenuItemSprite*)sender;
	EventParam* ep=new EventParam();
	ep->autorelease();
	ep->intParam=btn->getTag();
	SEND_EVENT(this,PVEEvent::PVEVIEW_GOTOTARGETPAGE,ep);
}

void PVEUILayer::setBtnsState( int page )
{
	if (page<=0)
	{
		m_BtnGoLeft->setEnabled(false);
		m_BtnGoRight->setEnabled(true);
		//setBtnLeftCanClick(false);
		//setBtnRightCanClick(true);
	}
	else if (page>=8)
	{
		m_BtnGoLeft->setEnabled(true);
		m_BtnGoRight->setEnabled(false);
		//setBtnLeftCanClick(true);
		//setBtnRightCanClick(false);
	}
	else
	{
		m_BtnGoLeft->setEnabled(true);
		m_BtnGoRight->setEnabled(true);
		//setBtnLeftCanClick(true);
		//setBtnRightCanClick(true);
	}
}

void PVEUILayer::refreshDropListData()
{
	m_DropListMenu->removeAllChildrenWithCleanup(true);
	INIParser parser("ui/PVE/configfile/Levels.ini");
	int btnNum=parser.getInt("Level","TotalLevelNum",0);
	float hStep=50;
	m_PlaceViewModel->setContentSize(CCSizeMake(367,btnNum*hStep));
	float hStart=btnNum*hStep-hStep/2.0;
	for (int i=1;i<=btnNum;i++)
	{
		char nodeName[50];
		sprintf(nodeName,"Level_%d",i);
		CCMenuItemSprite* btn=CCMenuItemSprite::create(
			CCSprite::create(PVE_FIELD_BUTTON_MAPNAME),
			CCSprite::create(PVE_FIELD_BUTTON_MAPNAME_SEL),
			CCSprite::create(PVE_FIELD_BUTTON_MAPNAME),
			this,menu_selector(PVEUILayer::OnBtnGotoTargetPage));
		m_DropListMenu->addChild(btn);
		//btn->setTag(i*1000+parser.getInt(nodeName,"Page",0));
		btn->setTag(parser.getInt(nodeName,"Page",0));
		btn->setPosition(ccp(183,hStart-(i-1)*hStep));
	}

}

//////////////////////////////////////////////////////////////////////////
//PVEMapLayer
PVEMapLayer::PVEMapLayer()
{
	m_MainBackground=NULL;
	m_LeftBackground=NULL;
	m_RightBackground=NULL;
	m_TempBackground=NULL;
	m_MaxPage=8;
	m_CurrentPage=1;
	m_Priority=0;
	m_CanDragMap=true;
	m_MoveTouchLeft=true;
	m_MoveToTargetPageArray=CCArray::createWithCapacity(8);m_MoveToTargetPageArray->retain();
}

PVEMapLayer::~PVEMapLayer()
{
	m_MoveToTargetPageArray->release();
}

bool PVEMapLayer::init()
{
	bool bRet=false;
	do 
	{
		initLayer();
		bRet=true;
	} while (0);
	return bRet;
}

PVEMapLayer* PVEMapLayer::create(int r)
{
	PVEMapLayer* pRet=new PVEMapLayer();
	pRet->m_Priority=r;
	if (pRet&&pRet->init())
	{
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return NULL;
}

void PVEMapLayer::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,m_Priority,true);
}

bool PVEMapLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	if (m_CanDragMap)
	{
		m_StartTouchPoint=pTouch->getLocationInView();
		m_StartTouchPoint=CCDirector::sharedDirector()->convertToGL(m_StartTouchPoint);
		m_StartTouchPoint.y=320;
	}
	return true;
}

void PVEMapLayer::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	if (m_CanDragMap)
	{
		CCPoint prePoint=pTouch->getPreviousLocationInView();
		CCPoint nowPoint=pTouch->getLocationInView();
		prePoint=CCDirector::sharedDirector()->convertToGL(prePoint);
		nowPoint=CCDirector::sharedDirector()->convertToGL(nowPoint);
	
		CCPoint offserPoint=ccpSub(nowPoint,prePoint);
		//判断方向
		if (offserPoint.x>0)
		{
			if (m_CurrentPage==1)
			{
				//m_CanDragMap=false;
				CCLOG("x=%f",this->getPosition().x);
				if (this->getPositionX()>=-10)return;
			}
		}
		else
		{
			if (m_CurrentPage==m_MaxPage)
			{
				if (this->getPositionX()<=960*(m_CurrentPage-1)-10)return;
			}
		}
		//m_CanDragMap=true;
		offserPoint.y=0;
		this->setPosition(ccpAdd(this->getPosition(),offserPoint));
	}
}

void PVEMapLayer::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	if (m_CanDragMap)
	{
		CCSize winSize=CCDirector::sharedDirector()->getWinSize();
		CCPoint endPoint=pTouch->getLocationInView();
		endPoint=CCDirector::sharedDirector()->convertToGL(endPoint);
		endPoint.y=320;
		CCPoint offsetPos=ccpSub(endPoint,m_StartTouchPoint);
		if (abs((int)offsetPos.x)<winSize.width/3)
		{//复位
			//this->setTouchEnabled(false);
			m_CanDragMap=false;
			this->runAction(CCSequence::create(CCMoveTo::create(0.5f,m_MapPos),CCCallFunc::create(this,callfunc_selector(PVEMapLayer::resetPosOver)),NULL));
		}
		else
		{
			//判断左右拖动
			if (offsetPos.x<0)//左拖
			{
				m_MoveTouchLeft=true;
				//先判断是否到达最后1页
				if (m_CurrentPage>=m_MaxPage)return;
				m_CurrentPage++;
				m_CanDragMap=false;
				this->runAction(CCSequence::create(CCMoveTo::create(0.5f,ccp(m_MapPos.x-960,m_MapPos.y)),CCCallFunc::create(this,callfunc_selector(PVEMapLayer::LayerMoveOver)),NULL));
			}
			else//右拖
			{
				m_MoveTouchLeft=false;
				//先判断是否在第一页
				if (m_CurrentPage<=1)return;
				m_CurrentPage--;
				m_CanDragMap=false;
				this->runAction(CCSequence::create(CCMoveTo::create(0.5f,ccp(m_MapPos.x+960,m_MapPos.y)),CCCallFunc::create(this,callfunc_selector(PVEMapLayer::LayerMoveOver)),NULL));
			}
		}
	}	
}

void PVEMapLayer::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{

}

void PVEMapLayer::initLayer()
{//OK
	m_MainBackground=CCSprite::create(PVE_FIELD_MAP);
	this->addChild(m_MainBackground);
	m_MainBackground->setPosition(ccp(480,320));
	createRoute(m_MainBackground);

 	m_RightBackground=CCSprite::create(PVE_FIELD_MAP);
 	this->addChild(m_RightBackground);
 	m_RightBackground->setPosition(ccp(1440,320));
	createRoute(m_RightBackground,2);
	m_MapPos=this->getPosition();
	this->setTouchEnabled(true);
}

void PVEMapLayer::createRoute(cocos2d::CCSprite* sprite)
{
	if (sprite==NULL)return;
	CCMenuP* menu=CCMenuP::create(m_Priority-1,NULL);
	sprite->addChild(menu,3);
	menu->setPosition(CCPointZero);
	char filePath[100];
	sprintf(filePath,"ui/PVE/configfile/RoutePage_%d.ini",m_CurrentPage);
	INIParser parser(filePath);
	for (int i=1;i<=4;i++)
	{
		CCMenuItemSprite* btnLevel=CCMenuItemSprite::create(
			CCSprite::create(PVE_FIELD_BUTTON_STAGE),
			CCSprite::create(PVE_FIELD_BUTTON_STAGE_SEL),
			CCSprite::create(PVE_FIELD_BUTTON_STAGE),
			this,menu_selector(PVEMapLayer::OnBtnEnterLevel));
		CCString* name=CCString::createWithFormat("Level_%d",i);
		menu->addChild(btnLevel);
		btnLevel->setPosition(parser.getPoint(name->getCString(),"Position",CCPointZero));
		btnLevel->setTag(i);
	}

	//线路
	for (int i=1;i<=20;i++)
	{
		CCSprite* spriteRoute=CCSprite::create(PVE_FIELD_PIC_ROAD);
		sprite->addChild(spriteRoute);
		CCString* nodeName=CCString::createWithFormat("Route_%d",i);
		spriteRoute->setPosition(parser.getPoint(nodeName->getCString(),"Position",CCPointZero));
		spriteRoute->setRotation(parser.getFloat(nodeName->getCString(),"Rotation",0.0f));
	}
}

void PVEMapLayer::createRoute(cocos2d::CCSprite* sprite,int targetPage)
{
	if (sprite==NULL)return;
	CCMenuP* menu=CCMenuP::create(m_Priority-1,NULL);
	sprite->addChild(menu,3);
	menu->setPosition(CCPointZero);
	
	char filePath[100];
	sprintf(filePath,"ui/PVE/configfile/RoutePage_%d.ini",targetPage);
	INIParser parser(filePath);

	for (int i=1;i<=4;i++)
	{
		CCMenuItemSprite* btnLevel=CCMenuItemSprite::create(
			CCSprite::create(PVE_FIELD_BUTTON_STAGE),
			CCSprite::create(PVE_FIELD_BUTTON_STAGE_SEL),
			CCSprite::create(PVE_FIELD_BUTTON_STAGE),
			this,menu_selector(PVEMapLayer::OnBtnEnterLevel));
		CCString* name=CCString::createWithFormat("Level_%d",i);
		btnLevel->setPosition(parser.getPoint(name->getCString(),"Position",CCPointZero));
		btnLevel->setTag(targetPage*100+i);
		menu->addChild(btnLevel);
	}

	//线路
	for (int i=1;i<=20;i++)
	{
		CCSprite* spriteRoute=CCSprite::create(PVE_FIELD_PIC_ROAD);
		sprite->addChild(spriteRoute);
		CCString* nodeName=CCString::createWithFormat("Route_%d",i);
		spriteRoute->setPosition(parser.getPoint(nodeName->getCString(),"Position",CCPointZero));
		spriteRoute->setRotation(parser.getFloat(nodeName->getCString(),"Rotation",0.0f));
	}
}

void PVEMapLayer::LayerMoveOver()
{
	if (m_MoveTouchLeft)
	{
		m_MapPos.x-=960;
		if (m_CurrentPage<8)
			createANewPage(ccpAdd(m_RightBackground->getPosition(),ccp(960,0)));
		//交换指针
		if (m_LeftBackground)
			m_LeftBackground->removeFromParentAndCleanup(true);
		m_LeftBackground=m_MainBackground;
		m_MainBackground=m_RightBackground;
		m_RightBackground=m_TempBackground;
		m_TempBackground=NULL;
	}
	else
	{
		m_MapPos.x+=960;
		if (m_CurrentPage>1)
			createANewPage(ccpAdd(m_LeftBackground->getPosition(),ccp(-960,0)));
		//交换指针
		if (m_RightBackground)
			m_RightBackground->removeFromParentAndCleanup(true);
		m_RightBackground=m_MainBackground;
		m_MainBackground=m_LeftBackground;
		m_LeftBackground=m_TempBackground;
		m_TempBackground=NULL;
	}
	m_CanDragMap=true;
}

void PVEMapLayer::moveToTargetPageOver()
{
	if (m_MoveTouchLeft)//left
	{
		int size=m_MoveToTargetPageArray->count();
		m_CurrentPage+=size;
		m_MapPos=ccpAdd(m_MapPos,ccp(size*(-960),0));
		if (size>=3)
		{
			for (int i=0;i<size-3;i++)
			{
				CCSprite* sprite=(CCSprite*)m_MoveToTargetPageArray->objectAtIndex(0);
				sprite->removeFromParentAndCleanup(true);
				m_MoveToTargetPageArray->removeObjectAtIndex(0);
			}
			//==3
			if (m_LeftBackground)
				m_LeftBackground->removeAllChildrenWithCleanup(true);
			m_MainBackground->removeAllChildrenWithCleanup(true);
			m_RightBackground->removeAllChildrenWithCleanup(true);
			m_LeftBackground=(CCSprite*)m_MoveToTargetPageArray->objectAtIndex(0);
			m_MainBackground=(CCSprite*)m_MoveToTargetPageArray->objectAtIndex(1);
			m_RightBackground=(CCSprite*)m_MoveToTargetPageArray->objectAtIndex(2);
			m_MoveToTargetPageArray->removeAllObjects();
		}
		else if (size==2)
		{
			if (m_LeftBackground)
				m_LeftBackground->removeAllChildrenWithCleanup(true);
			m_MainBackground->removeAllChildrenWithCleanup(true);
			m_LeftBackground=m_RightBackground;
			m_MainBackground=(CCSprite*)m_MoveToTargetPageArray->objectAtIndex(0);
			m_RightBackground=(CCSprite*)m_MoveToTargetPageArray->objectAtIndex(1);
			m_MoveToTargetPageArray->removeAllObjects();
		}
		else if (size==1)
		{
			if (m_LeftBackground)
				m_LeftBackground->removeAllChildrenWithCleanup(true);
			m_LeftBackground=m_MainBackground;
			m_MainBackground=m_RightBackground;
			m_RightBackground=(CCSprite*)m_MoveToTargetPageArray->objectAtIndex(0);
			m_MoveToTargetPageArray->removeAllObjects();
		}
	}
	else
	{
		int size=m_MoveToTargetPageArray->count();
		m_MapPos=ccpAdd(m_MapPos,ccp(size*960,0));
		m_CurrentPage-=size;
		if (size>=3)
		{
			for (int i=0;i<size-3;i++)
			{
				CCSprite* sprite=(CCSprite*)m_MoveToTargetPageArray->objectAtIndex(0);
				sprite->removeFromParentAndCleanup(true);
				m_MoveToTargetPageArray->removeObjectAtIndex(0);
			}
			//3
			m_LeftBackground->removeAllChildrenWithCleanup(true);
			m_MainBackground->removeAllChildrenWithCleanup(true);
			m_RightBackground->removeAllChildrenWithCleanup(true);
			m_RightBackground=(CCSprite*)m_MoveToTargetPageArray->objectAtIndex(0);
			m_MainBackground=(CCSprite*)m_MoveToTargetPageArray->objectAtIndex(1);
			m_LeftBackground=(CCSprite*)m_MoveToTargetPageArray->objectAtIndex(2);
			m_MoveToTargetPageArray->removeAllObjects();
		}
		else if (size==2)
		{
			m_RightBackground->removeAllChildrenWithCleanup(true);
			m_MainBackground->removeAllChildrenWithCleanup(true);
			m_RightBackground=m_LeftBackground;
			m_MainBackground=(CCSprite*)m_MoveToTargetPageArray->objectAtIndex(0);
			m_LeftBackground=(CCSprite*)m_MoveToTargetPageArray->objectAtIndex(1);
			m_MoveToTargetPageArray->removeAllObjects();
		}
		else if (size=1)
		{
			m_RightBackground->removeAllChildrenWithCleanup(true);
			m_RightBackground=m_MainBackground;
			m_MainBackground=m_LeftBackground;
			m_LeftBackground=(CCSprite*)m_MoveToTargetPageArray->objectAtIndex(0);
			m_MoveToTargetPageArray->removeAllObjects();
		}
	}
}

CCSprite* PVEMapLayer::createAPage(cocos2d::CCPoint point)
{
	CCSprite* sprite=CCSprite::create(PVE_FIELD_MAP);
	this->addChild(sprite);
	sprite->setPosition(point);
	createRoute(sprite,m_CurrentPage+1);
	return sprite;
}

void PVEMapLayer::resetPosOver()
{
	m_CanDragMap=true;
}

void PVEMapLayer::createANewPage(cocos2d::CCPoint point)
{
	m_TempBackground=CCSprite::create(PVE_FIELD_MAP);
	this->addChild(m_TempBackground);
	m_TempBackground->setPosition(point);
	createRoute(m_TempBackground,m_CurrentPage+1);
}

void PVEMapLayer::gotoTargetPage(int page)
{
	if (page>8||page<=0)return;
	if (m_CurrentPage==page)return;

	if (page<m_CurrentPage)
	{//-->right
		int pages=m_CurrentPage-page;
		m_MoveToTargetPageArray->removeAllObjects();
		float startPosX=m_LeftBackground->getPositionX();
		for (int i=0;i<page;i++)
		{
			startPosX-=960;
			CCSprite* page=createAPage(ccp(startPosX,320));
			m_MoveToTargetPageArray->addObject(page);
		}
		m_MoveTouchLeft=false;
		this->runAction(CCSequence::create(CCMoveBy::create(1.0f,ccp(960.0*page,1)),CCCallFunc::create(this,callfunc_selector(PVEMapLayer::moveToTargetPageOver)),NULL));
	}
	else
	{//-->left
		int pages=m_CurrentPage-page;
		m_MoveToTargetPageArray->removeAllObjects();
		float startPosX=m_RightBackground->getPositionX();
		for (int i=0;i<page;i++)
		{
			startPosX+=960;
			CCSprite* page=createAPage(ccp(startPosX,320));
			m_MoveToTargetPageArray->addObject(page);
		}
		m_MoveTouchLeft=true;
		this->runAction(CCSequence::create(CCMoveBy::create(1.0f,ccp(-960.0*page,1)),CCCallFunc::create(this,callfunc_selector(PVEMapLayer::moveToTargetPageOver)),NULL));
	}

}

void PVEMapLayer::OnBtnEnterLevel( cocos2d::CCObject* sender )
{
	PVELayer* parentLayer=(PVELayer*)getParent();
	if (parentLayer)
	{
		parentLayer->m_UILayer->setKeypadEnabled(false);
	}
	SEND_EVENT(this,PVEEvent::PVEVIEW_OPENLEVEL,NULL);
	//this->setKeypadEnabled(false);
}


//////////////////////////////////////////////////////////////////////////
//PVELevelLayer
PVELevelLayer::PVELevelLayer():m_Priority(0),m_PVEFightType(PVEFightType_NULL)
{
	m_LbRecommendLevel=NULL;
	m_LbExpendStrength=NULL;
	m_LbLimitTimes=NULL;
	m_LbPlaceName=NULL;
	m_LbExperience=NULL;
	m_LbGold=NULL;
	m_LbMoney=NULL;
	for (int i=0;i<6;i++)
		m_SpReward[i]=NULL;
}

PVELevelLayer::~PVELevelLayer()
{

}

PVELevelLayer* PVELevelLayer::create(int r,PVEFightType _fightType)
{
	PVELevelLayer* pRet=new PVELevelLayer();
	pRet->m_Priority=r;
	pRet->m_PVEFightType=_fightType;
	if (pRet&&pRet->init())
	{
		pRet->autorelease();
		pRet->initLayer();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return NULL;
}

void PVELevelLayer::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,m_Priority,true);
}

bool PVELevelLayer::ccTouchBegan( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent )
{
	return true;
}

void PVELevelLayer::onEnter()
{
	CCLayer::onEnter();
	this->setKeypadEnabled(true);
}

void PVELevelLayer::keyBackClicked()
{
	PVELayer* parentLayer=(PVELayer*)getParent();
	if (parentLayer)
	{
		parentLayer->m_UILayer->setKeypadEnabled(true);
	}
	this->removeFromParentAndCleanup(true);
}

void PVELevelLayer::keyMenuClicked()
{

}

void PVELevelLayer::initLayer()
{
	CCSprite* background=CCSprite::create(ATHLETIC_BACKGROUND);
	this->addChild(background);
	background->setPosition(ccp(480,320));

	//关卡信息标签背景
	CCSprite* spLevelInfoBackground=ToolsFun::createSpriteWithRepeatTexture(REPEATTEXTURE_1,CCSizeMake(822,248));
	this->addChild(spLevelInfoBackground);
	spLevelInfoBackground->setPosition(ccp(420,505));

	CCLabelTTF* lbReLevel=ToolsFun::createLabel(LanguageManager::shareManager()->getContentByKey("RECOMMEND_LEVEL").c_str(),DEF_FONT_NAME,30,ccp(100,600),this);
	CCLabelTTF* lbExpendStrength=ToolsFun::createLabel(LanguageManager::shareManager()->getContentByKey("COMSUME_STRENGTH").c_str(),DEF_FONT_NAME,30,ccp(100,540),this);
	CCLabelTTF* lbLimitTimes=ToolsFun::createLabel(LanguageManager::shareManager()->getContentByKey("LIMIT_TIMES").c_str(),DEF_FONT_NAME,30,ccp(100,420),this);
	m_LbRecommendLevel=ToolsFun::createLabel("test",DEF_FONT_NAME,30,ccp(180,600),this);
	m_LbExpendStrength=ToolsFun::createLabel("test",DEF_FONT_NAME,30,ccp(180,540),this);
	m_LbLimitTimes=ToolsFun::createLabel("test",DEF_FONT_NAME,30,ccp(180,420),this);
	m_LbRecommendLevel->setAnchorPoint(ccp(0.0f,0.5f));
	m_LbExpendStrength->setAnchorPoint(ccp(0.0f,0.5f));
	m_LbLimitTimes->setAnchorPoint(ccp(0.0f,0.5f));

	//CCLabelTTF* lbPlaceName=ToolsFun::createLabel(LanguageManager::shareManager()->getContentByKey("PLACE_NAME").c_str(),DEF_FONT_NAME,30,ccp(600,600),this);
	GameRoom_MapInfoNode* mapNode=GameRoom_MapInfoNode::create();
	this->addChild(mapNode);
	mapNode->setPosition(ccp(660,500));

	CCSprite* spLevelBackground=ToolsFun::createSpriteWithRepeatTexture(REPEATTEXTURE_1,CCSizeMake(934,364));
	this->addChild(spLevelBackground);
	spLevelBackground->setPosition(ccp(476,190));

	CCLabelTTF* lbReward=ToolsFun::createLabel(LanguageManager::shareManager()->getContentByKey("REWARDS").c_str(),DEF_FONT_NAME,30,ccp(90,330),this);
	CCLabelTTF* lbExperience=ToolsFun::createLabel(LanguageManager::shareManager()->getContentByKey("EXPERIENCE").c_str(),DEF_FONT_NAME,30,ccp(130,250),this);
	CCLabelTTF* lbGold=ToolsFun::createLabel(LanguageManager::shareManager()->getContentByKey("GOLD").c_str(),DEF_FONT_NAME,30,ccp(390,250),this);
	CCLabelTTF* lbMoney=ToolsFun::createLabel(LanguageManager::shareManager()->getContentByKey("MONEY").c_str(),DEF_FONT_NAME,30,ccp(130,200),this);
	m_LbExperience=ToolsFun::createLabel("999999",DEF_FONT_NAME,30,ccp(190,250),this);
	m_LbGold=ToolsFun::createLabel("999999",DEF_FONT_NAME,30,ccp(440,250),this);
	m_LbMoney=ToolsFun::createLabel("100/100",DEF_FONT_NAME,30,ccp(180,200),this);
	m_LbExperience->setAnchorPoint(ccp(0.0f,0.5f));
	m_LbGold->setAnchorPoint(ccp(0.0f,0.5f));
	m_LbMoney->setAnchorPoint(ccp(0.0f,0.5f));

	//奖品
	CCPoint startPoint=ccp(70,70);
	int index=0;
	for (int i=0;i<6;i++)
	{
		m_SpReward[i]=CCSprite::create(PVE_FIELD_PIC_GROOVE);
		this->addChild(m_SpReward[i]);
		m_SpReward[i]->setPosition(ccpAdd(startPoint,ccp(120*index++,0)));
	}
	createLevelMenu();

	this->setTouchEnabled(true);
}

void PVELevelLayer::createLevelMenu()
{
	CCMenuP* menu=CCMenuP::create(m_Priority,NULL);
	this->addChild(menu);
	menu->setPosition(CCPointZero);

	CCMenuItemSprite* btnGoback=ToolsFun::createBTN(LanguageManager::shareManager()->getContentByKey("GOBACK").c_str(),ButtomType_Red,this,menu_selector(PVELevelLayer::OnBtnGoBack));
	menu->addChild(btnGoback);
	btnGoback->setPosition(ccp(900,600));

	if (m_PVEFightType==PVEFightType_MONSTER)
	{
		CCMenuItemSprite* btnObserve=ToolsFun::createBTN(LanguageManager::shareManager()->getContentByKey("OBSERVE_FIGHT").c_str(),ButtomType_Blue2,this,menu_selector(PVELevelLayer::OnBtnObserve));
		CCMenuItemSprite* btnFight=ToolsFun::createBTN(LanguageManager::shareManager()->getContentByKey("FIGHTING").c_str(),ButtomType_Blue2,this,menu_selector(PVELevelLayer::OnBtnFight));
		menu->addChild(btnObserve);
		menu->addChild(btnFight);
		btnObserve->setPosition(ccp(850,290));
		btnFight->setPosition(ccp(850,150));
	}
	else if (m_PVEFightType==PVEFightType_BOSS)
	{
		CCMenuItemSprite* btnFindTeam=ToolsFun::createBTN(LanguageManager::shareManager()->getContentByKey("SEARCH_TEAM").c_str(),ButtomType_Blue2,this,menu_selector(PVELevelLayer::OnBtnFindTeam));
		CCMenuItemSprite* btnCreateTeam=ToolsFun::createBTN(LanguageManager::shareManager()->getContentByKey("CREATE_TEAM").c_str(),ButtomType_Blue2,this,menu_selector(PVELevelLayer::OnBtnCreateTeam));
		CCMenuItemSprite* btnFight=ToolsFun::createBTN(LanguageManager::shareManager()->getContentByKey("FAST_JOIN").c_str(),ButtomType_Blue2,this,menu_selector(PVELevelLayer::OnBtnFight));
		menu->addChild(btnFindTeam);
		menu->addChild(btnCreateTeam);
		menu->addChild(btnFight);
		btnFindTeam->setPosition(ccp(850,310));
		btnCreateTeam->setPosition(ccp(850,170));
		btnFight->setPosition(ccp(850,70));
	}
}

void PVELevelLayer::OnBtnGoBack( cocos2d::CCObject* sender )
{
	PVELayer* parentLayer=(PVELayer*)getParent();
	if (parentLayer)
	{
		parentLayer->m_UILayer->setKeypadEnabled(true);
	}
	this->removeFromParentAndCleanup(true);
}

void PVELevelLayer::OnBtnObserve( cocos2d::CCObject* sender )
{

}

void PVELevelLayer::OnBtnFight( cocos2d::CCObject* sender )
{
// 	PVEFightResultLayer* resultLayer=PVEFightResultLayer::create(m_Priority-20);
// 	this->addChild(resultLayer);

	SEND_EVENT(this,FightEvent::FIGHTVIEW_OPEN,NULL);
	this->setKeypadEnabled(false);
	//player1
	EventParam* ep1=new EventParam();
	ep1->intParam=1;
	ep1->autorelease();
	SEND_EVENT(this,FightEvent::FIGHTVIEW_ADDPLAYER,ep1);

	//player2
	EventParam* ep2=new EventParam();
	ep2->intParam=2;
	ep2->autorelease();
	SEND_EVENT(this,FightEvent::FIGHTVIEW_ADDPLAYER,ep2);

	//游戏开始
	SEND_EVENT(this,FightEvent::FIGHTVIEW_GAMESTART,NULL);
}

void PVELevelLayer::OnBtnFindTeam( cocos2d::CCObject* sender )
{
	FindTeamLayer* findTeamLayer=FindTeamLayer::create(m_Priority-20);
	this->addChild(findTeamLayer);
	this->setKeypadEnabled(false);
}

void PVELevelLayer::OnBtnCreateTeam( cocos2d::CCObject* sender )
{
	CreateTeamLayer* teamLayer=CreateTeamLayer::create(m_Priority-20);
	this->addChild(teamLayer);
	this->setKeypadEnabled(false);
}

//////////////////////////////////////////////////////////////////////////
//PVEGameRoomLayer

PVEGameRoomLayer::PVEGameRoomLayer():m_Priority(0)
{
	m_LbRoomName=NULL;
	m_SpMap=NULL;
}

PVEGameRoomLayer::~PVEGameRoomLayer()
{

}

PVEGameRoomLayer* PVEGameRoomLayer::create( int r )
{
	PVEGameRoomLayer* pRet=new PVEGameRoomLayer();
	pRet->m_Priority=r;
	if (pRet&&pRet->init())
	{
		pRet->autorelease();
		pRet->initLayer();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return NULL;
}

void PVEGameRoomLayer::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,m_Priority,true);
}

bool PVEGameRoomLayer::ccTouchBegan( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent )
{
	return true;
}

void PVEGameRoomLayer::onEnter()
{
	CCLayer::onEnter();
	this->setKeypadEnabled(true);
}

void PVEGameRoomLayer::keyBackClicked()
{
	SEND_EVENT(this,PVEEvent::PVEVIEW_SETLEVELKEYPADTRUE,NULL);
	this->removeFromParentAndCleanup(true);
}

void PVEGameRoomLayer::keyMenuClicked()
{

}

void PVEGameRoomLayer::initLayer()
{
	CCSprite* background=CCSprite::create(ATHLETIC_BACKGROUND);
	this->addChild(background);
	background->setPosition(ccp(480,320));

	//玩家背景
	CCSprite* playerBackground=ToolsFun::createSpriteWithRepeatTexture(ATHLETIC_TEXTURE_2,CCSizeMake(445,640));
	this->addChild(playerBackground);
	playerBackground->setPosition(ccp(227,320));
	
	//4个玩家
// 	CCSprite* player1=CCSprite::create(PVE_FIELD_BUTTON_SEAT_1);
// 	this->addChild(player1);player1->setPosition(ccp(120,160));
// 	CCSprite* player2=CCSprite::create(PVE_FIELD_BUTTON_SEAT_1);
// 	this->addChild(player2);player2->setPosition(ccp(340,160));
// 	CCSprite* player3=CCSprite::create(PVE_FIELD_BUTTON_SEAT_1);
// 	this->addChild(player3);player3->setPosition(ccp(120,480));
// 	CCSprite* player4=CCSprite::create(PVE_FIELD_BUTTON_SEAT_1);
// 	this->addChild(player4);player4->setPosition(ccp(340,480));
	GameRoom_PlayerNode* player1=GameRoom_PlayerNode::create();
	this->addChild(player1);player1->setPosition(ccp(120,160));
	player1->setNodeType(GameRoom_PlayerNodeType_Master);
	GameRoom_PlayerNode* player2=GameRoom_PlayerNode::create();
	this->addChild(player2);player2->setPosition(ccp(340,160));
	player2->setNodeType(GameRoom_PlayerNodeType_CommonPlayer);
	GameRoom_PlayerNode* player3=GameRoom_PlayerNode::create();
	this->addChild(player3);player3->setPosition(ccp(120,480));
	player3->setNodeType(GameRoom_PlayerNodeType_CommonPlayer);
	GameRoom_PlayerNode* player4=GameRoom_PlayerNode::create();
	this->addChild(player4);player4->setPosition(ccp(340,480));
	player4->setNodeType(GameRoom_PlayerNodeType_CommonPlayer);
	
	m_LbRoomName=CCLabelTTF::create("XXXXXXX",DEF_FONT_NAME,30);
	this->addChild(m_LbRoomName);
	m_LbRoomName->setAnchorPoint(ccp(0.0f,0.5f));
	m_LbRoomName->setPosition(ccp(475,588));

	m_SpMap=CCSprite::create(ATHLETIC_ROOM_MAP);
	this->addChild(m_SpMap);
	m_SpMap->setPosition(ccp(726,320));

	createGameRoomMenu();
	this->setTouchEnabled(true);
}

void PVEGameRoomLayer::createGameRoomMenu()
{
	CCMenuP* menu=CCMenuP::create(m_Priority-1,NULL);
	this->addChild(menu);
	menu->setPosition(CCPointZero);

	CCMenuItemSprite* btnGoback=ToolsFun::createBTN(LanguageManager::shareManager()->getContentByKey("GOBACK").c_str(),ButtomType_Red,this,menu_selector(PVEGameRoomLayer::OnBtnGoBack));
	btnGoback->setPosition(ccp(895,600));
	menu->addChild(btnGoback);

	CCMenuItemSprite* btnInvite=ToolsFun::createBTN(LanguageManager::shareManager()->getContentByKey("INVITE_PLAYER").c_str(),ButtomType_Blue2,this,menu_selector(PVEGameRoomLayer::OnBtnInvite));
	btnInvite->setPosition(ccp(590,85));
	menu->addChild(btnInvite);

	CCMenuItemSprite* btnStartGame=ToolsFun::createBTN(LanguageManager::shareManager()->getContentByKey("START_GAME").c_str(),ButtomType_Blue2,this,menu_selector(PVEGameRoomLayer::OnBtnStartGame));
	btnStartGame->setPosition(ccp(845,85));
	menu->addChild(btnStartGame);
}

void PVEGameRoomLayer::OnBtnGoBack( cocos2d::CCObject* sender )
{
	SEND_EVENT(this,PVEEvent::PVEVIEW_SETLEVELKEYPADTRUE,NULL);
	this->removeFromParentAndCleanup(true);
}

void PVEGameRoomLayer::OnBtnInvite( cocos2d::CCObject* sender )
{

}

void PVEGameRoomLayer::OnBtnStartGame( cocos2d::CCObject* sender )
{
	PVEFlopLayer* flopLayer=PVEFlopLayer::create(m_Priority-10);
	this->addChild(flopLayer);
}

void PVEGameRoomLayer::OnBtnSetReady( cocos2d::CCObject* sender )
{

}

//////////////////////////////////////////////////////////////////////////
//PVEFlopLayer

PVEFlopLayer::PVEFlopLayer():m_Priority(0),m_LbFreeFlop(NULL),m_LbGoldFlop(NULL)
{

}

PVEFlopLayer::~PVEFlopLayer()
{

}

bool PVEFlopLayer::init()
{
	bool bRet=false;
	do 
	{
		initLayer();
		bRet=true;
	} while (0);
	return bRet;
}

PVEFlopLayer* PVEFlopLayer::create( int r )
{
	PVEFlopLayer* pRet=new PVEFlopLayer();
	pRet->m_Priority=r;
	if (pRet&&pRet->init())
	{
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return NULL;
}

void PVEFlopLayer::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,m_Priority,true);
}

bool PVEFlopLayer::ccTouchBegan( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent )
{
	return true;
}

void PVEFlopLayer::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{

}

void PVEFlopLayer::initLayer()
{
	CCSprite* background=CCSprite::create(ATHLETIC_BACKGROUND);
	this->addChild(background);
	background->setPosition(ccp(480,320));

	CCLabelTTF* lbTitle=CCLabelTTF::create(LanguageManager::shareManager()->getContentByKey("PVE_FIGHT_FLOP").c_str(),DEF_FONT_NAME,32);
	this->addChild(lbTitle);
	lbTitle->setPosition(ccp(480,605));

	CCLabelTTF* lbFreeFlop=CCLabelTTF::create(LanguageManager::shareManager()->getContentByKey("FLOP_FREE").c_str(),DEF_FONT_NAME,28);
	this->addChild(lbFreeFlop);
	lbFreeFlop->setPosition(ccp(100,605));
	CCLabelTTF* lbGoldFlop=CCLabelTTF::create(LanguageManager::shareManager()->getContentByKey("FLOP_GOLD").c_str(),DEF_FONT_NAME,28);
	this->addChild(lbGoldFlop);
	lbGoldFlop->setPosition(ccp(360,605));

	m_LbFreeFlop=CCLabelTTF::create("123",DEF_FONT_NAME,28);
	this->addChild(m_LbFreeFlop);
	m_LbFreeFlop->setAnchorPoint(ccp(0.0f,0.5f));
	m_LbFreeFlop->setPosition(ccp(185,605));
	m_LbGoldFlop=CCLabelTTF::create("123",DEF_FONT_NAME,28);
	this->addChild(m_LbGoldFlop);
	m_LbGoldFlop->setAnchorPoint(ccp(0.0f,0.5f));
	m_LbGoldFlop->setPosition(ccp(437,605));

	createCard();
	createFlopMenu();
	this->setTouchEnabled(true);
}

void PVEFlopLayer::createCard()
{
	CCSprite* spCards[12];
	float xStep=150.0;
	float yStep=185.0;
	float startX=110.0;
	float startY=410.0;
	for (int i=0;i<12;i++)
	{
		spCards[i]=CCSprite::create(PVE_FIELD_CARD_FRONT);
		this->addChild(spCards[i]);
		int line=i/6;
		int xSpace=i%6;
		spCards[i]->setPosition(ccp(startX+xSpace*150,startY-line*185));
	}
}

void PVEFlopLayer::createFlopMenu()
{
	CCMenuP* menu=CCMenuP::create(m_Priority-1,NULL);
	this->addChild(menu);
	menu->setPosition(CCPointZero);

	CCMenuItemSprite* btnOK=ToolsFun::createBTN(LanguageManager::shareManager()->getContentByKey("BUTTON_OK").c_str(),ButtomType_Blue2,this,menu_selector(PVEFlopLayer::OnBtnOK));
	menu->addChild(btnOK);
	btnOK->setPosition(ccp(480,65));
}

void PVEFlopLayer::OnBtnOK( cocos2d::CCObject* sender )
{
	this->removeFromParentAndCleanup(true);
}
