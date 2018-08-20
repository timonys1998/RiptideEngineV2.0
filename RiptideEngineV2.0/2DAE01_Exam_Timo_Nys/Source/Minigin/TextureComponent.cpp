#include "MiniginPCH.h"
#include "TextureComponent.h"
#include "ResourceManager.h"
#include <SDL.h>



TextureComponent::TextureComponent(const std::string& filepath, bool visible, const FLOAT2& posOffset)
	:m_FilePath(filepath)
	,m_IsVisible(visible)
	,m_PosOffset(posOffset)
{
	if (m_spTexture == nullptr) {
		m_spTexture = ResourceManager::GetInstance().LoadTexture(filepath);
		SDL_QueryTexture(m_spTexture->GetSDLTexture(), nullptr, nullptr, &m_Width, &m_Height);
	}
}

TextureComponent::TextureComponent(const std::string& filepath, bool visible)
	:TextureComponent(filepath,visible,FLOAT2(0.0f,0.0f))
{
	
}

TextureComponent::TextureComponent(const std::string& filepath)
	:TextureComponent(filepath,true,FLOAT2(0.0f,0.0f))
{

}


TextureComponent::~TextureComponent()
{
	
}
