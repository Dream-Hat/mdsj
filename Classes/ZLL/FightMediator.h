#ifndef __MDSJ_ZLL_FIGHTMEDIATOR_H__
#define __MDSJ_ZLL_FIGHTMEDIATOR_H__
#include "cocos2d.h"
#include <vector>
#include "Define.h"

class FightLayer;

class FightMediator:public cocos2d::CCObject
{
public:
	FightMediator();
	~FightMediator();
protected:
	void startEventListen();
	void closeEventListen();
protected:
	void OnEvent_FightOpen(cocos2d::CCObject* sender,int msgid,cocos2d::CCObject* obj);
	void OnEvent_FightClose(cocos2d::CCObject* sender,int msgid,cocos2d::CCObject* obj);
	void OnEvent_NextTurn(cocos2d::CCObject* sender,int msgid,cocos2d::CCObject* obj);
	void OnEvent_AddPlayer(cocos2d::CCObject* sender,int msgid,cocos2d::CCObject* obj);
	void OnEvent_GameStart(cocos2d::CCObject* sender,int msgid,cocos2d::CCObject* obj);
	void OnEvent_UseSkillOrTools(cocos2d::CCObject* sender,int msgid,cocos2d::CCObject* obj);
	void OnEvent_NotifyNextPlayerAct(cocos2d::CCObject* sender,int msgid,cocos2d::CCObject* obj);
public:
	void setFightType(FightType _type);
	FightType getFightType(){return m_FightType;}
protected:
	//test function
	void initFightData();//初始化战斗数据
	void addPlayer(int type);
	void changeTurnIndex();
	void clearData();
protected:
	FightType m_FightType;

public:
	FightLayer* m_Layer;

public:
	int m_TurnIndex;		//当前轮到哪位玩家行动
	int m_MaxPlayerNum;		//当前场上最大玩家数
protected:
	std::vector<int> m_Team_1_List;
	std::vector<int> m_Team_2_List;
	std::vector<int> m_Monster_List;
};
#endif