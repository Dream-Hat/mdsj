
#pragma once



//13000
namespace Event
{
	static const int EVENT			= 13000;
	static const int CHAT_OPEN		= EVENT+1;
	static const int CLUB_OPEN		= EVENT+2;
	static const int FRIEND_OPEN	= EVENT+3;
	static const int MAIL_OPEN		= EVENT+4;
	static const int Shop_OPEN	= EVENT+5;
	static const int PACKSACK_OPEN	= EVENT+6;
	static const int RICHANG_OPEN	= EVENT+7;
	static const int SHIWUSUO_OPEN	= EVENT+8;
	static const int TASK_OPEN		= EVENT+9;
	static const int TIEJIANGPU_OPEN= EVENT+10;
	static const int VIP_OPEN		= EVENT+11;
	static const int ZHUJUE_OPEN	= EVENT+12;
	static const int SOUL_OPEN		= EVENT+13;
	static const int SPORT_OPEN		= EVENT+14;
	static const int SceneCover_OPEN = EVENT+15;
	static const int DLGLOGIN_OPEN	= EVENT+16;

	static const int EFFECT_HALF	= EVENT+50;
	static const int EFFECT_OVER	= EVENT+51;
	static const int CANCEL_HELP  = EVENT+52;
}


namespace SocketCMDConst
{
	/**10段*/
	static const int CMSG_LOGIN 							= 0x065;		//用户登录
	static const int SMSG_LOGIN 							= 0x066;		//用户登录
	static const int CMSG_LOGIN_GETROLELIST					= 0x067;		//获取角色列表
	static const int SMSG_LOGIN_GETROLELIST					= 0x068;		//获取角色列表
	static const int CMSG_LOGIN_CREATEROLER					= 0x069;		//创建角色
	static const int SMSG_LOGIN_CREATEROLER					= 0x06A;		//创建角色
	static const int CMSG_LOGIN_DELETEROLER 				= 0x06B;		//删除角色
	static const int SMSG_LOGIN_DELETEROLER 				= 0x06C;		//删除角色
	/**10段*/
	//static const int CMSG_LOGIN 							= 0x001;		//用户登录
}