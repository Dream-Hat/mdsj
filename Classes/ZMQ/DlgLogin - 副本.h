#pragma once

#include "cocos2d.h"
#include "cocos-ext.h"
#include "GameDef.h"


#define DLGLOGIN_TAG									   500
#define DLGLOGIN_TAG_LAYER							DLGLOGIN_TAG+1
#define DLGLOGIN_TAG_OTHER							DLGLOGIN_TAG+2
#define DLGLOGIN_TAG_REG							DLGLOGIN_TAG+3
#define DLGLOGIN_TAG_XUANFU							DLGLOGIN_TAG+4
#define DLGLOGIN_TAG_ROLE							DLGLOGIN_TAG+5
#define DLGLOGIN_TAG_CREATEROLE						DLGLOGIN_TAG+6

USING_NS_CC;
USING_NS_CC_EXT;

class DlgLoginMediator;
class DlgLogin : public CCLayer
{
public:
	DlgLoginMediator* m_Mediator;
	DlgLogin();
	~DlgLogin();

	bool init();

	

	virtual void onEnter();
	virtual void registerWithTouchDispatcher(void);
	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void onExit();
	cocos2d::CCPoint  m_beginPos;

	CREATE_FUNC(DlgLogin);

	void updateMessage(const char *label);
	void setVis(bool isVis);				//设置界面内全部层的可见性
private:
	void otherBtnCallBack(CCObject* pSender);
	void closeBtnCallBack(CCObject* pSender); //返回按钮事件，全部集合，根据layerNum切换

	void regBtnCallBack(CCObject* pSender);
	void loginBtnCallBack(CCObject* pSender);
	void joinBtnCallBack(CCObject* pSender);
	void sureBtnCallBack(CCObject* pSender);
	//role界面删除人物回调
	void delBtnCallBack(CCObject* pSender);
	//role界面创建人物回调
	void createBtnCallBack1(CCObject* pSender);
	//createRole界面创建按钮回调
	void createBtnCallBack(CCObject* pSender);
	//更新人物界面
	void updateRolePanel();
	//随机名字
	void randBtnCallBack(CCObject* pSender);
	//选择人物按钮回调，role界面
	void roleimgBtnCallBack(CCObject* pSender);
	//选择人物按钮回调，createRole界面
	void roleimgCreatBtnCallBack(CCObject* pSender);
	//左右箭头按钮回调
	void leftArrowBtnCallBack(CCObject* pSender);
	void rightArrowBtnCallBack(CCObject* pSender);
	//屏幕截图并移动效果
	void loadNextLayerEffect(int direction);
	//移动效果结束回调
	void moveEffectEndCallBack();
	//m_xuanfuLayout中选择服务器时的回调
	void selSevCallBack(CCObject* pSender);


public:
	UILayer* m_pUILayer; 
	Layout* m_createRoleLayout; //创建人物层
	Layout* m_layerLayout; // login层
	Layout* m_otherLayout; //其他平台层
	Layout* m_roleLayout;	//选择人物层
	Layout* m_regLayout;	//注册层
	Layout* m_xuanfuLayout;	//	选择服务器层

	Layout* m_rolePanel_0;
	Layout* m_rolePanel_1;

	int selRoleP;
	int selRoleCreate;
	int layerNum;
	int m_selSevNum;
	UITextButton* m_delBtn;
	UITextButton* m_createBtn;
	//x轴方向上移动的初始
	int m_initX;
	//方向X
	int m_directionX;
	//当前已经拥有的英雄数组,0为男，1为女,-1为无英雄
	int m_curRole[2];
	//当前进行创建的英雄的序号
	int m_curCreateNum;

};
class DlgLoginMediator:public CCObject
{
	AutoPtr<DlgLogin> _scene;
public:
	DlgLoginMediator();
	~DlgLoginMediator();
	void OnPackage(int xy,void* pack);
	void OnDlgOpen(CCObject* sender,int msgid,cocos2d::CCObject* obj);
	void dispose();//关界面

};