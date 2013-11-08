#include "ToolsFun.h"

USING_NS_CC;
namespace ToolsFun
{
	CCMenuItemImage* createABtn(char* btnFilePath,cocos2d::CCObject* target,SEL_MenuHandler selector)
	{
		CCMenuItemImage* btn=CCMenuItemImage::create(btnFilePath,btnFilePath,btnFilePath,target,selector);
		return btn;
	}

	CCMenuItemImage* createImgBtn(const char* normalImg,const char* selectedImg,const char* disibleImg)
	{
		CCMenuItemImage* btn=CCMenuItemImage::create(normalImg,selectedImg,disibleImg);
		return btn;
	}

	CCMenuItemSprite* createSpriteBtn(const char* normalImg,const char* selectedImg,const char* disibleImg)
	{
		CCMenuItemSprite* btn=CCMenuItemSprite::create(
			CCSprite::create(normalImg),
			CCSprite::create(selectedImg),
			CCSprite::create(disibleImg),
			NULL,NULL);
		return btn;
	}

	CCMenuItemSprite* createSpriteBtn(const char* normalImg,const char* selectedImg,const char* disibleImg,cocos2d::CCObject* target,cocos2d::SEL_MenuHandler selector)
	{
		CCMenuItemSprite* btn=CCMenuItemSprite::create(
			CCSprite::create(normalImg),
			CCSprite::create(selectedImg),
			CCSprite::create(disibleImg),
			target,selector);
		return btn;
	}

	CCMenuItemSprite* createBtn(const char* btnName,cocos2d::CCObject* target,SEL_MenuHandler selector)
	{
		CCSprite* normal=CCSprite::create(ATHLETIC_BUTTON_2_1);
		CCSprite* selected=CCSprite::create(ATHLETIC_BUTTON_2_2);
		CCSprite* disible=CCSprite::create(ATHLETIC_BUTTON_2_3);

		CCLabelTTF* normalLb=CCLabelTTF::create(btnName,DEF_FONT_NAME,16);
		CCLabelTTF* selectedLb=CCLabelTTF::create(btnName,DEF_FONT_NAME,16);
		CCLabelTTF* disibleLb=CCLabelTTF::create(btnName,DEF_FONT_NAME,16);

		CCSize normalSz=normal->getContentSize();
		CCSize selectedSz=selected->getContentSize();
		CCSize disibleSz=disible->getContentSize();

		normal->addChild(normalLb);
		selected->addChild(selectedLb);
		disible->addChild(disibleLb);

		normalLb->setPosition(ccp(normalSz.width/2,normalSz.height/2));
		selectedLb->setPosition(ccp(selectedSz.width/2,selectedSz.height/2));
		disibleLb->setPosition(ccp(disibleSz.width/2,disibleSz.height/2));

		CCMenuItemSprite* btn=CCMenuItemSprite::create(normal,selected,disible,target,selector);
		return btn;
	}

	CCMenuItemSprite* createBTN(const char* btnName,ButtomType type)
	{
		char* normalChar=NULL;
		char* selectChar=NULL;
		char* disbleChar=NULL;

		if (type==ButtomType_Red)
		{
			normalChar=ATHLETIC_BUTTON_1_1;
			selectChar=ATHLETIC_BUTTON_1_2;
			disbleChar=ATHLETIC_BUTTON_1_3;
		}
		else if (type==ButtomType_Blue1)
		{
			normalChar=ATHLETIC_BUTTON_2_1;
			selectChar=ATHLETIC_BUTTON_2_2;
			disbleChar=ATHLETIC_BUTTON_2_3;
		}
		else if (type==ButtomType_Blue1)
		{
			normalChar=ATHLETIC_BUTTON_3_1;
			selectChar=ATHLETIC_BUTTON_3_2;
			disbleChar=ATHLETIC_BUTTON_3_3;
		}
		else if (type==ButtomType_Blue1)
		{
			normalChar=ATHLETIC_BUTTON_REPLACE_1;
			selectChar=ATHLETIC_BUTTON_REPLACE_2;
			disbleChar=ATHLETIC_BUTTON_REPLACE_3;
		}
// 		else if (type==ButtomType_Replace)
// 		{
// 			normalChar=ATHLETIC_BUTTON_5_1;
// 			selectChar=ATHLETIC_BUTTON_5_2;
// 			disbleChar=ATHLETIC_BUTTON_5_2;
// 		}
		else
		{
			normalChar=ATHLETIC_BUTTON_5_1;
			selectChar=ATHLETIC_BUTTON_5_2;
			disbleChar=ATHLETIC_BUTTON_5_2;
		}


		CCSprite* normal=CCSprite::create(normalChar);
		CCSprite* selected=CCSprite::create(selectChar);
		CCSprite* disible=CCSprite::create(disbleChar);

		CCLabelTTF* normalLb=CCLabelTTF::create(btnName,DEF_FONT_NAME,30);
		CCLabelTTF* selectedLb=CCLabelTTF::create(btnName,DEF_FONT_NAME,30);
		CCLabelTTF* disibleLb=CCLabelTTF::create(btnName,DEF_FONT_NAME,30);

		CCSize normalSz=normal->getContentSize();
		CCSize selectedSz=selected->getContentSize();
		CCSize disibleSz=disible->getContentSize();

		normal->addChild(normalLb);
		selected->addChild(selectedLb);
		disible->addChild(disibleLb);

		normalLb->setPosition(ccp(normalSz.width/2,normalSz.height/2));
		selectedLb->setPosition(ccp(selectedSz.width/2,selectedSz.height/2));
		disibleLb->setPosition(ccp(disibleSz.width/2,disibleSz.height/2));

		CCMenuItemSprite* btn=CCMenuItemSprite::create(normal,selected,disible);
		return btn;
	}

