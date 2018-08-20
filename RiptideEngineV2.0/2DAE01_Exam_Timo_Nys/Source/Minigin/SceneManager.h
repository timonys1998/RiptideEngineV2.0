#pragma once
#include "Singleton.h"


	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		std::shared_ptr<Scene> CreateScene(const std::string& name);
		void SetActiveScene(const std::string name);
		std::shared_ptr<Scene> GetActiveScene()const { return m_spActiveScene; }
		std::shared_ptr<Scene> GetSceneWithName(const std::string& sceneName)const;

		void Update(float deltaTime);

	private:
		std::vector<std::shared_ptr<Scene>> m_spScenes;
		std::shared_ptr<Scene> m_spActiveScene;
	};

