#include "FightLayer.h"
#include "CMyMenu.h"
#include "ToolsFun.h"
#include "FightNode.h"
#include "FightMediator.h"
#include "LanguageManager.h"
#include "EventMSG.h"
#include "../ZMQ/MessageCenter.h"


#define PTM_WORLD_RATIO 30
#define LOCUSMASKTAGINEFFECTLAYER 10	//特效层上的轨迹遮罩标记号
#define VISVALBULLETWHENTOUCHMOVE	20	//玩家瞄准时用到的虚拟子弹的标记
#define TRUEBULLETINFLY		30	//在飞行过程中的子弹

USING_NS_CC;
FightLayer::FightLayer():m_MainLayer(0),m_EffectLayer(0),m_TipLayer(0),m_IconLayer(0),m_UILayer(0)
{
	m_MaxLayerMoveX=0.0f;
	m_MaxLayerMoveY=0.0f;
	m_MinLayerMoveX=-960.0f;
	m_MinLayerMoveY=-200.0f;
}

FightLayer::~FightLayer()
{

}

FightLayer* FightLayer::create(int r)
{
	FightLayer* pRet=new FightLayer();
	pRet->m_Priority=r;
	if (pRet&&pRet->initWithColor(ccc4(0,0,0,255)))
	{
		pRet->autorelease();
		pRet->initLayer();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return NULL;
}

void FightLayer::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,m_Priority,true);
}

bool FightLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	return true;
}

void FightLayer::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	CCPoint nowPoint=pTouch->getLocationInView();
	nowPoint=CCDirector::sharedDirector()->convertToGL(nowPoint);
 	CCPoint oldPoint=pTouch->getPreviousLocationInView();
	oldPoint=CCDirector::sharedDirector()->convertToGL(oldPoint);
	CCPoint transitionPoint=ccpSub(nowPoint,oldPoint);
	panForTranslation(transitionPoint);
}

void FightLayer::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{

}

void FightLayer::DrawLocusMask(cocos2d::CCPoint point)
{
	CCSprite* mask=(CCSprite*)m_EffectLayer->getChildByTag(LOCUSMASKTAGINEFFECTLAYER);
	if (mask!=NULL)
	{
		if (!mask->isVisible())
			mask->setVisible(true);
		mask->setPosition(point);
	}
	else
	{
		CCSprite* maskCreate=CCSprite::create(FIGHT_PIC_PATHWAY_03);
		m_EffectLayer->addChild(maskCreate);
		maskCreate->setTag(LOCUSMASKTAGINEFFECTLAYER);
		maskCreate->setPosition(point);
	}
}

void FightLayer::HideLocusMask()
{
	CCSprite* mask=(CCSprite*)m_EffectLayer->getChildByTag(LOCUSMASKTAGINEFFECTLAYER);
	if (mask!=NULL)
		mask->setVisible(false);
}

void FightLayer::NotifyMsg(char* _msg)
{
	m_TipLayer->showMsg(_msg);
}

void FightLayer::NotifyMsg(char* _msg,int _value)
{

}

void FightLayer::NotifyElementAct(int _turnID)
{
	m_MainLayer->notifyElementAct(_turnID);
}

void FightLayer::initLayer()
{
	m_MainLayer=FightMainLayer::create(m_Priority-10);
	this->addChild(m_MainLayer);
	m_MainLayer->setPosition(ccp(0,0));

	m_EffectLayer=FightEffectLayer::create();
	this->addChild(m_EffectLayer,FIGHTLAYER_EFFECT);
	m_EffectLayer->setPosition(m_MainLayer->getPosition());

	m_TipLayer=FightTipLayer::create();
	this->addChild(m_TipLayer,FIGHTLAYER_TIPLAYER);
	m_TipLayer->setPosition(m_MainLayer->getPosition());

	m_IconLayer=FightIconLayer::create();
	this->addChild(m_IconLayer,FIGHTLAYER_ICONLAYER);

	m_UILayer=FightUILayer::create(m_Priority-50);
	this->addChild(m_UILayer,FIGHTLAYER_UILAYER);

	m_MapContentSize=m_MainLayer->getLayerContentSize();

	this->setTouchEnabled(true);
}

void FightLayer::panForTranslation(cocos2d::CCPoint transitonPoint)
{
	CCPoint endPoint=ccp(0,0);
	checkLayerMovingBouding(transitonPoint,endPoint);
	m_MainLayer->setPosition(endPoint);
	m_EffectLayer->setPosition(endPoint);
	//m_TipLayer->setPosition(endPoint);
	//m_MainLayer->setPosition(ccpAdd(m_MainLayer->getPosition(),transitonPoint));
	//m_EffectLayer->setPosition(ccpAdd(m_EffectLayer->getPosition(),transitonPoint));
	//m_TipLayer->setPosition(ccpAdd(m_TipLayer->getPosition(),transitonPoint));
}

void FightLayer::setMainLayerPosition(cocos2d::CCPoint endPoint)
{
	//确定边框
	CCPoint lastPos=ccpSub(m_MainLayer->getPosition(),endPoint);
	//lastPos.x=-lastPos.x;
	lastPos.x=lastPos.x>m_MaxLayerMoveX?m_MaxLayerMoveX:lastPos.x;
	lastPos.x=lastPos.x<m_MinLayerMoveX?m_MinLayerMoveX:lastPos.x;
	lastPos.y=lastPos.y>m_MaxLayerMoveX?m_MaxLayerMoveX:lastPos.y;
	lastPos.y=lastPos.y<m_MinLayerMoveY?m_MinLayerMoveY:lastPos.y;

	m_MainLayer->setPosition(lastPos);
	m_EffectLayer->setPosition(lastPos);
	//m_TipLayer->setPosition(lastPos);
}

