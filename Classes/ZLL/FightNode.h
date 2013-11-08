#ifndef __MDSJ_ZLL_FIGHTNODE_H__
#define __MDSJ_ZLL_FIGHTNODE_H__
#include "cocos2d.h"
#include "FightNode.h"
#include <string>
#include "Define.h"
class FightElementDataNode
{
public:
	int _id;					//ID
	std::string _name;			//昵称姓名
	bool _sex;					//性别
	int _level;					//当前等级
	std::string _title;			//称号
	int _vipLv;					//VIP等级
	int _maxHp;					//最大生命值
	int _hp;					//生命值
	
	int _atk;					//攻击力
	int _def;					//防御力

	int _physical_atk;			//物理攻击力
	int _physical_def;			//物理防御力
	
	int _magic_atk;				//法术攻击力
	int _magic_def;				//法术防御力

	float _dex;					//命中率
	float _cri;					//暴击率
	float _block;					//格挡率
	float _agl;					//闪避率
	float _fc;					//战斗力

	int _weapon_id;				//装备1ID
	int _head_id;				//装备2ID
	int _clothing_id;			//装备3ID

	int _soul_1_id;				//魂魄1ID
	int _soul_2_id;				//魂魄2ID
	
	int _teamID;				//所属团队1-3
	int _turnIndex;				//轮到行动的序号

	cocos2d::CCPoint _startPoint;//
	FightElementNodeType _nodeType;//
};

class FightElementNode:public cocos2d::CCNode
{
public: 
	FightElementNode();
	~FightElementNode();
	virtual bool init();
	static FightElementNode* create(bool isBullet);

	void initWithNode(FightElementDataNode& _node,int _turnID);
	void initBullet();
	cocos2d::CCRect getMainFrameRect();
	void setFlipX(bool isFilpX);
	void setFlipY(bool isFilpY);
	void setFrontLeft(bool isLeft);//设置人物朝向
	void setTurnAct(bool isAct);	//设置当前回合是否轮到行动
	void changeHp(); //血量变化
protected:
	void setNodeElementPosition();
	void setElementDataDisplay();
public:
	void setTurnID(int _turnId){m_TurnId=_turnId;}
	int getTurnID(){return m_TurnId;}
	bool getFrontleft(){return m_FrontLeft;}
	int getElementTurnIndex(){return m_data._turnIndex;}
public:
	cocos2d::CCSprite* m_MainSprite;
	cocos2d::CCSprite* m_SpHpEmpty;
	cocos2d::CCSprite* m_SpHp;
	cocos2d::CCSprite* m_SpLevel;
	cocos2d::CCLabelAtlas* m_LbALvNum;
	cocos2d::CCLabelTTF* m_LbName;
	cocos2d::CCSprite* m_SpTurn;

public:
	bool m_IsBullet;//该节点是否是子弹
	bool m_IsVisualBullet;//表示是否虚拟的子弹
	//与m_IsBullet成对出现，表示子弹发射方
	//当m_IsBullet为Ture时，m_Atker为子弹的发射者
	//当m_IsBulletfals时，该值为NULL
	FightElementNode* m_Atker;
	FightElementDataNode m_data;
protected:
	
	int m_TurnId;
	bool m_Isinited;
	bool m_FrontLeft;
};


enum FightTipType
{
	FightTipType_NULL=0,
	FightTipType_ATK_Up,//攻击力上升
	FightTipType_ATK_Down,
	FightTipType_Def_Up,
	FightTipType_Def_Down,
	FightTipType_Hp_Up,
	FightTipType_Hp_Down,
	FightTipType_Dodge,//闪避
	FightTipType_Knock,//暴击
	FightTipType_Parry,//格挡
};

class FightTipNode:public cocos2d::CCNode
{
public:
	FightTipNode();
	~FightTipNode();
	virtual bool init();
	static FightTipNode* create(FightTipType _type,int _valueNum);
protected:
	void initNode();
	void setElementPos();
protected:
	cocos2d::CCSprite* m_SpType;
	cocos2d::CCLabelAtlas* m_LbValue;

	FightTipType m_Type;
	int m_Value;
};
#endif