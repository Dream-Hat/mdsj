#ifndef __MDSJ_ZLL_TOOLSFUN_H__
#define __MDSJ_ZLL_TOOLSFUN_H__
#include "cocos2d.h"
#include "Define.h"
#include "../ZMQ/GameDef.h"

namespace ToolsFun
{
	cocos2d::CCMenuItemImage* createABtn(char* btnFilePath,cocos2d::CCObject* target,cocos2d::SEL_MenuHandler selector);
	
	//根据3种状态的图片，创建按钮，不具备点击回调功能,返回类型为CCMenuItemImage
	cocos2d::CCMenuItemImage* createImgBtn(const char* normalImg,const char* selectedImg,const char* disibleImg);
	//根据3种状态的图片，创建按钮，不具备点击回调功能,返回类型为CCMenuItemSprite
	cocos2d::CCMenuItemSprite* createSpriteBtn(const char* normalImg,const char* selectedImg,const char* disibleImg);
	//根据3种状态的图片，创建按钮,返回类型为CCMenuItemSprite
	cocos2d::CCMenuItemSprite* createSpriteBtn(const char* normalImg,const char* selectedImg,const char* disibleImg,cocos2d::CCObject* target,cocos2d::SEL_MenuHandler selector);

	//根据按钮名字创建按钮
	cocos2d::CCMenuItemSprite* createBtn(const char* btnName,cocos2d::CCObject* target,cocos2d::SEL_MenuHandler selector);

	cocos2d::CCMenuItemSprite* createBTN(const char* btnName,ButtomType type);

	cocos2d::CCMenuItemSprite* createBTN(const char* btnName,ButtomType type,cocos2d::CCObject* target,cocos2d::SEL_MenuHandler selector);

	
	//创建只有1张图片的按钮
	cocos2d::CCMenuItemSprite* createOnePicBtn(const char* filePath,cocos2d::CCObject* target,cocos2d::SEL_MenuHandler selector,bool filpX=false);

	/*
	 * 更改指定精灵的显示帧
	 */
	void changeSpriteFrame(cocos2d::CCSprite* targetSp,const char* filePath);

	/*
	 * 创建具有重复纹理的精灵
	 * filePath，纹理图片地址
	 * tSize,创建后的精灵的大小
	 * sPos,创建好的精灵的坐标
	 */
	cocos2d::CCSprite* createSpriteWithRepeatTexture(const char* filePath,cocos2d::CCSize tSize);

	/*
	 * 创建具有单行文本的文本标签,如果父节点不存在返回null
	 * content,标签显示的文本内容
	 * floatName,字体名称
	 * fontSize,字体大小
	 * pNode,需要添加到的父节点
	 * pos,标签位置
	 */
	cocos2d::CCLabelTTF* createLabel(const char* content,const char* fontName,float fontSize,cocos2d::CCPoint pos,cocos2d::CCNode* pNode);

	/*
	 * 创建一个精灵并添加到ParentNode节点上，返回精灵指针。
	 * 如果精灵创建失败，或者父节点不存在，返回NULL
	 */
	cocos2d::CCSprite* createSprite(const char* filePath,cocos2d::CCPoint anchorPoint,cocos2d::CCPoint pos,cocos2d::CCNode* parentNode);





	void SaveFile(const char* content);
}

/*
 * 评星模块
 */
class Rating:public cocos2d::CCNode
{
public:
	Rating();
	~Rating();

};
#endif