void FightLayer::setViewToNextPlayer(int nextPlayerID)
{
	//先找到下一个要行动的玩家
	CCPoint nextPlayerPos=m_MainLayer->findTargetPlayerPosInParent(nextPlayerID);
	checkWorldFrameBox(nextPlayerPos);
	m_MainLayer->runAction(CCMoveTo::create(0.5f,nextPlayerPos));
	m_EffectLayer->runAction(CCMoveTo::create(0.5f,nextPlayerPos));
}

void FightLayer::showTip(cocos2d::CCPoint _showPos,FightTipType _type,int _value/* =0 */)
{
	//m_TipLayer->showTip(_showPos,_type,_value);
	m_MainLayer->showTip(_showPos,_type,_value);
}

void FightLayer::changeViewToNextPlayer()
{
	m_UILayer->setNextPlayerView();
}

void FightLayer::checkLayerMovingBouding(cocos2d::CCPoint &endPoint)
{
	//width
	endPoint.x=endPoint.x>m_MaxLayerMoveX?m_MaxLayerMoveX:endPoint.x;
	endPoint.x=endPoint.x<m_MinLayerMoveX?m_MinLayerMoveX:endPoint.x;

	//height
	endPoint.y=endPoint.y>m_MaxLayerMoveX?m_MaxLayerMoveX:endPoint.y;
	endPoint.y=endPoint.y<m_MinLayerMoveY?m_MinLayerMoveY:endPoint.y;
}

void FightLayer::checkLayerMovingBouding(cocos2d::CCPoint transitionPoint,cocos2d::CCPoint &endPont)
{
	CCPoint point=ccpAdd(m_MainLayer->getPosition(),transitionPoint);
	//checkLayerMovingBouding(point);
	endPont.x=point.x>m_MaxLayerMoveX?m_MaxLayerMoveX:point.x;
	endPont.x=endPont.x<m_MinLayerMoveX?m_MinLayerMoveX:endPont.x;
	
	//height
	endPont.y=point.y>m_MaxLayerMoveX?m_MaxLayerMoveX:point.y;
	endPont.y=endPont.y<m_MinLayerMoveY?m_MinLayerMoveY:endPont.y;
}

void FightLayer::checkWorldFrameBox(cocos2d::CCPoint &_point)
{
	_point.x=_point.x>m_MaxLayerMoveX?m_MaxLayerMoveX:_point.x;
	_point.x=_point.x<m_MinLayerMoveX?m_MinLayerMoveX:_point.x;
	_point.y=_point.y>m_MaxLayerMoveX?m_MaxLayerMoveX:_point.y;
	_point.y=_point.y<m_MinLayerMoveY?m_MinLayerMoveY:_point.y;
}

//////////////////////////////////////////////////////////////////////////
//FightMainLayer
FightMainLayer::FightMainLayer()
{
	m_Priority=0;
//	m_TurnIndex=-1;
	m_MinDistance=PTM_WORLD_RATIO;
	m_MaxDistance=70;
	m_CanAtk=false;
	m_b2World=NULL;
	m_WorldBody=NULL;
	m_CopyBullet=NULL;
	debugDraw=NULL;
	m_ContactListener=NULL;
	m_GameStarted=false;
	

	m_FightElementDic=CCArray::createWithCapacity(10);
	m_FightElementDic->retain();
}

FightMainLayer::~FightMainLayer()
{
	m_FightElementDic->release();
	delete m_b2World;
	m_b2World=NULL;
	delete m_ContactListener;
	m_ContactListener=NULL;
	if (debugDraw!=NULL)
		delete debugDraw;
	debugDraw=NULL;
}

bool FightMainLayer::init()
{
	bool bRet=false;
	do 
	{
		initLayer();
		bRet=true;
	} while (0);
	return bRet;
}

FightMainLayer* FightMainLayer::create( int r )
{
	FightMainLayer* pRet=new FightMainLayer();
	pRet->m_Priority=r;
	if (pRet&&pRet->init())
	{
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return NULL;
}

void FightMainLayer::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,m_Priority,true);
}

bool FightMainLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	CCObject* obj=NULL;
	CCARRAY_FOREACH(m_FightElementDic,obj)
	{
		FightElementNode* player=(FightElementNode*)obj;
		CCPoint newPoint=player->convertTouchToNodeSpaceAR(pTouch);
		int playerTurm=player->getElementTurnIndex();
		if (checkTouchInElement(player,newPoint)&&player->getElementTurnIndex()==m_FightMediator->m_TurnIndex)
		{
			m_CurrentSelectElement=player;
			m_CanAtk=true;
			m_FightMediator->m_Layer->DrawLocusMask(m_CurrentSelectElement->getPosition());
			break;
		}
	}
	if (m_CanAtk)
	{
		m_CopyPointList.clear();
		//float width=0.0f;
		if (m_CopyBullet==NULL)
		{
			m_CopyBullet=createCopyBullet(ccp(0,0));
			m_CopyBullet->SetAwake(true);
		}
		//this->unscheduleUpdate();
		this->unschedule(schedule_selector(FightMainLayer::update));
		return true;
	}
	//没有进入攻击瞄准状态，离开触摸方法前，将m_CurrentSelectElement重置为NULL
	m_CurrentSelectElement=NULL;
	return false;
}

