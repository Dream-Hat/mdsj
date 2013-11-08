/*
 * ��ϢЭ��
 */
#pragma once


namespace ArenaEvent
{
	static const int NAME						= 15000;
	static const int ARENAVIEW_OPEN				= NAME+1;	//�򿪾�����
	static const int ARENAVIEW_CLOSE			= NAME+2;	//�رվ�����
	static const int ARENAVIEW_SELECTGAMEMODE	= NAME+3;	//ѡ����Ϸģʽ
	static const int ARENAVIEW_ENTERROOM		= NAME+4;	//������Ϸ����
	static const int ARENAVIEW_FINDROOM			= NAME+5;	//������Ϸ����
	static const int ARENAVIEW_CREATEROOM		= NAME+6;	//������Ϸ����
	static const int ARENAVIEW_FINDPLAYER		= NAME+7;	//�������
	static const int ARENAVIEW_INVITEPLAYER		= NAME+8;	//�������

	static const int ARENAVIEW_SETREADY			= NAME+9;	//׼��
	static const int ARENAVIEW_REPLACESOUL		= NAME+10;	//�滻����
	static const int ARENAVIEW_REPLACEMAP		= NAME+11;	//�滻��ͼ
}


namespace PVEEvent
{
	static const int NAME						= 16000;
	static const int PVEVIEW_OPEN				= NAME+1;
	static const int PVEVIEW_CLOSE				= NAME+2;

	static const int PVEVIEW_MAPMOVELEFT		= NAME+3;
	static const int PVEVIEW_MAPMOVERIGHT		= NAME+4;
	static const int PVEVIEW_MAPMOVEOVER		= NAME+5;

	static const int PVEVIEW_OPENLEVEL			= NAME+6;	//�򿪹ؿ�
	static const int PVEVIEW_ENTERGAMEROOM		= NAME+7;	//������Ϸ����

	static const int PVEVIEW_GOTOTARGETPAGE		= NAME+8;	//��ͼ�����ϣ�ѡ�ؿ����л���ͼ

	static const int PVEVIEW_SETLEVELKEYPADTRUE = NAME+9;	//���ùؿ������android���ؼ�ʹ��
}

namespace FightEvent
{
	static const int NAME							= 17000;
	static const int FIGHTVIEW_OPEN					= NAME+1;
	static const int FIGHTVIEW_CLOSE				= NAME+2;
	static const int FIGHTVIEW_TURNOVER				= NAME+3;//�غ��ж�����
	static const int FIGHTVIEW_ADDPLAYER			= NAME+4;
	static const int FIGHTVIEW_GAMESTART			= NAME+5;
	static const int FIGHTVIEW_USESOULSKILL			= NAME+6;
	static const int FIGHTVIEW_USETOOLS				= NAME+7;
	static const int FIGHTVIEW_NEXTPLAYER			= NAME+8;
	//static const int FIGHTVIEW_NOTIFYPLAYERTOACT	= NAME+5;//֪ͨ��Ӧ����ж�
}

namespace SocketCMDConst
{
	/*7��,������*/
	static const int CMSG_ARENA_REQUESTMODELIST			= 0x2BD;	//�򿪾������������ȡģʽ�б�
	static const int SMSG_ARENA_RESPONSEMODELIST		= 0x2BE;

	static const int CMSG_ARENA_REQUESTROOMLIST			= 0x2BF;	//ѡ��ģʽ�������ȡ�����б�

	static const int CMSG_ARENA_REQUESTCREATEROOM		= 0x2C1;	//������Ϸ����

	static const int CMSG_ARENA_REQUESTENTERROOM		= 0x2C3;	//���뷿��

	static const int CMSG_ARENA_REQUESTSEARCHROOM		= 0x2C5;	//��������

	static const int CMSG_ARENA_REQUESTFASTENTER		= 0x2C7;	//���ټ���

	static const int CMSG_ARENA_REQUESTMODIFYROOMINFO	= 0x2C9;	//�޸ķ�����Ϣ

	static const int CMSG_ARENA_REQUESTSTARTGAME		= 0x2CB;	//��ʼ��Ϸ

	static const int CMSG_ARENA_REQUESTPREPARE			= 0x2CD;	//����׼��

	//static const int CMSG_ARENA_REQUEST
}