#include "MiniginPCH.h"
#include "Renderer.h"
#include <SDL.h>
#include "SceneManager.h"
#include "Scene.h"

void Renderer::Init(SDL_Window * window)
{
	mRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (mRenderer == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}
}

void Renderer::Render()
{
	SDL_RenderClear(mRenderer);

	SceneManager::GetInstance().GetActiveScene()->Render();
	
	SDL_RenderPresent(mRenderer);
}

void Renderer::Destroy()
{
	if (mRenderer != nullptr)
	{
		SDL_DestroyRenderer(mRenderer);
		mRenderer = nullptr;
	}
}


