#include "MiniginPCH.h"
#include "TextComponent.h"
#include "ResourceManager.h"
#include "RenderSystem.h"
#include "Texture2D.h"


TextComponent::TextComponent(const std::string& text, const FLOAT2& offset, bool shouldUpdate, const std::string& fontName, int fontSize, SDL_Color color)
	:m_Text(text)
	,m_Color(color)
	,m_ShouldUpdate(shouldUpdate)
	,m_Offset(offset)
{
	if(m_Font == nullptr)
	{
		m_Font = ResourceManager::GetInstance().LoadFont(fontName,fontSize);
	}
	const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), m_Color);
	if (surf == nullptr)
	{
		throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
	}
	auto texture = SDL_CreateTextureFromSurface(RenderSystem::GetInstance().GetSDLRenderer(), surf);
	if (texture == nullptr)
	{
		throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
	}
	SDL_FreeSurface(surf);
	m_Texture = std::make_shared<Texture2D>(texture);
}


TextComponent::~TextComponent()
{
}

void TextComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
	if (m_ShouldUpdate) {
		m_ShouldUpdate = false;
		const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), m_Color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(RenderSystem::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_Texture = std::make_shared<Texture2D>(texture);
	}
}

void TextComponent::SetText(std::string newText)
{
	m_Text = newText;
	m_ShouldUpdate = true;
}
