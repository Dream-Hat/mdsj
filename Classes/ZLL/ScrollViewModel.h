#ifndef __MDSJ_ZLL_SCROLLVIEWMODEL_H__
#define __MDSJ_ZLL_SCROLLVIEWMODEL_H__
#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
using namespace cocos2d::extension;


#define SCROLL_DEACCEL_RATE  0.95f
#define SCROLL_DEACCEL_DIST  1.0f
#define BOUNCE_DURATION      0.15f
#define INSET_RATIO          0.2f


class ScrollViewModel:public cocos2d::extension::CCScrollView
{
public:
	~ScrollViewModel();
	static ScrollViewModel* createP(int r,CCSize size, CCNode* container = NULL);
	static ScrollViewModel* create(int r);
	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);	virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
	
	void relocateContainer(bool animated);
	void mydeaccelerateScrolling(float dt);

	bool isDrag(){return m_bDragging;}
	bool isTouchMoved(){return m_bTouchMoved;}
	bool isDeaccelerateScrolling(){return deaccelerateScrolling;}
	void initScene();
	void createMenu();
protected:
	bool deaccelerateScrolling;
	cocos2d::CCLayer* mContainer;
	int mPriority;
	std::vector<cocos2d::CCMenuItemSprite*> mBtnItem;
};

/*
 * 右侧带滚动条的滚动区域
 */
class ScrollViewModelT:public ScrollViewModel
{

};
#endif