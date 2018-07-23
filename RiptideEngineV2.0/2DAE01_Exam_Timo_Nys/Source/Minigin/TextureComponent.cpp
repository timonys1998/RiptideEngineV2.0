#include "MiniginPCH.h"
#include "TextureComponent.h"
#include "ResourceManager.h"
#include <SDL.h>


TextureComponent::TextureComponent(std::string filename,int width,int height)
	:mWidth(width)
	,mHeight(height)
{
	if (mTexture == nullptr) {
		mTexture = ResourceManager::GetInstance().LoadTexture(filename);
	}
}



TextureComponent::~TextureComponent()
{
}
