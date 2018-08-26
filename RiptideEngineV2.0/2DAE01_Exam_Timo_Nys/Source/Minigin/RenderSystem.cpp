#include "MiniginPCH.h"
#include "RenderSystem.h"
#include <SDL.h>
#include "SceneManager.h"
#include "Scene.h"
#include "RenderComponent.h"


void RenderSystem::Init(SDL_Window* window)
{
	m_pRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (m_pRenderer == nullptr) {
		std::stringstream ss; ss << "SDL_CreateRenderer Error: " << SDL_GetError();
		throw std::runtime_error(ss.str().c_str());
	}
	
}

void RenderSystem::Render()const
{
	SDL_RenderClear(m_pRenderer);
	auto activeScene = SceneManager::GetInstance().GetActiveScene();
	auto sceneObjects = activeScene->GetObjects();
	for(unsigned int i = 0; i < sceneObjects.size();++i)
	{
		auto renCom = sceneObjects.at(i)->GetComponent<RenderComponent>();
		if (renCom && renCom->ShouldRender())
			renCom->Render();
	}
	SDL_RenderPresent(m_pRenderer);
}

void RenderSystem::Destroy()
{
	if(m_pRenderer)
	{
		SDL_DestroyRenderer(m_pRenderer);
		m_pRenderer = nullptr;
	}
}


