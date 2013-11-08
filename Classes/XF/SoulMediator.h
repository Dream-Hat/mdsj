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
	//������ť��ص�
	void tapMenuCallBack(CCObject* pSender);
	void pageViewCallBack(CCObject *pSender, PageCircleEventType type);
	void soulPageCallBack(CCObject *pSender, PageViewEventType type);
	//��ѡ��ѵ����
	void openSelXLCallBack(CCObject* pSender);
	//�ر�ѡ��ѵ����
	void closeSelXLCallBack(CCObject* pSender);
	//�ر�ѡ������زĽ���
	void closeSelWYCallBack(CCObject* pSender);
	//ѵ���Ի��������img�ص�
	void xlDlgDSrovCallBack(CCObject* pSender);
	//��갴ťͼ�꣬������鼰������
	void soulImgBtnCallBack(CCObject* pSender);
	//ȷ����ť�ص�
	void sureBtnCallBack(CCObject* pSender);
	//ι�������ڵ��ͼƬ�ص�
	void wyImgCallBack(CCObject* pSender);
	//ι�����渴ѡ��ص�
	void checkBoxWYCallBack(CCObject* pSender, CheckBoxEventType type);
	void changeState(SoulLayerType state);
	//�򿪺ϳ� ѡ������ز�
	void openSelHCCallBack(CCObject* pSender);
	void checkboxBgHCBtnCallBack(CCObject* pSender);
	void checkboxImgHCBtnCallBack(CCObject* pSender);
	void initCheckboxImgHC();
	//�ϳɽ��渴ѡ��ص�
	void checkBoxHCCallBack(CCObject* pSender, CheckBoxEventType type);
	//�򿪺ϳɽ��
	void openHCResult();
	void setVis();
	//��ȡ��ǰҳ�����������Ŀ
	int getCurWYSoulNum();
	//���õ�ǰҳ�����������Ŀ
	void setCurWYSoulNum(int soulIndex,bool isSel);


protected:
	UILayer* m_pUILayer;
	Layout* m_layerLayout;
	//soul������,���õ�
	Layout* m_soulLayout;
	//ѵ��ѡ����Ѳ۲���
	Layout* m_xl_dlg_layout;
	//ѵ������Ի��򲼾�
	Layout* m_xl_result_dlg_layout;
	//�洢�����ں��ѳ���
	UIWidget* m_xl_cjPanel;
	//ι�� �ز�ɸѡ���沼��
	Layout* m_wy_dlg_layout;
	//ι���������
	Layout* m_wy_result_dlg_layout;
	//ѡ��ϳ��زĲ���
	Layout* m_hc_dlg_layout;
	//�ϳɽ������
	Layout* m_hc_result_dlg_layout;
	//��ͬ��ť��Ӧ��ͬpage
	UIPageView* m_soulPage[4];
	//�Ƿ��Ѿ�����page
	bool m_isInputPage[4];
	UIPageCircle* m_pageView;

	//��ǰ�����Ĳ�
	SoulLayerType m_curLayerNum;
	//��¼ι�����氼���Ƿ������
	bool m_wySoulHas[3][6];
	//��ѡ��ι�����������
	int m_curWYSoulNum;
	//��ѡ��ϳɼ�������
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
	void dispose();//�ؽ���
};
