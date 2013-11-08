#ifndef __MDSJ_ZLL_TOOLSFUN_H__
#define __MDSJ_ZLL_TOOLSFUN_H__
#include "cocos2d.h"
#include "Define.h"
#include "../ZMQ/GameDef.h"

namespace ToolsFun
{
	cocos2d::CCMenuItemImage* createABtn(char* btnFilePath,cocos2d::CCObject* target,cocos2d::SEL_MenuHandler selector);
	
	//����3��״̬��ͼƬ��������ť�����߱�����ص�����,��������ΪCCMenuItemImage
	cocos2d::CCMenuItemImage* createImgBtn(const char* normalImg,const char* selectedImg,const char* disibleImg);
	//����3��״̬��ͼƬ��������ť�����߱�����ص�����,��������ΪCCMenuItemSprite
	cocos2d::CCMenuItemSprite* createSpriteBtn(const char* normalImg,const char* selectedImg,const char* disibleImg);
	//����3��״̬��ͼƬ��������ť,��������ΪCCMenuItemSprite
	cocos2d::CCMenuItemSprite* createSpriteBtn(const char* normalImg,const char* selectedImg,const char* disibleImg,cocos2d::CCObject* target,cocos2d::SEL_MenuHandler selector);

	//���ݰ�ť���ִ�����ť
	cocos2d::CCMenuItemSprite* createBtn(const char* btnName,cocos2d::CCObject* target,cocos2d::SEL_MenuHandler selector);

	cocos2d::CCMenuItemSprite* createBTN(const char* btnName,ButtomType type);

	cocos2d::CCMenuItemSprite* createBTN(const char* btnName,ButtomType type,cocos2d::CCObject* target,cocos2d::SEL_MenuHandler selector);

	
	//����ֻ��1��ͼƬ�İ�ť
	cocos2d::CCMenuItemSprite* createOnePicBtn(const char* filePath,cocos2d::CCObject* target,cocos2d::SEL_MenuHandler selector,bool filpX=false);

	/*
	 * ����ָ���������ʾ֡
	 */
	void changeSpriteFrame(cocos2d::CCSprite* targetSp,const char* filePath);

	/*
	 * ���������ظ�����ľ���
	 * filePath������ͼƬ��ַ
	 * tSize,������ľ���Ĵ�С
	 * sPos,�����õľ��������
	 */
	cocos2d::CCSprite* createSpriteWithRepeatTexture(const char* filePath,cocos2d::CCSize tSize);

	/*
	 * �������е����ı����ı���ǩ,������ڵ㲻���ڷ���null
	 * content,��ǩ��ʾ���ı�����
	 * floatName,��������
	 * fontSize,�����С
	 * pNode,��Ҫ��ӵ��ĸ��ڵ�
	 * pos,��ǩλ��
	 */
	cocos2d::CCLabelTTF* createLabel(const char* content,const char* fontName,float fontSize,cocos2d::CCPoint pos,cocos2d::CCNode* pNode);

	/*
	 * ����һ�����鲢��ӵ�ParentNode�ڵ��ϣ����ؾ���ָ�롣
	 * ������鴴��ʧ�ܣ����߸��ڵ㲻���ڣ�����NULL
	 */
	cocos2d::CCSprite* createSprite(const char* filePath,cocos2d::CCPoint anchorPoint,cocos2d::CCPoint pos,cocos2d::CCNode* parentNode);





	void SaveFile(const char* content);
}

/*
 * ����ģ��
 */
class Rating:public cocos2d::CCNode
{
public:
	Rating();
	~Rating();

};
#endif