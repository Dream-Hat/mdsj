#include "AlertDialog.h"
#include "layerManager.h"

class CMLabelTTF : public CCLabelTTF
{
public:
	static std::vector<CMLabelTTF*> s_pops;
	static bool s_inpoping;
	void actionend(){
		removeFromParentAndCleanup(true);
	}

	void newpop(){
		if(s_pops.size()>0){
			s_pops[0]->pop();
			s_pops[0]->release();
			s_pops.erase(s_pops.begin());
		}else{
			s_inpoping = false;
		}
	}

	void pop(){
		float scale = 1.0f;
		if(s_pops.size()>1){
			scale = 0.75f/(s_pops.size()-1);
		}
		LayerManager::centerBCLayer->addChild(this);
		CCFiniteTimeAction* ps1 = CCSpawn::create(CCScaleTo::create(0.2f*scale,1),CCMoveBy::create(0.2f,ccp(0,-20)),0);
		CCFiniteTimeAction* ps2 = CCSpawn::create(CCFadeOut::create(1*scale),CCMoveBy::create(1,ccp(0,80)),0);
		runAction(CCSequence::create(ps1,
			CCDelayTime::create(0.5f*scale),
			CCMoveBy::create(0.5f*scale,ccp(0,40)),
			CCCallFunc::create(this,callfunc_selector(CMLabelTTF::newpop)),
			ps2,
			CCCallFunc::create(this,callfunc_selector(CMLabelTTF::actionend)),
			0));
	}
};

std::vector<CMLabelTTF*> CMLabelTTF::s_pops;
bool CMLabelTTF::s_inpoping = false;

void Pop::popText(const char* text,cocos2d::ccColor3B cr)
{
	CMLabelTTF* pLabel = new CMLabelTTF();pLabel->autorelease();//CCLabelTTF::create(text,DEF_FONT_NAME,20);
	pLabel->initWithString(text,DEF_FONT_NAME,36);
	pLabel->setColor(cr);
	pLabel->setPosition(ccp(480,550));
	pLabel->setScale(0.2f);
	if(!CMLabelTTF::s_inpoping){
		CMLabelTTF::s_inpoping = true;
		pLabel->pop();
	}else{
		CMLabelTTF::s_pops.push_back(pLabel);
		pLabel->retain();
	}
}

void Pop::popTextByPosition( const char* text,cocos2d::ccColor3B cr,const cocos2d::CCPoint &pos )
{
	CMLabelTTF* pLabel = new CMLabelTTF();pLabel->autorelease();//CCLabelTTF::create(text,DEF_FONT_NAME,20);
	pLabel->initWithString(text,DEF_FONT_NAME,36);
	pLabel->setColor(cr);
	pLabel->setPosition(pos);
	pLabel->setScale(0.4f);
	if(!CMLabelTTF::s_inpoping){
		CMLabelTTF::s_inpoping = true;
		pLabel->pop();
	}else{
		CMLabelTTF::s_pops.push_back(pLabel);
		pLabel->retain();
	}
}
