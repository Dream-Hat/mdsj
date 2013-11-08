#ifndef __MDSJ_ZLL_PVENODE_H__
#define __MDSJ_ZLL_PVENODE_H__
#include "cocos2d.h"
#include "Define.h"
class RatingNode:public cocos2d::CCNode
{
public:
	RatingNode();
	~RatingNode();
	virtual bool init();
	CREATE_FUNC(RatingNode);
public:
	void initNodeWithType(int starNum);
protected:
	int m_StarNum;
};

/*
 * 房间内玩家面板节点
 */
class GameRoom_PlayerNode:public cocos2d::CCNode
{
public:
	GameRoom_PlayerNode();
	~GameRoom_PlayerNode();
	virtual bool init();
	CREATE_FUNC(GameRoom_PlayerNode);
protected:
	void initNode();
public:
	void setNodeType(GameRoom_PlayerNodeType nodeType);
protected:
	cocos2d::CCSprite* m_SpBackground;
	cocos2d::CCSprite* m_SpPlayer;
	cocos2d::CCSprite* m_SpMaster;
	cocos2d::CCSprite* m_SpGetReady;
	cocos2d::CCLabelTTF* m_LbPlayerNickName;
	cocos2d::CCLabelTTF* m_LbPlayerLevel;
protected:
	GameRoom_PlayerNodeType m_NodeType;
	int m_Team;//1 / 2
	bool m_IsReady;
};

/*
 * 游戏房间内地图信息模块
 */
class GameRoom_MapInfoNode:public cocos2d::CCNode
{
public:
	GameRoom_MapInfoNode();
	~GameRoom_MapInfoNode();
	virtual bool init();
	//CREATE_FUNC(GameRoom_MapInfoNode);
	static GameRoom_MapInfoNode* create();
protected:
	void initNode();
protected:
	cocos2d::CCSprite* m_SpBackground;
	cocos2d::CCSprite* m_SpMapName;
	RatingNode* m_RatingNode;
};
#endif