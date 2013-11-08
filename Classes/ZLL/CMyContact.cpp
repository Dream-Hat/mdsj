#include "CMyContact.h"
#include "FightNode.h"
void CMyContactListener::BeginContact(b2Contact* contact)
{
	if (contact)
	{
// 		FightElementNode* nodeA=(FightElementNode*)contact->GetFixtureA()->GetBody()->GetUserData();
// 		FightElementNode* nodeB=(FightElementNode*)contact->GetFixtureB()->GetBody()->GetUserData();
// 		//如果是虚拟子弹，则不加入碰撞
// 		if (nodeA!=NULL)
// 		{
// 			if (nodeA->m_IsBullet&&nodeA->m_IsVisualBullet)
// 			{//NodeA 是虚拟子弹
// 				B2_NOT_USED(contact);
// 				return;
// 			}
// 		}
// 		if (nodeB!=NULL)
// 		{
// 			if (nodeB->m_IsBullet&&nodeB->m_IsVisualBullet)
// 			{//NodeB是虚拟子弹
// 				B2_NOT_USED(contact);
// 				return;
// 			}
// 		}
 		CMyContact myContact;
 		myContact.fixtureA=contact->GetFixtureA();
		myContact.fixtureB=contact->GetFixtureB();
		m_ContactList.push_back(myContact);
	
	}
	B2_NOT_USED(contact); 
}

void CMyContactListener::EndContact(b2Contact* contact)
{
	m_ContactList.clear();
	B2_NOT_USED(contact); 
}

void CMyContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
	B2_NOT_USED(contact);
	B2_NOT_USED(oldManifold);
}

void CMyContactListener::PostSolve(const b2Contact* contact, const b2ContactImpulse* impulse)
{
	B2_NOT_USED(contact);
	B2_NOT_USED(impulse);
}
