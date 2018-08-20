
#include "MiniginPCH.h"
#include "BaseComponent.h"
#include <SDL_mixer.h>

class SoundEffectComponent : public BaseComponent
{
public:
	SoundEffectComponent(const std::string& soundFile);
	~SoundEffectComponent();
	void PlaySound();
	void Update(float deltaTime) override { UNREFERENCED_PARAMETER(deltaTime); };
private:
	Mix_Chunk * m_pSound;
};
