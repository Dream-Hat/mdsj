#include "CMyMenu.h"

USING_NS_CC;

CCRadioMenuP::CCRadioMenuP()
{

}

CCRadioMenuP::~CCRadioMenuP()
{

}

CCRadioMenuP* CCRadioMenuP::createWithP(int r,bool canSwallow,cocos2d::CCMenuItem* item, ...)
{
	va_list args;
	va_start(args,item);
	CCRadioMenuP* pRet=new CCRadioMenuP();
	pRet->m_Priority=r;
	pRet->m_SwallowsAll=canSwallow;

	CCArray* pArray = NULL;
	if(item)
	{
		pArray = CCArray::create(item, NULL);
		CCMenuItem *i = va_arg(args, CCMenuItem*);
		while(i)
		{
			pArray->addObject(i);
			i = va_arg(args, CCMenuItem*);
		}
	}

	if (pRet&&pRet->initWithArray(pArray))
	{
		pRet->autorelease();
		va_end(args);
		return pRet;
	}

	va_end(args);
	CC_SAFE_DELETE(pRet);
	return NULL;
}

void CCRadioMenuP::setSelectedItem(cocos2d::CCMenuItem* item)
{
	m_pSelectedItem=NULL;
	m_pSelectedItem=item;
}

bool CCRadioMenuP::ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event)
{
	if (m_eState!=kCCMenuStateWaiting)
		return false;
	CCMenuItem* curSelection=this->itemForTouch(touch);//获取当前触摸到的按钮
	if (curSelection)
	{
		//判断点击的按钮是不是已经按下
		if (curSelection==m_pSelectedItem)return false;

		curSelection->selected();
		m_CurHightLighted=curSelection;
		if (m_CurHightLighted)
		{
			if (m_pSelectedItem!=curSelection)
			{
				m_pSelectedItem->unselected();
			}
			m_eState=kCCMenuStateTrackingTouch;
			thisTouchedButtoned=true;
			return true;
		}
	}
	else
	{
		thisTouchedButtoned=false;
		return true;
	}
	return false;
}

void CCRadioMenuP::ccTouchEnded(cocos2d::CCTouch* touch, cocos2d::CCEvent* event)
{
	//CCAssert(m_eState==kCCMenuStateTrackingTouch,"[Menu ccTouchEnded] -- invalid state");
	if (m_eState==kCCMenuStateTrackingTouch&&thisTouchedButtoned)
	{
		CCMenuItem* curSelection=this->itemForTouch(touch);
		if (curSelection!=m_CurHightLighted&&curSelection!=NULL)
		{
			m_pSelectedItem->selected();
			m_CurHightLighted->unselected();
			m_CurHightLighted=NULL;
			m_eState=kCCMenuStateWaiting;
			return;
		}
		m_pSelectedItem=m_CurHightLighted;
		m_CurHightLighted->activate();
		m_CurHightLighted=NULL;

		m_eState=kCCMenuStateWaiting;

		thisTouchedButtoned=false;
	}
}

void CCRadioMenuP::ccTouchCancelled(cocos2d::CCTouch *touch, cocos2d::CCEvent* event)
{
	//CCAssert(m_eState==kCCMenuStateTrackingTouch,"[Menu ccTouchCacelled] -- invalid state");
	if (m_eState==kCCMenuStateTrackingTouch&&thisTouchedButtoned)
	{
		m_pSelectedItem->selected();
		m_CurHightLighted->unselected();
		m_CurHightLighted=NULL;
		m_eState=kCCMenuStateWaiting;
	}
}

void CCRadioMenuP::ccTouchMoved(cocos2d::CCTouch* touch, cocos2d::CCEvent* event)
{
	//CCAssert(m_eState==kCCMenuStateTrackingTouch,"[Menu ccTouchMoved] -- invalid state");
	if (m_eState==kCCMenuStateTrackingTouch&&thisTouchedButtoned)
	{
		CCMenuItem* curSelection=this->itemForTouch(touch);
		if (curSelection!=m_CurHightLighted&&curSelection!=NULL)
		{
			m_CurHightLighted->unselected();
			curSelection->selected();
			m_CurHightLighted=curSelection;
			return;
		}
	}
}

