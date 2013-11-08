#include "Facade.h"

static Facade *s_sharedFacade = NULL;

Facade *Facade::instance(void)
{
	if (!s_sharedFacade)
	{
		s_sharedFacade = new Facade();
	}
	return s_sharedFacade;
}

/** Destroys the single instance of MessageCenter. */
void Facade::purgeFacade(void)
{

	CC_SAFE_RELEASE_NULL(s_sharedFacade);

}
Facade::Facade()
{
	
}

void Facade::clear()
{
	map<int,CCObject*>::iterator iter;
	for (iter=mediatorVector.begin();iter!=mediatorVector.end();iter++)
	{
		CCObject* r = iter->second;
		r->release();
	}
	mediatorVector.clear();
}

Facade::~Facade()
{
	clear();
}
void Facade::addMediator(int mark,CCObject* mediator)
{
	mediatorVector.insert(pair<int,CCObject*>(mark,mediator));
}
void Facade::newMediator()
{
	
	
	
	
	
}
CCObject*  Facade::getMediator(int mark)
{
	if (mediatorVector.find(mark) != mediatorVector.end())
		return mediatorVector.find(mark)->second;
	return NULL;
}