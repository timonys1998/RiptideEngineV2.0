
#include "MiniginPCH.h"
#include "SoundeffectComponent.h"



SoundEffectComponent::SoundEffectComponent(const std::string& soundFile)
{
	m_pSound = Mix_LoadWAV(soundFile.c_str());
	if(m_pSound == nullptr)
	{
		std::cout << "Sound is not found \n";
	}
}


SoundEffectComponent::~SoundEffectComponent()
{
	Mix_FreeChunk(m_pSound);
}

void SoundEffectComponent::PlaySound()
{
	if (Mix_PlayChannel(-1, m_pSound, 0) == -1)
		std::cout << "WTF";
}



