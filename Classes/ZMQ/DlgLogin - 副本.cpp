#include "DlgLogin.h"
#include "GameDef.h"
#include "GameResource.h"
#include "SceneCover.h"
#include "layerManager.h"
#include "MessageCenter.h"
#include "AllCommandSignal.h"
#include "../ZLL/LanguageManager.h"
#include "../proto_files/LandProto.pb.h"

using namespace com::tiange::mdsj::proto;
DlgLoginMediator::DlgLoginMediator()
{
	_scene = NULL;

	ADD_EVENT_LISTENER(OnDlgOpen,NULL,this,Event::DLGLOGIN_OPEN,DlgLoginMediator)
	ADD_PACK_LISTENER(OnPackage,this,SocketCMDConst::SMSG_LOGIN,DlgLoginMediator)
}

DlgLoginMediator::~DlgLoginMediator()
{
	if (_scene)
	{
		_scene->removeFromParentAndCleanup(true);
	}
}

void DlgLoginMediator::OnPackage(int xy,void* pack)
{
	switch(xy)
	{
	case SocketCMDConst::SMSG_LOGIN:
		{
			LoginResponse login;
			std::string str = *((std::string*)pack);
			login.ParseFromString(str);
			std::string a = login.version();
			LandResult b = login.result();
			switch(b)
			{
			case SUCCESS:
				{
					_scene->layerNum = DLGLOGIN_TAG_XUANFU;
					_scene->setVis(false);
					_scene->m_xuanfuLayout->setVisible(true);
					_scene->m_xuanfuLayout->setTouchEnable(true,true);
				}break;
			case KEY_INVALID:
				{
					_scene->updateMessage("erroe key");
				}break;
			case VERSION_LOWER:
				{

				}break;
			case USER_NOT_EXSIT:
				{

				}break;
			default:
				break;
			}

// 			else
// 			{
// 				UILabel* lbltext = dynamic_cast<UILabel*>(_scene->lay->getChildByName("tipsLabel"));
// 				lbltext->setVisible(true);
// 			}
		}break;
	case SocketCMDConst::SMSG_LOGIN_GETROLELIST:
		{

		}break;
	case SocketCMDConst::SMSG_LOGIN_CREATEROLER:
		{

		}break;
	case SocketCMDConst::SMSG_LOGIN_DELETEROLER:
		{

		}break;
	default:
		break;
	}
}

void DlgLoginMediator::OnDlgOpen( CCObject* sender,int msgid,cocos2d::CCObject* obj)
{
	if (_scene == NULL)
	{
		_scene = DlgLogin::create();
		//_scene->retain();
		_scene->m_Mediator = this;
		//ADD_SCENE_TO_LAYER(_scene.obj(),LayerManager::sceneUILayer);
		CCDirector::sharedDirector()->getRunningScene()->addChild(_scene.obj());
	}
}

void DlgLoginMediator::dispose()
{
	if (_scene)
	{
		_scene->setKeypadEnabled(false);
		//REMOVE_SCENE_FROM_LAYER(_scene)
		_scene->removeFromParentAndCleanup(true);
			//_scene->release();
		_scene = NULL;
	}
}
DlgLogin::DlgLogin() : m_pUILayer(NULL)
	,m_createRoleLayout(NULL)
	,m_layerLayout(NULL)
	,m_otherLayout(NULL)
	,m_roleLayout(NULL)
	,m_regLayout(NULL)
	,m_xuanfuLayout(NULL)
	,m_rolePanel_0(NULL)
	,m_rolePanel_1(NULL)
{
}

DlgLogin::~DlgLogin()
{
	if (m_pUILayer)
	{
		removeFromParentAndCleanup(m_pUILayer);
		m_pUILayer = NULL;
	}
}

