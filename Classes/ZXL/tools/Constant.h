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

//��Ϸ�۸�
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

//���ݿ�ͷ��ǩ���ж��Ƿ��Ǹ���Ϸ�İ�
#define DatagramHeadTag 0x0B

//�����ݰ���ʽ
enum eMainDatagramType{
	Main_HANDSHAKE = 0x01,
	Main_HEARTBEAT,
	Main_DATA,
	Main_KICK
};
//�������ݰ���ʽ
enum eHandshakeDatagramType{
	Handshake_REQUEST = 0x01,
	Handshake_RESPONSE,
	Handshake_ACK
};
//�������ݰ���ʽ
enum eDataDatagramType{
	Data_REQUEST = 0x00,
	Data_NOTIFY,
	Data_RESPONSE,
	Data_PUSH
};
//���ݴ�����Ϣ
enum eDataCode{
	DataCode_ok = 0x01,
	DataCode_no_server,
	DataCode_logout_or_timeout,
	DataCode_param_or_type_err,
	DataCode_server_err
};
//���ִ�����Ϣ
enum eHandshakeCode{
	HandshakeCode_ok =200,
	HandshakeCode_failed = 500,
	HandshakeCode_version_err = 501
};
//���ݰ�������״̬
enum ePackageMnangerState{
	ManangerState_Unknow = 0,		//δ��ʼ��
	ManangerState_ConnectOK,			
	ManangerState_ConnectERR,
	ManangerState_HandshakeOK,
	ManangerState_HandshakeERR ,
	ManangerState_DataCodeOK,
	ManangerState_DataCodeERR
};
}//namespace Datagram end

#endif