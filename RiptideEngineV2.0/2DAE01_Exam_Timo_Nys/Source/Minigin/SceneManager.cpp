#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"
#include <algorithm>


void SceneManager::Update(float deltaTime)
{
	if (mActiveScene)
		mActiveScene->Update(deltaTime);
	else
		std::cout << "No scene set as active scene \n";
}


void SceneManager::CreateScene(std::shared_ptr<Scene> gameScene)
{
	mScenes.push_back(gameScene);
}

void SceneManager::SetActiveScene(const std::string name)
{
	auto it = find_if(mScenes.begin(),mScenes.end(),[name](std::shared_ptr<Scene> scene)
	{
		return name == scene->GetName();
	});

	if(it != mScenes.end())
	{
		mActiveScene = *it;
	}
}

