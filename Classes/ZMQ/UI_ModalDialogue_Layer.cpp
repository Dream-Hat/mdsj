#include "UI_ModalDialogue_Layer.h"

USING_NS_CC;
USING_NS_CC_EXT;

#define MODAL_DIALOGUE_ZORDER 9999


UI_ModalDialogue_Layer* UI_ModalDialogue_Layer::s_pInstance = NULL;

UI_ModalDialogue_Layer::UI_ModalDialogue_Layer(void)
{
}

UI_ModalDialogue_Layer::~UI_ModalDialogue_Layer(void)
{

}

bool UI_ModalDialogue_Layer::init()
{
	if (!UILayer::init())
	{
		return false;
	}

	UIWidget* pWidget = CCUIHELPER->createWidgetFromJsonFile("ui/Model_Dialogue/Model_Dialogue.ExportJson");
	addWidget( pWidget );

	m_pLabCaption = (UILabel*)getWidgetByName("lbl_Caption");
	m_pLabContent = (UILabel*)getWidgetByName("lbl_Content");

	m_pBtn_Ok = (UIButton*)getWidgetByName("btn_OK");
	m_pBtn_Ok->addReleaseEvent(this,coco_releaseselector(UI_ModalDialogue_Layer::btn_Click));
	m_pBtn_Ok->setWidgetTag(RT_Ok);

	m_pBtn_Yes = (UIButton*)getWidgetByName("btn_Yes");
	m_pBtn_Yes->addReleaseEvent(this,coco_releaseselector(UI_ModalDialogue_Layer::btn_Click));
	m_pBtn_Yes->setWidgetTag(RT_YES);

	m_pBtn_No = (UIButton*)getWidgetByName("btn_No");
	m_pBtn_No->addReleaseEvent(this,coco_releaseselector(UI_ModalDialogue_Layer::btn_Click));
	m_pBtn_No->setWidgetTag(RT_NO);

	return true;
}

void UI_ModalDialogue_Layer::btn_Click( CCObject* pSender )
{
	HideModal();

	if (m_pFunc)
	{
		UIButton* pBtn = dynamic_cast<UIButton*>(pSender);
		CC_ASSERT( pBtn );
		int nTag = pBtn->getWidgetTag();
		if ( RT_Ok==nTag || RT_YES==nTag )
		{
			m_pFunc();
		}
	}
}

void UI_ModalDialogue_Layer::updateLayer(const char* szTitle,const char* szContent,DialogueType type,pCall p)
{
	s_pInstance->m_pLabCaption->setText(szTitle);
	s_pInstance->m_pLabContent->setText(szContent);
	s_pInstance->m_Type = type;
	s_pInstance->m_pFunc = p;

	if (DT_Normal==s_pInstance->m_Type)
	{
		m_pBtn_Ok->setVisible(false);
		m_pBtn_Yes->setVisible(false);
		m_pBtn_No->setVisible(false);
	}
	else if (DT_Ok==m_Type)
	{
		m_pBtn_Ok->setVisible(true);
		m_pBtn_Yes->setVisible(false);
		m_pBtn_No->setVisible(false);
	}
	else if (DT_Yes_No==m_Type)
	{
		m_pBtn_Ok->setVisible(false);
		m_pBtn_Yes->setVisible(true);
		m_pBtn_No->setVisible(true);
	}
	else
	{
		CCLOG("UI_ModalDialogue_Layer::error m_Type");
	}
}

void UI_ModalDialogue_Layer::DoModal(const char* szTitle,const char* szContent,DialogueType type,pCall p)
{
	if (!s_pInstance)
	{
		s_pInstance = UI_ModalDialogue_Layer::create();
		s_pInstance->retain(); //let it leak,that's allright
	}
	CC_ASSERT(s_pInstance);
	s_pInstance->HideModal();

	s_pInstance->updateLayer(szTitle,szContent,type,p);

	CCScene* pCurrentScene = CCDirector::sharedDirector()->getRunningScene();
	CC_ASSERT(pCurrentScene);
	pCurrentScene->addChild(s_pInstance,MODAL_DIALOGUE_ZORDER);

	CCLOG("UI_ModalDialogue_Layer::ShowModal()");

}

void UI_ModalDialogue_Layer::HideModal()
{
	if (s_pInstance&&s_pInstance->getParent())
	{
		s_pInstance->removeFromParent();
		CCLOG("UI_ModalDialogue_Layer::HideModal()");
	}
}