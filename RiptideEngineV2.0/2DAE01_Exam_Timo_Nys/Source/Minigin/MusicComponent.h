#pragma once
#include "BaseComponent.h"
#include <SDL_mixer.h>

class MusicComponent final : public BaseComponent
{
public:
	MusicComponent(const std::string& musicFile);
	~MusicComponent();

	void Update(float deltaTime) override { UNREFERENCED_PARAMETER(deltaTime); };
	void PlayMusic();
private:
	Mix_Music * m_pMusic;
};

