#include "MiniginPCH.h"
#include "BombComponent.h"
#include "GameObject.h"
#include "RenderComponent.h"
#include "SceneManager.h"
#include "Scene.h"
#include "PlayerInfoComponent.h"
#include "Grid.h"
#include "UISystem.h"
#include "AIComponent.h"
#include "SoundEffectComponent.h"


BombComponent::BombComponent(std::shared_ptr<GameObject> owningEntity, int tickCount)
	:m_TicksToExplode(tickCount)
	,m_spOwningEntity(owningEntity)
{
}


BombComponent::~BombComponent()
{
}

void BombComponent::Update(float deltaTime)
{
	m_Timer += deltaTime;
	if(m_Timer >= m_TicksToExplode)
	{
		Explode();
	}

}

void BombComponent::Explode()const
{
	auto obj = GetOwner().lock();
	obj->GetComponent<SoundEffectComponent>()->PlaySound();
	obj->GetComponent<RenderComponent>()->EnableRendering(false);
	auto playerInfo = m_spOwningEntity->GetComponent<PlayerInfoComponent>();
	if(!playerInfo)
	{
		auto aiComp = m_spOwningEntity->GetComponent<AIComponent>();
		aiComp->DecreaseBombsPlaced();
	}
	else
	{
		playerInfo->DecreaseBombsPlaced();
		//Update bomb UI as well using the UISystem
		UISystem::GetInstance().ChangeBombCapacity(playerInfo->GetID(), playerInfo->GetBombsAvailable());
	}
 	
	
	
	//Calculate the bombs tile index and remove it from the grids bomb map
	int tileIdx = Grid::GetInstance().GetIndex(obj);
	Grid::GetInstance().RemoveBomb(tileIdx);
	if(playerInfo)
	{
		int range = playerInfo->GetBombRange();
		Grid::GetInstance().AddExplosions(GetOwner().lock(), range);
		if(range >= 2)
		{
			playerInfo->DecreaseBombRange();
		}
	}
	else
		Grid::GetInstance().AddExplosions(GetOwner().lock(), 1);
	SceneManager::GetInstance().GetActiveScene()->Remove(obj);
}
