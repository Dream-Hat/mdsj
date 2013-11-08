#pragma once

#include "cocos2d.h"
#include "cocos-ext.h"

#include "GameDef.h"
USING_NS_CC;
USING_NS_CC_EXT;

class KeyboardLayer : public CCLayer
{
	AutoPtr<UILabel> mNumber;
	unsigned int m_max; 
	unsigned int m_min; 
	unsigned int m_int;
	unsigned int m_value;
	CCObject* target;
	SEL_CallFuncO selector;
	int posx,posy;
public:
	KeyboardLayer(){}
	~KeyboardLayer(){}

	void menuCloseCallback(CCObject* pSender){
		removeFromParentAndCleanup(true);
	}
	void menuMinCallback(CCObject* pSender){
		m_value = m_min; 
		mNumber->setText(CCString::createWithFormat("%d",m_value)->getCString());
	}
	void menuMaxCallback(CCObject* pSender){
		m_value = m_max; 
		mNumber->setText(CCString::createWithFormat("%d",m_value)->getCString());
	}
	void menuBackCallback(CCObject* pSender){
		int v = 0;
		if(strlen(mNumber->getStringValue())>1){
			char s[20];
			strcpy(s,mNumber->getStringValue());
			s[strlen(s)-1]=0;
			v = atoi(s);
		}
		//if(v<m_min)return;
		//if(v>m_max)return;
		m_value = v; 
		mNumber->setText(CCString::createWithFormat("%d",m_value)->getCString());
	}
	unsigned int getInputValue(){return m_value;}
	void menuOkCallback(CCObject* pSender){
		if(m_value<m_min||m_value>m_max){
			if(m_value<m_min)m_value=m_min;
			if(m_value>m_max)m_value=m_max;
			//m_value = v; 
			mNumber->setText(CCString::createWithFormat("%d",m_value)->getCString());
			return;
		}
		if(target&&selector)
			(target->*selector)(this);
		removeFromParentAndCleanup(true);
	}
	void menuClearCallback(CCObject* pSender){
		m_value = m_int; 
		mNumber->setText(CCString::createWithFormat("%d",m_value)->getCString());
	}
	void menuShuziCallback(CCObject* pSender){
		
		int txt = ((UIButton*)pSender)->getTag();
		if(txt>=0&&txt<=9){
			int v = 0;
			char s[20]={0};
			strcpy(s,mNumber->getStringValue());
			v = atoi(s);
			v = v*10+txt; 
			//if(v<m_min)return;
			if(v>m_max)v=m_max;
			m_value = v; 
			mNumber->setText(CCString::createWithFormat("%d",m_value)->getCString());
		}
	}

	static KeyboardLayer* create(int r,CCObject* t,SEL_CallFuncO hd,unsigned int v,unsigned int max=99999999,unsigned int min=0){
		KeyboardLayer *pRet = new KeyboardLayer();
		pRet->autorelease();

		if(v<min)v=min;
		if(v>max)v=max;

		pRet->target = t;
		pRet->selector = hd;
		pRet->m_max = max; 
		pRet->m_min = min; 
		pRet->m_int = v;
		pRet->m_value = v; 

		UILayer* uiLayer = UILayer::create();
		uiLayer->setTouchPriority(r);
		uiLayer->scheduleUpdate();
		pRet->addChild(uiLayer);

		Layout* lay = dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile("ui/Keyboard/Keyboard.json"));
		uiLayer->addWidget(lay);
		UITextButton* returnBtn = dynamic_cast<UITextButton*>(lay->getChildByName("returnBtn"));
		returnBtn->addReleaseEvent(pRet,coco_releaseselector(KeyboardLayer::menuCloseCallback));
		UITextButton* delBtn = dynamic_cast<UITextButton*>(lay->getChildByName("delBtn"));
		delBtn->addReleaseEvent(pRet,coco_releaseselector(KeyboardLayer::menuBackCallback));
		UITextButton* sureBtn = dynamic_cast<UITextButton*>(lay->getChildByName("sureBtn"));
		sureBtn->addReleaseEvent(pRet,coco_releaseselector(KeyboardLayer::menuOkCallback));
		for (int i = 0; i <10;i++)
		{
			UITextButton* num = dynamic_cast<UITextButton*>(lay->getChildByName(CCString::createWithFormat("num_%d",i)->getCString()));
			num->addReleaseEvent(pRet,coco_releaseselector(KeyboardLayer::menuShuziCallback));
		}
// 		build.getBUTTON("min")->setTarget(pRet,menu_selector(KeyboardLayer::menuMinCallback));
// 		build.getBUTTON("max")->setTarget(pRet,menu_selector(KeyboardLayer::menuMaxCallback));
//		build.getBUTTON("Clear")->setTarget(pRet,menu_selector(KeyboardLayer::menuClearCallback));

 		pRet->mNumber = dynamic_cast<UILabel*>(lay->getChildByName("Label"));
		pRet->mNumber->setText(CCString::createWithFormat("%d",pRet->m_value)->getCString()); 
		return pRet;
	}
};