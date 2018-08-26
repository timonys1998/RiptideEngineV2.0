#pragma once
#include "MiniginPCH.h"
#include "BaseComponent.h"
#include <SDL_mixer.h>

class SoundEffectComponent final : public BaseComponent
{
public:
	SoundEffectComponent(const std::string& soundFile);
	~SoundEffectComponent();
	void PlaySound();
	void Update(float deltaTime) override { UNREFERENCED_PARAMETER(deltaTime); };

	SoundEffectComponent(const SoundEffectComponent& other) = delete;
	SoundEffectComponent(const SoundEffectComponent&& other) = delete;
	SoundEffectComponent& operator=(const SoundEffectComponent& other) = delete;
	SoundEffectComponent& operator=(const SoundEffectComponent&& other) = delete;
private:
	Mix_Chunk * m_pSound;
};
