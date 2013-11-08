#ifndef __MDSJ_ZLL_CMYMENU_H__
#define __MDSJ_ZLL_CMYMENU_H__
#include "cocos2d.h"

/*
 * 单选按钮菜单
 * 使用时需要设置菜单优先级以及是否需要进行吞噬触摸操作
 * 创建菜单后需要调用setSelectedItem(item)，设置一个默认选中的按钮
 */
class CCRadioMenuP:public cocos2d::CCMenu
{
public:
	CCRadioMenuP(void);
	~CCRadioMenuP(void);

	void setSelectedItem(cocos2d::CCMenuItem* item);

	virtual void registerWithTouchDispatcher();

	virtual bool ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
	virtual void ccTouchMoved(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
	virtual void ccTouchEnded(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
	virtual void ccTouchCancelled(cocos2d::CCTouch *touch, cocos2d::CCEvent* event);

	static CCRadioMenuP* createWithP(int r,bool canSwallow,cocos2d::CCMenuItem* item, ...);

public:
	int m_Priority;
	bool m_SwallowsAll;
	cocos2d::CCMenuItem* m_CurHightLighted;//当前选中的按钮
	bool thisTouchedButtoned;//是否点击在菜单中的某个按钮上
};

/*
 * 具有触摸优先级的菜单
 */
class CCMenuP : public cocos2d::CCMenu
{
	int _Priority;
	bool _s;
	bool _SwallowsAll;

public:
	bool thisTouchedObject;
public:
	static CCMenuP* create(int r,cocos2d::CCMenuItem* item, ...);

	static CCMenuP* createSwallows(int r,cocos2d::CCMenuItem* item, ...);

	virtual void registerWithTouchDispatcher();

	
	virtual bool ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
	virtual void ccTouchEnded(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
	virtual void ccTouchCancelled(cocos2d::CCTouch *touch, cocos2d::CCEvent* event);
	virtual void ccTouchMoved(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);

};

#endif