#include "MiniginPCH.h"
#include "UISystem.h"
#include "RenderComponent.h"
#include "TextureComponent.h"
#include "TextComponent.h"
#include "GameModeSelectorComponent.h"
#include "InputComponent.h"
#include "FPSCalculatorComponent.h"



void UISystem::MakeMenu(std::shared_ptr<Scene> menu)
{
	m_spMainMenu = GameObject::Instantiate();
	m_spMainMenu->AddComponent(std::make_shared<RenderComponent>());
	m_spMainMenu->AddComponent(std::make_shared<TextureComponent>("background.jpg"));
	m_spMainMenu->AddComponent(std::make_shared<TextureComponent>("Bomberman_Title.png",true,FLOAT2(20.0f,150.0f)));
	m_spMainMenu->AddComponent(std::make_shared<TextComponent>("1 : Singleplayer  /  2 : co-op  /  3 : versus",FLOAT2(25.0f,350.0f), false));
	m_spMainMenu->AddComponent(std::make_shared<GameModeSelectorComponent>());
	m_spMainMenu->AddComponent(std::make_shared<InputComponent>());
	m_spMainMenu->GetComponent<InputComponent>()->AddInput(InputComponent::Button::NUM1, std::make_shared<SelectMode>(GameMode::Singleplayer));
	m_spMainMenu->GetComponent<InputComponent>()->AddInput(InputComponent::Button::NUM2, std::make_shared<SelectMode>(GameMode::COOP));
	m_spMainMenu->GetComponent<InputComponent>()->AddInput(InputComponent::Button::NUM3, std::make_shared<SelectMode>(GameMode::Versus));
	
		

	//FPS counter
	m_spFpsCounter = GameObject::Instantiate(FLOAT2(10.0f, 10.0f));
	m_spFpsCounter->AddComponent(std::make_shared<FPSCalculatorComponent>());
	m_spFpsCounter->AddComponent(std::make_shared<TextComponent>("0", FLOAT2(10.0f, 10.0f), true));
	m_spFpsCounter->AddComponent(std::make_shared<RenderComponent>());
	menu->Add(m_spMainMenu);
	menu->Add(m_spFpsCounter);
}

void UISystem::MakeUI(std::shared_ptr<Scene> game,GameMode mode)
{
	game->Add(m_spFpsCounter);

	//Player 1 Bombs available
	m_spBombsAvailableP1 = GameObject::Instantiate(FLOAT2(5.0f, 490.0f));
	m_spBombsAvailableP1->AddComponent(std::make_shared<RenderComponent>());
	m_spBombsAvailableP1->AddComponent(std::make_shared<TextComponent>("BOMBS P1: 2", FLOAT2(0, 0), true));
	game->Add(m_spBombsAvailableP1);

	//Player 1 lives
	m_spLivesP1 = GameObject::Instantiate(FLOAT2(5.0f, 520.0f));
	m_spLivesP1->AddComponent(std::make_shared<RenderComponent>());
	m_spLivesP1->AddComponent(std::make_shared<TextComponent>("LIVES P1: 2"));
	game->Add(m_spLivesP1);

	if(mode == GameMode::Versus)
	{
		auto versusObj = GameObject::Instantiate(FLOAT2(227.5f, 490.0f));
		versusObj->AddComponent(std::make_shared<RenderComponent>());
		versusObj->AddComponent(std::make_shared<TextureComponent>("vs.png"));
		game->Add(versusObj);
	}

	if(mode == GameMode::Versus || mode == GameMode::COOP )
	{
		//Player 2 Bombs available
		m_spBombsAvailableP2 = GameObject::Instantiate(FLOAT2(330.0f, 490.0f));
		m_spBombsAvailableP2->AddComponent(std::make_shared<RenderComponent>());
		m_spBombsAvailableP2->AddComponent(std::make_shared<TextComponent>("BOMBS P2: 2", FLOAT2(0, 0), true));
		game->Add(m_spBombsAvailableP2);

		//Player 2 lives
		m_spLivesP2 = GameObject::Instantiate(FLOAT2(346.0f, 520.0f));
		m_spLivesP2->AddComponent(std::make_shared<RenderComponent>());
		m_spLivesP2->AddComponent(std::make_shared<TextComponent>("LIVES P2: 2"));
		game->Add(m_spLivesP2);
	}
}

void UISystem::UpdateFPSCounter()const
{
	m_spFpsCounter->GetComponent<TextComponent>()->SetText(
		std::to_string(m_spFpsCounter->GetComponent<FPSCalculatorComponent>()->GetFps()));
}



void UISystem::ChangeBombCapacity(int playerID, int value) const
{
	if(playerID == 1)
	{
		m_spBombsAvailableP1->GetComponent<TextComponent>()->SetText("BOMBS P1: " + std::to_string(value));
	}
	else if(playerID == 2)
	{
		m_spBombsAvailableP2->GetComponent<TextComponent>()->SetText("BOMBS P2: " + std::to_string(value));
	}
	
}

void UISystem::ChangeHealthValue(int playerID, int value) const
{
	if (playerID == 1)
	{
		m_spLivesP1->GetComponent<TextComponent>()->SetText("LIVES P1: " + std::to_string(value));
	}
	else
	{
		m_spLivesP2->GetComponent<TextComponent>()->SetText("LIVES P2: " + std::to_string(value));
	}
}



