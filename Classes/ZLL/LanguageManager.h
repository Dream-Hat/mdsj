/*
 * 语言管理类
 * 单例模式
 */


#ifndef __MDSJ_ZLL_LANGUAGEMANAGER_H__
#define __MDSJ_ZLL_LANGUAGEMANAGER_H__
#include "cocos2d.h"

USING_NS_CC;
class LanguageManager
{
public:
	~LanguageManager();
	static LanguageManager* shareManager();
	void setLanguageFile(const char* filePath);
	bool init();
	void purge();

	std::string getContentByKey(std::string keyName);
	
protected:
	LanguageManager():m_Dict(NULL){}
	void copyFromDictionary(cocos2d::CCDictionary* dict);
protected:
	cocos2d::CCDictionary* m_Dict;
};


#endif
