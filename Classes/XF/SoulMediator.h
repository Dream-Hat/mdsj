#pragma once

#include "cocos2d.h"
#include "cocos-ext.h"
#include "../ZMQ/GameDef.h"
#include "../ZMQ/MessageCenter.h"
#include "../ZMQ/UIPageCircle.h"



USING_NS_CC;
USING_NS_CC_EXT;

#define SOUL_BTN_JJ				1000
#define SOUL_BTN_XL             1001
#define SOUL_BTN_WY				1002
#define SOUL_BTN_HC				1003
#define SOUL_BTN_HC_DLG_PAGE	1004

typedef enum
{
	SOULLAYER_TAG_LAYER,
	SOULLAYER_TAG_JJ,
	SOULLAYER_TAG_XL,
	SOULLAYER_TAG_WY,
	SOULLAYER_TAG_HC,
	SOULLAYER_TAG_XL_DLG,
	SOULLAYER_TAG_XL_RESULT_DLG,
	SOULLAYER_TAG_WY_DLG,
	SOULLAYER_TAG_WY_RESULT_DLG,
	SOULLAYER_TAG_HC_DLG,
	SOULLAYER_TAG_HC_RESULT_DLG
}SoulLayerType;

class SoulMediator;
class SoulLayer : public CCLayer
{
public:
	SoulMediator* m_Mediator;
	SoulLayer(){ m_pUILayer=NULL;
	m_layerLayout=NULL;
	m_soulLayout=NULL;
	m_xl_dlg_layout=NULL;
	m_xl_result_dlg_layout=NULL;
	m_wy_dlg_layout=NULL;
	m_wy_result_dlg_layout=NULL;
	m_hc_dlg_layout=NULL;
	m_hc_result_dlg_layout = NULL;}
	~SoulLayer(){}

	bool init();

	
	void keyBackClicked();
	virtual void onEnter();
	virtual void registerWithTouchDispatcher(void);
	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	cocos2d::CCPoint  m_beginPos;

	CREATE_FUNC(SoulLayer);


private:
	void yesBtnCallBack(CCObject* pSender);
	void closeBtnCallBack(CCObject* pSender);
	//顶部按钮组回调
	void tapMenuCallBack(CCObject* pSender);
	void pageViewCallBack(CCObject *pSender, PageCircleEventType type);
	void soulPageCallBack(CCObject *pSender, PageViewEventType type);
	//打开选择训练槽
	void openSelXLCallBack(CCObject* pSender);
	//关闭选择训练槽
	void closeSelXLCallBack(CCObject* pSender);
	//关闭选择灵魂素材界面
	void closeSelWYCallBack(CCObject* pSender);
	//训练对话框滚动层img回调
	void xlDlgDSrovCallBack(CCObject* pSender);
	//灵魂按钮图标，打开灵魂简介及操作层
	void soulImgBtnCallBack(CCObject* pSender);
	//确定按钮回调
	void sureBtnCallBack(CCObject* pSender);
	//喂养界面内点击图片回调
	void wyImgCallBack(CCObject* pSender);
	//喂养界面复选框回调
	void checkBoxWYCallBack(CCObject* pSender, CheckBoxEventType type);
	void changeState(SoulLayerType state);
	//打开合成 选择灵魂素材
	void openSelHCCallBack(CCObject* pSender);
	void checkboxBgHCBtnCallBack(CCObject* pSender);
	void checkboxImgHCBtnCallBack(CCObject* pSender);
	void initCheckboxImgHC();
	//合成界面复选框回调
	void checkBoxHCCallBack(CCObject* pSender, CheckBoxEventType type);
	//打开合成结果
	void openHCResult();
	void setVis();
	//获取当前页内已有灵魂数目
	int getCurWYSoulNum();
	//设置当前页内已有灵魂数目
	void setCurWYSoulNum(int soulIndex,bool isSel);


protected:
	UILayer* m_pUILayer;
	Layout* m_layerLayout;
	//soul操作层,共用的
	Layout* m_soulLayout;
	//训练选择好友槽布局
	Layout* m_xl_dlg_layout;
	//训练结果对话框布局
	Layout* m_xl_result_dlg_layout;
	//存储界面内好友场景
	UIWidget* m_xl_cjPanel;
	//喂养 素材筛选界面布局
	Layout* m_wy_dlg_layout;
	//喂养结果布局
	Layout* m_wy_result_dlg_layout;
	//选择合成素材布局
	Layout* m_hc_dlg_layout;
	//合成结果布局
	Layout* m_hc_result_dlg_layout;
	//不同按钮对应不同page
	UIPageView* m_soulPage[4];
	//是否已经加入page
	bool m_isInputPage[4];
	UIPageCircle* m_pageView;

	//当前所处的层
	SoulLayerType m_curLayerNum;
	//记录喂养界面凹槽是否有灵魂
	bool m_wySoulHas[3][6];
	//已选择喂养的灵魂数量
	int m_curWYSoulNum;
	//已选择合成技能数量
	int m_curHCSkillNum;
	//
	int m_checkNum;
};

class SoulMediator:public CCObject
{
	AutoPtr<SoulLayer> _scene;
public:
	SoulMediator();
	~SoulMediator();
	void OnPackage(short xy,char* pack,int len);
	void OnSoulOpen(CCObject* sender,int msgid,cocos2d::CCObject* obj);
	void dispose();//关界面
};
