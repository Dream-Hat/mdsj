#include "IniParser.h"
USING_NS_CC;

static bool isnullchar(char p){
	return p>=0&&p<=' ';
}

//拆分字符串
static int split_modify_linestring(char* str,char dot,std::vector<char*>& lines){
	int alllen = strlen(str);
	int curstart = -1;
	for(int i=0;i<alllen;i++){
		if((dot>' '&&str[i]==dot)||(dot<=' '&&/*str[i]<=' '*/isnullchar(str[i]))){
			str[i] = 0;

			if(curstart>=0){
				for(int j=i-1;j>=curstart;j--){//去掉后面不可见字符
					if(/*str[j]<=' '*/isnullchar(str[j])){
						str[j] = 0;
					}else break;
				}
				lines.push_back(str+curstart);

				curstart = -1;
			}
		}else if(/*str[i]>' '*/!isnullchar(str[i])&&curstart<0){
			curstart = i;
		}
	}
	if(curstart>=0){
		for(int j=alllen-1;j>=curstart;j--){//去掉后面不可见字符
			if(/*str[j]<=' '*/isnullchar(str[j])){
				str[j] = 0;
			}else break;
		}
		lines.push_back(str+curstart);
	}
	return lines.size();
}

static int split_modify_linestring(std::string &chars,char dot,std::vector<std::string>& lines)
{
	lines.clear();
}


INIParser::INIParser( const char* inifile )
{
	m_IniContent=0;
	unsigned long nSize=0;
	bool bRet=CCFileUtils::sharedFileUtils()->isPopupNotify();
	CCFileUtils::sharedFileUtils()->setPopupNotify(false);
	unsigned char* pBuffer=CCFileUtils::sharedFileUtils()->getFileData(CCFileUtils::sharedFileUtils()->fullPathForFilename(inifile).c_str(),"rb",&nSize);
	CCFileUtils::sharedFileUtils()->setPopupNotify(bRet);

	if (pBuffer!=NULL&&nSize>0)
	{
		m_IniContent=new char[nSize+1];
		memcpy(m_IniContent,pBuffer,nSize);
		m_IniContent[nSize]=0;
		//CCLOG("1111111");
	}
// 	else
// 	{
// 		CCLOG("222222");
// 	}
	if (pBuffer)delete [] pBuffer;
	parser();
}

INIParser::~INIParser()
{
	if (m_IniContent)
		delete [] m_IniContent;
}

void INIParser::parser()
{
	secs.clear();
	if(m_IniContent==0)return;

	std::string cursec="";
	stringMapString cursecs;

	const char* EQ = "=";
	const char* FEN = ";";

	char* start = m_IniContent;
	if(strlen(m_IniContent)>3
		&&(unsigned char)m_IniContent[0]==0xEF
		&&(unsigned char)m_IniContent[1]==0xBB
		&&(unsigned char)m_IniContent[2]==0xBF)start += 3;
	int linelen = getline(start);
	while(linelen>0){
		char* line=trimline(start,linelen);

		if(line&&line[0]!=FEN[0]){
			int line_len = strlen(line);
			if(line_len>=3){
				if(line[0]=='['&&line[line_len-1]==']'){//new section
					if(cursec.length()>0&&cursecs.size()>0){
						secs[cursec] = cursecs;
					}

					line[line_len-1] = 0;
					cursec = line+1;
					cursecs.clear();
				}else if(cursec.length()>0){
					char* eq = strstr(line,EQ);
					if(eq){
						char*left= trimline(line,eq-line);
						char*right=trimline(eq+1,line_len-(eq-line)-1);
						if(left&&right){
							*eq = 0;
							cursecs[left]=right;
						}
					}
				}
			}
		}

		start += linelen;
		linelen = getline(start);
	}

	if(cursec.length()>0&&cursecs.size()>0){
		secs[cursec] = cursecs;
	}

	//mprase = true;
	delete [] m_IniContent;m_IniContent=0;
}

int INIParser::getline( char* str )
{
	const char* NEWLINE="\n";
	if (str[0]==0)return 0;
	char* strold=str;
	while (str[0]==NEWLINE[0])
		str++;
	
	char* p=strstr(str,NEWLINE);

	if (p==0)
		return strlen(strold);
	else
		return p-strold;
}

