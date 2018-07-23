#pragma once
#include "Singleton.h"


	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		void CreateScene(std::shared_ptr<Scene> gameScene);
		void SetActiveScene(const std::string name);
		std::shared_ptr<Scene> GetActiveScene()const { return mActiveScene; }

		void Update(float deltaTime);

	private:
		std::vector<std::shared_ptr<Scene>> mScenes;
		std::shared_ptr<Scene> mActiveScene;
	};

