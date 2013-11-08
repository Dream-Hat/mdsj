#include "ScrollViewModel.h"
USING_NS_CC;
using namespace cocos2d::extension;
ScrollViewModel::~ScrollViewModel()
{

}

ScrollViewModel* ScrollViewModel::createP( int r,CCSize size, CCNode* container /*= NULL*/ )
{
	ScrollViewModel* pRet=new ScrollViewModel();
	pRet->mPriority=r;
	pRet->deaccelerateScrolling=false;
	if (pRet&&pRet->initWithViewSize(size, container))
	{
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return NULL;
}

ScrollViewModel* ScrollViewModel::create( int r )
{
	ScrollViewModel* pRet=new ScrollViewModel();
	pRet->mPriority=r;
	pRet->deaccelerateScrolling=false;
	if (pRet&&pRet->init())
	{
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return NULL;
}

void ScrollViewModel::registerWithTouchDispatcher()
{
	CCDirector* pDirector=CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->addTargetedDelegate(this, mPriority, false);
}

bool ScrollViewModel::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	return CCScrollView::ccTouchBegan(pTouch,pEvent);
}

void ScrollViewModel::ccTouchMoved( CCTouch* touch, CCEvent* event )
{
	if (!this->isVisible())
		return;

	if (m_pTouches->containsObject(touch))
	{
		if (m_pTouches->count() == 1 && m_bDragging)
		{
			CCPoint moveDistance, newPoint, maxInset, minInset;
			CCRect  frame;
			float newX, newY;


			CCPoint frameOriginal = this->getParent()->convertToWorldSpace(this->getPosition());
			frame = CCRectMake(frameOriginal.x, frameOriginal.y, m_tViewSize.width, m_tViewSize.height);

			newPoint     = this->convertTouchToNodeSpace((CCTouch*)m_pTouches->objectAtIndex(0));
			moveDistance = ccpSub(newPoint, m_tTouchPoint);
			float moveDistance2 = 0;
			if(m_eDirection==kCCScrollViewDirectionVertical)moveDistance2 = abs(moveDistance.y);
			else if(m_eDirection==kCCScrollViewDirectionHorizontal)moveDistance2 = abs(moveDistance.x);
			if(m_bTouchMoved==true||moveDistance2>3){
				m_bTouchMoved  = true;
				m_tTouchPoint  = newPoint;

				if (frame.containsPoint(this->convertToWorldSpace(newPoint)))
				{
					switch (m_eDirection)
					{
					case kCCScrollViewDirectionVertical:
						moveDistance = ccp(0.0f, moveDistance.y);
						break;
					case kCCScrollViewDirectionHorizontal:
						moveDistance = ccp(moveDistance.x, 0.0f);
						break;
					default:
						break;
					}

					m_pContainer->setPosition(ccpAdd(m_pContainer->getPosition(), moveDistance));

					maxInset = m_fMaxInset;
					minInset = m_fMinInset;


					//check to see if offset lies within the inset bounds
					newX     = MIN(m_pContainer->getPosition().x, maxInset.x);
					newX     = MAX(newX, minInset.x);
					newY     = MIN(m_pContainer->getPosition().y, maxInset.y);
					newY     = MAX(newY, minInset.y);

					m_tScrollDistance     = ccpSub(moveDistance, ccp(newX - m_pContainer->getPosition().x, newY - m_pContainer->getPosition().y));
					this->setContentOffset(ccp(newX, newY));
				}
			}
		}
		else if (m_pTouches->count() == 2 && !m_bDragging)
		{
			const float len = ccpDistance(m_pContainer->convertTouchToNodeSpace((CCTouch*)m_pTouches->objectAtIndex(0)),
				m_pContainer->convertTouchToNodeSpace((CCTouch*)m_pTouches->objectAtIndex(1)));
			this->setZoomScale(this->getZoomScale()*len/m_fTouchLength);
		}
	}

}

void ScrollViewModel::ccTouchEnded( CCTouch* touch, CCEvent* event )
{
	if (!this->isVisible())
	{
		return;
	}
	if (m_pTouches->containsObject(touch))
	{
		if (m_pTouches->count() == 1 && m_bTouchMoved)
		{
			deaccelerateScrolling = true;
			this->schedule(schedule_selector(ScrollViewModel::mydeaccelerateScrolling));
		}
		m_pTouches->removeObject(touch);
	} 

	if (m_pTouches->count() == 0)
	{
		m_bDragging = false;    
		m_bTouchMoved = false;
	}
}

void ScrollViewModel::relocateContainer( bool animated )
{
	CCPoint oldPoint, min, max;
	float newX, newY;

	min = this->minContainerOffset();
	max = this->maxContainerOffset();

	oldPoint = m_pContainer->getPosition();

	newX     = oldPoint.x;
	newY     = oldPoint.y;
	if (m_eDirection == kCCScrollViewDirectionBoth || m_eDirection == kCCScrollViewDirectionHorizontal)
	{
		newX     = MIN(newX, max.x);
		newX     = MAX(newX, min.x);
	}

	if (m_eDirection == kCCScrollViewDirectionBoth || m_eDirection == kCCScrollViewDirectionVertical)
	{
		newY     = MIN(newY, max.y);
		newY     = MAX(newY, min.y);
	}

	if (newY != oldPoint.y || newX != oldPoint.x)
	{
		this->setContentOffset(ccp(newX, newY), animated);
	}
}

void ScrollViewModel::mydeaccelerateScrolling( float dt )
{
	if (m_bDragging)
	{
		this->unschedule(schedule_selector(ScrollViewModel::mydeaccelerateScrolling));
		deaccelerateScrolling = false;
		return;
	}

	float newX, newY;
	CCPoint maxInset, minInset;

	m_pContainer->setPosition(ccpAdd(m_pContainer->getPosition(), m_tScrollDistance));

	if (m_bBounceable)
	{
		maxInset = m_fMaxInset;
		minInset = m_fMinInset;
	}
	else
	{
		maxInset = this->maxContainerOffset();
		minInset = this->minContainerOffset();
	}

	//check to see if offset lies within the inset bounds
	newX     = MIN(m_pContainer->getPosition().x, maxInset.x);
	newX     = MAX(newX, minInset.x);
	newY     = MIN(m_pContainer->getPosition().y, maxInset.y);
	newY     = MAX(newY, minInset.y);

	m_tScrollDistance     = ccpSub(m_tScrollDistance, ccp(newX - m_pContainer->getPosition().x, newY - m_pContainer->getPosition().y));
	m_tScrollDistance     = ccpMult(m_tScrollDistance, SCROLL_DEACCEL_RATE);
	this->setContentOffset(ccp(newX,newY));

	if ((fabsf(m_tScrollDistance.x) <= SCROLL_DEACCEL_DIST &&
		fabsf(m_tScrollDistance.y) <= SCROLL_DEACCEL_DIST) ||
		newX == maxInset.x || newX == minInset.x ||
		newY == maxInset.y || newY == minInset.y)
	{
		this->unschedule(schedule_selector(ScrollViewModel::mydeaccelerateScrolling));
		this->relocateContainer(true);
		deaccelerateScrolling = false;
	}
}
