/*///////////////////////////////////////////////////////////////////////////////////
//提供二进制数据流
//bios			基类
//	biostream	输入流
//	biostream	输出流
//biosexception	异常类
//
//提供对所有 C 固有类型的 << 和 >> 操作符重载
//其中对char* 的写入方式与MFC的CString兼容。在流中当第一个字节的无符号值小于255时,该值
//表示其后字符串的字节长度；当流中第一个字节的无符号值等于255时,则其后的unsigned short
//值为字符串长度，在该unsigned short之后为字符串内容。当unsigned short==0xffff,则其后的
//四字节值(unsigned long)为字符串长度，在unsigned long之后是字符串内容.
//
//bios 提供:
//  attach方法 将流绑定到内存缓冲区上
//  length方法 获得流当前已使用的长度
//  avail方法  获得缓冲区当前可用的长度
//
//biostream 提供:
//  write方法    将数据写入缓冲区
//  seekp方法	   在流中定位
//  
//biostream 提供:
//  read方法	   从流中读数据
//  seekg方法    在流中定位
// peek         从流中预读一个字节（不影响流的当前位置）
//
//biosexception
// 提供两个枚举常量
//     end;	   从流里读数据时读到流的缓冲区末尾 由biostream.read 抛出	
//	 overflow: 往流里写数据时超出流的缓冲区末尾 由biostream.write 抛出
////////////////////////////////////////////////////////////////////////////////////*/


#ifndef _WIN32TOOLS_BIOSTREAM_H
#define	_WIN32TOOLS_BIOSTREAM_H

#define DEF_BIG_ENDIAN false
#define STRING_0_STREAM  0
#define STRING_2_STREAM  2
#define STRING_C_STREAM  3
#define STRING_USE		 STRING_2_STREAM

#define STRING_MAXLEN	1024

#include <cstring>
#include <string>
namespace Win32Tools {

class biosexception 
{
public:
	enum BIOSEXCEPTION_CODE {
		none = 0,
		end = 1,		//从流里读数据时读到流的缓冲区末尾
		overflow = 2,	//往流里写数据时超出流的缓冲区末尾
		stringtoolong = 3,	//读标准C字符串时超长
		streamdirecterror//方向错误
	};

	BIOSEXCEPTION_CODE	m_cause;

	biosexception(BIOSEXCEPTION_CODE cause = none):m_cause(cause){}
};

class biostream 
{
	bool mendian;
protected:
	char*	pbase;	//缓冲区的头指针
	char*	pcurr;	//缓冲区中的当前指针
	char*	pend;	//缓冲区的尾指针
	int		m_mode; //该流的模式 in(1) or out(2) fix(0)
	bool isneedfree;
public:
	void endian(bool b){mendian = b;}
	biostream():pbase(0),pcurr(0),pend(0),m_mode(0),isneedfree(false),mendian(DEF_BIG_ENDIAN){
	}
	biostream(char* pch,long nLength):pbase(pch),pcurr(pch),isneedfree(false),m_mode(0),mendian(DEF_BIG_ENDIAN){
		pend = pch+nLength;
	}
	biostream(long nLength):isneedfree(true),m_mode(0),mendian(DEF_BIG_ENDIAN){
		pbase = new char[nLength];
		pcurr = pbase;
		pend = pbase+nLength;
	}
	void attach(char* pch,long nLength) {//将流关联到一个缓冲区//pch 缓冲区的开始地址//nLength: 缓冲区的大小
		reset();
		isneedfree = false;
		pbase = pcurr = pch;
		pend = pbase+nLength;
	}
	void alloc(long nLength) {//将流关联到一个缓冲区//pch 缓冲区的开始地址//nLength: 缓冲区的大小
		reset();
		isneedfree = true;
		pbase = new char[nLength];
		pcurr = pbase;
		pend = pbase+nLength;
	}
	~biostream() {
		reset();
	}
	void setmode(int mode){
		m_mode = mode==1?1:(mode==2?2:0);
	}

	//将流与缓冲区脱离
	void reset() { 
		if(isneedfree&&pbase!=0)
			delete [] pbase;
		isneedfree = false;
		pbase = pcurr = pend = 0 ;
	}

	//得到缓冲区剩余可用的长度
	//seek到不同的位置会影响该函数结果
	long avail() const 
	{ 
		long ret = (long)(pend - pcurr); 
		return ret;
	}

