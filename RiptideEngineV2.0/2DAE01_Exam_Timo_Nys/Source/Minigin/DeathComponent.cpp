#include "MiniginPCH.h"
#include "DeathComponent.h"
#include "SceneManager.h"
#include "Grid.h"
#include "RenderComponent.h"
#include "PlayerInfoComponent.h"
#include "AIComponent.h"


DeathComponent::DeathComponent()
{
}


DeathComponent::~DeathComponent()
{
}

void DeathComponent::Die()const
{
	auto owner = GetOwner().lock();
	std::string name;
	owner->GetComponent<RenderComponent>()->EnableRendering(false);
	if (owner->HasComponent<PlayerInfoComponent>()) {
		name = owner->GetComponent<PlayerInfoComponent>()->GetName();
		Grid::GetInstance().RemoveEntity(name);
		Grid::GetInstance().CheckGameOver();
	}
	else {
		name = owner->GetComponent<AIComponent>()->GetName();
		Grid::GetInstance().RemoveEntity(name);
	}
	SceneManager::GetInstance().GetActiveScene()->Remove(owner);
}
