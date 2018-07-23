#include "MiniginPCH.h"
#include "PacManSingleplayerScene.h"
#include "Grid.h"
#include "RenderComponent.h"
#include "TextComponent.h"
#include "FPSCalculatorComponent.h"
#include "Player.h"
#include "Ghost.h"
#include "AIComponent.h"


PacManSingleplayerScene::PacManSingleplayerScene()
	:Scene("PacManSinglePlayer")
{
	Init();
}


PacManSingleplayerScene::~PacManSingleplayerScene()
{
}

void PacManSingleplayerScene::Init()
{
	mPacMan = std::make_shared<Player>(glm::vec2(320, 352),"SinglePacMan.png");
	mGhost1 = std::make_shared<Ghost>(glm::vec2(320, 192), "Ghost.png");
	mGhosts.push_back(mGhost1);
	mGhost2 = std::make_shared<Ghost>(glm::vec2(288, 160), "Ghost.png");
	mGhosts.push_back(mGhost2);
	mGhost3 = std::make_shared<Ghost>(glm::vec2(320, 192), "Ghost.png");
	mGhosts.push_back(mGhost3);
	mGhost4 = std::make_shared<Ghost>(glm::vec2(288, 160), "Ghost.png");
	mGhosts.push_back(mGhost4);
	
	mGridObjects.push_back(mPacMan);
	mGridObjects.push_back(mGhost1);
	mGridObjects.push_back(mGhost2);
	mGridObjects.push_back(mGhost3);
	mGridObjects.push_back(mGhost4);
	mGrid = std::make_shared<Grid>("level1.txt",640,mGridObjects);
	Add(mGrid);


	mFpsCounter = std::make_shared<GameObject>();
	mFpsCounter->AddComponent(std::make_shared<TextComponent>("Lingua.otf", 20, SDL_Color{ 200,155,15 }));
	mFpsCounter->AddComponent(std::make_shared<FPSCalculatorComponent>());
	mFpsCounter->GetComponent<TextComponent>()->SetText(std::to_string(mFpsCounter->GetComponent<FPSCalculatorComponent>()->GetFps()));
	mFpsCounter->AddComponent(std::make_shared<RenderComponent>(mFpsCounter->GetComponent<TextComponent>()->GetTexture()));
	mFpsCounter->GetComponent<Transform>()->SetPosition(0.0f, 0);
	Add(mFpsCounter);

	mScoreCounter = std::make_shared<GameObject>();
	mScoreCounter->AddComponent(std::make_shared<TextComponent>("Lingua.otf", 20, SDL_Color{ 200,155,15 }));
	mScoreCounter->GetComponent<TextComponent>()->SetText("Score: " + std::to_string(mScore));
	mScoreCounter->AddComponent(std::make_shared<RenderComponent>(mScoreCounter->GetComponent<TextComponent>()->GetTexture()));
	mScoreCounter->GetComponent<Transform>()->SetPosition(200.0f, 0.0f);
	Add(mScoreCounter);

	mLifeCounter = std::make_shared<GameObject>();
	mLifeCounter->AddComponent(std::make_shared<TextComponent>("Lingua.otf", 20, SDL_Color{ 200,155,15 }));
	mLifeCounter->GetComponent<TextComponent>()->SetText("Lifes: " + std::to_string(mPacMan->GetLives()));
	mLifeCounter->AddComponent(std::make_shared<RenderComponent>(mLifeCounter->GetComponent<TextComponent>()->GetTexture()));
	mLifeCounter->GetComponent<Transform>()->SetPosition(400.0f, 0.0f);
	Add(mLifeCounter);

}

void PacManSingleplayerScene::SceneUpdate(float deltaTime)
{
	
	mFPSIntervalCounter += deltaTime;
	if (mFPSIntervalCounter >= mFPSTimeInterval) {
		mFpsCounter->GetComponent<TextComponent>()->SetText(std::to_string(mFpsCounter->GetComponent<FPSCalculatorComponent>()->GetFps()));
		mFpsCounter->GetComponent<RenderComponent>()->ChangeRenderingTexture(mFpsCounter->GetComponent<TextComponent>()->GetTexture());
		mFPSIntervalCounter = 0.0f;
	}
	mScoreCounter->GetComponent<TextComponent>()->SetText("Score: " + std::to_string(mScore));
	mScoreCounter->GetComponent<RenderComponent>()->ChangeRenderingTexture(mScoreCounter->GetComponent<TextComponent>()->GetTexture());

	mLifeCounter->GetComponent<TextComponent>()->SetText("Lifes: " + std::to_string(mPacMan->GetLives()));
	mLifeCounter->GetComponent<RenderComponent>()->ChangeRenderingTexture(mLifeCounter->GetComponent<TextComponent>()->GetTexture());

	HandleGameState();
	HandlePacMan(deltaTime);
	HandleGhosts(deltaTime);
	CheckForDeath();
}

