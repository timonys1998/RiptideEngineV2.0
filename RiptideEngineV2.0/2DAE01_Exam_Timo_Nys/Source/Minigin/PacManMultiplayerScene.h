#pragma once
#include "Scene.h"
#include "Grid.h"
#include "Player.h"
class Ghost;

class PacManMultiplayerScene final : public Scene
{
public:
	explicit PacManMultiplayerScene();
	virtual ~PacManMultiplayerScene();

	void Init() override;
	void SceneUpdate(float deltaTime) override;
private:
	void HandlePlayers(float deltaTime);
	void HandleGhosts(float deltaTime);
	void CheckForDeath();
	void HandleGameState()const;

	std::shared_ptr<Player> mPacMan;
	std::shared_ptr<Player> mMsPacMan;
	std::shared_ptr<Ghost> mGhost1;
	std::shared_ptr<Ghost> mGhost2;
	std::shared_ptr<Ghost> mGhost3;
	std::shared_ptr<Ghost> mGhost4;
	std::shared_ptr<Grid> mGrid;
	std::shared_ptr<GameObject> mFpsCounter;
	std::shared_ptr<GameObject> mScoreCounter;
	std::shared_ptr<GameObject> mLifeCounter;

	std::vector<std::shared_ptr<GameObject>> mGridObjects;
	std::vector<std::shared_ptr<Ghost>> mGhosts;

	float mFPSIntervalCounter = 0.0f;
	float mFPSTimeInterval = 1.0f;
	int mScore = 0;
};