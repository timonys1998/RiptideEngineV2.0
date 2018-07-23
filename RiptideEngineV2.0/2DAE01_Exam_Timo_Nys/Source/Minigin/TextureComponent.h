#pragma once
#include "BaseComponent.h"
#include "Texture2D.h"

class TextureComponent final : public BaseComponent
{
public:
	explicit TextureComponent(std::string filename, int width = 32, int = 32);
	virtual ~TextureComponent();

	void Update(float deltaTime) override { UNREFERENCED_PARAMETER(deltaTime); };
	std::shared_ptr<Texture2D> GetTexture()const { return mTexture; }
	int GetWidth()const { return mWidth; }
	int GetHeight() const { return mHeight; }
private:
	std::shared_ptr<Texture2D> mTexture;
	int mWidth, mHeight;
};