void FightMainLayer::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	if (m_CurrentSelectElement!=NULL&&m_CanAtk)
	{
		CCPoint nodePos=m_CurrentSelectElement->getPosition();
		//朝向
		CCPoint nowPoint=this->convertTouchToNodeSpaceAR(pTouch);
		if (nowPoint.x>nodePos.x)
			m_CurrentSelectElement->setFrontLeft(true);
		else
			m_CurrentSelectElement->setFrontLeft(false);

		//计算距离，并给虚拟子弹增加初始速度
		float distanceX=nowPoint.x-nodePos.x;
		float distanceY=nowPoint.y-nodePos.y;
		float angle=atan2(distanceY,distanceX);
		float distance=sqrt(distanceX*distanceX+distanceY*distanceY);
		if (distance>150.0f)distance=150.0f;
		CCLOG("distance=%f",distance);
		m_CopyBullet->SetTransform(b2Vec2(nodePos.x/PTM_WORLD_RATIO,nodePos.y/PTM_WORLD_RATIO),0);
		//给模拟子弹施加1个力;
		m_CopyBullet->SetLinearVelocity(b2Vec2(-distance*cos(angle)/4.0f,-distance*sin(angle)/4.0f));
		m_CopyBullet->SetAwake(true);
		setCopyPosPoint();

	}
}

void FightMainLayer::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	if (m_CopyBullet!=NULL)
	{
		this->removeChildByTag(VISVALBULLETWHENTOUCHMOVE,true);
		m_b2World->DestroyBody(m_CopyBullet);
		m_CopyBullet=NULL;
		//this->scheduleUpdate();
		schedule(schedule_selector(FightMainLayer::update),0.01f);
	}
	if (m_CanAtk)//生成攻击子弹
	{
		CCPoint nowPoint=this->convertTouchToNodeSpaceAR(pTouch);
		//原地产生子弹
		CCPoint nodePos=m_CurrentSelectElement->getPosition();
		{
			float distanceX=nowPoint.x-nodePos.x;
			float distanceY=nowPoint.y-nodePos.y;
			float angle=atan2(distanceY,distanceX);
			float distance=sqrt(distanceX*distanceX+distanceY*distanceY);
			if (distance>150.0f)distance=150.0f;
			b2Body* bulletBody=createBullet(nodePos);
			if (bulletBody)
			{
				FightElementNode* bulletNode=(FightElementNode*)bulletBody->GetUserData();
				if (bulletNode)
				{
					m_LastFrameBulletPos=bulletNode->getPosition();
				}
			}
			//给模拟子弹施加1个力
			bulletBody->SetLinearVelocity(b2Vec2(-distance*cos(angle)/4.0f,-distance*sin(angle)/4.0f));
			this->schedule(schedule_selector(FightMainLayer::bulletTick),0.01f);
			
		}
	}
	m_CurrentSelectElement=NULL;
	m_CopyPointList.clear();
	m_CanAtk=false;
	m_FightMediator->m_Layer->HideLocusMask();
}

void FightMainLayer::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	if (m_CopyBullet!=NULL)
	{
		this->removeChildByTag(VISVALBULLETWHENTOUCHMOVE,true);
		m_b2World->DestroyBody(m_CopyBullet);
		m_CopyBullet=NULL;
		//this->scheduleUpdate();
	}
	if (m_CanAtk)//生成攻击子弹
	{
		CCPoint nowPoint=this->convertTouchToNodeSpaceAR(pTouch);
		//原地产生子弹
		CCPoint nodePos=m_CurrentSelectElement->getPosition();
		float distance=ccpDistance(nowPoint,nodePos);
		if (distance>=m_MinDistance)
		{
			float cosData=(nowPoint.x-nodePos.x)/distance;
			float sinData=(nowPoint.y-nodePos.y)/distance;

			b2Body* bulletBody=createBullet(nodePos);
			//给模拟子弹施加1个力
			bulletBody->ApplyForce(b2Vec2(-15.0f*distance*cosData,-15.0f*distance*sinData),bulletBody->GetWorldCenter());
			bulletBody->SetLinearDamping(0.2f);
		}
	}
	m_CurrentSelectElement=NULL;
	m_CopyPointList.clear();
	m_CanAtk=false;
	m_FightMediator->m_Layer->HideLocusMask();
}

void FightMainLayer::initLayer()
{
	CCSprite* background=CCSprite::create(FIGHT_BGPIC_BACKGROUND);
	//this->addChild(background);
	//background->setAnchorPoint(ccp(0,0));

	CCTMXTiledMap* map=CCTMXTiledMap::create(FIGHT_TILED_MAP_BACKGROUND);
	this->addChild(map);
	map->setPosition(ccp(0,0));

	m_MapSize=map->getContentSize();
	checkMapSize();
	
	createWorld();
	schedule(schedule_selector(FightMainLayer::update),0.01f);
	this->setTouchEnabled(true);
}

void FightMainLayer::checkMapSize()
{
	CCSize winSize=CCDirector::sharedDirector()->getWinSize();
	if (m_MapSize.width<winSize.width)m_MapSize.width=winSize.width;
	if (m_MapSize.height<winSize.height)m_MapSize.height=winSize.height;
	m_LeftDownPoint=ccp(winSize.width-m_MapSize.width,0);
	m_RightTopPoint=ccp(0,m_MapSize.height-winSize.height);
}

