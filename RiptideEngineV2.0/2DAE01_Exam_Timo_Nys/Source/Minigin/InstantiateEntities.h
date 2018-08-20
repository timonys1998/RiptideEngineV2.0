#pragma once
#include "Enums.h"
#include "Structs.h"
#include "Transform.h"
#include "TextureComponent.h"
#include "RenderComponent.h"
#include "InputComponent.h"
#include "MoveComponent.h"
#include "BombComponent.h"
#include "PlayerInfoComponent.h"
#include "AIComponent.h"
#include "ExplosionComponent.h"
#include "PickupComponent.h"
#include "SubjectComponent.h"
#include "PlayerObserverComponent.h"
#include "HealthComponent.h"
#include "DeathComponent.h"
#include "SoundEffectComponent.h"


inline std::shared_ptr<GameObject> InstantiatePlayer(const FLOAT2& position, ControlType controlsType,const std::string& name)
{
	std::shared_ptr<GameObject> playerObj = std::make_shared<GameObject>();
	playerObj->AddComponent(std::make_shared<Transform>(position));
	playerObj->AddComponent(std::make_shared<TextureComponent>("bomberman1.png"));
	playerObj->AddComponent(std::make_shared<RenderComponent>());
	playerObj->AddComponent(std::make_shared<InputComponent>());
	playerObj->AddComponent(std::make_shared<MoveComponent>());
	playerObj->AddComponent(std::make_shared<HealthComponent>(2));
	playerObj->AddComponent(std::make_shared<DeathComponent>());
	playerObj->AddComponent(std::make_shared<SoundEffectComponent>("../Sounds/pickingUp.wav"));
	playerObj->AddComponent(std::make_shared<PlayerInfoComponent>(name,controlsType));
	if (controlsType == ControlType::Keyboard)
	{
		playerObj->GetComponent<InputComponent>()->AddInput(InputComponent::Button::RIGHTARROW, std::make_shared<SetDir>(Direction::RIGHT));
		playerObj->GetComponent<InputComponent>()->AddInput(InputComponent::Button::LEFTARROW, std::make_shared<SetDir>(Direction::LEFT));
		playerObj->GetComponent<InputComponent>()->AddInput(InputComponent::Button::UPARROW, std::make_shared<SetDir>(Direction::UP));
		playerObj->GetComponent<InputComponent>()->AddInput(InputComponent::Button::DOWNARROW, std::make_shared<SetDir>(Direction::DOWN));
		playerObj->GetComponent<InputComponent>()->AddInput(InputComponent::Button::SPACE, std::make_shared<PlaceBomb>());
	}
	else if (controlsType == ControlType::Controller)
	{
		playerObj->GetComponent<InputComponent>()->AddInput(InputComponent::Button::DPAD_RIGHT, std::make_shared<SetDir>(Direction::RIGHT));
		playerObj->GetComponent<InputComponent>()->AddInput(InputComponent::Button::DPAD_LEFT, std::make_shared<SetDir>(Direction::LEFT));
		playerObj->GetComponent<InputComponent>()->AddInput(InputComponent::Button::DPAD_UP, std::make_shared<SetDir>(Direction::UP));
		playerObj->GetComponent<InputComponent>()->AddInput(InputComponent::Button::DPAD_DOWN, std::make_shared<SetDir>(Direction::DOWN));
		playerObj->GetComponent<InputComponent>()->AddInput(InputComponent::Button::Button_X, std::make_shared<PlaceBomb>());
	}

	playerObj->SetTag("Player");
	playerObj->AddComponent(std::make_shared<PlayerObserverComponent>());
	return playerObj;
}