void PacManSingleplayerScene::HandlePacMan(float deltaTime)
{
	auto pacDir = mPacMan->GetDirection();
	std::shared_ptr<Tile> tile;
	switch (pacDir)
	{
	case Player::LEFT:
		tile = mGrid->GetTiles().at(mGrid->GetTileLeftIdx(mPacMan));
		if (tile->GetType() != Tile::GhostWall && tile->GetType() != Tile::Wall)
		{
			mPacMan->Move(tile->GetComponent<Transform>()->GetPosition(), deltaTime);
		}
		break;
	case Player::RIGHT:
		tile = mGrid->GetTiles().at(mGrid->GetTileRightIdx(mPacMan));
		if (tile->GetType() != Tile::GhostWall && tile->GetType() != Tile::Wall)
		{
			mPacMan->Move(tile->GetComponent<Transform>()->GetPosition(), deltaTime);
		}
		break;
	case Player::DOWN:
		tile = mGrid->GetTiles().at(mGrid->GetTileDownIdx(mPacMan));
		if (tile->GetType() != Tile::GhostWall && tile->GetType() != Tile::Wall)
		{
			mPacMan->Move(tile->GetComponent<Transform>()->GetPosition(), deltaTime);
		}
		break;
	case Player::UP:
		tile = mGrid->GetTiles().at(mGrid->GetTileUpIdx(mPacMan));
		if (tile->GetType() != Tile::GhostWall && tile->GetType() != Tile::Wall)
		{
			mPacMan->Move(tile->GetComponent<Transform>()->GetPosition(), deltaTime);
		}
		break;
	}
}

void PacManSingleplayerScene::HandleGhosts(float deltaTime)
{
	for (auto ghost : mGhosts)
	{
		auto gDir = ghost->GetComponent<AIComponent>()->GetInstruction();
		std::shared_ptr<Tile> tile;
		switch (gDir)
		{
		case AIComponent::LEFT:
			tile = mGrid->GetTiles().at(mGrid->GetTileLeftIdx(ghost));
			if (tile->GetType() == Tile::Wall)
			{
				ghost->GetComponent<AIComponent>()->GenerateNewMoveInstruction();
			}
			else
			{
				ghost->Move(tile->GetComponent<Transform>()->GetPosition(), deltaTime);
			}
			break;
		case AIComponent::RIGHT:
			tile = mGrid->GetTiles().at(mGrid->GetTileRightIdx(ghost));
			if (tile->GetType() == Tile::Wall)
			{
				ghost->GetComponent<AIComponent>()->GenerateNewMoveInstruction();
			}
			else
			{
				ghost->Move(tile->GetComponent<Transform>()->GetPosition(), deltaTime);
			}
			break;
		case AIComponent::DOWN:
			tile = mGrid->GetTiles().at(mGrid->GetTileDownIdx(ghost));
			if (tile->GetType() == Tile::Wall)
			{
				ghost->GetComponent<AIComponent>()->GenerateNewMoveInstruction();
			}
			else
			{
				ghost->Move(tile->GetComponent<Transform>()->GetPosition(), deltaTime);
			}
			break;
		case AIComponent::UP:
			tile = mGrid->GetTiles().at(mGrid->GetTileUpIdx(ghost));
			if (tile->GetType() == Tile::Wall)
			{
				ghost->GetComponent<AIComponent>()->GenerateNewMoveInstruction();
			}
			else
			{
				ghost->Move(tile->GetComponent<Transform>()->GetPosition(), deltaTime);
			}
			break;

		}
	}
}

void PacManSingleplayerScene::CheckForDeath()
{
	if (mPacMan->IsAlive()) {
	for(auto ghost : mGhosts)
	{
		if (mGrid->GetTileIdx(mPacMan) == mGrid->GetTileIdx(ghost) )
		{
			
				mPacMan->Die();
			}
		}
	}
}

void PacManSingleplayerScene::HandleGameState() const
{
	if(mPacMan->GetLives() < 0)
	{
		SDL_Quit();
	}
}