void FightMainLayer::createWorld()
{
	//世界重力
	b2Vec2 gravity;
	gravity.Set(0.0f,-10.0f);

	m_b2World=new b2World(gravity);
	m_b2World->SetAllowSleeping(true);
	m_b2World->SetContinuousPhysics(true);

	b2BodyDef worldBodyDef;
	worldBodyDef.position.SetZero();

	m_WorldBody=m_b2World->CreateBody(&worldBodyDef);
	//设置世界的边框
	b2EdgeShape worldBox;
	worldBox.Set(b2Vec2(0,0),b2Vec2(m_MapSize.width/PTM_WORLD_RATIO,0));
	m_WorldBody->CreateFixture(&worldBox,0);
	worldBox.Set(b2Vec2(0,0),b2Vec2(0,m_MapSize.height/PTM_WORLD_RATIO));
	m_WorldBody->CreateFixture(&worldBox,0);
	worldBox.Set(b2Vec2(0,m_MapSize.height/PTM_WORLD_RATIO),b2Vec2(m_MapSize.width/PTM_WORLD_RATIO,m_MapSize.height/PTM_WORLD_RATIO));
	m_WorldBody->CreateFixture(&worldBox,0);
	worldBox.Set(b2Vec2(m_MapSize.width/PTM_WORLD_RATIO,m_MapSize.height/PTM_WORLD_RATIO),b2Vec2(m_MapSize.width/PTM_WORLD_RATIO,0));
	m_WorldBody->CreateFixture(&worldBox,0);

	//地形碰撞结构
	b2BodyDef groundBodyDef;        //定义了静态刚体的位置原点
	groundBodyDef.position.Set(0/PTM_WORLD_RATIO, 10/PTM_WORLD_RATIO); //位置设置为屏幕正中
	b2Body* groundBody = m_b2World->CreateBody(&groundBodyDef); //定义静态刚体模板
	b2PolygonShape m_triangleDef; 
	m_triangleDef.SetAsBox(1920/PTM_WORLD_RATIO,256/PTM_WORLD_RATIO);
// 	m_triangleDef.m_vertexCount = 4;        //边数
// 	m_triangleDef.m_vertices[0].Set(1920/PTM_WORLD_RATIO,0);
// 	m_triangleDef.m_vertices[1].Set(1920/PTM_WORLD_RATIO,484/PTM_WORLD_RATIO);
// 	m_triangleDef.m_vertices[2].Set(0,484/PTM_WORLD_RATIO);
// 	m_triangleDef.m_vertices[3].Set(0,0);     

	b2FixtureDef fixtureDef;  
	fixtureDef.shape = &m_triangleDef;  
	fixtureDef.density = 0.0f;              //定义密度
	fixtureDef.friction = 0.1f;             //摩擦力
	fixtureDef.restitution = 0.2f;          //弹力，恢复原状
	groundBody->CreateFixture(&fixtureDef); 

	//增加碰撞监听器
	m_ContactListener = new CMyContactListener();
	m_b2World->SetContactListener(m_ContactListener);

	debugDraw = new GLESDebugDraw(PTM_WORLD_RATIO); //这里新建一个 debug渲染模块
	m_b2World->SetDebugDraw(debugDraw); //设置
	uint32 flags = 0;
	flags += b2Draw::e_shapeBit ;
	//b2Draw::e_centerOfMassBit; //获取需要显示debugdraw的块
	//b2Draw::e_aabbBit; //AABB块
	//b2Draw::e_centerOfMassBit; 物体质心
	//b2Draw::e_jointBit; //关节
	//b2Draw::e_shapeBit; 形状
	debugDraw->SetFlags(flags); //需要显示那些东西
	draw(); //画出来

}

void FightMainLayer::update(float dt)
{	
	m_b2World->Step(dt,10,10);
	for (b2Body* pBody=m_b2World->GetBodyList();pBody;pBody=pBody->GetNext())
	{
		void* pUserData=pBody->GetUserData();
		if (NULL!=pUserData)
		{
			FightElementNode* element=(FightElementNode*)pUserData;
			b2Vec2 b2v=pBody->GetPosition();
			element->setPosition(ccp(b2v.x*PTM_WORLD_RATIO,b2v.y*PTM_WORLD_RATIO));
		}
	}
	//检查碰撞
	std::vector<b2Body*> toDestoryList;//删除列表
	for (std::vector<CMyContact>::iterator it=m_ContactListener->m_ContactList.begin();it!=m_ContactListener->m_ContactList.end();++it)
	{
		CMyContact contact=(CMyContact)*it;

		b2Body* bodyA=contact.fixtureA->GetBody();
		b2Body* bodyB=contact.fixtureB->GetBody();

		FightElementNode* nodeA=(FightElementNode*)bodyA->GetUserData();
		FightElementNode* nodeB=(FightElementNode*)bodyB->GetUserData();

		if ((nodeA==NULL&&nodeB!=NULL)||(nodeA!=NULL&&nodeB==NULL))
		{//子弹打到墙
			FightElementNode* bulletNode=NULL;
			b2Body* bulletBody=NULL;
			if (nodeA!=NULL)
			{
				if (nodeA->m_IsBullet)
					bulletBody=bodyA;
			}
			else
			{
				if (nodeB->m_IsBullet)
					bulletBody=bodyB;
			}
			if (bulletBody!=NULL)
			{
				if (checkCanPushBackDestoryList(toDestoryList,bulletBody))
				{
					toDestoryList.push_back(bulletBody);
					if (m_GameStarted)
						m_FightMediator->m_Layer->changeViewToNextPlayer();
				}
			}
			
		}
		else
		{
			if (nodeA->m_IsBullet&&&nodeB->m_IsBullet)
			{//子弹打到子弹
				toDestoryList.push_back(bodyA);
				toDestoryList.push_back(bodyB);
				if (m_GameStarted)
					m_FightMediator->m_Layer->changeViewToNextPlayer();
			}
			else
			{//子弹打到物体
				if (nodeA->m_IsBullet&&nodeB!=nodeA->m_Atker)
				{
					toDestoryList.push_back(bodyA);
					//显示B扣血提示
					if (nodeA->m_data._atk>0)
						m_FightMediator->m_Layer->showTip(nodeB->getPosition(),FightTipType_Hp_Down,nodeA->m_data._atk);
					//之后根据B的血量，确定是否要删除B
					nodeB->m_data._hp-=nodeA->m_data._atk;
					nodeB->changeHp();
					checkFightResult(nodeB);
					if (nodeB->m_data._hp<=0)
					{
						if (checkCanPushBackDestoryList(toDestoryList,bodyB))
						{
							toDestoryList.push_back(bodyB);
						}
					}
					if (m_GameStarted)
						m_FightMediator->m_Layer->changeViewToNextPlayer();
				}
				if (nodeB->m_IsBullet&&nodeA!=nodeB->m_Atker)
				{
					toDestoryList.push_back(bodyB);
					//之后根据A的血量，确定是否要删除A
					if (nodeB->m_data._atk>0)
						m_FightMediator->m_Layer->showTip(nodeA->getPosition(),FightTipType_Hp_Down,nodeB->m_data._atk);
					nodeA->m_data._hp-=nodeB->m_data._atk;
					nodeA->changeHp();
					checkFightResult(nodeA);
					if (nodeA->m_data._hp<=0)
					{
						if (checkCanPushBackDestoryList(toDestoryList,bodyA))
						{
							toDestoryList.push_back(bodyA);
						}
					}
					if (m_GameStarted)
						m_FightMediator->m_Layer->changeViewToNextPlayer();
				}
			}
		}
	}
	//从删除列表中删除子弹
	std::vector<b2Body*>::iterator it=toDestoryList.begin();
	bool enterDeleteWhile=false;
	if (it!=toDestoryList.end())
		enterDeleteWhile=true;
	while (it!=toDestoryList.end())
	{
		b2Body* pBody=(b2Body*)*it;
		it++;
		FightElementNode* bulletElement=(FightElementNode*)pBody->GetUserData();
		this->removeChild(bulletElement,true);
		bulletElement=NULL;
		if (pBody!=NULL)
			m_b2World->DestroyBody(pBody);
	}
	if (enterDeleteWhile)
	{
		this->unschedule(schedule_selector(FightMainLayer::bulletTick));
		SEND_EVENT(this,FightEvent::FIGHTVIEW_TURNOVER,NULL);
	}
	toDestoryList.clear();
}

