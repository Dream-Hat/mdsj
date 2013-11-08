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
	void setVis(bool isVis);				//���ý�����ȫ����Ŀɼ���
private:
	void otherBtnCallBack(CCObject* pSender);
	void closeBtnCallBack(CCObject* pSender); //���ذ�ť�¼���ȫ�����ϣ�����layerNum�л�

	void regBtnCallBack(CCObject* pSender);
	void loginBtnCallBack(CCObject* pSender);
	void joinBtnCallBack(CCObject* pSender);
	void sureBtnCallBack(CCObject* pSender);
	//role����ɾ������ص�
	void delBtnCallBack(CCObject* pSender);
	//role���洴������ص�
	void createBtnCallBack1(CCObject* pSender);
	//createRole���洴����ť�ص�
	void createBtnCallBack(CCObject* pSender);
	//�����������
	void updateRolePanel();
	//�������
	void randBtnCallBack(CCObject* pSender);
	//ѡ�����ﰴť�ص���role����
	void roleimgBtnCallBack(CCObject* pSender);
	//ѡ�����ﰴť�ص���createRole����
	void roleimgCreatBtnCallBack(CCObject* pSender);
	//���Ҽ�ͷ��ť�ص�
	void leftArrowBtnCallBack(CCObject* pSender);
	void rightArrowBtnCallBack(CCObject* pSender);
	//��Ļ��ͼ���ƶ�Ч��
	void loadNextLayerEffect(int direction);
	//�ƶ�Ч�������ص�
	void moveEffectEndCallBack();
	//m_xuanfuLayout��ѡ�������ʱ�Ļص�
	void selSevCallBack(CCObject* pSender);


public:
	UILayer* m_pUILayer; 
	Layout* m_createRoleLayout; //���������
	Layout* m_layerLayout; // login��
	Layout* m_otherLayout; //����ƽ̨��
	Layout* m_roleLayout;	//ѡ�������
	Layout* m_regLayout;	//ע���
	Layout* m_xuanfuLayout;	//	ѡ���������

	Layout* m_rolePanel_0;
	Layout* m_rolePanel_1;

	int selRoleP;
	int selRoleCreate;
	int layerNum;
	int m_selSevNum;
	UITextButton* m_delBtn;
	UITextButton* m_createBtn;
	//x�᷽�����ƶ��ĳ�ʼ
	int m_initX;
	//����X
	int m_directionX;
	//��ǰ�Ѿ�ӵ�е�Ӣ������,0Ϊ�У�1ΪŮ,-1Ϊ��Ӣ��
	int m_curRole[2];
	//��ǰ���д�����Ӣ�۵����
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
	void dispose();//�ؽ���

};