bool DlgLogin::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!CCLayer::init());
		m_Mediator = NULL;
		m_pUILayer = UILayer::create();
		m_pUILayer->setTouchPriority(-200);
		m_pUILayer->scheduleUpdate();
		addChild(m_pUILayer);

		Layout* lay = dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile("ui/LoginUI/LoginUI.json"));
		m_pUILayer->addWidget(lay);
		layerNum = DLGLOGIN_TAG_LAYER;
		selRoleP = -1;
		selRoleCreate = -1;
		m_selSevNum = -1;
		m_curRole[0] = 0;
		m_curRole[1] = 1;
		m_createRoleLayout = dynamic_cast<Layout*>(lay->getChildByName("createRolePanel"));
		m_createRoleLayout->setTouchEnable(false,true);
		m_createRoleLayout->setVisible(false);
		m_layerLayout = dynamic_cast<Layout*>(lay->getChildByName("layerPanel"));
		m_layerLayout->setTouchEnable(true,true);
		m_layerLayout->setVisible(true);
		m_xuanfuLayout = dynamic_cast<Layout*>(lay->getChildByName("xuanfuPanel"));
		m_xuanfuLayout->setTouchEnable(false,true);
		m_xuanfuLayout->setVisible(false);
		m_roleLayout = dynamic_cast<Layout*>(lay->getChildByName("rolePanel"));
		m_roleLayout->setTouchEnable(false,true);
		m_roleLayout->setVisible(false);
		m_regLayout = dynamic_cast<Layout*>(lay->getChildByName("regPanel"));
		m_regLayout->setTouchEnable(false,true);
		m_regLayout->setVisible(false);
		m_otherLayout = dynamic_cast<Layout*>(lay->getChildByName("otherPanel"));
		m_otherLayout->setTouchEnable(false,true);
		m_otherLayout->setVisible(false);

		UITextButton* otherBtn = dynamic_cast<UITextButton*>(m_layerLayout->getChildByName("otherBtn"));
		otherBtn->addReleaseEvent(this, coco_releaseselector(DlgLogin::otherBtnCallBack));
		UITextButton* regBtn = dynamic_cast<UITextButton*>(m_layerLayout->getChildByName("regBtn"));
		regBtn->addReleaseEvent(this, coco_releaseselector(DlgLogin::regBtnCallBack));
		UITextButton* loginBtn = dynamic_cast<UITextButton*>(m_layerLayout->getChildByName("loginBtn"));
		loginBtn->addReleaseEvent(this, coco_releaseselector(DlgLogin::loginBtnCallBack));

		UITextButton* returnBtn = dynamic_cast<UITextButton*>(m_otherLayout->getChildByName("returnBtn"));
		returnBtn->addReleaseEvent(this, coco_releaseselector(DlgLogin::closeBtnCallBack));
		UITextButton* loginBtn1 = dynamic_cast<UITextButton*>(m_otherLayout->getChildByName("loginBtn"));
		loginBtn1->addReleaseEvent(this, coco_releaseselector(DlgLogin::loginBtnCallBack));

		UITextButton* returnBtn1 = dynamic_cast<UITextButton*>(m_regLayout->getChildByName("returnBtn"));
		returnBtn1->addReleaseEvent(this, coco_releaseselector(DlgLogin::closeBtnCallBack));
		UITextButton* reg1 = dynamic_cast<UITextButton*>(m_regLayout->getChildByName("regBtn"));
		reg1->addReleaseEvent(this, coco_releaseselector(DlgLogin::regBtnCallBack));

		UITextButton* returnBtn2 = dynamic_cast<UITextButton*>(m_xuanfuLayout->getChildByName("returnBtn"));
		returnBtn2->addReleaseEvent(this, coco_releaseselector(DlgLogin::closeBtnCallBack));
		UITextButton* joinBtn = dynamic_cast<UITextButton*>(m_xuanfuLayout->getChildByName("joinBtn"));
		joinBtn->addReleaseEvent(this, coco_releaseselector(DlgLogin::joinBtnCallBack));
		UIImageView* leftArrow = dynamic_cast<UIImageView*>(m_xuanfuLayout->getChildByName("leftArrow"));
		leftArrow->addReleaseEvent(this,coco_releaseselector(DlgLogin::leftArrowBtnCallBack));
		UIImageView* rightArrow = dynamic_cast<UIImageView*>(m_xuanfuLayout->getChildByName("rightArrow"));
		rightArrow->addReleaseEvent(this,coco_releaseselector(DlgLogin::rightArrowBtnCallBack));
		for (int i = 0; i < 4; i++)
		{
			Layout* xuanfulay = dynamic_cast<Layout*>(m_xuanfuLayout->getChildByName(CCString::createWithFormat("sevPanel_%d",i)->getCString()));
			xuanfulay->addReleaseEvent(this,coco_releaseselector(DlgLogin::selSevCallBack));
		}
		Layout* topPanel = dynamic_cast<Layout*>(m_xuanfuLayout->getChildByName("topPanel"));
		topPanel->addReleaseEvent(this,coco_releaseselector(DlgLogin::selSevCallBack));
		UITextButton* returnBtn3 = dynamic_cast<UITextButton*>(m_roleLayout->getChildByName("returnBtn"));
		returnBtn3->addReleaseEvent(this, coco_releaseselector(DlgLogin::closeBtnCallBack));
		UITextButton* sureBtn = dynamic_cast<UITextButton*>(m_roleLayout->getChildByName("sureBtn"));
		sureBtn->addReleaseEvent(this, coco_releaseselector(DlgLogin::sureBtnCallBack));
		m_delBtn = dynamic_cast<UITextButton*>(m_roleLayout->getChildByName("delBtn"));
		m_delBtn->addReleaseEvent(this, coco_releaseselector(DlgLogin::delBtnCallBack));
		m_delBtn->setVisible(false);
		m_delBtn->disable();
		m_rolePanel_0 = dynamic_cast<Layout*>(m_roleLayout->getChildByName("rolePanel_0"));
		m_rolePanel_1 = dynamic_cast<Layout*>(m_roleLayout->getChildByName("rolePanel_1"));
		UIButton* createBtn1 = dynamic_cast<UIButton*>(m_rolePanel_0->getChildByName("createBtn"));
		createBtn1->addReleaseEvent(this,coco_releaseselector(DlgLogin::createBtnCallBack1));
		UIButton* createBtn2 = dynamic_cast<UIButton*>(m_rolePanel_1->getChildByName("createBtn"));
		createBtn2->addReleaseEvent(this,coco_releaseselector(DlgLogin::createBtnCallBack1));
		UIButton* ImageView0 = dynamic_cast<UIButton*>(m_rolePanel_0->getChildByName("Button"));
		ImageView0->addReleaseEvent(this,coco_releaseselector(DlgLogin::roleimgBtnCallBack));
		UIButton* ImageView1 = dynamic_cast<UIButton*>(m_rolePanel_1->getChildByName("Button"));
		ImageView1->addReleaseEvent(this,coco_releaseselector(DlgLogin::roleimgBtnCallBack));
		
		UITextButton* returnBtn4 = dynamic_cast<UITextButton*>(m_createRoleLayout->getChildByName("returnBtn"));
		returnBtn4->addReleaseEvent(this, coco_releaseselector(DlgLogin::closeBtnCallBack));
		m_createBtn = dynamic_cast<UITextButton*>(m_createRoleLayout->getChildByName("createBtn"));
		m_createBtn->addReleaseEvent(this, coco_releaseselector(DlgLogin::createBtnCallBack));
		m_createBtn->disable();
		UIButton* randBtn = dynamic_cast<UIButton*>(m_createRoleLayout->getChildByName("randBtn"));
		randBtn->addReleaseEvent(this, coco_releaseselector(DlgLogin::randBtnCallBack));
		UIButton* ImageView_00 = dynamic_cast<UIButton*>(m_createRoleLayout->getChildByName("ImageView_0"));
		ImageView_00->addReleaseEvent(this, coco_releaseselector(DlgLogin::roleimgCreatBtnCallBack));
		UIButton* ImageView_11 = dynamic_cast<UIButton*>(m_createRoleLayout->getChildByName("ImageView_1"));
		ImageView_11->addReleaseEvent(this, coco_releaseselector(DlgLogin::roleimgCreatBtnCallBack));

		bRet = true;

	} while (0);

	return bRet;
}