void FightMainLayer::draw()
{
// 	glDisable(GL_TEXTURE_2D);
// 	glDisableClientState(GL_COLOR_ARRAY);
// 	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
// 
// 	m_b2World->DrawDebugData(); //这个一定要写
// 	 
// 	glEnable(GL_TEXTURE_2D);
// 	glEnableClientState(GL_COLOR_ARRAY);
// 	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
}

void FightMainLayer::addPlayer(FightElementDataNode& _node)
{
	FightElementNode* player=FightElementNode::create(false);
	this->addChild(player);
	player->setPosition(_node._startPoint);
	player->initWithNode(_node,_node._teamID);
	m_FightElementDic->addObject(player);

	//创建Player刚体
	b2Body* playerBody=createPlayerBody(player);
	//player->changeHp(-10);
}

void FightMainLayer::notifyElementAct(int _turnID)
{
	//提示通知信息，更改倒计时，改变玩家行动标记
	CCObject* obj;
	CCARRAY_FOREACH(m_FightElementDic,obj)
	{
		FightElementNode* elementNode=(FightElementNode*)obj;
		if (elementNode->getElementTurnIndex()==_turnID)
			elementNode->setTurnAct(true);
		else
			elementNode->setTurnAct(false);
	}
}

CCPoint FightMainLayer::findTargetPlayerPosInParent(int turnIndex)
{
	CCPoint point=ccp(0,0);
	CCObject* obj;
	CCARRAY_FOREACH(m_FightElementDic,obj)
	{
		FightElementNode* fightElementNode=(FightElementNode*)obj;
		if (fightElementNode->getTurnID()==turnIndex)
		{
			point=fightElementNode->getPosition();
			break;
		}
	}
	return point;
}

void FightMainLayer::showTip(cocos2d::CCPoint _showPoint,FightTipType _type,int _value/* =0 */)
{
	FightTipNode* tip=FightTipNode::create(_type,_value);
	this->addChild(tip);
	tip->setPosition(_showPoint);
	tip->setScale(0.1f);

	tip->runAction(CCSequence::create(
		CCScaleTo::create(0.1f,1.0f),
		CCMoveBy::create(0.3f,ccp(0,10)),
		CCHide::create(),
		CCCallFuncN::create(this,callfuncN_selector(FightMainLayer::CallBack_ObjRemoveFromParent)),NULL));


	
}

b2Body* FightMainLayer::createPlayerBody( FightElementNode* _node )
{
 	b2BodyDef elementDef;
	elementDef.type=b2_dynamicBody;
	elementDef.position.Set(_node->getPositionX()/PTM_WORLD_RATIO,_node->getPositionY()/PTM_WORLD_RATIO);
	elementDef.userData=_node;
	b2Body* elementBody=m_b2World->CreateBody(&elementDef);
	b2PolygonShape elementShape;
	CCSize size=_node->m_MainSprite->getContentSize();
	elementShape.SetAsBox(size.width/2/PTM_WORLD_RATIO,size.height/2/PTM_WORLD_RATIO);
	b2FixtureDef elementFixtureDef;
	elementFixtureDef.shape=&elementShape;
	elementFixtureDef.density=1.0f;
	elementFixtureDef.friction=0.0f;
	elementBody->CreateFixture(&elementFixtureDef);
	return elementBody;
}

