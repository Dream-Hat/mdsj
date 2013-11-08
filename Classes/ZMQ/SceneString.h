#ifndef __SceneString_H__
#define __SceneString_H__

#include "cocos2d.h"

#include "SimpleAudioEngine.h"

USING_NS_CC;

class SceneString : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();

	static SceneString* show();
    
	void setText(const char* pContent);

    // a selector callback
    void menuCloseCallback(CCObject* pSender);


    // implement the "static node()" method manually
    CREATE_FUNC(SceneString);

private:
	CCLabelTTF*			m_lblText;
};

#endif  // __SceneCover_H__