void DlgLogin::closeBtnCallBack(CCObject* pSender)
{
	switch(layerNum){
		case DLGLOGIN_TAG_REG:
		case DLGLOGIN_TAG_OTHER:
		case DLGLOGIN_TAG_XUANFU:
		{
			layerNum = DLGLOGIN_TAG_LAYER;
			setVis(false);
			m_layerLayout->setVisible(true);
			m_layerLayout->setTouchEnable(true,true);
		}break;
		case DLGLOGIN_TAG_ROLE:
			{
				layerNum = DLGLOGIN_TAG_XUANFU;
				setVis(false);
				m_xuanfuLayout->setVisible(true);
				m_xuanfuLayout->setTouchEnable(true,true);

			}break;
		case DLGLOGIN_TAG_CREATEROLE:
			{
				layerNum = DLGLOGIN_TAG_ROLE;
				setVis(false);
				m_roleLayout->setVisible(true);
				m_roleLayout->setTouchEnable(true,true);
				updateRolePanel();
			}break;
	default:
		break;
	}

}


void DlgLogin::onEnter()
{
	CCLayer::onEnter();
	setTouchEnabled(true);
	setKeypadEnabled(true);
}

void DlgLogin::registerWithTouchDispatcher( void )
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -190, true);
}

bool DlgLogin::ccTouchBegan( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent )
{
	return true;
}

