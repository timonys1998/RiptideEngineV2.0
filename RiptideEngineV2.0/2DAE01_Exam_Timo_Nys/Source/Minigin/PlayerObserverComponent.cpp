#include "MiniginPCH.h"
#include "PlayerObserverComponent.h"
#include "GameObject.h"
#include "PickupComponent.h"
#include "PlayerInfoComponent.h"
#include "UISystem.h"
#include "InputComponent.h"
#include "HealthComponent.h"


PlayerObserverComponent::PlayerObserverComponent()
{
}


PlayerObserverComponent::~PlayerObserverComponent()
{
}

void PlayerObserverComponent::OnNotify(std::shared_ptr<GameObject> entity, Event e)
{
	UNREFERENCED_PARAMETER(entity);
	auto player = entity;
	auto playerInfo = entity->GetComponent<PlayerInfoComponent>();
	ControlType controls;
	if (entity->GetComponent<PlayerInfoComponent>()->GetID() == GetOwner().lock()->GetComponent<PlayerInfoComponent>()->GetID()) {
		switch (e)
		{
		case Event::DetonatorPickup:
			playerInfo->SetHasDetonator(true);
			controls = playerInfo->GetControls();
			if (controls == ControlType::Keyboard)
				player->GetComponent<InputComponent>()->AddInput(InputComponent::Button::ENTER, std::make_shared<Detonate>());
			else
				player->GetComponent<InputComponent>()->AddInput(InputComponent::Button::Button_B, std::make_shared<Detonate>());
			break;
		case Event::BombUpPickup:
			playerInfo->IncreaseBombCapacity();
			UISystem::GetInstance().ChangeBombCapacity(playerInfo->GetID(), playerInfo->GetBombsAvailable());
			break;
		case Event::RangeUpPickup:
			playerInfo->IncreaseBombRange();
			break;
		case Event::HeartPickup:
			auto healthComp = player->GetComponent<HealthComponent>();
			healthComp->Increase(1);
			UISystem::GetInstance().ChangeHealthValue(playerInfo->GetID(), healthComp->GetLives() + 1);
			break;
		}
	}
}