	CCMenuItemSprite* createBTN( const char* btnName,ButtomType type,cocos2d::CCObject* target,cocos2d::SEL_MenuHandler selector )
	{
		CCMenuItemSprite* btn=createBTN(btnName,type);
		btn->setTarget(target,selector);
		return btn;
	}

	
	CCMenuItemSprite* createOnePicBtn(const char* filePath,cocos2d::CCObject* target,cocos2d::SEL_MenuHandler selector,bool filpX/* =false */)
	{
		CCMenuItemSprite* btn=NULL;
		if (!filpX)
		{
			btn=CCMenuItemSprite::create(
			CCSprite::create(filePath),
			CCSprite::create(filePath),
			CCSprite::create(filePath),
			target,selector);
		}
		else
		{
			CCSprite* normal=CCSprite::create(filePath);
			CCSprite* selected=CCSprite::create(filePath);
			CCSprite* disible=CCSprite::create(filePath);
			normal->setFlipX(filpX);
			selected->setFlipX(filpX);
			disible->setFlipX(filpX);
			btn=CCMenuItemSprite::create(
				normal,
				selected,
				disible,
				target,selector);
		}
// 		CCMenuItemSprite* btn=btn=CCMenuItemSprite::create(
// 			CCSprite::create(filePath)->setFlipX(filpX),
// 			CCSprite::create(filePath)->setFlipX(filpX),
// 			CCSprite::create(filePath)->setFlipX(filpX),
// 			target,selector);
		return btn;
	}

	void changeSpriteFrame( cocos2d::CCSprite* targetSp,const char* filePath )
	{
		if (targetSp==NULL)return;
		CCTexture2D* texture=CCTextureCache::sharedTextureCache()->addImage(filePath);
		if (texture==NULL)return;
		CCSize texSize=texture->getContentSize();
		CCRect texRect=CCRectMake(0,0,texSize.width,texSize.height);
		CCSpriteFrame* frame=CCSpriteFrame::createWithTexture(texture,texRect);
		targetSp->setDisplayFrame(frame);
	}

	cocos2d::CCSprite* createSpriteWithRepeatTexture( const char* filePath,cocos2d::CCSize tSize )
	{
		CCSprite* sprite=CCSprite::create(filePath);
		if (NULL==sprite)return NULL;
		CCRect rt=CCRectMake(0,0,tSize.width,tSize.height);
		sprite->setTextureRect(rt);
		ccTexParams tp={GL_LINEAR,GL_LINEAR,GL_REPEAT,GL_REPEAT};
		sprite->getTexture()->setTexParameters(&tp);
		return sprite;
	}

	cocos2d::CCLabelTTF* createLabel( const char* content,const char* fontName,float fontSize,cocos2d::CCPoint pos,cocos2d::CCNode* pNode )
	{
		if (pNode==NULL)return NULL;
		CCLabelTTF* lb=CCLabelTTF::create(content,fontName,fontSize);
		pNode->addChild(lb);
		lb->setPosition(pos);
		return lb;
	}

	cocos2d::CCSprite* createSprite( const char* filePath,cocos2d::CCPoint anchorPoint,cocos2d::CCPoint pos,cocos2d::CCNode* parentNode )
	{
		if (parentNode==NULL)return NULL;
		CCSprite* sprite=CCSprite::create(filePath);
		if (NULL==sprite)return NULL;
		parentNode->addChild(sprite);
		sprite->setAnchorPoint(anchorPoint);
		sprite->setPosition(pos);
		return sprite;
	}




	void SaveFile(const char* content)
	{
		FILE* fp=fopen("log.txt","a+");
		unsigned long len=strlen(content);
		fwrite(content,sizeof(char),len,fp);
		fclose(fp);
	}
}
