#include "MiniginPCH.h"
#include "VersusScene.h"
#include "TextComponent.h"
#include "RenderComponent.h"
#include "FPSCalculatorComponent.h"


VersusScene::VersusScene()
	:Scene("VersusScene")
{
	Init();
}


VersusScene::~VersusScene()
{
}

void VersusScene::Init()
{
	mPacMan = std::make_shared<Player>(glm::vec2(320, 352), "SinglePacMan.png");
	mPlayerGhost = std::make_shared<Player>(glm::vec2(320, 192), "Ghost.png", Player::ControlsType::CONTROLLER);
	
	mGridObjects.push_back(mPacMan);
	mGridObjects.push_back(mPlayerGhost);
	
	mGrid = std::make_shared<Grid>("level1.txt", 640, mGridObjects);
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

void VersusScene::SceneUpdate(float deltaTime)
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
	HandlePlayers(deltaTime);
	CheckForDeath();
}

void VersusScene::HandlePlayers(float deltaTime)
{
	//PacMan 
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

	//Ghost player
	auto ghostDir = mPlayerGhost->GetDirection();
	std::shared_ptr<Tile> tile1;
	switch (ghostDir)
	{
	case Player::LEFT:
		tile = mGrid->GetTiles().at(mGrid->GetTileLeftIdx(mPlayerGhost));
		if (tile->GetType() != Tile::Wall)
		{
			mPlayerGhost->Move(tile->GetComponent<Transform>()->GetPosition(), deltaTime);
		}
		break;
	case Player::RIGHT:
		tile = mGrid->GetTiles().at(mGrid->GetTileRightIdx(mPlayerGhost));
		if (tile->GetType() != Tile::Wall)
		{
			mPlayerGhost->Move(tile->GetComponent<Transform>()->GetPosition(), deltaTime);
		}
		break;
	case Player::DOWN:
		tile = mGrid->GetTiles().at(mGrid->GetTileDownIdx(mPlayerGhost));
		if (tile->GetType() != Tile::Wall)
		{
			mPlayerGhost->Move(tile->GetComponent<Transform>()->GetPosition(), deltaTime);
		}
		break;
	case Player::UP:
		tile = mGrid->GetTiles().at(mGrid->GetTileUpIdx(mPlayerGhost));
		if (tile->GetType() != Tile::Wall)
		{
			mPlayerGhost->Move(tile->GetComponent<Transform>()->GetPosition(), deltaTime);
		}
		break;
	}
}

void VersusScene::CheckForDeath()
{
	if (mPacMan->IsAlive()) {
			if (mGrid->GetTileIdx(mPacMan) == mGrid->GetTileIdx(mPlayerGhost))
			{
				mPacMan->Die();
			}
		}
}

void VersusScene::HandleGameState() const
{
	if (mPacMan->GetLives() < 0)
	{
		SDL_Quit();
	}
}
