/*
 * ������Mediator
 */
#ifndef __MDSJ_ZLL_ARENAMEDIATOR_H__
#define __MDSJ_ZLL_ARENAMEDIATOR_H__
#include "cocos2d.h"

class ArenaLayer;
class ArenaMediator:public cocos2d::CCObject
{
public:
	ArenaMediator();
	~ArenaMediator();
protected:
	void startEventListen();//���������¼�
	void closeEventListen();
	void startPackListen();//����������Ϣ
	void closePackListen();
protected:
	void OnEvent_ArenaOpen(cocos2d::CCObject* sender,int msgid,cocos2d::CCObject* obj);
	void OnEvent_ArenaClose(cocos2d::CCObject* sender,int msgid,cocos2d::CCObject* obj);
protected:
	void OnPackage_ModeList(int xy,void* pack); //��ȡģʽ�б�
	void OnPackage_GameRoomList(int xy,void* pack); //��ȡ��Ϸ�б�
	//void OnPackage_
public:
	ArenaLayer* _layer;

};
#endif