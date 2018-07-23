#pragma once
#include "Scene.h"

class MainMenuScene final : public Scene
{
public:
	MainMenuScene();
	virtual ~MainMenuScene();

	void Init() override;
	void SceneUpdate(float deltaTime) override;

private:
	std::shared_ptr<GameObject> mBackground;
	std::shared_ptr<GameObject> mSinglePlayerIcon;
	std::shared_ptr<GameObject> mMultiPlayerIcon;
	std::shared_ptr<GameObject> mGhostIcon;
	std::shared_ptr<GameObject> mFpsCounter;
	std::shared_ptr<GameObject> mMenuText;

	float mFPSIntervalCounter = 0.0f;
	float mFPSTimeInterval = 1.0f;
};