bool INIParser::isspace( char p )
{
	if (p=='\n'||p=='\r'||p=='\t'||p==' ')
		return true;
	else
		return false;
}

char* INIParser::trimline( char* start,int len )
{
	char* line=0;
	for (int i=0;i<len;i++)
	{
		if (isspace(start[i])){
			start[i]=0;
		}else{
			line=&(start[i]);
			break;
		}
	}

	if (line)
	{
		for (int i=len-1;i>=0;i--)
		{
			if (isspace(start[i])){
				start[i]=0;
			}else{
				break;
			}
		}
	}
	return line;
}

std::string INIParser::getString(const char* lpAppName,const char* lpKeyName,const char* nDefault)
{
	std::map<std::string,stringMapString>::iterator it=secs.find(lpAppName);
	if (it==secs.end())return nDefault;
	stringMapString::iterator its=it->second.find(lpKeyName);
	if (its==it->second.end())return nDefault;
	return its->second;
}

std::string INIParser::getString(const char* lpAppName,const char* lpKeyName)
{
	std::map<std::string,stringMapString>::iterator it=secs.find(lpAppName);
	if (it==secs.end())return std::string(" ");
	stringMapString::iterator its=it->second.find(lpKeyName);
	if (its==it->second.end())return std::string(" "); 
	return its->second;
}

cocos2d::CCPoint INIParser::getPoint( const char* lpAppName,const char* lpKeyName,cocos2d::CCPoint defaultPoint )
{
	std::map<std::string,stringMapString>::iterator it=secs.find(lpAppName);
	if (it==secs.end())return defaultPoint;
	stringMapString::iterator its=it->second.find(lpKeyName);
	if (its==it->second.end())return defaultPoint;
	std::string content=its->second;

	std::vector<char*> pointList;
	int len=content.length();
	if (len==0)return defaultPoint;
	char* chars=new char[len+1];
	chars[len]=0;
	memcpy(chars,content.c_str(),len);
	split_modify_linestring(chars,',',pointList);
	if (pointList.size()==2)
	{
		float x=atof(pointList[0]);
		float y=atof(pointList[1]);
		pointList.clear();
		delete chars;
		return ccp(x,y);
	}
	else
	{
		pointList.clear();
		delete chars;
		return defaultPoint;
	}
}

cocos2d::CCPoint INIParser::getPoint(const char* lpAppName,const char* lpKeyName)
{
	std::map<std::string,stringMapString>::iterator it=secs.find(lpAppName);
	if (it==secs.end())return ccp(0,0);
	stringMapString::iterator its=it->second.find(lpKeyName);
	if (its==it->second.end())return ccp(0,0);
	std::string content=its->second;

	std::vector<char*> pointList;
	int len=content.length();
	if (len==0)return ccp(0,0);
	char* chars=new char[len+1];
	chars[len]=0;
	memcpy(chars,content.c_str(),len);
	split_modify_linestring(chars,',',pointList);
	if (pointList.size()==2)
	{
		float x=atof(pointList[0]);
		float y=atof(pointList[1]);
		pointList.clear();
		delete chars;
		return ccp(x,y);
	}
	else
	{
		pointList.clear();
		delete chars;
		return ccp(0,0);
	}
}

cocos2d::CCRect INIParser::getRect(const char* lpAppName,const char* lpKeyName,cocos2d::CCRect defaultRect)
{
	std::map<std::string,stringMapString>::iterator it=secs.find(lpAppName);
	if (it==secs.end())return defaultRect;
	stringMapString::iterator its=it->second.find(lpKeyName);
	if (its==it->second.end())return defaultRect;
	std::string content=its->second;

	std::vector<char*> floatList;
	int len=content.length();
	if (len==0)return defaultRect;
	char* chars=new char[len+1];
	chars[len]=0;
	memcpy(chars,content.c_str(),len);
	split_modify_linestring(chars,',',floatList);
	if (floatList.size()==4)
	{
		float startfloat=atof(floatList[0]);
		float endfloat=atof(floatList[1]);
		float width=atof(floatList[2]);
		float height=atof(floatList[3]);
		floatList.clear();
		delete chars;
		return CCRectMake(startfloat,endfloat,width,height);
	}
	else
	{
		floatList.clear();
		delete chars;
		return defaultRect;
	}
}

