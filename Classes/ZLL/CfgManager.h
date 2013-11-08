/*
 * ������Ϣ������
 * ������ȡ�����ļ�
 */
#ifndef __MDSJ_ZLL_CFGMANAGER_H__
#define __MDSJ_ZLL_CFGMANAGER_H__
#include <map>
#include <string>
#include <vector>
#include "biostream.h"

#include "TestData.h"

//��ϷģʽVo
class GameModeStepVo
{
public:
	int _id;
	std::string _modeName;
	std::string _modeContent;
	int _level;
};

class GameRoomPlayerStepVo
{
public:
	int _id;
	int _headId;			
	std::string _name;
	int _level;
	int _vipLevel;
	bool _isReady;
	bool _roomMaster;
	int _teamId;
};


class CfgManger
{
	static CfgManger* instance;
	CfgManger();
public:
	static CfgManger* shareCfgManger();
	static void pure();

//��Ϸģʽ
protected:
	bool gamemode_load;
	std::map<int,GameModeStepVo*> _gameModeDic;
	static void gamemodev_load();
	static void gamemodev_clear();
public:
	static GameModeStepVo* getGameModeStep(int id){gamemodev_load();return instance->_gameModeDic[id];}
	static std::map<int,GameModeStepVo*>& getGameMode(){gamemodev_load();return instance->_gameModeDic;}

//��Ϸ����
protected:
	bool gameroomplayer_load;
	std::map<int,GameRoomPlayerStepVo*> _gameRoomPlayerDic;
	static void gameroomplayerv_load();
	static void gameroomplayerv_clear();
public:
	static GameRoomPlayerStepVo* getPlayerStep(int id){gameroomplayerv_load();return instance->_gameRoomPlayerDic[id];}
	static std::map<int,GameRoomPlayerStepVo*>& getRoomPlayerDicc(){gameroomplayerv_load();return instance->_gameRoomPlayerDic;}

//��Ϸ�����������
protected:
	bool gamerooms_load;
	std::map<int,GameRoomsStepVo*> _gameRoomsDic;
	static void gameroomsv_load();
	static void gameroomsv_clear();
public:
	static std::map<int,GameRoomsStepVo*>& getRoomsDic(){gameroomsv_load();return instance->_gameRoomsDic;}

//�ؿ�������Ϣ
protected:
	bool levels_load;
	std::map<int,LevelStepVo*> _levelsDic;
	static void levelsv_load();
	static void levelsv_clear();
public:
	static std::map<int,LevelStepVo*>& getLevelsDic(){levelsv_load();return instance->_levelsDic;}



};
#endif