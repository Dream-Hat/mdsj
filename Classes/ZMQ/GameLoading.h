#pragma once

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

class GameLoading : public CCLayer
{
public:
	GameLoading();
	~GameLoading();

	virtual bool init();

	static void show();

	CREATE_FUNC(GameLoading);

private:
	void tickLoadGameRes(float dt);

	void onEnterTransitionDidFinish();

private:
	float				m_scale;
};