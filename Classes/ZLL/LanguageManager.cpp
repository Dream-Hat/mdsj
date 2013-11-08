#include "LanguageManager.h"
#include <string>

USING_NS_CC;

static LanguageManager* instance=NULL;



LanguageManager::~LanguageManager()
{
	if (m_Dict!=NULL)
	{
		delete m_Dict;
		m_Dict=NULL;
	}
}

LanguageManager* LanguageManager::shareManager()
{
	if (!instance)
	{
		instance=new LanguageManager();
		instance->init();
	}
	return instance;
}

void LanguageManager::setLanguageFile( const char* filePath )
{
	std::string fullPath=CCFileUtils::sharedFileUtils()->fullPathForFilename(filePath);
	CCDictionary* dict=CCDictionary::createWithContentsOfFile(fullPath.c_str());
	copyFromDictionary(dict);
	//m_Dict=CCDictionary::createWithContentsOfFile(fullPath.c_str());
}

bool LanguageManager::init()
{
	if (m_Dict==NULL)
		m_Dict=new cocos2d::CCDictionary();
	return true;
}

void LanguageManager::purge()
{
	if (instance!=NULL)
		delete instance;
}

void LanguageManager::copyFromDictionary( cocos2d::CCDictionary* dict )
{
	if (NULL==m_Dict)
		m_Dict=new cocos2d::CCDictionary();
	CCDictElement* pElement = NULL;
	CCDICT_FOREACH(dict, pElement)
	{
		CCString* tcontentStr=(CCString*)pElement->getObject();
		CCString* contentStr=CCString::createWithFormat("%s",tcontentStr->getCString());
		std::string keyName=pElement->getStrKey();
		m_Dict->setObject(contentStr,keyName);
	}
}

std::string LanguageManager::getContentByKey( std::string keyName )
{
	if (m_Dict)
	{
		CCString* contentStr=(CCString*)m_Dict->objectForKey(keyName);
		std::string content=std::string(contentStr->getCString());
		return content;
	}
	else
		return "";
}



