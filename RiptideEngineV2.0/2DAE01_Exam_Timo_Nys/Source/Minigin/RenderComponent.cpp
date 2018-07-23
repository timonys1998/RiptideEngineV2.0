#include "MiniginPCH.h"
#include "RenderComponent.h"
#include "SDL.h"
#include "Renderer.h"
#include "Texture2D.h"
#include "GameObject.h"



RenderComponent::RenderComponent(std::shared_ptr<Texture2D> textureToRender)
	:mTextureToRender(textureToRender)
{
	mTextureToRender = textureToRender;
}


RenderComponent::~RenderComponent()
{
}

void RenderComponent::RenderTexture() const
{
	SDL_Rect dst;
	dst.x = static_cast<int>(mOwner.lock()->GetComponent<Transform>()->GetPosition().x);
	dst.y = static_cast<int>(mOwner.lock()->GetComponent<Transform>()->GetPosition().y);
	SDL_QueryTexture(mTextureToRender->GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	SDL_RenderCopy(Renderer::GetInstance().GetSDLRenderer(), mTextureToRender->GetSDLTexture(), nullptr, &dst);
}

