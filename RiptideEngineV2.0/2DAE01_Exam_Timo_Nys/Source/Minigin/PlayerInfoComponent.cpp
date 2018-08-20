#include "MiniginPCH.h"
#include "PlayerInfoComponent.h"
#include "Grid.h"
#include "UISystem.h"
#include "HealthComponent.h"


PlayerInfoComponent::PlayerInfoComponent(const std::string& name, ControlType controlType  ,int maxBombs,int bombRange)
	:m_MaxBombs(maxBombs)
	,m_BombRange(bombRange)
	,m_Name(name)
	,m_TypeOfControls(controlType)
{
	m_PlayerID = Grid::GetInstance().GetPlayerAmount();
}


PlayerInfoComponent::~PlayerInfoComponent()
{
}

void PlayerInfoComponent::Respawn()
{
	m_IsRespawning = true;
	auto player = GetOwner().lock();
	player->GetComponent<Transform>()->ResetPosition();
	player->GetComponent<HealthComponent>()->Decrease(1);
	int currHealth = player->GetComponent<HealthComponent>()->GetLives();
	if(currHealth >= 0)
		UISystem::GetInstance().ChangeHealthValue(player->GetComponent<PlayerInfoComponent>()->GetID(),
		currHealth--);

}
