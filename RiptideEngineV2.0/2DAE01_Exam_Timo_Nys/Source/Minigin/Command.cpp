#include "MiniginPCH.h"
#include "Command.h"
#include "SceneManager.h"
#include "GameModeSelectorComponent.h"
#include "Grid.h"
#include "MoveComponent.h"
#include "InstantiateEntities.h"
#include "PlayerInfoComponent.h"
#include "UISystem.h"
#include <algorithm>
#include <SDL.h>

#include "Game.h"




SetDir::SetDir(Direction direction)
	:m_Direction(direction)
{

}

void SetDir::Execute(std::shared_ptr<GameObject> ob)
{
	auto moveComp = ob->GetComponent<MoveComponent>();
	if(moveComp)
	{
		if (!moveComp->ShouldMove())
		{
			auto type = Grid::GetInstance().GetTileTypeInDirection(ob, m_Direction);
			int indexNextTile = Grid::GetInstance().GetIndexInDirection(ob, m_Direction);
			if (type != TileType::HardWall && type != TileType::SoftWall && !Grid::GetInstance().TileHasBomb(indexNextTile) )
			{
				ob->GetComponent<MoveComponent>()->SetDirection(m_Direction);
				moveComp->SetTarget(Grid::GetInstance().GetPosInDirection(ob, m_Direction));
				ob->GetComponent<MoveComponent>()->DoMove(true);
			}
		}
	}
}


void SelectMode::Execute(std::shared_ptr<GameObject> ModeSelector)
{
	auto gamemodeSelector = ModeSelector->GetComponent<GameModeSelectorComponent>();
	if (gamemodeSelector)
			gamemodeSelector->LoadGame(m_GameMode);
}

void PlaceBomb::Execute(std::shared_ptr<GameObject> obj)
{
	auto playerInfo = obj->GetComponent<PlayerInfoComponent>();
	auto moveComp = obj->GetComponent<MoveComponent>();
	int idx = Grid::GetInstance().GetIndex(obj);
	if (playerInfo) {
		if (playerInfo->CanPlaceBomb() && !Grid::GetInstance().TileHasBomb(idx) && !moveComp->ShouldMove()) {
			playerInfo->IncreaseBombsPlaced();
			Grid::GetInstance().AddBomb(obj);
			UISystem::GetInstance().ChangeBombCapacity(playerInfo->GetID(), playerInfo->GetBombsAvailable());
			if (playerInfo->HasDetonator()) playerInfo->SetHasDetonator(false);
		}
	}
}	

void Detonate::Execute(std::shared_ptr<GameObject> obj)
{
	std::cout << "executed";
	auto bombs = Grid::GetInstance().GetBombs();
	auto found = std::find_if(bombs.begin(),bombs.end(),[obj](std::pair<int,std::shared_ptr<GameObject>> bomb)
	{
		return bomb.second->GetComponent<BombComponent>()->GetOwning()->GetComponent<PlayerInfoComponent>()->GetID() == obj->GetComponent<PlayerInfoComponent>()->GetID();
	});

	if (found != bombs.end()) {
		(*found).second->GetComponent<BombComponent>()->Explode();

		if (obj->GetComponent<PlayerInfoComponent>()->GetControls() == ControlType::Keyboard)
			obj->GetComponent<InputComponent>()->RemoveInput(InputComponent::Button::ENTER);
		else
			obj->GetComponent<InputComponent>()->RemoveInput(InputComponent::Button::Button_B);
	}

}

