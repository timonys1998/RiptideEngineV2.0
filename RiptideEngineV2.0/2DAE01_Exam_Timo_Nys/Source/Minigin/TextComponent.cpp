#include "MiniginPCH.h"
#include "TextComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Texture2D.h"


TextComponent::TextComponent(std::string fontName,int fontSize,SDL_Color color, std::string text)
	:mText(text)
	,mColor(color)
{
	if(mFont == nullptr)
	{
		mFont = ResourceManager::GetInstance().LoadFont(fontName,fontSize);
	}
	

}


TextComponent::~TextComponent()
{
}

void TextComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
	if (mShouldUpdate) {
		mShouldUpdate = false;
		const auto surf = TTF_RenderText_Blended(mFont->GetFont(), mText.c_str(), mColor);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		mTexture = std::make_shared<Texture2D>(texture);
	}
}

void TextComponent::SetText(std::string newText)
{
	mText = newText;
	mShouldUpdate = true;
}
