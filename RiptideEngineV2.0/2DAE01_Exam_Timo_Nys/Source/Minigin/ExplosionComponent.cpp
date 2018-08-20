#include "MiniginPCH.h"
#include "ExplosionComponent.h"
#include "RenderComponent.h"
#include "Grid.h"


ExplosionComponent::ExplosionComponent(int propagationRange, Direction propagationDirection)
	:m_PropagationRange(propagationRange)
	,m_PropagationDirection(propagationDirection)
{
}


ExplosionComponent::~ExplosionComponent()
{
}

void ExplosionComponent::Update(float deltaTime)
{
	m_Timer += deltaTime;
	if(m_Timer >= m_LastingTime)
	{
		Clear();
	}
}

void ExplosionComponent::Propagate()const
{
	if(m_PropagationRange > 0)
	{
		auto idx = Grid::GetInstance().GetIndex(GetOwner().lock());
		Grid::GetInstance().AddExplosionInDirection(idx, m_PropagationDirection);
		
	}
}

void ExplosionComponent::Clear()const
{
	auto obj = GetOwner().lock();
	obj->GetComponent<RenderComponent>()->EnableRendering(false);

	//Remove the explosion from the grid and scene
	int tileIdx = Grid::GetInstance().GetIndex(obj);
	Grid::GetInstance().RemoveExplosion(tileIdx);
	SceneManager::GetInstance().GetActiveScene()->Remove(obj);
}
