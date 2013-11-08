#ifndef __MDSJ_ZLL_TESTDATA_H__
#define __MDSJ_ZLL_TESTDATA_H__
#include "cocos2d.h"
#include <string>

class GameRoomsStepVo
{
public:
	int _id;
	int _level;
	int _playernum;
	int _islock;
	std::string _roomname;

	friend Win32Tools::biostream& operator<<(Win32Tools::biostream& bios,const GameRoomsStepVo& v)
	{
		bios<<v._id<<v._level<<v._playernum<<v._islock<<v._roomname;
		return bios;
	}

	friend Win32Tools::biostream& operator>>(Win32Tools::biostream& bios,GameRoomsStepVo& v)
	{
		bios>>v._id>>v._level>>v._playernum>>v._islock>>v._roomname;
		return bios;
	}
};


//关卡信息数据结构
class LevelMonsterStepVo;
class LevelProdsStepVo;
class LevelStepVo
{
public:
	int _id;
	int _mapid;
	int _playernum;
	std::vector<cocos2d::CCPoint> _playerstartpos;
	std::vector<class LevelMonsterStepVo> _monters;
	int _expendStrenght;
	float _degree;
	int _fighttimes;
	int _experience;
	int _gold;
	int _money;
	std::vector<LevelProdsStepVo> _prods;
};

class LevelMonsterStepVo
{
public:
	int _id;
	int _num;
	int _level;
	std::vector<cocos2d::CCPoint> _startPos;
	int _prodsid;
	int _prodsnum;
	int _skillid;
};
class LevelProdsStepVo
{
protected:
	int _id;
	float _probability;
};
#endif