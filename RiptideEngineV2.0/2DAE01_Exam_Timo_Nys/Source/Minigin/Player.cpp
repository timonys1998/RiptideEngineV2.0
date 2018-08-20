#include "MiniginPCH.h"
#include "Player.h"
#include "TextureComponent.h"
#include "RenderComponent.h"
#include "InputComponent.h"
#include "MoveComponent.h"


std::shared_ptr<Player> Player::Instantiate(const FLOAT2& position,ControlType controlsType,bool isEnemy)
{
	UNREFERENCED_PARAMETER(isEnemy);
	std::shared_ptr<Player> playerObj = std::make_shared<Player>();
	playerObj->AddComponent(std::make_shared<Transform>(position));
	playerObj->AddComponent(std::make_shared<TextureComponent>("bomberman1.png"));
	playerObj->AddComponent(std::make_shared<RenderComponent>());
	playerObj->AddComponent(std::make_shared<InputComponent>());
	playerObj->AddComponent(std::make_shared<MoveComponent>());
	if(controlsType == ControlType::Keyboard)
	{
		playerObj->GetComponent<InputComponent>()->AddInput(InputComponent::Button::RIGHTARROW, std::make_shared<SetDir>(Direction::RIGHT));
		playerObj->GetComponent<InputComponent>()->AddInput(InputComponent::Button::LEFTARROW, std::make_shared<SetDir>(Direction::LEFT));
		playerObj->GetComponent<InputComponent>()->AddInput(InputComponent::Button::UPARROW, std::make_shared<SetDir>(Direction::UP));
		playerObj->GetComponent<InputComponent>()->AddInput(InputComponent::Button::DOWNARROW, std::make_shared<SetDir>(Direction::DOWN));
	}
	else if(controlsType == ControlType::Controller)
	{
		//playerObj->GetComponent<InputComponent>()
	}


	return playerObj;
}

Player::~Player()
{
}
