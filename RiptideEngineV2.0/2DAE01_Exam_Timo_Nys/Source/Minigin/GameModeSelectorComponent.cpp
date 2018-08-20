#include "MiniginPCH.h"
#include "GameModeSelectorComponent.h"
#include "SceneManager.h"
#include "Player.h"
#include "Grid.h"
#include "UISystem.h"
#include "Game.h"


GameModeSelectorComponent::GameModeSelectorComponent()
{
}


GameModeSelectorComponent::~GameModeSelectorComponent()
{
}

void GameModeSelectorComponent::LoadGame(GameMode mode)
{
	auto gameScene = SceneManager::GetInstance().GetSceneWithName("Game");
	
	switch(mode)
	{
	case GameMode::Singleplayer:
		Game::SaveGamemode(GameMode::Singleplayer);
		Grid::GetInstance().AddPlayerAtTile(16,"Player1");
		Grid::GetInstance().AddEnemyAtTile(208, "Enemy1");
		Grid::GetInstance().AddEnemyAtTile(197, "Enemy2");
		Grid::GetInstance().AddEnemyAtTile(28, "Enemy3");
		break;
	case GameMode::COOP:
		Game::SaveGamemode(GameMode::COOP);
		Grid::GetInstance().AddPlayerAtTile(16, "Player1");
		Grid::GetInstance().AddEnemyAtTile(29, "Enemy1");
		Grid::GetInstance().AddEnemyAtTile(197, "Enemy2");
		Grid::GetInstance().AddPlayerAtTile(208, "Player2",ControlType::Controller);
		break;
	case GameMode::Versus:
		Game::SaveGamemode(GameMode::Versus);
		Grid::GetInstance().AddPlayerAtTile(16, "Player1");
		Grid::GetInstance().AddPlayerAtTile(208, "Player2", ControlType::Controller);
		break;
	default:
		break;
	}
	UISystem::GetInstance().MakeUI(gameScene,mode);
	SceneManager::GetInstance().SetActiveScene("Game");
}