b2Body* FightMainLayer::createBullet(cocos2d::CCPoint point)
{
	FightElementNode* bulletNode=FightElementNode::create(true);
	bulletNode->initBullet();
	this->addChild(bulletNode);
	bulletNode->setTag(TRUEBULLETINFLY);
	bulletNode->m_Atker=m_CurrentSelectElement;
	bulletNode->setPosition(point);
	bulletNode->m_data=m_CurrentSelectElement->m_data;
	CCSize bulletSize=bulletNode->getContentSize();

	b2BodyDef bulletDef;
	bulletDef.type=b2_dynamicBody;
	bulletDef.position.Set(point.x/PTM_WORLD_RATIO,point.y/PTM_WORLD_RATIO);
	bulletDef.userData=bulletNode;
	b2Body* bulletBody=m_b2World->CreateBody(&bulletDef);
	//b2PolygonShape bulletShape;
	b2CircleShape bulletShape;
	bulletShape.m_radius=30.0f/PTM_WORLD_RATIO;
	//bulletShape.SetAsBox(bulletSize.width/2/PTM_WORLD_RATIO,bulletSize.height/2/PTM_WORLD_RATIO);
	b2FixtureDef bulletFixtureDef;
	bulletFixtureDef.shape=&bulletShape;
	bulletFixtureDef.density=1.0f;
	bulletFixtureDef.friction=0.0f;
	bulletFixtureDef.isSensor=true;
	bulletBody->CreateFixture(&bulletFixtureDef);
	return bulletBody;
}

b2Body* FightMainLayer::createCopyBullet(cocos2d::CCPoint point)
{
	FightElementNode* bulletNode=FightElementNode::create(true);
	bulletNode->initBullet();
	bulletNode->m_Atker=m_CurrentSelectElement;
	bulletNode->m_IsVisualBullet=true;
	this->addChild(bulletNode);
	bulletNode->setTag(VISVALBULLETWHENTOUCHMOVE);

	bulletNode->setPosition(point);
	CCSize bulletSize=bulletNode->getContentSize();
	m_BulletHeight=bulletSize.height;

	b2BodyDef bulletDef;
	bulletDef.type=b2_dynamicBody;
	bulletDef.position.Set(point.x/PTM_WORLD_RATIO,point.y/PTM_WORLD_RATIO);
	bulletDef.userData=bulletNode;
	b2Body* bulletBody=m_b2World->CreateBody(&bulletDef);
	//b2PolygonShape bulletShape;
	b2CircleShape bulletShape;
	bulletShape.m_radius=30.0f/PTM_WORLD_RATIO;
	//bulletShape.SetAsBox(bulletSize.width/2/PTM_WORLD_RATIO,bulletSize.height/2/PTM_WORLD_RATIO);
	b2FixtureDef bulletFixtureDef;
	bulletFixtureDef.shape=&bulletShape;
	bulletFixtureDef.density=1.0f;
	bulletFixtureDef.friction=0.0f;
	bulletFixtureDef.isSensor=true;
	bulletBody->CreateFixture(&bulletFixtureDef);
	return bulletBody;
}

bool FightMainLayer::checkTouchInElement(FightElementNode* _node,cocos2d::CCPoint _point)
{
	if (_node==NULL)return false;
	CCRect rect=_node->getMainFrameRect();
	if (rect.containsPoint(_point))
		return true;
	else return false;
}

void FightMainLayer::setCopyPosPoint()
{
	if (m_CanAtk)
	{
		m_CopyPointList.clear();
		b2Vec2 nowB2v=m_CopyBullet->GetPosition();
		m_CopyPointList.push_back(ccp(nowB2v.x*PTM_WORLD_RATIO,nowB2v.y*PTM_WORLD_RATIO));
		for (int i=0;i<=30;i++)
		{
			m_b2World->Step(1.0f/30.0f,10,10);
			b2Vec2 b2v=m_CopyBullet->GetPosition();
			CCPoint point=ccp(b2v.x*PTM_WORLD_RATIO,b2v.y*PTM_WORLD_RATIO);
			m_CopyPointList.push_back(point);
			//检查碰撞，如果子弹与其他刚体碰撞，退出
			for (std::vector<CMyContact>::iterator it=m_ContactListener->m_ContactList.begin();it!=m_ContactListener->m_ContactList.end();++it)
			{
				CMyContact contact=(CMyContact)*it;
				FightElementNode* nodeA=(FightElementNode*)contact.fixtureA->GetBody()->GetUserData();
				FightElementNode* nodeB=(FightElementNode*)contact.fixtureB->GetBody()->GetUserData();
				if ((nodeA==NULL&&nodeB!=NULL)||(nodeA!=NULL&&nodeB==NULL))
				{//子弹打到墙
					b2Body* bulletBody=NULL;
					FightElementNode* bulletElement=NULL;
					if (nodeA!=NULL)
					{
						if (nodeA->m_IsBullet&&nodeA->m_IsVisualBullet)
							bulletElement=nodeA;
					}
					else
					{
						if (nodeB->m_IsBullet&&nodeB->m_IsVisualBullet)
							bulletElement=nodeB;
					}
					if (bulletElement!=NULL)return;
				}
				else
				{
					if (nodeA->m_IsBullet&&nodeB->m_IsBullet)return;//子弹打到子弹
					else
					{//子弹打到物体
						if (nodeA->m_IsBullet&&nodeA->m_IsVisualBullet&&nodeA->m_Atker!=nodeB)
							return;
						if (nodeB->m_IsBullet&&nodeB->m_IsVisualBullet&&nodeB->m_Atker!=nodeA)
							return;
					}
				}
			}
		}
	}
}

bool FightMainLayer::checkCanPushBackDestoryList(std::vector<b2Body*> _destroyList,b2Body* _body)
{
	bool bRet=false;
	std::vector<b2Body*>::iterator it=find(_destroyList.begin(),_destroyList.end(),_body);
	if (it==_destroyList.end())
		bRet=true;
	else
		bRet=false;
	return bRet;
}

