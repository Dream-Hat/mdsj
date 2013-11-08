
//ºêÎÄ¼þ

#ifndef _GAME_DEF_
#define _GAME_DEF_


// ZÖá
#define Z_00	0
#define Z_10	10
#define Z_20	20
#define Z_30	30
#define Z_40	40
#define Z_Max	1000


enum
{
	// logo
	E_Scene_Logo = 0,
	// loading
	E_Scene_Loading,
	// cover
	E_Scene_Cover,
	// shop
	E_Scene_Shop,
	// game
	E_Scene_Game
};



#define SAFE_RELEASE(a)  if(a){a->release();a=0;}
#define SAFE_DELETE(a)  if(a){delete (a);a=0;}
#define SAFE_FUN_DELETE(a,f)  if(a){(f)(a);a=0;}
#define SAFE_DELETE_ARRAY(a)  if(a){delete [] (a);a=0;}


#define SAFE_DELETE_INT_PTR_MAP(m,c)	{\
	for(std::map<int,c*>::iterator it=m.begin();it!=m.end();it++){\
	delete it->second;\
	}m.clear();}

#define SAFE_DELETE_PTR_VECTOR(m,c)	{\
	for(std::vector<c*>::iterator it=m.begin();it!=m.end();it++){\
	delete (*it);\
	}m.clear();}

#ifndef VIOASSERT
#if defined DEBUG || defined _DEBUG
#define VIOASSERT(p) if(!(p)){char*___x=0;*___x=0;}
#else
#define VIOASSERT(p)
#endif
#endif


template<class T>
class AutoPtr
{
	T* _t;
public:
	AutoPtr(){
		_t = 0;
	}
	AutoPtr(const T* strSrc){
		_t = (T*)strSrc;
		if(_t)_t->retain();
	}
	AutoPtr(const AutoPtr<T>& strSrc){
		_t = strSrc.obj();
		if(_t)_t->retain();
	}
	AutoPtr& operator=(const T* strSrc )
	{
		SAFE_RELEASE(_t);
		_t = (T*)strSrc;
		if(_t)_t->retain();

		return( *this );
	}
	AutoPtr& operator=(const AutoPtr<T>& strSrc )
	{
		SAFE_RELEASE(_t);
		_t = strSrc.obj();
		if(_t)_t->retain();

		return( *this );
	}
	~AutoPtr(){
		SAFE_RELEASE(_t);
	}
	void detch(){
		SAFE_RELEASE(_t);
	}
	bool operator!() const
	{
		return (_t == NULL);
	}
	T* operator->() const
	{
		return _t;
	}
	operator const T*() const
	{
		return _t;
	}
	T* obj() const
	{
		return _t;
	}
};

typedef AutoPtr<cocos2d::CCLabelTTF> CCLabelTTFRef;
typedef AutoPtr<cocos2d::CCSprite> CCSpriteRef;
typedef AutoPtr<cocos2d::CCMenuItemSprite> CCMenuItemSpriteRef;
typedef AutoPtr<cocos2d::CCMenuItemFont> CCMenuItemFontRef;
typedef AutoPtr<cocos2d::CCMenuItemImage> CCMenuItemImageRef;
typedef AutoPtr<cocos2d::CCMenuItemLabel> CCMenuItemLabelRef;

#define DEF_FONT_NAME	"Arial"

#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
namespace TextChange{
	static std::string GB2313_UTF_8_TEMP(const char* gb2312)
	{
		wchar_t unicode[10000];
		char utf_8[10000];
		memset(utf_8,0,sizeof(utf_8));
		::MultiByteToWideChar(CP_ACP,0,gb2312,-1,unicode,sizeof(unicode)/sizeof(unicode[0]));
		::WideCharToMultiByte(CP_UTF8,0,unicode,-1,utf_8,sizeof(utf_8)/sizeof(utf_8[0]),0,0);
		return utf_8;
	}
}
#define TXT(a) (TextChange::GB2313_UTF_8_TEMP(a).c_str())
#else
#define TXT(a) (a)
#endif



#endif
