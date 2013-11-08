#ifndef  _APP_DELEGATE_H_
#define  _APP_DELEGATE_H_

#include "cocos2d.h"

/**
@brief    The cocos2d Application.

The reason for implement as private inheritance is to hide some interface call by CCDirector.
*/
class  AppDelegate : private cocos2d::CCApplication
{
public:

	static const int ChatMediatorMark = 10;
	static const int ClubMediatorMark = 11;
	static const int FriendMediatorMark = 12;
	static const int MailMediatorMark = 13;
	static const int ShopMediatorMark = 14;
	static const int PacksackMediatorMark = 15;
	static const int RichangMediatorMark = 16;
	static const int ShiwusuoMediatorMark = 17;
	static const int TaskMediatorMark = 18;
	static const int TiejiangpuMediatorMark = 19;
	static const int VipMediatorMark = 20;
	static const int ZhujueMediatorMark = 21;
	static const int SoulMediatorMark = 22;
	static const int SportMediatorMark = 23;
	static const int DlgLoginMediatorMark = 24;

	static const int ArenaMediatorMark=50;	//¾º¼¼³¡
	static const int PVEMediatorMark=ArenaMediatorMark+1;
	static const int FightMediatorMark=ArenaMediatorMark+2;

	void ReStartupGame();

    AppDelegate();
    virtual ~AppDelegate();

    /**
    @brief    Implement CCDirector and CCScene init code here.
    @return true    Initialize success, app continue.
    @return false   Initialize failed, app terminate.
    */
    virtual bool applicationDidFinishLaunching();

    /**
    @brief  The function be called when the application enter background
    @param  the pointer of the application
    */
    virtual void applicationDidEnterBackground();

    /**
    @brief  The function be called when the application enter foreground
    @param  the pointer of the application
    */
    virtual void applicationWillEnterForeground();
};

#endif // _APP_DELEGATE_H_

