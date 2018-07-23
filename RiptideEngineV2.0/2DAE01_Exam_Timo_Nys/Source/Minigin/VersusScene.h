#pragma once
#include "Scene.h"
#include "Grid.h"
#include "Player.h"

class VersusScene : public Scene
{
public:
	explicit VersusScene();
	virtual ~VersusScene();

	void Init() override;
	void SceneUpdate(float deltaTime) override;
private:
	void HandlePlayers(float deltaTime);
	void CheckForDeath();
	void HandleGameState()const;

	std::shared_ptr<Player> mPacMan;
	std::shared_ptr<Player> mPlayerGhost;

	std::shared_ptr<Grid> mGrid;
	std::shared_ptr<GameObject> mFpsCounter;
	std::shared_ptr<GameObject> mScoreCounter;
	std::shared_ptr<GameObject> mLifeCounter;

	std::vector<std::shared_ptr<GameObject>> mGridObjects;

	float mFPSIntervalCounter = 0.0f;
	float mFPSTimeInterval = 1.0f;
	int mScore = 0;

};

