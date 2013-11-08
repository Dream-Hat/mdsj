#pragma once

#include "cocos2d.h"
#include "cocos-ext.h"
#include "GameDef.h"

USING_NS_CC;
USING_NS_CC_EXT;




class Pop
{
public:
	static void popText(const char* text,cocos2d::ccColor3B cr);
	static void popTextByPosition(const char* text,cocos2d::ccColor3B cr,const cocos2d::CCPoint &pos);
};