inline std::shared_ptr<GameObject> InstantiateEnemy(const FLOAT2& position, const std::string& name)
{
	std::shared_ptr<GameObject> enemyObj = std::make_shared<GameObject>();
	enemyObj->AddComponent(std::make_shared<Transform>(position));
	enemyObj->AddComponent(std::make_shared<TextureComponent>("bomberman1.png"));
	enemyObj->AddComponent(std::make_shared<RenderComponent>());
	enemyObj->AddComponent(std::make_shared<AIComponent>(name));
	enemyObj->AddComponent(std::make_shared<MoveComponent>());
	enemyObj->AddComponent(std::make_shared<DeathComponent>());
	
	enemyObj->SetTag("Enemy");

	return enemyObj;
}

inline std::shared_ptr<GameObject> InstantiateBomb(const FLOAT2& position, int tickCount,std::shared_ptr<GameObject> owningEntity)
{
	std::shared_ptr<GameObject> bombObj = std::make_shared<GameObject>();
	bombObj->AddComponent(std::make_shared<Transform>(position));
	bombObj->AddComponent(std::make_shared<TextureComponent>("Bomb.png"));
	bombObj->AddComponent(std::make_shared<RenderComponent>());
	bombObj->AddComponent(std::make_shared<BombComponent>(owningEntity,tickCount));
 	bombObj->AddComponent(std::make_shared<SoundEffectComponent>("../Sounds/blast.wav"));

	bombObj->SetTag("Bomb");
	return bombObj;
}

inline std::shared_ptr<GameObject> InstantiateExplosion(const FLOAT2& position,int range,Direction direction )
{
	std::shared_ptr<GameObject> explosionObj = std::make_shared<GameObject>();
	explosionObj->AddComponent(std::make_shared<Transform>(position));
	explosionObj->AddComponent(std::make_shared<TextureComponent>("Explosion.png"));
	explosionObj->AddComponent(std::make_shared<RenderComponent>());
	explosionObj->AddComponent(std::make_shared<ExplosionComponent>(range - 1,direction));

	explosionObj->SetTag("Explosion");

	return explosionObj;
}

inline std::shared_ptr<GameObject> InstantiatePickup(const FLOAT2& position,PickupType type)
{
	std::shared_ptr<GameObject> pickupObj = std::make_shared<GameObject>();
	pickupObj->AddComponent(std::make_shared<Transform>(position));
	pickupObj->AddComponent(std::make_shared<RenderComponent>());

	switch (type)
	{
	case PickupType::IncreaseMaxBombs:
		pickupObj->AddComponent(std::make_shared<TextureComponent>("BombUp.png"));
		break;
	case PickupType::IncreaseRange:
		pickupObj->AddComponent(std::make_shared<TextureComponent>("RangeUp.png"));
		break;
	case PickupType::Detonator:
		pickupObj->AddComponent(std::make_shared<TextureComponent>("Detonator.png"));
		break;
	case PickupType::Heart:
		pickupObj->AddComponent(std::make_shared<TextureComponent>("Heart.png"));
		break;
	}

	pickupObj->AddComponent(std::make_shared<PickupComponent>(type));
	pickupObj->AddComponent(std::make_shared<SubjectComponent>());

	auto entities = Grid::GetInstance().GetEntities();
	auto player1 = entities.find("Player1");
	pickupObj->GetComponent<SubjectComponent>()->Attach(player1->second->GetComponent<PlayerObserverComponent>());

	//Check if a second player can be found
	auto player2 = entities.find("Player2");
	if(player2 != entities.end())
	{
		pickupObj->GetComponent<SubjectComponent>()->Attach(player2->second->GetComponent<PlayerObserverComponent>());
	}

	pickupObj->SetTag("Pickup");
	
	return pickupObj;
}

inline std::shared_ptr<GameObject> InstantiateDoor(const FLOAT2& position)
{
	std::shared_ptr<GameObject> doorObj = std::make_shared<GameObject>();
	doorObj->AddComponent(std::make_shared<Transform>(position));
	doorObj->AddComponent(std::make_shared<RenderComponent>());
	doorObj->AddComponent(std::make_shared<TextureComponent>("Door.png"));

	doorObj->SetTag("Door");

	return doorObj;
}
