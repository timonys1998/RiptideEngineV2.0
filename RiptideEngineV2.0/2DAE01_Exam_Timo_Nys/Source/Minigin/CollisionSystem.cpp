#include "MiniginPCH.h"
#include "CollisionSystem.h"
#include "Grid.h"
#include "PlayerInfoComponent.h"
#include "UISystem.h"
#include "AIComponent.h"
#include "BombComponent.h"
#include "SubjectComponent.h"
#include "DeathComponent.h"
#include "HealthComponent.h"
#include "PickupComponent.h"
#include "SoundeffectComponent.h"


void CollisionSystem::LateUpdate()
{
	//All different collision checks
	for(auto& e : Grid::GetInstance().GetEntities())
	{
		if(e.second->GetTag() == "Player")
		{
			CheckCollisionWithDoor(e.second);
			CheckCollisionWithEnemies(e.second);
			CheckCollisionWithExplosions(e.second);
			CheckCollisionWithPowerups(e.second);
			
		}
		else if(e.second->GetTag() == "Enemy")
		{
			CheckCollisionWithExplosions(e.second);
			CheckCollisionWithPowerups(e.second);
		}
	
	}

	for(auto& b : Grid::GetInstance().GetBombs())
	{
		CheckCollisionWithExplosions(b.second);
	}
	for (auto& b : Grid::GetInstance().GetPowerups())
	{
		CheckCollisionWithExplosions(b.second);
	}
}

void CollisionSystem::CheckCollisionWithEnemies(std::shared_ptr<GameObject> player)
{
	for (auto e : Grid::GetInstance().GetEntities())
	{
		if (e.second->GetTag() == "Enemy")
		{
			int playerTileIdx = Grid::GetInstance().GetIndex(player);
			int enemyTileIdx = Grid::GetInstance().GetIndex(e.second);

			if(playerTileIdx == enemyTileIdx && !player->GetComponent<PlayerInfoComponent>()->IsRespawning())
			{
				if (player->GetComponent<HealthComponent>()->GetLives() >= 1)
					player->GetComponent<PlayerInfoComponent>()->Respawn();
				else
					player->GetComponent<DeathComponent>()->Die();
		
			}
		}
	}
}

void CollisionSystem::CheckCollisionWithExplosions(std::shared_ptr<GameObject> entity)
{
	for (auto e : Grid::GetInstance().GetExplosions())
	{
			int entityTileIdx = Grid::GetInstance().GetIndex(entity);
			int explosionTileIdx = Grid::GetInstance().GetIndex(e.second);

			if (entityTileIdx == explosionTileIdx)
			{
				if (entity->GetTag() == "Enemy")
				{
					entity->GetComponent<DeathComponent>()->Die();
				}
				else if(entity->GetTag() == "Player" && !entity->GetComponent<PlayerInfoComponent>()->IsRespawning())
				{
					if (entity->GetComponent<HealthComponent>()->GetLives() >= 1)
						entity->GetComponent<PlayerInfoComponent>()->Respawn(); 
					else
						entity->GetComponent<DeathComponent>()->Die();
				}
				else if(entity->GetTag() == "Bomb")
				{
					entity->GetComponent<BombComponent>()->Explode();
				}
				else if(entity->GetTag() == "Pickup")
				{
					Grid::GetInstance().RemovePickup(entityTileIdx);
				}
			}
		}
}

void CollisionSystem::CheckCollisionWithPowerups(std::shared_ptr<GameObject> entity)
{
	for (auto p : Grid::GetInstance().GetPowerups())
	{
		int entityTileIdx = Grid::GetInstance().GetIndex(entity);
		int powerupTileIdx = Grid::GetInstance().GetIndex(p.second);

		if (entityTileIdx == powerupTileIdx)
		{
			if (entity->GetTag() == "Enemy")
			{
				Grid::GetInstance().RemovePickup(powerupTileIdx);
			}
			else if (entity->GetTag() == "Player" )
			{
				entity->GetComponent<SoundEffectComponent>()->PlaySound();
				auto type = p.second->GetComponent<PickupComponent>()->GetType();
				switch (type)
				{
				case PickupType::Detonator:
					p.second->GetComponent<SubjectComponent>()->Notify(entity, Event::DetonatorPickup);
					break;
				case PickupType::IncreaseMaxBombs:
					p.second->GetComponent<SubjectComponent>()->Notify(entity, Event::BombUpPickup);
					break;
				case PickupType::IncreaseRange:
					p.second->GetComponent<SubjectComponent>()->Notify(entity, Event::RangeUpPickup);
					break;
				case PickupType::Heart:
					p.second->GetComponent<SubjectComponent>()->Notify(entity, Event::HeartPickup);
					break;
				}
				
				Grid::GetInstance().RemovePickup(powerupTileIdx);
			}
			else if(entity->GetTag() == "Explosion")
			{
				Grid::GetInstance().RemovePickup(powerupTileIdx);	
			}
			
		}
	}
}

void CollisionSystem::CheckCollisionWithDoor(std::shared_ptr<GameObject> player)
{
	auto door = Grid::GetInstance().GetDoor();
	int playerTileIdx = Grid::GetInstance().GetIndex(player);
	int doorTileIdx = door.first;

	if (playerTileIdx == doorTileIdx)
 		Grid::GetInstance().CheckGameOver();
}

