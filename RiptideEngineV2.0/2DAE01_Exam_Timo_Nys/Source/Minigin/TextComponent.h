#pragma once
#include "BaseComponent.h"
#include "Font.h"
#include "Texture2D.h"


class TextComponent : public BaseComponent
{
public:
	TextComponent(std::string fontName , int fontSize = 36,SDL_Color color = { 255,255,255 }, std::string text = "Text");
	~TextComponent();

	void Update(float deltaTime) override;
	void SetText(std::string newText);
	std::shared_ptr<Texture2D> GetTexture()const { return mTexture; }
private:
	std::shared_ptr<Font>	mFont;
	std::string mText;
	std::shared_ptr<Texture2D> mTexture;
	const SDL_Color mColor;
	bool mShouldUpdate = true;
};

