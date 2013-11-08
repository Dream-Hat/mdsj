#ifndef __MDSJ_ZLL_CMYCONTACT_H__
#define __MDSJ_ZLL_CMYCONTACT_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include <vector>

class CMyContact
{
public:
	b2Fixture* fixtureA;
	b2Fixture* fixtureB;
};

class CMyContactListener:public b2ContactListener
{
	virtual void BeginContact(b2Contact* contact);
	virtual void EndContact(b2Contact* contact);
	virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
	virtual void PostSolve(const b2Contact* contact, const b2ContactImpulse* impulse);

public:
	std::vector<CMyContact> m_ContactList;
};
#endif