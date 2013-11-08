/*
 * 竞技场中需要的子模块
 */

#ifndef __MDSJ_ZLL_ARENANODE_H__
#define __MDSJ_ZLL_ARENANODE_H__
#include "cocos2d.h"
#include <string>
#include "CfgManager.h"

#include "../proto_files/AthleticProto.pb.h"
//游戏模式组件
class GameModeNode:public cocos2d::CCNode
{
public:
	GameModeNode();
	~GameModeNode();
	virtual bool init();
	CREATE_FUNC(GameModeNode);
public:
	void changeContent(const char* content);
	void changeModeDisplay(const char* filePath);
	void setData(com::tiange::mdsj::proto::ModeListResponse_Mode* _mode);
protected:
	void initNode();

protected:
	cocos2d::CCSprite* m_SpMode;
	cocos2d::CCSprite* m_SpLocked;
	cocos2d::CCLabelTTF* m_LbContent;
	cocos2d::CCLabelTTF* m_LbLimitLv;
};

//游戏房间模块
class GameRoomsNode:public cocos2d::CCNode
{
public:
	GameRoomsNode();
	~GameRoomsNode();
	virtual bool init();
	CREATE_FUNC(GameRoomsNode);
protected:
	void initNode();
protected:
	cocos2d::CCSprite* m_SpIcon;
	cocos2d::CCLabelTTF* m_LbRoomName;
	cocos2d::CCLabelTTF* m_LbLevel;
	cocos2d::CCLabelTTF* m_LbPlayerNum;
	cocos2d::CCSprite* m_SpIsLock;
};

//房间内玩家模块
class PlayerVoInRoom
{
public:
	int teamId;
	int headId;			//头像ID
	std::string _name;
	int level;
	int vipLevel;
	bool isReady;
	bool roomMaster;
	bool isCopy;
	PlayerVoInRoom():teamId(0),headId(0),_name(""),level(0),vipLevel(0),isReady(false),roomMaster(false),isCopy(false){}
	void copyFromVo(GameRoomPlayerStepVo* playerVo)
	{
		if (NULL!=playerVo)
		{
			teamId=playerVo->_teamId;
			headId=playerVo->_headId;
			_name=playerVo->_name;
			level=playerVo->_level;
			vipLevel=playerVo->_vipLevel;
			isReady=playerVo->_isReady;
			roomMaster=playerVo->_roomMaster;
			isCopy=true;
		}
	}
};

class TeamNodeInRoom:public cocos2d::CCNode
{
public: 
	TeamNodeInRoom();
	~TeamNodeInRoom();
	virtual bool init();
	CREATE_FUNC(TeamNodeInRoom);
	static TeamNodeInRoom* createWithPlayer(int teamId,const PlayerVoInRoom &player1,const PlayerVoInRoom &player2);

protected:
	void initNode();
protected:
	int m_TeamID;
	PlayerVoInRoom m_PlayerTop;
	PlayerVoInRoom m_PlayerBottom;

protected:
	cocos2d::CCSprite* m_SpTopPlayer;
	cocos2d::CCSprite* m_SpBottomPlayer;
	cocos2d::CCSprite* m_SpMasterTag;
};

//基本通用模块，头像图片和1个按钮
enum CommonNodeType
{
	CommonNodeType_Null=0,
	CommonNodeType_Soul=1,
	CommonNodeType_Map,
};
class CommonNode:public cocos2d::CCNode
{
public:
	CommonNode();
	~CommonNode();
	virtual bool init();
	static CommonNode* create(CommonNodeType nodeType);
protected:
	void initNode();
public:
	CommonNodeType m_NodeType;
	cocos2d::CCSprite* m_SpHeader;
	cocos2d::CCMenuItemSprite* m_BtnCall;
};


/*
 * 游戏模式图片
 * 用于模式选择界面中的按钮
 */
class GameModeSprite:public cocos2d::CCSprite
{
public:
	GameModeSprite();
	~GameModeSprite();
	/*filePath:精灵图片的地址，content:描述的文字信息，limiteLv:限制等级*/
	static GameModeSprite* create(const char* filePath,const char* content,int limiteLv);
protected:
	void initSprite();

protected:
	cocos2d::CCLabelTTF* m_LbContent;
	cocos2d::CCLabelTTF* m_LbLimiteLV;
	char* filePath;
};
#endif