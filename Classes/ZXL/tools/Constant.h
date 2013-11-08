#ifndef __CONSTANT_H__
#define __CONSTANT_H__

/*
static const char * TEXTURE_PATH = "texture/";

static const char * ACTION_PATH = "action/";

static const char * FONT_PATH = "font/";

static const char * DAT_PATH = "dat/";

static const char * CACHE_PATH = "";

static const char * SHADER_PATH = "shader/"; 

static const char * PARTICAL_PATH = "particle/";

static const char * SOUND_PATH = "sound/";

static char* bizhong = "cny.dat";

static bool bShare = false;

//游戏价格
static char* game_price = "game_price.dat";

static int PAY_PLATFORM = 0;*/

 enum  
{
	GameTouchWaiting,
	GameTouchTrackingTouch
};

enum {
	TouchNormalPriority = 0,
};
namespace DatagramDef{//namespace Datagram start

//数据开头标签，判断是否是该游戏的包
#define DatagramHeadTag 0x0B

//主数据包格式
enum eMainDatagramType{
	Main_HANDSHAKE = 0x01,
	Main_HEARTBEAT,
	Main_DATA,
	Main_KICK
};
//握手数据包格式
enum eHandshakeDatagramType{
	Handshake_REQUEST = 0x01,
	Handshake_RESPONSE,
	Handshake_ACK
};
//数据数据包格式
enum eDataDatagramType{
	Data_REQUEST = 0x00,
	Data_NOTIFY,
	Data_RESPONSE,
	Data_PUSH
};
//数据错误信息
enum eDataCode{
	DataCode_ok = 0x01,
	DataCode_no_server,
	DataCode_logout_or_timeout,
	DataCode_param_or_type_err,
	DataCode_server_err
};
//握手错误信息
enum eHandshakeCode{
	HandshakeCode_ok =200,
	HandshakeCode_failed = 500,
	HandshakeCode_version_err = 501
};
//数据包管理器状态
enum ePackageMnangerState{
	ManangerState_Unknow = 0,		//未初始化
	ManangerState_ConnectOK,			
	ManangerState_ConnectERR,
	ManangerState_HandshakeOK,
	ManangerState_HandshakeERR ,
	ManangerState_DataCodeOK,
	ManangerState_DataCodeERR
};
}//namespace Datagram end

#endif