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
	/*��PVE����*/
	void OnEvent_PVEViewOpen(cocos2d::CCObject* sender,int msgid,cocos2d::CCObject* obj);		
	/*�ر�PVE����*/
	void OnEvent_PVEViewClose(cocos2d::CCObject* sender, int msgid,cocos2d::CCObject* obj);
	/*��ͼ�ƶ�*/
	void OnEvent_PVEViewMove(cocos2d::CCObject* sender,int msgid,cocos2d::CCObject* obj);
	/*��ָ���ؿ�*/
	void OnEvent_PVEViewOpenLevel(cocos2d::CCObject* sender,int msgid,cocos2d::CCObject* obj);
	/*������Ϸ����*/
	void OnEvent_PVEViewEnterGameRoom(cocos2d::CCObject* sender,int msgid,cocos2d::CCObject* obj);
	/*��ͼת��ָ��ҳ��*/
	void OnEvent_PVEViewGotoTargetPage(cocos2d::CCObject* sender,int msgid,cocos2d::CCObject* obj);

	void OnEvent_PVELevelSetKeyPadTrue(cocos2d::CCObject* sender,int msgid,cocos2d::CCObject* obj);
public:
	PVELayer* _layer;
};
#endif