#include "MiniginPCH.h"
#include "Game.h"
#include "SceneManager.h"
#include "Grid.h"
#include "RenderSystem.h"
#include <SDL.h>
#include "ResourceManager.h"
#include "UISystem.h"
#include "InputManager.h"
#include "CollisionSystem.h"
#include "SDL_mixer.h"

GameMode Game::m_GameMode = GameMode::None;

Game::Game(const std::string& resourcePath)
	:m_ResourcePath(resourcePath)
{
	Init();
}

Game::~Game()
{
	Cleanup();
}

void Game::HandleInput()
{
	InputManager::GetInstance().HandleInput();
}

void Game::Update(float deltaTime)
{
	UISystem::GetInstance().UpdateFPSCounter();
	SceneManager::GetInstance().Update(deltaTime);
}

void Game::LateUpdate()
{
	//Collision handling
	CollisionSystem::GetInstance().LateUpdate();
}

bool Game::EndGame()
{
	if(m_GameMode != GameMode::None)
		return Grid::GetInstance().GameIsOver();
	return false;
}

void Game::Init()
{
	InitSoundMixer();
	InitWindow();
	InitSystems();
	InitScenes();
}

void Game::InitWindow()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	m_pWindow = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		SDL_WINDOW_OPENGL
	);
	if (m_pWindow == nullptr)
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}
}

void Game::InitSystems()
{
	RenderSystem::GetInstance().Init(m_pWindow);
	ResourceManager::GetInstance().Init(m_ResourcePath);

}

void Game::InitScenes()
{
	//Create a scene and call the UI systems create functions, this will create the corresponding bomberman main menu
	auto mainMenuScene = SceneManager::GetInstance().CreateScene("MainMenu");
	SceneManager::GetInstance().SetActiveScene("MainMenu");
	UISystem::GetInstance().MakeMenu(mainMenuScene);

	auto gameScene = SceneManager::GetInstance().CreateScene("Game");
	Grid::GetInstance().GenerateLevel(gameScene,"level1.txt");
}

void Game::InitSoundMixer()
{
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1)
		std::cout << "Failed";
	Mix_AllocateChannels(1);
}

void Game::Cleanup()
{
	Mix_CloseAudio();
	RenderSystem::GetInstance().Destroy();
	SDL_DestroyWindow(m_pWindow);
	m_pWindow = nullptr;
	SDL_Quit();
}

void Game::Render()
{
	RenderSystem::GetInstance().Render();
}
