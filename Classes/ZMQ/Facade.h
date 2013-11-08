#pragma once
#include "cocos2d.h"
#include <map>
using namespace std;
USING_NS_CC;
namespace Layer_Touch_Priority
{
	static const int Scene_Layer_P = 0;
	static const int First_Panel_Layer_P = -2000;//家宅
	static const int Normal_Panel_Layer_P = -3000;//主窗口
	static const int Leaf_Panel_Layer_P = -4000;//跑商 人物属性面板
	static const int Battle_Panel_Layer_P = -5000; // 战斗 战役 登陆
	static const int Story_Panel_Layer_P = -6000; // 消息  注册人物
	static const int Notify_Panel_Layer_P = -7000; // 消息  注册人物
}

class Facade : public CCObject
{
public:
	

	map<int,CCObject*> mediatorVector;
	Facade();
	~Facade();
	/** Gets the single instance of MessageCenter. */
	static Facade *instance(void);
	/** Destroys the single instance of MessageCenter. */
	static void purgeFacade(void);
	void clear();
	
	void addMediator(int mark,CCObject* mediator);
	void newMediator();
	CCObject* getMediator(int mark);

	
	
};