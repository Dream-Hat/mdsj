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
	std::string _name;			//�ǳ�����
	bool _sex;					//�Ա�
	int _level;					//��ǰ�ȼ�
	std::string _title;			//�ƺ�
	int _vipLv;					//VIP�ȼ�
	int _maxHp;					//�������ֵ
	int _hp;					//����ֵ
	
	int _atk;					//������
	int _def;					//������

	int _physical_atk;			//��������
	int _physical_def;			//���������
	
	int _magic_atk;				//����������
	int _magic_def;				//����������

	float _dex;					//������
	float _cri;					//������
	float _block;					//����
	float _agl;					//������
	float _fc;					//ս����

	int _weapon_id;				//װ��1ID
	int _head_id;				//װ��2ID
	int _clothing_id;			//װ��3ID

	int _soul_1_id;				//����1ID
	int _soul_2_id;				//����2ID
	
	int _teamID;				//�����Ŷ�1-3
	int _turnIndex;				//�ֵ��ж������

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
	void setFrontLeft(bool isLeft);//�������ﳯ��
	void setTurnAct(bool isAct);	//���õ�ǰ�غ��Ƿ��ֵ��ж�
	void changeHp(); //Ѫ���仯
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
	bool m_IsBullet;//�ýڵ��Ƿ����ӵ�
	bool m_IsVisualBullet;//��ʾ�Ƿ�������ӵ�
	//��m_IsBullet�ɶԳ��֣���ʾ�ӵ����䷽
	//��m_IsBulletΪTureʱ��m_AtkerΪ�ӵ��ķ�����
	//��m_IsBulletfalsʱ����ֵΪNULL
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
	FightTipType_ATK_Up,//����������
	FightTipType_ATK_Down,
	FightTipType_Def_Up,
	FightTipType_Def_Down,
	FightTipType_Hp_Up,
	FightTipType_Hp_Down,
	FightTipType_Dodge,//����
	FightTipType_Knock,//����
	FightTipType_Parry,//��
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