void FightMainLayer::checkFightResult(FightElementNode* _node)
{
	if (_node!=NULL)
	{
		if (_node->m_data._hp<=0)
		{
			_node->removeFromParentAndCleanup(true);
		}
	}
}

void FightMainLayer::bulletTick(float dt)
{
	FightElementNode* bulletNode=(FightElementNode*)this->getChildByTag(TRUEBULLETINFLY);
	if (NULL!=bulletNode)
	{
		CCPoint endPos=ccpSub(bulletNode->getPosition(),m_LastFrameBulletPos);		
		m_LastFrameBulletPos=bulletNode->getPosition();
		m_FightMediator->m_Layer->setMainLayerPosition(endPos);
	}
}

void FightMainLayer::CallBack_ObjRemoveFromParent(cocos2d::CCNode* sender)
{
	FightTipNode* tip=(FightTipNode*)sender;
	if (tip)
	{
		tip->removeFromParentAndCleanup(true);
	}
}

//////////////////////////////////////////////////////////////////////////
//FightUILayer
FightUILayer::FightUILayer():m_Priority(0)
{
	m_BtnSoul[0]=0;
	m_BtnSoul[1]=0;
	m_BtnSoul[2]=0;
	m_BtnSoul[3]=0;
	m_BtnTools[0]=0;
	m_BtnTools[1]=0;
	m_BtnTools[2]=0;
	m_BtnTools[3]=0;
}

FightUILayer::~FightUILayer()
{

}

bool FightUILayer::init()
{
	bool bRet=false;
	do 
	{
		initLayer();
		bRet=true;
	} while (0);
	return bRet;
}

