#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"
#include <algorithm>


std::shared_ptr<Scene> SceneManager::GetSceneWithName(const std::string& sceneName) const
{
	for(auto scene : m_spScenes)
	{
		if (scene->GetName() == sceneName)
			return scene;
	}
	std::cout << "Scene with name " << sceneName << " does not exist \n";
	return nullptr;
}

void SceneManager::Update(float deltaTime)
{
	if (m_spActiveScene)
		m_spActiveScene->Update(deltaTime);
	else
		std::cout << "No scene set as active scene \n";
}




std::shared_ptr<Scene> SceneManager::CreateScene(const std::string& name)
{
	auto scene = std::shared_ptr<Scene>(std::make_shared<Scene>(name));
	m_spScenes.push_back(scene);
	return scene;
}

void SceneManager::SetActiveScene(const std::string name)
{
	auto it = std::find_if(m_spScenes.begin(),m_spScenes.end(),[name](std::shared_ptr<Scene> scene)
	{
		return name == scene->GetName();
	});

	if(it != m_spScenes.end())
	{
		m_spActiveScene = *it;
	}
}

