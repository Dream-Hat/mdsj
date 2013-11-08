#include "FightNode.h"
USING_NS_CC;

FightElementNode::FightElementNode()
{
	m_MainSprite=NULL;
	m_SpHpEmpty=NULL;
	m_SpHp=NULL;
	m_SpLevel=NULL;
	m_LbALvNum=NULL;
	m_LbName=NULL;
	m_SpTurn=NULL;
	m_Atker=NULL;
	m_IsBullet=false;
	m_IsVisualBullet=false;
	m_TurnId=0;
	m_Isinited=false;
	m_FrontLeft=true;
}

FightElementNode::~FightElementNode()
{

}

bool FightElementNode::init()
{
	bool bRet=false;
	do 
	{
		bRet=true;
	} while (0);
	return bRet;
}

FightElementNode* FightElementNode::create(bool isBullet)
{
	FightElementNode* pRet=new FightElementNode();
	pRet->m_IsBullet=isBullet;
	if (pRet&&pRet->init())
	{
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return NULL;
}

void FightElementNode::initWithNode( FightElementDataNode& _node ,int _turnId)
{
	m_data=_node;
	if (!m_IsBullet)
	{
		m_MainSprite=CCSprite::create(FIGHT_PIC_PLAYER_1);
		this->addChild(m_MainSprite);
		this->setContentSize(m_MainSprite->getContentSize());
		//this->setAnchorPoint(ccp(0.5f,-0.5f));
	}
	else
	{
		m_MainSprite=CCSprite::create(FIGHT_PIC_BULLET);
		this->addChild(m_MainSprite);
		this->setContentSize(m_MainSprite->getContentSize());
		return;
	}

	m_SpHpEmpty=CCSprite::create(FIGHT_PIC_PLAYERMHP);
	this->addChild(m_SpHpEmpty);

	m_SpHp=CCSprite::create(FIGHT_PIC_PLAYERHP_BLUE);
	this->addChild(m_SpHp);

	m_SpLevel=CCSprite::create(FIGHT_PIC_PLAYERLV_0);
	this->addChild(m_SpLevel);

	m_LbALvNum=CCLabelAtlas::create("11",FIGHT_PIC_PLAYERLEVELNUM,22,28,'0');
	this->addChild(m_LbALvNum);

	m_LbName=CCLabelTTF::create("name",DEF_FONT_NAME,20);
	this->addChild(m_LbName);

	m_SpTurn=CCSprite::create(FIGHT_LABEL_ACTOR);
	this->addChild(m_SpTurn);
	m_SpTurn->setVisible(false);
	m_TurnId=_turnId;
	m_Isinited=true;
	
	setNodeElementPosition();
	setElementDataDisplay();

}

void FightElementNode::initBullet()
{
	m_MainSprite=CCSprite::create(FIGHT_PIC_BULLET);
	this->addChild(m_MainSprite);
	this->setContentSize(m_MainSprite->getContentSize());
}

void FightElementNode::setNodeElementPosition()
{
	if (!m_TurnId&&m_IsBullet)return;
	CCSize size=m_MainSprite->getContentSize();

	CCSize hpSize=m_SpHpEmpty->getContentSize();
	m_SpHpEmpty->setPosition(ccp(0,size.height/2+5+hpSize.height/2));

	m_SpHp->setAnchorPoint(ccp(0.0f,0.5f));
	m_SpHp->setPosition(ccp(-hpSize.width/2,m_SpHpEmpty->getPosition().y));
	
	m_SpLevel->setPosition(ccp(-size.width/2,m_SpLevel->getContentSize().height/2.0+3+m_SpHpEmpty->getPosition().y));
	m_LbALvNum->setPosition(m_SpLevel->getPosition());

	m_LbName->setAnchorPoint(ccp(0.0f,0.5f));
	m_LbName->setPosition(ccp(m_SpLevel->getPosition().x+m_SpLevel->getContentSize().width/2+10,m_SpLevel->getPosition().y));

	m_SpTurn->setAnchorPoint(ccp(0.5f,0.0f));
	m_SpTurn->setPosition(ccp(0,m_LbName->getPosition().y+10));
}

void FightElementNode::setElementDataDisplay()
{
	if (m_LbName)
		m_LbName->setString(m_data._name.c_str());


}

cocos2d::CCRect FightElementNode::getMainFrameRect()
{
	if (m_MainSprite==NULL)return CCRectZero;
	CCRect oldBoundingBox=m_MainSprite->boundingBox();
	float scaleX=abs(m_MainSprite->getScaleX());
	float scaleY=abs(m_MainSprite->getScaleY());
	CCPoint oldOrigin=oldBoundingBox.origin;
	CCPoint newOrigin=CCPointMake(oldOrigin.x*scaleX,oldOrigin.y*scaleY);
	CCSize newSize=m_MainSprite->getContentSize();
	CCRect rect=CCRectMake(newOrigin.x,newOrigin.y,newSize.width,newSize.height);
	return rect;
}

void FightElementNode::setFlipX( bool isFilpX )
{
	if (m_MainSprite&&isFilpX)
	{
// 		float scaleValue=abs(m_MainSprite->getScaleX());
// 		scaleValue=-scaleValue;
// 		m_MainSprite->setScaleX(scaleValue);
		m_MainSprite->setFlipX(isFilpX);
	}
}

void FightElementNode::setFlipY( bool isFilpY )
{
	if (m_MainSprite&&isFilpY)
	{
		float scaleValue=abs(m_MainSprite->getScaleY());
		scaleValue=-scaleValue;
		m_MainSprite->setScaleY(scaleValue);
	}
}

void FightElementNode::setFrontLeft(bool isLeft)
{
	if (!m_FrontLeft)
	{
		if (isLeft)
		{
			m_MainSprite->setFlipX(!m_MainSprite->isFlipX());
			m_FrontLeft=!m_FrontLeft;
		}
	}
	else
	{
		if (!isLeft)
		{
			m_MainSprite->setFlipX(!m_MainSprite->isFlipX());
			m_FrontLeft=!m_FrontLeft;
		}
	}
}

void FightElementNode::setTurnAct(bool isAct)
{
	if (m_SpTurn)
		m_SpTurn->setVisible(isAct);
}

void FightElementNode::changeHp()
{
	//m_data._hp+=_changedHp;
	//
	float hpPercent=(float)m_data._hp/(float)m_data._maxHp;
	CCSize size=m_SpHpEmpty->getContentSize();
	m_SpHp->setTextureRect(CCRectMake(0,0,size.width*hpPercent,size.height));
}


//////////////////////////////////////////////////////////////////////////
//FightTipNode

FightTipNode::FightTipNode():m_SpType(0),m_LbValue(0),m_Type(FightTipType_NULL),m_Value(0)
{

}

FightTipNode::~FightTipNode()
{

}

bool FightTipNode::init()
{
	bool bRet=false;
	do 
	{
		initNode();
		bRet=true;
	} while (0);
	return bRet;
}

FightTipNode* FightTipNode::create( FightTipType _type,int _valueNum )
{
	FightTipNode* pRet=new FightTipNode();
	pRet->m_Type=_type;
	pRet->m_Value=_valueNum;
	if (pRet&&pRet->init())
	{
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return NULL;
}

void FightTipNode::initNode()
{
	char* typePath=NULL;
	char* valuePath=NULL;
	if (m_Type==FightTipType_ATK_Up)
	{
		typePath=FIGHT_LABEL_ABILITYUP_ATTACK;
		valuePath=FIGHT_LABEL_ABILITYUP_BUMBER;
	}
	else if (m_Type==FightTipType_ATK_Down)
	{
		typePath=FIGHT_LABEL_ABILITYDOWN_ATTACK;
		valuePath=FIGHT_LABEL_ABILITYDOWN_NUMBER;
	}
	else if (m_Type==FightTipType_Def_Up)
	{
		typePath=FIGHT_LABEL_ABILITYUP_DEFENCE;
		valuePath=FIGHT_LABEL_ABILITYUP_BUMBER;
	}
	else if (m_Type==FightTipType_Def_Down)
	{
		typePath=FIGHT_LABEL_ABILITYDOWN_DEFENCE;
		valuePath=FIGHT_LABEL_ABILITYDOWN_NUMBER;
	}
	else if (m_Type==FightTipType_Hp_Up)
	{
		typePath=FIGHT_LABEL_ABILITYIUP_HP;
		valuePath=FIGHT_LABEL_ABILITYUP_BUMBER;
	}
	else if (m_Type==FightTipType_Hp_Down)
	{
		typePath=FIGHT_LABEL_ABILITYDOWN_HP;
		valuePath=FIGHT_LABEL_ABILITYDOWN_NUMBER;
	}
	else if (m_Type==FightTipType_Dodge)
	{
		typePath=FIGHT_LABEL_NAME_DODGE;
	}
	else if (m_Type==FightTipType_Knock)
	{
		typePath=FIGHT_LABEL_NAME_KNOCK;
	}
	else if (m_Type==FightTipType_Parry)
	{
		typePath=FIGHT_LABEL_NAME_PARRY;
	}

	if (typePath)
	{
		m_SpType=CCSprite::create(typePath);
		this->addChild(m_SpType);
	}
	if (valuePath)
	{
		CCString* valueStr=CCString::createWithFormat(":%d",m_Value);
		m_LbValue=CCLabelAtlas::create(valueStr->getCString(),valuePath,33,36,'0');
		this->addChild(m_LbValue);
	}

	setElementPos();
}

void FightTipNode::setElementPos()
{
	if (m_SpType&&m_LbValue)
	{
		m_SpType->setAnchorPoint(ccp(1.0f,0.5f));
		m_LbValue->setAnchorPoint(ccp(0.0f,0.5f));
	}
}