void DlgLogin::ccTouchEnded( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent )
{
	
}
void DlgLogin::setVis( bool isVis )
{
	m_createRoleLayout->setVisible(isVis);
	m_createRoleLayout->setTouchEnable(isVis,true);
	m_layerLayout->setVisible(isVis);
	m_layerLayout->setTouchEnable(isVis,true);
	m_otherLayout->setVisible(isVis);
	m_otherLayout->setTouchEnable(isVis,true);
	m_roleLayout->setVisible(isVis);
	m_roleLayout->setTouchEnable(isVis,true);
	m_regLayout->setVisible(isVis);
	m_regLayout->setTouchEnable(isVis,true);
	m_xuanfuLayout->setVisible(isVis);
	m_xuanfuLayout->setTouchEnable(isVis,true);
}

void DlgLogin::otherBtnCallBack( CCObject* pSender )
{
	layerNum = DLGLOGIN_TAG_OTHER;
	setVis(false);
	m_otherLayout->setVisible(true);
	m_otherLayout->setTouchEnable(true,true);
}

void DlgLogin::regBtnCallBack( CCObject* pSender )
{
	if (layerNum == DLGLOGIN_TAG_LAYER)
	{
		layerNum = DLGLOGIN_TAG_REG;
		setVis(false);
		m_regLayout->setVisible(true);
		m_regLayout->setTouchEnable(true,true);
	}
	else
	{
		layerNum = DLGLOGIN_TAG_LAYER;
		setVis(false);
		m_layerLayout->setVisible(true);
		m_layerLayout->setTouchEnable(true,true);
	}

}

void DlgLogin::loginBtnCallBack( CCObject* pSender )
{
	Layout* lay;
	if (layerNum == DLGLOGIN_TAG_LAYER)
	{
		lay = m_layerLayout;
	}
	else if (DLGLOGIN_TAG_OTHER == layerNum)
	{
		lay = m_otherLayout;
	}
	else
	{
		return;
	}
	
	//输入的用户名
	UITextField* inputUser = dynamic_cast<UITextField*>(lay->getChildByName("userName"));;
	//输入的密码
	UITextField* inputPassword= dynamic_cast<UITextField*>(lay->getChildByName("userPassword"));

	LoginRequest login;
	std::string strDat("");
	login.set_user(inputUser->getStringValue());
	login.set_key(inputPassword->getStringValue());
	login.set_version("123");
	login.SerializeToString(&strDat);
	SEND_PACK(SocketCMDConst::CMSG_LOGIN,strDat)
}

