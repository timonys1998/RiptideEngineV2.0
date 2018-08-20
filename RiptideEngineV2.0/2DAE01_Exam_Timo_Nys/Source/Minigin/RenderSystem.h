#pragma once
#include "Singleton.h"

struct SDL_Texture;
struct SDL_Window;
struct SDL_Renderer;

class RenderSystem final : public Singleton<RenderSystem>
{
	SDL_Renderer* m_pRenderer = nullptr;

public:
	void Init(SDL_Window* window);
	void Render()const;
	void Destroy();


	SDL_Renderer* GetSDLRenderer() const { return m_pRenderer; }

private:
	
};