cocos2d::CCRect INIParser::getRect(const char* lpAppName,const char* lpKeyName)
{
	std::map<std::string,stringMapString>::iterator it=secs.find(lpAppName);
	if (it==secs.end())return CCRectMake(0,0,0,0);
	stringMapString::iterator its=it->second.find(lpKeyName);
	if (its==it->second.end())return CCRectMake(0,0,0,0);
	std::string content=its->second;

	std::vector<char*> floatList;
	int len=content.length();
	if (len==0)return CCRectMake(0,0,0,0);
	char* chars=new char[len+1];
	chars[len]=0;
	memcpy(chars,content.c_str(),len);
	split_modify_linestring(chars,',',floatList);
	if (floatList.size()==4)
	{
		float startfloat=atof(floatList[0]);
		float endfloat=atof(floatList[1]);
		float width=atof(floatList[2]);
		float height=atof(floatList[3]);
		floatList.clear();
		delete chars;
		return CCRectMake(startfloat,endfloat,width,height);
	}
	else
	{
		floatList.clear();
		delete chars;
		return CCRectMake(0,0,0,0);
	}
}

cocos2d::CCSize INIParser::getContentSize(const char* lpAppName,const char* lpKeyName,cocos2d::CCSize defaultSize)
{
	std::map<std::string,stringMapString>::iterator it=secs.find(lpAppName);
	if (it==secs.end())return defaultSize;
	stringMapString::iterator its=it->second.find(lpKeyName);
	if (its==it->second.end())return defaultSize;
	std::string content=its->second;

	std::vector<char*> floatList;
	int len=content.length();
	if (len==0)return defaultSize;
	char* chars=new char[len+1];
	chars[len]=0;
	memcpy(chars,content.c_str(),len);
	split_modify_linestring(chars,',',floatList);
	if (floatList.size()==2)
	{
		float width=atof(floatList[0]);
		float height=atof(floatList[1]);
		floatList.clear();
		delete chars;
		return CCSizeMake(width,height);
	}
	else
	{
		floatList.clear();
		delete chars;
		return defaultSize;
	}
}

cocos2d::CCSize INIParser::getContentSize(const char* lpAppName,const char* lpKeyName)
{
	std::map<std::string,stringMapString>::iterator it=secs.find(lpAppName);
	if (it==secs.end())return CCSizeMake(0,0);
	stringMapString::iterator its=it->second.find(lpKeyName);
	if (its==it->second.end())return CCSizeMake(0,0);
	std::string content=its->second;

	std::vector<char*> floatList;
	int len=content.length();
	if (len==0)return CCSizeMake(0,0);
	char* chars=new char[len+1];
	chars[len]=0;
	memcpy(chars,content.c_str(),len);
	split_modify_linestring(chars,',',floatList);
	if (floatList.size()==2)
	{
		float width=atof(floatList[0]);
		float height=atof(floatList[1]);
		floatList.clear();
		delete chars;
		return CCSizeMake(width,height);
	}
	else
	{
		floatList.clear();
		delete chars;
		return CCSizeMake(0,0);
	}
}

int INIParser::getInt( const char* lpAppName,const char* lpKeyName,int nDefault )
{
	std::map<std::string,stringMapString>::iterator it=secs.find(lpAppName);
	if (it==secs.end())return nDefault;
	stringMapString::iterator its=it->second.find(lpKeyName);
	if (its==it->second.end())return nDefault;
	std::string content=its->second;
	return atoi(its->second.c_str());
}

float INIParser::getFloat( const char* lpAppName,const char* lpKeyName,float nDefalut )
{
	std::map<std::string,stringMapString>::iterator it=secs.find(lpAppName);
	if (it==secs.end())return nDefalut;
	stringMapString::iterator its=it->second.find(lpKeyName);
	if (its==it->second.end())return nDefalut;
	std::string content=its->second;
	return atof(its->second.c_str());
}


