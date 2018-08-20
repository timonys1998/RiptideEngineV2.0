#include "MiniginPCH.h"
#include "SubjectComponent.h"
#include "algorithm"


SubjectComponent::SubjectComponent()
{
}


SubjectComponent::~SubjectComponent()
{
}

void SubjectComponent::Attach(std::shared_ptr<ObserverComponent> observer)
{
	m_spObservers.push_back(observer);
}

void SubjectComponent::Detach(std::shared_ptr<ObserverComponent> observer)
{
	m_spObservers.erase(std::remove(m_spObservers.begin(), m_spObservers.end(), observer), m_spObservers.end());
}

void SubjectComponent::Notify(std::shared_ptr<GameObject> entity, Event e)
{
	//Loop over all observers and update them accordingly
	for(auto o : m_spObservers)
	{
		o->OnNotify(entity, e);
	}
}