void DlgLogin::joinBtnCallBack( CCObject* pSender )
{
	if (-1 == m_selSevNum)
	{
		return;
	}
	layerNum = DLGLOGIN_TAG_ROLE;
	setVis(false);
	m_roleLayout->setVisible(true);
	m_roleLayout->setTouchEnable(true,true);
	UIButton* img0 = dynamic_cast<UIButton*>(m_rolePanel_0->getChildByName("Button"));
	img0->setVisible(true);
	UIButton* btn0 = dynamic_cast<UIButton*>(m_rolePanel_0->getChildByName("createBtn"));
	btn0->disable();
	btn0->setVisible(false);
	UILabel* lab0 = dynamic_cast<UILabel*>(m_rolePanel_0->getChildByName("label_0"));
	lab0->setVisible(true);
	UILabel* lab1 = dynamic_cast<UILabel*>(m_rolePanel_0->getChildByName("label_1"));
	lab1->setVisible(true);

	UIButton* img1 = dynamic_cast<UIButton*>(m_rolePanel_1->getChildByName("Button"));
	img1->setVisible(true);
	UIButton* btn1 = dynamic_cast<UIButton*>(m_rolePanel_1->getChildByName("createBtn"));
	btn1->disable();
	btn1->setVisible(false);
	UILabel* lab2 = dynamic_cast<UILabel*>(m_rolePanel_1->getChildByName("label_0"));
	lab2->setVisible(true);
	UILabel* lab3 = dynamic_cast<UILabel*>(m_rolePanel_1->getChildByName("label_1"));
	lab3->setVisible(true);
}

void DlgLogin::sureBtnCallBack( CCObject* pSender )
{
	//场景切换
	CCTransitionScene *reScene = NULL;

	float t = 1.2f;

	CCScene* runScene = SceneCover::scene();
	reScene = CCTransitionPageTurn::create(t , runScene,false);
	CCDirector::sharedDirector()->replaceScene(reScene);

//	CCScene* pScene = CCDirector::sharedDirector()->getRunningScene();
// 	if (!pScene)
// 	{
// 		CCDirector::sharedDirector()->runWithScene(reScene);
// 	}
// 	else
// 	{
// 		CCDirector::sharedDirector()->replaceScene(reScene);
// 	}
	
	LayerManager::createAllLayer(reScene);

	CCDirector::sharedDirector()->replaceScene(reScene);
}

void DlgLogin::delBtnCallBack( CCObject* pSender )
{
	m_curRole[selRoleP] = -1;
	Layout* lay = dynamic_cast<Layout*>(m_roleLayout->getChildByName(CCString::createWithFormat("rolePanel_%d",selRoleP)->getCString()));

	UIButton* img0 = dynamic_cast<UIButton*>(lay->getChildByName("Button"));
	img0->disable();
	img0->setVisible(false);
	UIButton* btn0 = dynamic_cast<UIButton*>(lay->getChildByName("createBtn"));
	btn0->active();
	btn0->setVisible(true);
	UILabel* lab0 = dynamic_cast<UILabel*>(lay->getChildByName("label_0"));
	lab0->setVisible(false);
	UILabel* lab1 = dynamic_cast<UILabel*>(lay->getChildByName("label_1"));
	lab1->setVisible(false);

	m_delBtn->setVisible(false);
	m_delBtn->disable();
	selRoleP = -1;
}

void DlgLogin::createBtnCallBack1( CCObject* pSender )
{
	UIButton* btn = dynamic_cast<UIButton*>(pSender);
	m_curCreateNum = btn->getTag()%50;
	layerNum = DLGLOGIN_TAG_CREATEROLE;
	setVis(false);
	m_createRoleLayout->setVisible(true);
	m_createRoleLayout->setTouchEnable(true,true);
}

void DlgLogin::createBtnCallBack( CCObject* pSender)
{
	layerNum = DLGLOGIN_TAG_ROLE;
	setVis(false);
	m_roleLayout->setVisible(true);
	m_roleLayout->setTouchEnable(true,true);
	m_curRole[m_curCreateNum] = selRoleCreate;

	Layout* lay = dynamic_cast<Layout*>(m_roleLayout->getChildByName(CCString::createWithFormat("rolePanel_%d",m_curCreateNum)->getCString()));
	UIButton* img0 = dynamic_cast<UIButton*>(lay->getChildByName("Button"));
	if (0 == selRoleCreate)
	{
		img0->setNormalTexture("ui/LoginUI/land_cartoon_male.png",UI_TEX_TYPE_LOCAL);
		img0->setPressedTexture("ui/LoginUI/land_cartoon_male_sel.png",UI_TEX_TYPE_LOCAL);
	}
	else if(1 == selRoleCreate)
	{
		img0->setNormalTexture("ui/LoginUI/land_cartoon_female.png",UI_TEX_TYPE_LOCAL);
		img0->setPressedTexture("ui/LoginUI/land_cartoon_female_sel.png",UI_TEX_TYPE_LOCAL);
	}
	updateRolePanel();
}

