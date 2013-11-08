#ifndef __MDSJ_ZLL_PVEMEDIATOR__
#define __MDSJ_ZLL_PVEMEDIATOR__
#include "cocos2d.h"



class PVELayer;
class PVEMediator:public cocos2d::CCObject
{
public:
	PVEMediator();
	~PVEMediator();

protected:
	void startEventListen();
	void closeEventListen();

protected:
	/*打开PVE界面*/
	void OnEvent_PVEViewOpen(cocos2d::CCObject* sender,int msgid,cocos2d::CCObject* obj);		
	/*关闭PVE界面*/
	void OnEvent_PVEViewClose(cocos2d::CCObject* sender, int msgid,cocos2d::CCObject* obj);
	/*地图移动*/
	void OnEvent_PVEViewMove(cocos2d::CCObject* sender,int msgid,cocos2d::CCObject* obj);
	/*打开指定关卡*/
	void OnEvent_PVEViewOpenLevel(cocos2d::CCObject* sender,int msgid,cocos2d::CCObject* obj);
	/*进入游戏房间*/
	void OnEvent_PVEViewEnterGameRoom(cocos2d::CCObject* sender,int msgid,cocos2d::CCObject* obj);
	/*地图转到指定页面*/
	void OnEvent_PVEViewGotoTargetPage(cocos2d::CCObject* sender,int msgid,cocos2d::CCObject* obj);

	void OnEvent_PVELevelSetKeyPadTrue(cocos2d::CCObject* sender,int msgid,cocos2d::CCObject* obj);
public:
	PVELayer* _layer;
};
#endif