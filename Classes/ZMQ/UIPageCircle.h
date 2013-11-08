

#ifndef __MDSJ_ZMQ_UIPAGCIRCLE_H__
#define __MDSJ_ZMQ_UIPAGCIRCLE_H__

#include "CocoStudio/GUI/Layouts/Layout.h"
#include "CocoStudio/GUI/UIWidgets/ScrollWidget/UIScrollInterface.h"

NS_CC_EXT_BEGIN

typedef enum
{
    PAGCIRCLE_EVENT_TURNING,
}PageCircleEventType;

typedef void (CCObject::*SEL_PageCircleEvent)(CCObject*, PageCircleEventType);
#define pagecircleeventselector(_SELECTOR)(SEL_PageCircleEvent)(&_SELECTOR)

/*******Compatible*******/
typedef void (CCObject::*SEL_PageCirclePageTurningEvent)(CCObject*);
#define coco_PageCircle_PageTurning_selector(_SELECTOR) (SEL_PageCirclePageTurningEvent)(&_SELECTOR)
/************************/

typedef enum {
    PAGECIRCLE_TOUCHLEFT,
    PAGECIRCLE_TOUCHRIGHT
}PCTouchDir;

class UIPageCircle : public Layout , public UIScrollInterface
{
    
public:
    UIPageCircle();
    virtual ~UIPageCircle();
    static UIPageCircle* create();
    void addWidgetToPage(UIWidget* widget, int pageIdx, bool forceCreate);
    void addPage(Layout* page);
    void insertPage(Layout* page, int idx);
    void removePage(Layout* page);
    void removePageAtIndex(int index);
    void scrollToPage(int idx);
    int getCurPageIndex() const;
    
    // event
    void addEventListener(CCObject *target, SEL_PageCircleEvent selector);
    /*******Compatible*******/
    //Add call back function called when page turning.
    void addPageTurningEvent(CCObject *target, SEL_PageCirclePageTurningEvent selector);
    /**************/
    
    //override "removeChild" method of widget.
    virtual bool removeChild(UIWidget* widget);
    
    //override "removeAllChildrenAndCleanUp" method of widget.
    virtual void removeAllChildren();
    
    //override "onTouchBegan" method of widget.
    virtual bool onTouchBegan(const CCPoint &touchPoint);
    
    //override "onTouchMoved" method of widget.
    virtual void onTouchMoved(const CCPoint &touchPoint);
    
    //override "onTouchEnded" method of widget.
    virtual void onTouchEnded(const CCPoint &touchPoint);
    
    //override "onTouchCancelled" method of widget.
    virtual void onTouchCancelled(const CCPoint &touchPoint);
    
    //override "update" method of widget.
    virtual void update(float dt);
    
    virtual void doLayout(){};
    
    /*compatible*/
    /**
     * These methods will be removed
     */
    int getPage() const{return getCurPageIndex();};
    void removePage(Layout* page, bool cleanup){removePage(page);};
    void removePageAtIndex(int index, bool cleanup){removePageAtIndex(index);};
    /************/
protected:
    virtual bool addChild(UIWidget* widget);
    virtual bool init();
    Layout* createPage();
    float getPositionXByIndex(int idx);
    void updateBoundaryPages();
    virtual void handlePressLogic(const CCPoint &touchPoint);
    virtual void handleMoveLogic(const CCPoint &touchPoint);
    virtual void handleReleaseLogic(const CCPoint &touchPoint);
    virtual void interceptTouchEvent(int handleState, UIWidget* sender, const CCPoint &touchPoint);
    virtual void checkChildInfo(int handleState, UIWidget* sender, const CCPoint &touchPoint);
    virtual bool scrollPages(float touchOffset);
    void movePages(float offset);
    void pageTurningEvent();
    void updateChildrenSize();
    void updateChildrenPosition();
    virtual void onSizeChanged();
//    virtual bool isInScrollDegreeRange(UIWidget* widget);
    /*compatible*/
    /**
     * These methods will be removed
     */
    virtual void setClippingEnable(bool is){setClippingEnabled(is);};
    /************/
    virtual void setClippingEnabled(bool able){Layout::setClippingEnabled(able);};
public:
	CCArray* m_pages;
protected:
    int m_nCurPageIdx;
    
    PCTouchDir m_touchMoveDir;
    float m_fTouchStartLocation;
    float m_fTouchEndLocation;
    float m_fTouchMoveStartLocation;
    CCPoint movePagePoint;
    UIWidget* m_pLeftChild;
    UIWidget* m_pRightChild;
    float m_fLeftBoundary;
    float m_fRightBoundary;
    bool m_bIsAutoScrolling;
    float m_fAutoScrollDistance;
    float m_fAutoScrollSpeed;
    int m_nAutoScrollDir;
    float m_fChildFocusCancelOffset;
    CCObject* m_pEventListener;
    SEL_PageCircleEvent m_pfnEventSelector;
    /*compatible*/
    CCObject* m_pPageTurningListener;
    SEL_PageCirclePageTurningEvent m_pfnPageTurningSelector;
    /************/
};

NS_CC_EXT_END

#endif /* defined(__MDSJ_ZMQ_UIPAGCIRCLE_H__) */
