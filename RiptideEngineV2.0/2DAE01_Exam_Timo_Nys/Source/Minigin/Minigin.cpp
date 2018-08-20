#include "MiniginPCH.h"
#include "Minigin.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "RenderSystem.h"
#include "ResourceManager.h"
#include <SDL.h>
#include "GameObject.h"
#include "Scene.h"
#include "Game.h"
#include "SDL_mixer.h"


void Minigin::Run()
{
	std::shared_ptr<Game> spGame(std::make_shared<Game>("../Data/"));
	bool doContinue = true;
	auto lastTime = std::chrono::high_resolution_clock::now();
		while (doContinue)
		{
			auto currentTime = std::chrono::high_resolution_clock::now();
			auto deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();

			spGame->HandleInput();
			spGame->Update(deltaTime);
			spGame->Render();
			spGame->LateUpdate();
			
			lastTime = currentTime;
			doContinue = !spGame->EndGame();
			if(GetAsyncKeyState(VK_ESCAPE) & 0x8000)
			{
				doContinue = false;
			}
			
		}
		
		
}