	//得到缓冲区被使用的长度
	//seek到不同的位置会影响该函数结果
	long length() const 
	{ 
		long ret= (long)(pcurr - pbase); 
		return ret;
	}

	char* buffer() const { 
		return pbase; 
	}

	//offset: 移动的字节数
	//seekmode: 从哪个位置开始移动
	biostream& seek(long offset,int seekmode) {
		if(m_mode==0)return *((biostream*)0);
			//throw biosexception(biosexception::streamdirecterror);
		switch(seekmode)
		{
		case 1:
			pcurr = pbase+offset;
			break;
		case -1:
			pcurr = pend+offset;
			break;
		default:
			pcurr += offset;
			break;
		}
		if(avail() < 0 || avail() > (pend-pbase))return *((biostream*)0);
			//throw biosexception(m_mode==2?(biosexception::overflow):(biosexception::end));
		return *this;
	}


	//向输出流写入内容
	//p 要写入的内容
	//len p 的长度

	biostream& write(const char* p,long len)
	{
		if(m_mode==0)m_mode=2;
		else if(m_mode!=2)return *((biostream*)0);
			//throw biosexception(biosexception::streamdirecterror);
		if(avail() < len)return *((biostream*)0);
			//throw biosexception(biosexception::overflow);
		switch(len)
		{
		case 1:
			*pcurr = *p;
			break;
		case 2:
			*((unsigned short*)((unsigned char*)pcurr)) = *((unsigned short*)((unsigned char*)p));
			break;
		case 4:
			*((unsigned long*)((unsigned char*)pcurr)) = *((unsigned long*)((unsigned char*)p));
			break;
		default:
			memcpy(pcurr,p,len);
			break;
		}
		pcurr+=len;
		return *this;
	}

	inline biostream& operator<<(char);
	inline biostream& operator<<(unsigned char);
	inline biostream& operator<<(short);
	inline biostream& operator<<(unsigned short);
	inline biostream& operator<<(int);
	inline biostream& operator<<(unsigned int);
	inline biostream& operator<<(long);
	inline biostream& operator<<(unsigned long);
	inline biostream& operator<<(long long);
	inline biostream& operator<<(unsigned long long);
	inline biostream& operator<<(float);
	inline biostream& operator<<(double);
	inline biostream& operator<<(bool);
	inline biostream& operator<<(const char*);
	inline biostream& operator<<(const unsigned char*);
	//inline biostream& writecstring(const char* p);//输出字符串最后补\0
	inline biostream& operator<<(const std::string);

	//从输入流中读len长度的字节放入p中
    biostream& read(char* p,long len) {
		if(m_mode==0)m_mode=1;
		else if(m_mode!=1)return *((biostream*)0);
			//throw biosexception(biosexception::streamdirecterror);
		if(avail() < len)return *((biostream*)0);
			//throw biosexception(biosexception::end);
		switch(len)
		{
		case 1:
			*p = *pcurr;
			break;
		case 2:
			*((unsigned short*)((unsigned char*)p)) = *((unsigned short*)((unsigned char*)pcurr));
			break;
		case 4:
			*((unsigned long*)((unsigned char*)p)) = *((unsigned long*)((unsigned char*)pcurr));
			//unsigned long aaa=*((unsigned long*)((unsigned char*)p));
			break;
		default:
			memcpy(p,pcurr,len);
			break;
		}
		pcurr += len;
		return *this;
	}

	//预读下一个字节
	int peekbyte() {
		if(m_mode==0)m_mode=1;
		else if(m_mode!=1)return -1;
			//throw biosexception(biosexception::streamdirecterror);
		if(pcurr>=pend)
		{
			return -1;
			//throw biosexception(biosexception::end);
		}
		else
			return static_cast<int>(*(pcurr));
	}

	int peeklength_1_3_7(){
		if(m_mode==0)m_mode=1;
		else if(m_mode!=1)return -1;
		if(pcurr>=pend)
		{
			return -1;
			//throw biosexception(biosexception::end);
		}
		
		int seeks=0;
		unsigned char blen;
		(*this) >> blen;seeks--;
		if(blen < 0xff){
			if(seeks)this->seek(seeks,0);return blen;
		}
		else
		{
			if(pcurr+3>=pend){
				if(seeks)this->seek(seeks,0);return -1;
			}
			else
			{
				unsigned short slen;
				(*this) >> slen;seeks-=2;
				if(slen<0xffff){
					if(seeks)this->seek(seeks,0);return blen;
				}
				else
				{
					if(pcurr+7>=pend){
						if(seeks)this->seek(seeks,0);return -1;
					}
					else
					{
						unsigned int ilen;
						(*this) >> ilen;seeks-=4;
						if(seeks)this->seek(seeks,0);return ilen;
					}
				}
			}
		}
	}