FightUILayer* FightUILayer::create( int r )
{
	FightUILayer* pRet=new FightUILayer();
	pRet->m_Priority=r;
	if (pRet&&pRet->init())
	{
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return NULL;
}

void FightUILayer::onEnter()
{
	CCLayer::onEnter();
	this->setKeypadEnabled(true);
}

void FightUILayer::keyBackClicked()
{
	SEND_EVENT(this,PVEEvent::PVEVIEW_SETLEVELKEYPADTRUE,NULL);
	SEND_EVENT(this,FightEvent::FIGHTVIEW_CLOSE,NULL);
}

void FightUILayer::keyMenuClicked()
{

}

void FightUILayer::setNextPlayerView()
{
	mBtnViewToNextPlayer->activate();
}

void FightUILayer::initLayer()
{
	CCMenuP* menu=CCMenuP::create(m_Priority-1,NULL);
	this->addChild(menu);
	menu->setPosition(CCPointZero);

	CCMenuItemSprite* btnExit=ToolsFun::createSpriteBtn(FIGHT_PIC_BTN_EXIT_1,FIGHT_PIC_BTN_EXIT_2,FIGHT_PIC_BTN_EXIT_1,this,menu_selector(FightUILayer::OnBtnExit));
	menu->addChild(btnExit);
	btnExit->setPosition(ccp(910,605));

	CCMenuItemSprite* btnChat=ToolsFun::createSpriteBtn(FIGHT_PIC_BTN_CHAT,FIGHT_PIC_BTN_CHAT,FIGHT_PIC_BTN_CHAT,this,menu_selector(FightUILayer::OnBtnOpenChat));
	menu->addChild(btnChat);
	btnChat->setPosition(ccp(70,65));

	float xStart=395.0f;
	float yStart=105.0f;
	float xStep=68.0;
	float yStep=68.0;
	float yToolsStart=yStart-yStep;

	for (int i=0;i<4;i++)
	{
		m_BtnSoul[i]=ToolsFun::createSpriteBtn(FIGHT_BGPIC_ITEMSOUL,FIGHT_BGPIC_ITEMSOUL,FIGHT_BGPIC_ITEMSOUL,this,menu_selector(FightUILayer::OnBtnUseSoul));
		menu->addChild(m_BtnSoul[i]);
		m_BtnSoul[i]->setPosition(ccp(xStart+i*xStep,yStart));

		m_BtnTools[i]=ToolsFun::createSpriteBtn(FIGHT_BGPIC_ITEMSOUL,FIGHT_BGPIC_ITEMSOUL,FIGHT_BGPIC_ITEMSOUL,this,menu_selector(FightUILayer::OnBtnUseTools));
		menu->addChild(m_BtnTools[i]);
		m_BtnTools[i]->setPosition(ccp(xStart+i*xStep,yToolsStart));
	}

	//移动界面到下一个玩家
	mBtnViewToNextPlayer=ToolsFun::createSpriteBtn(FIGHT_PIC_BTN_EXIT_1,FIGHT_PIC_BTN_EXIT_2,FIGHT_PIC_BTN_EXIT_1,this,menu_selector(FightUILayer::OnBtnViewToNextPlayer));
	menu->addChild(mBtnViewToNextPlayer);
	mBtnViewToNextPlayer->setVisible(false);
	mBtnViewToNextPlayer->setPosition(ccp(910,100));
}

void FightUILayer::OnBtnExit( cocos2d::CCObject* sender )
{
	SEND_EVENT(this,FightEvent::FIGHTVIEW_CLOSE,NULL);
}

void FightUILayer::OnBtnOpenChat( cocos2d::CCObject* sender )
{

}

void FightUILayer::OnBtnUseSoul( cocos2d::CCObject* sender )
{
	int soulIndex=-1;
	if (m_BtnSoul[0]==sender)
		soulIndex=1;
	else if (m_BtnSoul[1]==sender)
		soulIndex=2;
	else if (m_BtnSoul[2]==sender)
		soulIndex=3;
	else if (m_BtnSoul[3]==sender)
		soulIndex=4;
	if (soulIndex!=-1)
	{
		EventParam* ep=new EventParam();
		ep->autorelease();
		ep->intParam=soulIndex;
		SEND_EVENT(this,FightEvent::FIGHTVIEW_USESOULSKILL,ep);
	}
}

void FightUILayer::OnBtnUseTools(cocos2d::CCObject* sender)
{
	int toolsIndex=-1;
	if (m_BtnTools[0]==sender)
		toolsIndex=1;
	else if (m_BtnTools[1]==sender)
		toolsIndex=2;
	else if (m_BtnTools[2]==sender)
		toolsIndex=3;
	else if (m_BtnTools[3]==sender)
		toolsIndex=4;
	if (toolsIndex!=-1)
	{
		EventParam* ep=new EventParam();
		ep->autorelease();
		ep->intParam=toolsIndex;
		SEND_EVENT(this,FightEvent::FIGHTVIEW_USETOOLS,ep);
	}
}

void FightUILayer::OnBtnViewToNextPlayer(cocos2d::CCObject* sender)
{
	SEND_EVENT(this,FightEvent::FIGHTVIEW_NEXTPLAYER,NULL);
}

//////////////////////////////////////////////////////////////////////////
//FightIconLayer
FightIconLayer::FightIconLayer()
{

}

FightIconLayer::~FightIconLayer()
{

}

bool FightIconLayer::init()
{
	bool bRet=false;
	do 
	{
		initLayer();
		bRet=true;
	} while (0);
	return bRet;
}

void FightIconLayer::initLayer()
{
	CCSprite* spTurnBackground=CCSprite::create(FIGHT_BGPIC_PLAYERORDER);
	this->addChild(spTurnBackground);
	spTurnBackground->setPosition(ccp(145.0f,555.0f));

	CCLabelTTF* lbCurrentPlayer=CCLabelTTF::create(LanguageManager::shareManager()->getContentByKey("FIGHT_CURRENTPLAYER").c_str(),DEF_FONT_NAME,20);
	this->addChild(lbCurrentPlayer);
	lbCurrentPlayer->setPosition(ccp(42.0f,613.0f));

	CCLabelTTF* lbNextPlayer=CCLabelTTF::create(LanguageManager::shareManager()->getContentByKey("FIGHT_NEXTPLAYER").c_str(),DEF_FONT_NAME,20);
	this->addChild(lbNextPlayer);
	lbNextPlayer->setPosition(ccp(42.0f,573.0f));
}

//////////////////////////////////////////////////////////////////////////
//FightEffectLayer
FightEffectLayer::FightEffectLayer()
{

}

FightEffectLayer::~FightEffectLayer()
{

}

bool FightEffectLayer::init()
{
	bool bRet=false;
	do 
	{
		initLayer();
		bRet=true;
	} while (0);
	return bRet;
}

void FightEffectLayer::draw()
{
	ccDrawColor4B(255,0,0,255);
	ccPointSize(2);
	std::vector<CCPoint>::iterator it;
	for (it=mFightMediator->m_Layer->m_MainLayer->m_CopyPointList.begin();it!=mFightMediator->m_Layer->m_MainLayer->m_CopyPointList.end();++it)
	{
		CCPoint point=(CCPoint)*it;
		CCPoint drawPoint=ccp(point.x,point.y);
		ccDrawPoint(drawPoint);
	}

	CHECK_GL_ERROR_DEBUG();

	glLineWidth(2);
	ccDrawColor4B(255,255,255,255);
	
}

void FightEffectLayer::initLayer()
{

}

//////////////////////////////////////////////////////////////////////////
//FightTipLayer

FightTipLayer::FightTipLayer()
{

}

FightTipLayer::~FightTipLayer()
{

}

bool FightTipLayer::init()
{
	bool bRet=false;
	do 
	{
		initLayer();
		bRet=true;
	} while (0);
	return bRet;
}

void FightTipLayer::initLayer()
{

}

void FightTipLayer::showMsgOver(cocos2d::CCObject* obj)
{
	CCLabelTTF* lbMsg=(CCLabelTTF*)obj;
	if (lbMsg!=NULL)
	{
		this->removeChild(lbMsg,true);
	}
}

void FightTipLayer::CallBack_ObjRemoveFromParent(cocos2d::CCNode* sender)
{
	FightTipNode* tip=(FightTipNode*)sender;
	if (tip)
	{
		tip->removeFromParentAndCleanup(true);
	}
}

void FightTipLayer::showMsg( char* msg )
{
	CCLabelTTF* lbMsg=CCLabelTTF::create(msg,DEF_FONT_NAME,40);
	this->addChild(lbMsg);
	lbMsg->setPosition(ccp(480,500));
	lbMsg->setScale(0.1f);

	lbMsg->runAction(CCSequence::create(CCScaleTo::create(0.5f,1.0f),CCMoveTo::create(1.0f,ccp(480,680)),CCCallFuncO::create(this,callfuncO_selector(FightTipLayer::showMsgOver),lbMsg),NULL));
}

void FightTipLayer::showTip( cocos2d::CCPoint _showPoint,FightTipType _type,int _value/*=0*/ )
{
	FightTipNode* tip=FightTipNode::create(_type,_value);
	this->addChild(tip);
	tip->setPosition(_showPoint);
	tip->setScale(0.1f);

	tip->runAction(CCSequence::create(
		CCScaleTo::create(0.1f,1.0f),
		CCMoveBy::create(0.3f,ccp(0,10)),
		CCHide::create(),
		CCCallFuncN::create(this,callfuncN_selector(FightTipLayer::CallBack_ObjRemoveFromParent)),NULL));
}

