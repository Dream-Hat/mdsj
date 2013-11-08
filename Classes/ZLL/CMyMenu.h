#ifndef __MDSJ_ZLL_CMYMENU_H__
#define __MDSJ_ZLL_CMYMENU_H__
#include "cocos2d.h"

/*
 * ��ѡ��ť�˵�
 * ʹ��ʱ��Ҫ���ò˵����ȼ��Լ��Ƿ���Ҫ�������ɴ�������
 * �����˵�����Ҫ����setSelectedItem(item)������һ��Ĭ��ѡ�еİ�ť
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
	cocos2d::CCMenuItem* m_CurHightLighted;//��ǰѡ�еİ�ť
	bool thisTouchedButtoned;//�Ƿ����ڲ˵��е�ĳ����ť��
};

/*
 * ���д������ȼ��Ĳ˵�
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