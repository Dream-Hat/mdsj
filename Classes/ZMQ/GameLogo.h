
#ifndef __GAME_LOGO_H__
#define __GAME_LOGO_H__

#include "cocos2d.h"
using namespace cocos2d;
class GameLogo :public cocos2d::CCLayer
{
public:
	GameLogo(void);
	~GameLogo(void);

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  

	//退出
	virtual void onExit();

	//更新
	virtual void ShowLogo(float dt);

	// implement the "static node()" method manually
	CREATE_FUNC(GameLogo);

	//回调方法
	virtual void gameCallback(CCObject* pSender);

	//场景入口
	static CCScene* scene();
};

#endif