void DlgLogin::randBtnCallBack( CCObject* pSender )
{
	UITextField* userName = dynamic_cast<UITextField*>(m_createRoleLayout->getChildByName("createUserName"));
	userName->setText(LanguageManager::shareManager()->getContentByKey("CLUB_SGJH").c_str());
}

void DlgLogin::roleimgBtnCallBack( CCObject* pSender )
{
	UIButton* role_0 = dynamic_cast<UIButton*>(m_rolePanel_0->getChildByName("Button"));
	UIButton* role_1 = dynamic_cast<UIButton*>(m_rolePanel_1->getChildByName("Button"));
	UIButton* lay = dynamic_cast<UIButton*>(pSender);
	int temp = lay->getTag() %50;
	if (selRoleP == temp)
	{
		selRoleP =-1;
		role_0->setFocused(false);
		role_1->setFocused(false);
	}
	else if (1 == temp)
	{
		selRoleP =1;
		role_0->setFocused(false);
		role_1->setFocused(true);
	}
	else if (0 == temp)
	{
		selRoleP =0;
		role_0->setFocused(true);
		role_1->setFocused(false);
	}

	if (-1 == selRoleP)
	{
		m_delBtn->setVisible(false);
		m_delBtn->disable();
	}
	else
	{
		m_delBtn->setVisible(true);
		m_delBtn->active();
	}
}

void DlgLogin::roleimgCreatBtnCallBack( CCObject* pSender )
{
	UIButton* role_0 = dynamic_cast<UIButton*>(m_createRoleLayout->getChildByName("ImageView_0"));
	UIButton* role_1 = dynamic_cast<UIButton*>(m_createRoleLayout->getChildByName("ImageView_1"));
	UIButton* lay = dynamic_cast<UIButton*>(pSender);
	int temp = lay->getTag() %50;
	if (selRoleCreate == temp)
	{
		selRoleCreate =-1;
		role_0->setFocused(false);
		role_1->setFocused(false);
	}
	else if (1 == temp)
	{
		selRoleCreate =1;
		role_0->setFocused(false);
		role_1->setFocused(true);
	}
	else if (0 == temp)
	{
		selRoleCreate =0;
		role_0->setFocused(true);
		role_1->setFocused(false);
	}

	if (-1 == selRoleCreate)
	{
		m_createBtn->disable();
	}
	else
	{
		m_createBtn->active();
	}
}

void DlgLogin::loadNextLayerEffect(int direction)
{
	m_xuanfuLayout->setVisible(true);
	m_xuanfuLayout->setTouchEnable(false,true);
	Layout* selSev = dynamic_cast<Layout*>(m_xuanfuLayout->getChildByName("selSevPanel"));
	m_directionX = direction;
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCSize laySize = selSev->getSize();
	CCPoint layPoint = selSev->getPosition();
	CCRenderTexture* rt = CCRenderTexture::create(winSize.width, winSize.height);
	rt->begin();
	selSev->getRenderer()->visit();
	rt->end();
	CCSprite* retval =  CCSprite::createWithTexture(rt->getSprite()->getTexture(),selSev->getRect());
	retval->setTag(Z_Max);
	retval->setPosition(ccp(0,layPoint.y));
	retval->setAnchorPoint(ccp(0,0));
	retval->setFlipY(true);
	addChild(retval,0);
	selSev->setPosition(ccp(winSize.width * (0-direction),layPoint.y));
	selSev->setAnchorPoint(ccp(0,0));
	for (int i = 0; i < 4;i++)
	{
		Layout* selSevLay = dynamic_cast<Layout*>(m_xuanfuLayout->getChildByName(CCString::createWithFormat("sevPanel_%d",i)->getCString()));
		selSevLay->setBackGroundColor(ccc3(25,13,9));
	}
	//结束且释放  
	CC_SAFE_DELETE(rt);

	CCMoveTo* r1 = CCMoveTo::create(0.9f,ccp(winSize.width*direction,layPoint.y));
	CCMoveTo* r2 = CCMoveTo::create(0.9f,ccp(0,layPoint.y));
	CCCallFunc* callFEnd =CCCallFunc::create(this,callfunc_selector(DlgLogin::moveEffectEndCallBack));
	retval->runAction(CCSequence::create(r1,NULL));
	selSev->runAction(CCSequence::create(r2,callFEnd,NULL));
}

