#include "MiniginPCH.h"
#include "Command.h"
#include "SceneManager.h"


SetDir::SetDir(Player::Dir direction, std::shared_ptr<Player> player)
	:mPlayer(player)
	,mDirection(direction)
{
}

void SetDir::Execute()
{
	mPlayer->SetDirection(mDirection);
}

SelectMode::SelectMode(const std::string& levelName)
	:mLevelToLoad(levelName)
{
}

void SelectMode::Execute()
{
	SceneManager::GetInstance().SetActiveScene(mLevelToLoad);
}