void CCRadioMenuP::registerWithTouchDispatcher()
{
	CCDirector* pDirector=CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->addTargetedDelegate(this,m_Priority,m_SwallowsAll);
}

//////////////////////////////////////////////////////////////////////////
//CCMenuP

CCMenuP* CCMenuP::create(int r,cocos2d::CCMenuItem* item, ...)
{
	va_list args;
	va_start(args,item);
	CCMenuP *pRet = new CCMenuP();
	pRet->_Priority = r;
	pRet->_s = true;
	pRet->_SwallowsAll = false;

	CCArray* pArray = NULL;
	if(item)
	{
		pArray = CCArray::create(item, NULL);
		CCMenuItem *i = va_arg(args, CCMenuItem*);
		while(i)
		{
			pArray->addObject(i);
			i = va_arg(args, CCMenuItem*);
		}
	}

	if (pRet && pRet->initWithArray(pArray))
	{
		pRet->autorelease();
		va_end(args);
		return pRet;
	}
	va_end(args);
	CC_SAFE_DELETE(pRet);
	return NULL;
}

CCMenuP* CCMenuP::createSwallows(int r,cocos2d::CCMenuItem* item, ...)
{
	va_list args;
	va_start(args,item);
	CCMenuP *pRet = new CCMenuP();
	pRet->_Priority = r;
	pRet->_s = true;
	pRet->_SwallowsAll = true;

	CCArray* pArray = NULL;
	if(item)
	{
		pArray = CCArray::create(item, NULL);
		CCMenuItem *i = va_arg(args, CCMenuItem*);
		while(i)
		{
			pArray->addObject(i);
			i = va_arg(args, CCMenuItem*);
		}
	}

	if (pRet && pRet->initWithArray(pArray))
	{
		pRet->autorelease();
		va_end(args);
		return pRet;
	}
	va_end(args);
	CC_SAFE_DELETE(pRet);
	return NULL;
}

void CCMenuP::registerWithTouchDispatcher()
{
	cocos2d::CCDirector* pDirector = cocos2d::CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->addTargetedDelegate(this, _Priority, _s);
}

bool CCMenuP::ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event)
{
	bool b = cocos2d::CCMenu::ccTouchBegan(touch,event);
	thisTouchedObject = b;
	return _SwallowsAll?true:b;
}

void CCMenuP::ccTouchMoved(cocos2d::CCTouch* touch, cocos2d::CCEvent* event)
{
	if(thisTouchedObject)cocos2d::CCMenu::ccTouchMoved(touch,event);
}

void CCMenuP::ccTouchEnded(cocos2d::CCTouch* touch, cocos2d::CCEvent* event)
{
	if(thisTouchedObject)cocos2d::CCMenu::ccTouchEnded(touch,event);
}

void CCMenuP::ccTouchCancelled(cocos2d::CCTouch *touch, cocos2d::CCEvent* event)
{
	if(thisTouchedObject)cocos2d::CCMenu::ccTouchCancelled(touch,event);
}

// #if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
// void CCMenuP::onEnter()
// {
// 	CCMenu::onEnter();
// 	setKeypadEnabled(true);
// }
// 
// void CCMenuP::keyBackClicked()
// {
// 
// }
// 
// void CCMenuP::keyMenuClicked()
// {
// 
// }
// 
// #endif



#define pj_hex_digits   "0123456789abcdef"  
void pj_val_to_hex_digit(unsigned value, char *p) //十进制转成16进制  
{  
	*p++ = pj_hex_digits[ (value & 0xF0) >> 4 ];  
	*p   = pj_hex_digits[ (value & 0x0F) ];  
}  