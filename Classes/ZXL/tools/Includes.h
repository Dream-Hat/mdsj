#ifndef __INCLUDES_H__
#define __INCLUDES_H__

#include <iostream>
#include <fstream>
/*
#include <tchar.h>
#include <direct.h>*/
#include  <stdlib.h>

//#include  <io.h>
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "Constant.h"

#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;  

using namespace CocosDenshion;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#include <android/log.h>
#endif



#endif