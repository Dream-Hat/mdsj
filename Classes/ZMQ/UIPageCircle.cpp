

#include "UIPageCircle.h"

NS_CC_EXT_BEGIN

UIPageCircle::UIPageCircle():
m_nCurPageIdx(0),
m_pages(NULL),
m_touchMoveDir(PAGECIRCLE_TOUCHLEFT),
m_fTouchStartLocation(0.0f),
m_fTouchEndLocation(0.0f),
m_fTouchMoveStartLocation(0.0f),
movePagePoint(CCPointZero),
m_pLeftChild(NULL),
m_pRightChild(NULL),
m_fLeftBoundary(0.0f),
m_fRightBoundary(0.0f),
m_bIsAutoScrolling(false),
m_fAutoScrollDistance(0.0f),
m_fAutoScrollSpeed(0.0f),
m_nAutoScrollDir(0),
m_fChildFocusCancelOffset(5.0f),
m_pEventListener(NULL),
m_pfnEventSelector(NULL),
/*compatible*/
m_pPageTurningListener(NULL),
m_pfnPageTurningSelector(NULL)
    /************/
{
}

UIPageCircle::~UIPageCircle()
{
    m_pages->release();
}

UIPageCircle* UIPageCircle::create()
{
    UIPageCircle* widget = new UIPageCircle();
    if (widget && widget->init())
    {
        widget->autorelease();
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return NULL;
}

bool UIPageCircle::init()
{
    if (Layout::init())
    {
        m_pages = CCArray::create();
        m_pages->retain();
        setClippingEnabled(false);
        setUpdateEnabled(true);
        return true;
    }
    return false;
}

void UIPageCircle::addWidgetToPage(UIWidget *widget, int pageIdx, bool forceCreate)
{
    if (!widget)
    {
        return;
    }
    int pageCount = m_pages->count();
    if (pageIdx < 0 || pageIdx >= pageCount)
    {
        if (forceCreate)
        {
            if (pageIdx > pageCount)
            {
                CCLOG("pageIdx is %d, it will be added as page id [%d]",pageIdx,pageCount);
            }
            Layout* newPage = createPage();
            newPage->addChild(widget);
            addPage(newPage);
        }
    }
    else
    {
        Layout * page = dynamic_cast<Layout*>(m_pages->objectAtIndex(pageIdx));
        if (page)
        {
            page->addChild(widget);
        }
    }
    
}

Layout* UIPageCircle::createPage()
{
    Layout* newPage = Layout::create();
    newPage->setSize(getSize());
    return newPage;
}

void UIPageCircle::addPage(Layout* page)
{
    if (!page)
    {
        return;
    }
    if (page->getWidgetType() != WidgetTypeContainer)
    {
        return;
    }
    if (m_pages->containsObject(page))
    {
        return;
    }
    CCSize pSize = page->getSize();
    CCSize pvSize = getSize();
    if (!pSize.equals(pvSize))
    {
        CCLOG("page size does not match pageCircle size, it will be force sized!");
        page->setSize(pvSize);
    }
    page->setPosition(ccp(getPositionXByIndex(m_pages->count()), 0));
    m_pages->addObject(page);
    addChild(page);
    updateBoundaryPages();
}

void UIPageCircle::insertPage(Layout* page, int idx)
{
    if (idx < 0)
    {
        return;
    }
    if (!page)
    {
        return;
    }
    if (page->getWidgetType() != WidgetTypeContainer)
    {
        return;
    }
    if (m_pages->containsObject(page))
    {
        return;
    }
    
    int pageCount = m_pages->count();
    if (idx >= pageCount)
    {
        addPage(page);
    }
    else
    {
        m_pages->insertObject(page, idx);
        page->setPosition(ccp(getPositionXByIndex(idx), 0));
        addChild(page);
        CCSize pSize = page->getSize();
        CCSize pvSize = getSize();
        if (!pSize.equals(pvSize))
        {
            CCLOG("page size does not match pageCircle size, it will be force sized!");
            page->setSize(pvSize);
        }
        ccArray* arrayPages = m_pages->data;
        int length = arrayPages->num;
        for (int i=(idx+1); i<length; i++) {
            UIWidget* behindPage = dynamic_cast<UIWidget*>(arrayPages->arr[i]);
            CCPoint formerPos = behindPage->getPosition();
            behindPage->setPosition(ccp(formerPos.x+getSize().width, 0));
        }
        updateBoundaryPages();
    }
}

void UIPageCircle::removePage(Layout* page)
{
    if (!page)
    {
        return;
    }
    removeChild(page);
    updateChildrenPosition();
    updateBoundaryPages();
}

void UIPageCircle::removePageAtIndex(int index)
{
    if (index < 0 || index >= (int)(m_pages->count()))
    {
        return;
    }
    Layout* page = dynamic_cast<Layout*>(m_pages->objectAtIndex(index));
    if (page)
    {
        removePage(page);
    }
}

void UIPageCircle::updateBoundaryPages()
{
    if (m_pages->count() <= 0)
    {
        m_pLeftChild = NULL;
        m_pRightChild = NULL;
    }
    m_pLeftChild = dynamic_cast<UIWidget*>(m_pages->objectAtIndex(0));
    m_pRightChild = dynamic_cast<UIWidget*>(m_pages->lastObject());
}

float UIPageCircle::getPositionXByIndex(int idx)
{
    return (getSize().width*(idx-m_nCurPageIdx));
}

bool UIPageCircle::addChild(UIWidget* widget)
{
    return Layout::addChild(widget);
}

bool UIPageCircle::removeChild(UIWidget* widget)
{
    if (m_pages->containsObject(widget))
    {
        m_pages->removeObject(widget);
        return Layout::removeChild(widget);
    }
    return false;
}

void UIPageCircle::onSizeChanged()
{
    Layout::onSizeChanged();
    m_fRightBoundary = getSize().width;
    updateChildrenSize();
    updateChildrenPosition();
}

void UIPageCircle::updateChildrenSize()
{
    if (!m_pages)
    {
        return;
    }
    
    CCSize selfSize = getSize();
    for (unsigned int i=0; i<m_pages->count(); i++)
    {
        Layout* page = dynamic_cast<Layout*>(m_pages->objectAtIndex(i));
        page->setSize(selfSize);
    }
}

void UIPageCircle::updateChildrenPosition()
{
    if (!m_pages)
    {
        return;
    }
    
    int pageCount = m_pages->data->num;
    if (pageCount <= 0)
    {
        m_nCurPageIdx = 0;
        return;
    }
    if (m_nCurPageIdx >= pageCount)
    {
        m_nCurPageIdx = pageCount-1;
    }
    float pageWidth = getSize().width;
    ccArray* arrayPages = m_pages->data;
    for (int i=0; i<pageCount; i++)
    {
        Layout* page = dynamic_cast<Layout*>(arrayPages->arr[i]);
        page->setPosition(ccp((i-m_nCurPageIdx)*pageWidth, 0));
    }
}

void UIPageCircle::removeAllChildren()
{
    m_pages->removeAllObjects();
    Layout::removeAllChildren();
}

void UIPageCircle::scrollToPage(int idx)
{
    if (idx < 0 || idx >= (int)(m_pages->count()))
    {
        return;
    }
    m_nCurPageIdx = idx;
    UIWidget* curPage = dynamic_cast<UIWidget*>(m_pages->objectAtIndex(idx));
    m_fAutoScrollDistance = -(curPage->getPosition().x);
    m_fAutoScrollSpeed = fabs(m_fAutoScrollDistance)/0.2f;
    m_nAutoScrollDir = m_fAutoScrollDistance > 0 ? 1 : 0;
    m_bIsAutoScrolling = true;
}

void UIPageCircle::update(float dt)
{
    if (m_bIsAutoScrolling)
    {
        switch (m_nAutoScrollDir)
        {
            case 0:
            {
                float step = m_fAutoScrollSpeed*dt;
                if (m_fAutoScrollDistance + step >= 0.0f)
                {
                    step = -m_fAutoScrollDistance;
                    m_fAutoScrollDistance = 0.0f;
                    m_bIsAutoScrolling = false;
                    pageTurningEvent();
                }
                else
                {
                    m_fAutoScrollDistance += step;
                }
                scrollPages(-step);
                break;
            }
                break;
            case 1:
            {
                float step = m_fAutoScrollSpeed*dt;
                if (m_fAutoScrollDistance - step <= 0.0f)
                {
                    step = m_fAutoScrollDistance;
                    m_fAutoScrollDistance = 0.0f;
                    m_bIsAutoScrolling = false;
                    pageTurningEvent();
                }
                else
                {
                    m_fAutoScrollDistance -= step;
                }
                scrollPages(step);
                break;
            }
            default:
                break;
        }
    }
}

bool UIPageCircle::onTouchBegan(const CCPoint &touchPoint)
{
    bool pass = Layout::onTouchBegan(touchPoint);
    handlePressLogic(touchPoint);
    return pass;
}

void UIPageCircle::onTouchMoved(const CCPoint &touchPoint)
{
    m_touchMovePos.x = touchPoint.x;
    m_touchMovePos.y = touchPoint.y;
    handleMoveLogic(touchPoint);
    if (m_pWidgetParent)
    {
        m_pWidgetParent->checkChildInfo(1,this,touchPoint);
    }
    moveEvent();
    if (!hitTest(touchPoint))
    {
        setFocused(false);
        onTouchEnded(touchPoint);
    }
}

void UIPageCircle::onTouchEnded(const CCPoint &touchPoint)
{
    Layout::onTouchEnded(touchPoint);
    handleReleaseLogic(touchPoint);
}

void UIPageCircle::movePages(float offset)
{
    ccArray* arrayPages = m_pages->data;
    int length = arrayPages->num;
    for (int i = 0; i < length; i++)
    {
        UIWidget* child = (UIWidget*)(arrayPages->arr[i]);
        movePagePoint.x = child->getPosition().x + offset;
        movePagePoint.y = child->getPosition().y;
        child->setPosition(movePagePoint);
    }
}

bool UIPageCircle::scrollPages(float touchOffset)
{
    if (m_pages->count() <= 0)
    {
        return false;
    }
    
    if (!m_pLeftChild || !m_pRightChild)
    {
        return false;
    }
    
    float realOffset = touchOffset;
    
//     switch (m_touchMoveDir)
//     {
//         case PAGECIRCLE_TOUCHLEFT: // left
// 			{
// 				if (m_pRightChild->getRightInParent() + touchOffset <= m_fRightBoundary)
// 				{
// 					realOffset = m_fRightBoundary - m_pRightChild->getRightInParent();
// 					movePages(realOffset);
// 					return false;
// 				}
// 			}break;
// 		case PAGECIRCLE_TOUCHRIGHT: // right
//             if (m_pLeftChild->getLeftInParent() + touchOffset >= m_fLeftBoundary)
//             {
//                 realOffset = m_fLeftBoundary - m_pLeftChild->getLeftInParent();
//                 movePages(realOffset);
//                 return false;
//             }
//             break;
//         default:
//             break;
//     }
    
    movePages(realOffset);
    return true;
}

void UIPageCircle::onTouchCancelled(const CCPoint &touchPoint)
{
    Layout::onTouchCancelled(touchPoint);
}

void UIPageCircle::handlePressLogic(const CCPoint &touchPoint)
{
    CCPoint nsp = m_pRenderer->convertToNodeSpace(touchPoint);
    m_fTouchMoveStartLocation = nsp.x;
    m_fTouchStartLocation = nsp.x;
}

void UIPageCircle::handleMoveLogic(const CCPoint &touchPoint)
{
    CCPoint nsp = m_pRenderer->convertToNodeSpace(touchPoint);
    float offset = 0.0;
    float moveX = nsp.x;
    offset = moveX - m_fTouchMoveStartLocation;
    m_fTouchMoveStartLocation = moveX;
    if (offset < 0)
    {
        m_touchMoveDir = PAGECIRCLE_TOUCHLEFT;
    }
    else if (offset > 0)
    {
        m_touchMoveDir = PAGECIRCLE_TOUCHRIGHT;
    }
    scrollPages(offset);
}

void UIPageCircle::handleReleaseLogic(const CCPoint &touchPoint)
{
    UIWidget* curPage = dynamic_cast<UIWidget*>(m_pages->objectAtIndex(m_nCurPageIdx));
    if (curPage)
    {
        CCPoint curPagePos = curPage->getPosition();
        int pageCount = m_pages->count();
        float curPageLocation = curPagePos.x;
        float pageWidth = getSize().width;
        float boundary = pageWidth/2.0f;
        if (curPageLocation <= -boundary)
        {
            if (m_nCurPageIdx >= pageCount-1)
            {
                scrollPages(-curPageLocation);
            }
            else
            {
                scrollToPage(m_nCurPageIdx+1);
            }
        }
        else if (curPageLocation >= boundary)
        {
            if (m_nCurPageIdx <= 0)
            {
                scrollPages(-curPageLocation);
            }
            else
            {
                scrollToPage(m_nCurPageIdx-1);
            }
        }
        else
        {
            scrollToPage(m_nCurPageIdx);
        }
    }
}

void UIPageCircle::checkChildInfo(int handleState,UIWidget* sender, const CCPoint &touchPoint)
{
    interceptTouchEvent(handleState, sender, touchPoint);
}

void UIPageCircle::interceptTouchEvent(int handleState, UIWidget *sender, const CCPoint &touchPoint)
{
    switch (handleState)
    {
        case 0:
            handlePressLogic(touchPoint);
            break;
        case 1:
			{
				float offset = 0;
				offset = fabs(sender->getTouchStartPos().x - touchPoint.x);
				if (offset > m_fChildFocusCancelOffset)
				{
					sender->setFocused(false);
					handleMoveLogic(touchPoint);
				}
			}
            break;
        case 2:
            handleReleaseLogic(touchPoint);
            break;
            
        case 3:
            break;
    }
}

void UIPageCircle::pageTurningEvent()
{
    /*Compatible*/
    if (m_pPageTurningListener && m_pfnPageTurningSelector)
    {
        (m_pPageTurningListener->*m_pfnPageTurningSelector)(this);
    }
    /************/
    if (m_pEventListener && m_pfnEventSelector)
    {
        (m_pEventListener->*m_pfnEventSelector)(this, PAGCIRCLE_EVENT_TURNING);
    }
}

void UIPageCircle::addEventListener(CCObject *target, SEL_PageCircleEvent selector)
{
    m_pEventListener = target;
    m_pfnEventSelector = selector;
}

/*Compatible*/
void UIPageCircle::addPageTurningEvent(CCObject *target, SEL_PageCirclePageTurningEvent selector)
{
    m_pPageTurningListener = target;
    m_pfnPageTurningSelector = selector;
}
/************/

int UIPageCircle::getCurPageIndex() const
{
    return m_nCurPageIdx;
}

NS_CC_EXT_END