	inline biostream& operator>>(char&);
	inline biostream& operator>>(unsigned char&);
	inline biostream& operator>>(short&);
	inline biostream& operator>>(unsigned short&);
	inline biostream& operator>>(int&);
	inline biostream& operator>>(unsigned int&);
	inline biostream& operator>>(long&);
	inline biostream& operator>>(unsigned long&);
	inline biostream& operator>>(long long&);
	inline biostream& operator>>(unsigned long long&);
	inline biostream& operator>>(float&);
	inline biostream& operator>>(double&);
	inline biostream& operator>>(bool&);
	inline biostream& operator>>(char*);
	inline biostream& operator>>(unsigned char*);
	//inline biostream& readcstring(char* p,unsigned int maxsize);//读一个字符串直到碰到\0
	inline biostream& operator>>(std::string&);
};
typedef biostream bistream;
typedef biostream bostream;

inline biostream& biostream::operator<<(char _c) { 
	write((const char*)&_c,sizeof(char)); 
	return *this; 
}
inline biostream& biostream::operator<<(unsigned char _c) {
	write((const char*)&_c,sizeof(unsigned char));
	return *this;
}
inline biostream& biostream::operator<<(short _s) {
	write((const char*)&_s,sizeof(short));
	return *this;
}
inline biostream& biostream::operator<<(unsigned short _s) {
	write((const char*)&_s,sizeof(unsigned short));
	return *this;
}
inline biostream& biostream::operator<<(int _i) {
	write((const char*)&_i,sizeof(int));
	return *this;
}
inline biostream& biostream::operator<<(unsigned int _i) {
	write((const char*)&_i,sizeof(unsigned int));
	return *this;
}
inline biostream& biostream::operator<<(long _l) {
	write((const char*)&_l,sizeof(long));
	return *this;
}
inline biostream& biostream::operator<<(unsigned long _l) {
	write((const char*)&_l,sizeof(unsigned long));
	return *this;
}
inline biostream& biostream::operator<<(long long _i64)
{
	write((const char*)&_i64,sizeof(long long));
	return *this;
}
inline biostream& biostream::operator<<(unsigned long long _i64)
{
	write((const char*)&_i64,sizeof(unsigned long long));
	return *this;
}
inline biostream& biostream::operator<<(float _f) {
	write((const char*)&_f,sizeof(float));
	return *this;
}
inline biostream& biostream::operator<<(double _d) {
	write((const char*)&_d,sizeof(double));
	return *this;
}
inline biostream& biostream::operator<<(bool _b) {
	write((const char*)&_b,sizeof(bool));
	return *this;
}
inline biostream& biostream::operator<<(const char* _s) {
#if STRING_USE==STRING_2_STREAM
	#ifdef WIN_ANSI_TO_UTF8_WRITE
		char utf_8[10240]={0};
		wchar_t unicode[10240];
		::MultiByteToWideChar(CP_ACP,0,_s,-1,unicode,sizeof(unicode)/sizeof(unicode[0]));
		::WideCharToMultiByte(CP_UTF8,0,unicode,-1,utf_8,sizeof(utf_8)/sizeof(utf_8[0]),0,0);
		int  slen = (int)strlen(utf_8);
		operator<<((unsigned short)slen);
		write((const char*)utf_8,slen);
		return *this;
	#else
		int  slen = (int)strlen(_s);
		operator<<((unsigned short)slen);
		write((const char*)_s,slen);
		return *this;
	#endif
#elif STRING_USE==STRING_C_STREAM
	size_t len = strlen(p)+1;
	if(avail() < (long)len)return *((biostream*)0);
		//throw biosexception(biosexception::overflow);
	memcpy(pcurr,p,len);
	pcurr += len;
	return *this;
#else
	int  slen = (int)strlen(_s);
	if(slen < 255)
	{
		operator<<((unsigned char)slen);
	}
	else if(slen < 0xfffe)
	{
		operator<<((unsigned char)0xff);
		operator<<((unsigned short)slen);
	}
	else
	{
		operator<<((unsigned char)0xff);
		operator<<((unsigned short)0xffff);
		operator<<((unsigned long)slen);
	}
	write((const char*)_s,slen);
	return *this;
#endif
}
inline biostream& biostream::operator<<(const unsigned char* _s) {
	return operator<<((const char*)_s);
}
/*inline biostream& biostream::writecstring(const char* p)
{
	size_t len = strlen(p)+1;
	if(avail() < (long)len)return *((biostream*)0);
		//throw biosexception(biosexception::overflow);
	memcpy(pcurr,p,len);
	pcurr += len;
	return *this;
}*/

inline biostream& biostream::operator<<(std::string _s)
{
	return operator<<((const char*)(_s.c_str()));
}


inline biostream& biostream::operator>>(char& _c) {
	read(&_c,sizeof(char));
	return *this;
}
inline biostream& biostream::operator>>(unsigned char& _c) {
	read((char*)&_c,sizeof(unsigned char));
	return *this;
}
inline biostream& biostream::operator>>(short& _s) {
	read((char*)&_s,sizeof(short));
	return *this;
}
inline biostream& biostream::operator>>(unsigned short& _s) {
	read((char*)&_s,sizeof(unsigned short));
	return *this; 
}
inline biostream& biostream::operator>>(int& _i) {
	read((char*)&_i,sizeof(int));
	return *this;
}
inline biostream& biostream::operator>>(unsigned int& _i) {
	read((char*)&_i,sizeof(unsigned int));
	return *this;
}

inline biostream& biostream::operator>>(long& _l) {
	read((char*)&_l,sizeof(long));
	return *this;
}
inline biostream& biostream::operator>>(unsigned long& _l) {
	read((char*)&_l,sizeof(unsigned long));
	return *this;
}
inline biostream& biostream::operator>>(long long& _i64) {
	read((char*)&_i64,sizeof(long long));
	return *this;
}
inline biostream& biostream::operator>>(unsigned long long& _i64)
{
	read((char*)&_i64,sizeof(unsigned long long));
	return *this;
}
inline biostream& biostream::operator>>(float& _f) {
	read((char*)&_f,sizeof(float));
	return *this;
}
inline biostream& biostream::operator>>(double& _d) {
	read((char*)&_d,sizeof(double));
	return *this;
}
inline biostream& biostream::operator>>(bool& _b) {
	read((char*)&_b,sizeof(bool));
	return *this;
}
inline biostream& biostream::operator>>(char* _s) {
#if STRING_USE==STRING_2_STREAM
	unsigned short wlen;
	operator>>(wlen);
	return read(_s,wlen);
#elif STRING_USE==STRING_C_STREAM
	int av = this->avail();
	int currsize = av<(int)maxsize?av:(int)maxsize;
	char* ptend = (char*)memchr(pcurr,0,currsize);
	if(ptend == NULL)
	{
		if(avail() >= (int)maxsize)return *((biostream*)0);
			//throw biosexception(biosexception::stringtoolong);
		else return *((biostream*)0);
			//throw biosexception(biosexception::end);
	}
	memcpy(p,pcurr,ptend-pcurr+1);
	pcurr = (ptend+1);
	return *this;
#else
	unsigned char blen;
	operator>>(blen);
	if(blen < 0xff)
		return read(_s,blen);

	unsigned short wlen;
	operator>>(wlen);
	if(wlen < 0xfffe)
		return read(_s,wlen);

	unsigned long dwlen;
	operator>>(dwlen);
	return read(_s,dwlen);
#endif
}
inline biostream& biostream::operator>>(unsigned char* _s) {
	return operator>>((char*)_s);
}

/*inline biostream& biostream::readcstring(char* p,unsigned int maxsize)
{
	int av = this->avail();
	int currsize = av<(int)maxsize?av:(int)maxsize;
	char* ptend = (char*)memchr(pcurr,0,currsize);
	if(ptend == NULL)
	{
		if(avail() >= (int)maxsize)return *((biostream*)0);
			//throw biosexception(biosexception::stringtoolong);
		else return *((biostream*)0);
			//throw biosexception(biosexception::end);
	}
	memcpy(p,pcurr,ptend-pcurr+1);
	pcurr = (ptend+1);
	return *this;
}*/

inline biostream& biostream::operator>>(std::string& _s) {
	char str[STRING_MAXLEN]={0};
	operator>>(str);
	_s = str;
	return *this;
}

} // end of namespace Win32Tools

#endif
