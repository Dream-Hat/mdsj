/*
 * 消息协议
 */
#pragma once


namespace ArenaEvent
{
	static const int NAME						= 15000;
	static const int ARENAVIEW_OPEN				= NAME+1;	//打开竞技场
	static const int ARENAVIEW_CLOSE			= NAME+2;	//关闭竞技场
	static const int ARENAVIEW_SELECTGAMEMODE	= NAME+3;	//选择游戏模式
	static const int ARENAVIEW_ENTERROOM		= NAME+4;	//进入游戏房间
	static const int ARENAVIEW_FINDROOM			= NAME+5;	//查找游戏房间
	static const int ARENAVIEW_CREATEROOM		= NAME+6;	//创建游戏房间
	static const int ARENAVIEW_FINDPLAYER		= NAME+7;	//查找玩家
	static const int ARENAVIEW_INVITEPLAYER		= NAME+8;	//邀请玩家

	static const int ARENAVIEW_SETREADY			= NAME+9;	//准备
	static const int ARENAVIEW_REPLACESOUL		= NAME+10;	//替换魂魄
	static const int ARENAVIEW_REPLACEMAP		= NAME+11;	//替换地图
}


namespace PVEEvent
{
	static const int NAME						= 16000;
	static const int PVEVIEW_OPEN				= NAME+1;
	static const int PVEVIEW_CLOSE				= NAME+2;

	static const int PVEVIEW_MAPMOVELEFT		= NAME+3;
	static const int PVEVIEW_MAPMOVERIGHT		= NAME+4;
	static const int PVEVIEW_MAPMOVEOVER		= NAME+5;

	static const int PVEVIEW_OPENLEVEL			= NAME+6;	//打开关卡
	static const int PVEVIEW_ENTERGAMEROOM		= NAME+7;	//进入游戏房间

	static const int PVEVIEW_GOTOTARGETPAGE		= NAME+8;	//地图界面上，选关卡，切换地图

	static const int PVEVIEW_SETLEVELKEYPADTRUE = NAME+9;	//设置关卡界面的android返回键使能
}

namespace FightEvent
{
	static const int NAME							= 17000;
	static const int FIGHTVIEW_OPEN					= NAME+1;
	static const int FIGHTVIEW_CLOSE				= NAME+2;
	static const int FIGHTVIEW_TURNOVER				= NAME+3;//回合行动结束
	static const int FIGHTVIEW_ADDPLAYER			= NAME+4;
	static const int FIGHTVIEW_GAMESTART			= NAME+5;
	static const int FIGHTVIEW_USESOULSKILL			= NAME+6;
	static const int FIGHTVIEW_USETOOLS				= NAME+7;
	static const int FIGHTVIEW_NEXTPLAYER			= NAME+8;
	//static const int FIGHTVIEW_NOTIFYPLAYERTOACT	= NAME+5;//通知对应玩家行动
}

namespace SocketCMDConst
{
	/*7段,竞技场*/
	static const int CMSG_ARENA_REQUESTMODELIST			= 0x2BD;	//打开竞技场，请求获取模式列表
	static const int SMSG_ARENA_RESPONSEMODELIST		= 0x2BE;

	static const int CMSG_ARENA_REQUESTROOMLIST			= 0x2BF;	//选择模式，请求获取房间列表

	static const int CMSG_ARENA_REQUESTCREATEROOM		= 0x2C1;	//创建游戏房间

	static const int CMSG_ARENA_REQUESTENTERROOM		= 0x2C3;	//进入房间

	static const int CMSG_ARENA_REQUESTSEARCHROOM		= 0x2C5;	//搜索房间

	static const int CMSG_ARENA_REQUESTFASTENTER		= 0x2C7;	//快速加入

	static const int CMSG_ARENA_REQUESTMODIFYROOMINFO	= 0x2C9;	//修改房间信息

	static const int CMSG_ARENA_REQUESTSTARTGAME		= 0x2CB;	//开始游戏

	static const int CMSG_ARENA_REQUESTPREPARE			= 0x2CD;	//设置准备

	//static const int CMSG_ARENA_REQUEST
}