void DlgLogin::leftArrowBtnCallBack( CCObject* pSender )
{
	loadNextLayerEffect(1);
}

void DlgLogin::rightArrowBtnCallBack( CCObject* pSender )
{
	loadNextLayerEffect(-1);
}

void DlgLogin::moveEffectEndCallBack()
{
	m_xuanfuLayout->setTouchEnable(true,true);
	this->removeChildByTag(Z_Max);
	for (int i = 0; i < 4;i++)
	{
		Layout* selSevLay = dynamic_cast<Layout*>(m_xuanfuLayout->getChildByName(CCString::createWithFormat("sevPanel_%d",i)->getCString()));
		selSevLay->setBackGroundColor(ccc3(25,13,9));
	}
}

void DlgLogin::selSevCallBack(CCObject* pSender)
{
	Layout* lay = dynamic_cast<Layout*>(pSender);
	m_selSevNum = lay->getTag() %80;
	if (5 == m_selSevNum)
	{
		for (int i = 0; i < 4;i++)
		{
			Layout* selSevLay = dynamic_cast<Layout*>(m_xuanfuLayout->getChildByName(CCString::createWithFormat("sevPanel_%d",i)->getCString()));
			selSevLay->setBackGroundColor(ccc3(25,13,9));
		}
		Layout* topPanel = dynamic_cast<Layout*>(m_xuanfuLayout->getChildByName("topPanel"));
		topPanel->setColor(ccc3(23,23,56));
	}
	else
	{
		Layout* topPanel = dynamic_cast<Layout*>(m_xuanfuLayout->getChildByName("topPanel"));
		topPanel->setColor(ccc3(255,255,255));
		for (int i = 0; i < 4;i++)
		{
			Layout* selSevLay = dynamic_cast<Layout*>(m_xuanfuLayout->getChildByName(CCString::createWithFormat("sevPanel_%d",i)->getCString()));
			selSevLay->setBackGroundColor(ccc3(25,13,9));

			if (i == m_selSevNum)
			{
				selSevLay->setBackGroundColor(ccc3(92,92,76));
			}
		}
	}
}

void DlgLogin::updateRolePanel()
{
	
	for (int i  = 0; i < 2;i++)
	{
		bool isvis;
		Layout* lay = dynamic_cast<Layout*>(m_roleLayout->getChildByName(CCString::createWithFormat("rolePanel_%d",i)->getCString()));
		if (-1 == m_curRole[i])
		{
			isvis = false;
		}
		else
		{
			isvis = true;
		}

		UIButton* img0 = dynamic_cast<UIButton*>(lay->getChildByName("Button"));
		UITextButton* btn0 = dynamic_cast<UITextButton*>(lay->getChildByName("createBtn"));
		if (isvis)
		{
			img0->active();
			btn0->disable();
		}
		else
		{
			img0->disable();
			btn0->active();
		}
		img0->setVisible(isvis);
		btn0->setVisible(!isvis);
		UILabel* lab0 = dynamic_cast<UILabel*>(lay->getChildByName("label_0"));
		lab0->setVisible(isvis);
		UILabel* lab1 = dynamic_cast<UILabel*>(lay->getChildByName("label_1"));
		lab1->setVisible(isvis);
	}
}

void DlgLogin::updateMessage( const char *label )
{
	Layout* lay;
	if (layerNum == DLGLOGIN_TAG_LAYER)
	{
		lay = m_layerLayout;
	}
	else if (DLGLOGIN_TAG_OTHER == layerNum)
	{
		lay = m_otherLayout;
	}
	else
	{
		return;
	}
	UILabel* lbltext = dynamic_cast<UILabel*>(lay->getChildByName("tipsLabel"));
	lbltext->setVisible(true);
}

void DlgLogin::onExit()
{
	CCLayer::onExit();
	REMOVE_EVENT_LISTENER(NULL,this,Event::DLGLOGIN_OPEN)
}
