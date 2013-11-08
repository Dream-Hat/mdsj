#ifndef __UI_MODAL_DIALOGUE_LAYER_H__
#define __UI_MODAL_DIALOGUE_LAYER_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include <functional>

typedef std::function<void(void)> pCall;


class UI_ModalDialogue_Layer : public cocos2d::extension::UILayer
{
public:

	enum DialogueType
	{
		DT_Normal = 0,
		DT_Ok,
		DT_Yes_No,
	};
	enum ResultTag
	{
		RT_Ok = 0,
		RT_YES,
		RT_NO,
	};
private:
	UI_ModalDialogue_Layer(void);
	~UI_ModalDialogue_Layer(void);

	CREATE_FUNC(UI_ModalDialogue_Layer);

	virtual bool init();

public:
	static void DoModal(const char* szTitle,const char* szContent,DialogueType type=DT_Normal,pCall p=nullptr);
	static void HideModal();

private:
	void updateLayer(const char* szTitle,const char* szContent,DialogueType type,pCall p);
	void btn_Click( cocos2d::CCObject* pSender );

private:
	static UI_ModalDialogue_Layer* s_pInstance;

	cocos2d::extension::UILabel*    m_pLabCaption;
	cocos2d::extension::UILabel*    m_pLabContent;
	cocos2d::extension::UIButton*        m_pBtn_Ok;
	cocos2d::extension::UIButton*        m_pBtn_Yes;
	cocos2d::extension::UIButton*        m_pBtn_No;

	DialogueType            m_Type;
	pCall                    m_pFunc;
};

#endif //__UI_MODAL_DIALOGUE_LAYER_H__