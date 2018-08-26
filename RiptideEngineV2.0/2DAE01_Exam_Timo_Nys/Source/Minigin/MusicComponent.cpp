#include "MiniginPCH.h"
#include "MusicComponent.h"
#include <SDL_mixer.h>


MusicComponent::MusicComponent(const std::string& musicFile)
{
	m_pMusic = Mix_LoadMUS(musicFile.c_str());
}



MusicComponent::~MusicComponent()
{
	Mix_FreeMusic(m_pMusic);
}

void MusicComponent::PlayMusic()
{
	Mix_PlayMusic(m_pMusic, -1);
}
