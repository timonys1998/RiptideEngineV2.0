#pragma once
#include "Minigin.h"
#include <SDL.h>
#include "GameModeSelectorComponent.h"

class Game
{
public:
	Game(const std::string& resourcePath); //Constructor where we give the path of the resources for this game
	~Game();
	static void SaveGamemode(GameMode mode) { m_GameMode = mode; }
	static GameMode GetGameMode() { return m_GameMode; }
	void HandleInput(); 
	void Render();
	void Update(float deltaTime);
	void LateUpdate(); //used for updating e.g collisions

	bool EndGame(); //Check to see if any of the game ending conditions are met and act on that

private:
	SDL_Window* m_pWindow; //Game window
	std::string m_ResourcePath; //Path to the folder with resources
	static GameMode m_GameMode;
	void Init();//Here we call our other Init functions to limit the amount of code in 1 function
	void InitWindow();
	void InitSystems(); //Init systems like our grid and UI system
	void InitScenes(); //Init the scenes used in our game
	void InitSoundMixer();
	void Cleanup();

};

