#ifndef __INIPARSER_H__
#define __INIPARSER_H__

#include "cocos2d.h"
#include <string>
#include <map>

typedef std::map<std::string,std::string> stringMapString;


class INIParser
{
public:
	INIParser(const char* inifile);
	~INIParser();
	std::string getString(const char* lpAppName,const char* lpKeyName,const char* nDefault);
	std::string getString(const char* lpAppName,const char* lpKeyName);

	cocos2d::CCPoint getPoint(const char* lpAppName,const char* lpKeyName,cocos2d::CCPoint defaultPoint);
	cocos2d::CCPoint getPoint(const char* lpAppName,const char* lpKeyName);

	cocos2d::CCRect getRect(const char* lpAppName,const char* lpKeyName,cocos2d::CCRect defaultRect);
	cocos2d::CCRect getRect(const char* lpAppName,const char* lpKeyName);

	cocos2d::CCSize getContentSize(const char* lpAppName,const char* lpKeyName,cocos2d::CCSize defaultSize);
	cocos2d::CCSize getContentSize(const char* lpAppName,const char* lpKeyName);

	int getInt(const char* lpAppName,const char* lpKeyName,int nDefault);

	float getFloat(const char* lpAppName,const char* lpKeyName,float nDefalut);
protected:
	void parser();
	int getline(char* str);
	bool isspace(char p);
	char* trimline(char* start,int len);
protected:
	char* m_IniContent;
	std::map<std::string,stringMapString> secs;
};  
#endif