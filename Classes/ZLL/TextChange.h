//ÖÐÎÄ×ª»»
#ifndef __MDSJ_ZLL_TEXTCHANGE_H__
#define __MDSJ_ZLL_TEXTCHANGE_H__

#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
namespace TextUTFChange
{
	static std::string GB2312_UTF_CHANGE(const char* _gb2312)
	{
		wchar_t unicode[10000];
		char utf_8[10000];
		memset(utf_8,0,sizeof(utf_8));
		::MultiByteToWideChar(CP_ACP,0,_gb2312,-1,unicode,sizeof(unicode)/sizeof(unicode[0]));
		::WideCharToMultiByte(CP_UTF8,0,unicode,-1,utf_8,sizeof(utf_8)/sizeof(utf_8[0]),0,0);
		return utf_8;
	}
}
#define UTFTXT(content) (TextUTFChange::GB2312_UTF_CHANGE(content).c_str())
#else
#define UTFTXT(content) (content);
#endif

#endif