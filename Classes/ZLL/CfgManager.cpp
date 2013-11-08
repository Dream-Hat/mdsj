#include "CfgManager.h"
#include "cocos2d.h"
#include "ToolsFun.h"
USING_NS_CC;

CfgManger* CfgManger::instance=0;

#define CFG_INIT_READ(s) \
	if(instance==0)instance = new CfgManger();\
	if(instance->s##_load)return;\
	else instance->s##_load = true;\
	unsigned long nSize = 0;\
	bool b = cocos2d::CCFileUtils::sharedFileUtils()->isPopupNotify();\
	cocos2d::CCFileUtils::sharedFileUtils()->setPopupNotify(false);\
	unsigned char* pBuffer = cocos2d::CCFileUtils::sharedFileUtils()->getFileData(cocos2d::CCFileUtils::sharedFileUtils()->fullPathForFilename("config/"#s".v").c_str(), "rb", &nSize);\
	cocos2d::CCFileUtils::sharedFileUtils()->setPopupNotify(b);\
	Win32Tools::biostream bios((char*)pBuffer,nSize);\
	//s##v_clear();

#define CFG_END_READ if(pBuffer)delete [] pBuffer;

#define cityBossMapId 		3003

CfgManger::CfgManger()
{
	gamemode_load=false;
	gameroomplayer_load=false;
	gamerooms_load=false;
	levels_load=false;
}

CfgManger* CfgManger::shareCfgManger()
{
	if (!instance)
		instance=new CfgManger();
	return instance;
}

void CfgManger::pure()
{
	if (instance==0)return;
	gamemodev_clear();
	gameroomplayerv_clear();
	gameroomsv_clear();
	levelsv_clear();
	delete instance;
	instance = 0;
}

void CfgManger::gamemodev_load()
{
	CFG_INIT_READ(gamemode);

	char* str=(char*)pBuffer;
	if (pBuffer[0]==0xEF&&pBuffer[0]==0xEF&&pBuffer[0]==0xEF)
		str+=3;
	int len=strlen(str);
	int index=0;
	char* ps=0;
	while (index<len)
	{
		if(str[index]==0x0D&&(index+1==len||str[index+1]==0x0A))
		{//一行到了
			str[index]=0;
			if(index+1<len)str[index+1]=0;
			if(ps!=0)
			{
				if(ps[0]>='0'&&ps[0]<='4')
				{
					char* sid=ps;
					char* smodename=strstr(ps,"|");smodename[0]=0;smodename++;
					char* smodecontent=strstr(smodename,"|");smodecontent[0]=0;smodecontent++;
					char* slevel=strstr(smodecontent,"|");slevel[0]=0;slevel++;
					GameModeStepVo* vo=new GameModeStepVo();
					vo->_id=atoi(sid);
					vo->_modeName=smodename;
					vo->_modeContent=smodecontent;
					vo->_level=atoi(slevel);
					instance->_gameModeDic[vo->_id]=vo;
				}
			}
			index+=2;
			ps=0;
		}
		else
		{
			if (ps==0)
				ps=&(str[index]);
			index++;
		}
	}
	if (ps!=0)
	{
		if (ps[0]>='0'&&ps[0]<='4')
		{
			char* sid=ps;
			char* smodename=strstr(ps,"|");smodename[0]=0;smodename++;
			char* smodecontent=strstr(smodename,"|");smodecontent[0]=0;smodecontent++;
			char* slevel=strstr(smodecontent,"|");slevel[0]=0;slevel++;
			GameModeStepVo* vo=new GameModeStepVo();
			vo->_id=atoi(sid);
			vo->_modeName=smodename;
			vo->_modeContent=smodecontent;
			vo->_level=atoi(slevel);
			instance->_gameModeDic[vo->_id]=vo;
		}
	}
	CFG_END_READ;
}

void CfgManger::gamemodev_clear()
{
	SAFE_DELETE_INT_PTR_MAP(instance->_gameModeDic,GameModeStepVo);
}

void CfgManger::gameroomplayerv_load()
{
	CFG_INIT_READ(gameroomplayer);
	char* str=(char*)pBuffer;
	if (pBuffer[0]==0xEF&&pBuffer[0]==0xEF&&pBuffer[0]==0xEF)
		str+=3;
	int len=strlen(str);
	int index=0;
	char* ps=0;
	while (index<len)
	{
		if(str[index]==0x0D&&(index+1==len||str[index+1]==0x0A))
		{//一行到了
			str[index]=0;
			if(index+1<len)str[index+1]=0;
			if(ps!=0)
			{
				if(ps[0]>='0'&&ps[0]<='8')
				{
					char* sid=ps;
					char* sheadid=strstr(sid,"|");sheadid[0]=0;sheadid++;
					char* sname=strstr(sheadid,"|");sname[0]=0;sname++;
					char* slevel=strstr(sname,"|");slevel[0]=0;slevel++;
					char* sviplevel=strstr(slevel,"|");sviplevel[0]=0;sviplevel++;
					char* sisready=strstr(sviplevel,"|");sisready[0]=0;sisready++;
					char* sroommaster=strstr(sisready,"|");sroommaster[0]=0;sroommaster++;
					char* steamid=strstr(sroommaster,"|");steamid[0]=0;steamid++;
					GameRoomPlayerStepVo* vo=new GameRoomPlayerStepVo();
					vo->_id=atoi(sid);
					vo->_headId=atoi(sheadid);
					vo->_name=sname;
					vo->_level=atoi(slevel);
					vo->_vipLevel=atoi(sviplevel);
					vo->_isReady=atoi(sisready)!=0;
					vo->_roomMaster=atoi(sroommaster)!=0;
					//vo->_isReady=static_cast<bool>(atoi(sisready));
					//vo->_roomMaster=static_cast<bool>(atoi(sroommaster));
					vo->_teamId=atoi(steamid);
					instance->_gameRoomPlayerDic[vo->_id]=vo;
				}
			}
			index+=2;
			ps=0;
		}
		else
		{
			if (ps==0)
				ps=&(str[index]);
			index++;
		}
	}
	if (ps!=0)
	{
		if (ps[0]>='0'&&ps[0]<='8')
		{
			char* sid=ps;
			char* sheadid=strstr(sid,"|");sheadid[0]=0;sheadid++;
			char* sname=strstr(sheadid,"|");sname[0]=0;sname++;
			char* slevel=strstr(sname,"|");slevel[0]=0;slevel++;
			char* sviplevel=strstr(slevel,"|");sviplevel[0]=0;sviplevel++;
			char* sisready=strstr(sviplevel,"|");sisready[0]=0;sisready++;
			char* sroommaster=strstr(sisready,"|");sroommaster[0]=0;sroommaster++;
			char* steamid=strstr(sroommaster,"|");steamid[0]=0;steamid++;
			GameRoomPlayerStepVo* vo=new GameRoomPlayerStepVo();
			vo->_id=atoi(sid);
			vo->_headId=atoi(sheadid);
			vo->_name=sname;
			vo->_level=atoi(slevel);
			vo->_vipLevel=atoi(sviplevel);
			vo->_isReady=atoi(sisready)!=0;
			vo->_roomMaster=atoi(sroommaster)!=0;
			vo->_teamId=atoi(steamid);
			instance->_gameRoomPlayerDic[vo->_id]=vo;
		}
	}
	CFG_END_READ;
}

void CfgManger::gameroomplayerv_clear()
{
	SAFE_DELETE_INT_PTR_MAP(instance->_gameRoomPlayerDic,GameRoomPlayerStepVo);
}


void CfgManger::gameroomsv_load()
{
	CFG_INIT_READ(gamerooms);

	char* str=(char*)pBuffer;
	if (pBuffer[0]==0xEF&&pBuffer[0]==0xEF&&pBuffer[0]==0xEF)
		str+=3;
	int len=strlen(str);
	int index=0;
	char* ps=0;
	while (index<len)
	{
		if(str[index]==0x0D&&(index+1==len||str[index+1]==0x0A))
		{//一行到了
			str[index]=0;
			if(index+1<len)str[index+1]=0;
			if(ps!=0)
			{
				if(ps[0]>='0'&&ps[0]<='5')
				{
					char* sid=ps;
					char* sroomname=strstr(sid,"|");sroomname[0]=0;sroomname++;
					char* slevel=strstr(sroomname,"|");slevel[0]=0;slevel++;
					char* splayernum=strstr(slevel,"|");splayernum[0]=0;splayernum++;
					char* sislock=strstr(splayernum,"|");sislock[0]=0;sislock++;
					GameRoomsStepVo* vo=new GameRoomsStepVo();
					vo->_id=atoi(sid);
					vo->_roomname=sroomname;
					vo->_level=atoi(slevel);
					vo->_playernum=atoi(splayernum);
					vo->_islock=atoi(sislock);
					instance->_gameRoomsDic[vo->_id]=vo;
				}
			}
			index+=2;
			ps=0;
		}
		else
		{
			if (ps==0)
				ps=&(str[index]);
			index++;
		}
	}
	if (ps!=0)
	{
		if (ps[0]>='0'&&ps[0]<='5')
		{
			char* sid=ps;
			char* sroomname=strstr(sid,"|");sroomname[0]=0;sroomname++;
			char* slevel=strstr(sroomname,"|");slevel[0]=0;slevel++;
			char* splayernum=strstr(slevel,"|");splayernum[0]=0;splayernum++;
			char* sislock=strstr(splayernum,"|");sislock[0]=0;sislock++;
			GameRoomsStepVo* vo=new GameRoomsStepVo();
			vo->_id=atoi(sid);
			vo->_roomname=sroomname;
			vo->_level=atoi(slevel);
			vo->_playernum=atoi(splayernum);
			vo->_islock=atoi(sislock);
			instance->_gameRoomsDic[vo->_id]=vo;
		}
	}

// 	int l=0;
// 	bios>>l;
// 	for (int i=0;i<l;i++)
// 	{
// 		GameRoomsStepVo* vo=new GameRoomsStepVo();
// 		bios>>(*vo);
// 		instance->_gameRoomsDic[vo->_id]=vo;
// 		CCLOG("%s",vo->_roomname);
// 	}
	CFG_END_READ;
}

void CfgManger::gameroomsv_clear()
{
	SAFE_DELETE_INT_PTR_MAP(instance->_gameRoomsDic,GameRoomsStepVo);
}

void CfgManger::levelsv_load()
{
	
}

void CfgManger::levelsv_clear()
{
	//SAFE_DELETE_INT_PTR_MAP(instance->_gameRoomsDic,LevelStepVo);
}
