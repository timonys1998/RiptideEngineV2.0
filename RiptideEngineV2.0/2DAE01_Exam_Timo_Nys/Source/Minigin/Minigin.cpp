#include "MiniginPCH.h"
#include "Minigin.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <SDL.h>
#include "GameObject.h"
#include "Scene.h"
#include "MainMenuScene.h"
#include "PacManSingleplayerScene.h"
#include "PacManMultiplayerScene.h"
#include "VersusScene.h"


void Minigin::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		SDL_WINDOW_OPENGL
	);
	if (window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(window);
}

/**
 * Code constructing the scene world starts here
 */
void Minigin::LoadGame() const
{
	SceneManager::GetInstance().CreateScene(std::make_shared<MainMenuScene>());
	SceneManager::GetInstance().CreateScene(std::make_shared<PacManSingleplayerScene>());
	SceneManager::GetInstance().CreateScene(std::make_shared<PacManMultiplayerScene>());
	SceneManager::GetInstance().CreateScene(std::make_shared<VersusScene>());
	SceneManager::GetInstance().SetActiveScene("MainMenu");
}

void Minigin::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(window);
	window = nullptr;
	SDL_Quit();
}

void Minigin::Run()
{
	Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");

	LoadGame();

	{
		
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();

		
		bool doContinue = true;
		auto lastTime = std::chrono::high_resolution_clock::now();
		while (doContinue)
		{
			auto currentTime = std::chrono::high_resolution_clock::now();
			auto deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();

			doContinue = input.ProcessInput();

			sceneManager.Update(deltaTime);
			renderer.Render();

			lastTime = currentTime;
			if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)doContinue = false;
		}
		
	}

	Cleanup();
}
