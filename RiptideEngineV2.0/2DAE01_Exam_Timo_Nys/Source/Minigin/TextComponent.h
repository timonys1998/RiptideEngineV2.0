#pragma once
#include "BaseComponent.h"
#include "Font.h"
#include "Texture2D.h"
#include "Structs.h"




class TextComponent : public BaseComponent
{
public:
	TextComponent(const std::string& text,const FLOAT2& offset = FLOAT2(0.0f,0.0f),bool shouldUpdate = false ,const std::string& fontName = "Lingua.otf" , int fontSize = 24,SDL_Color color = { 255,255,255 } );
	~TextComponent();

	TextComponent(const TextComponent& other) = delete;
	TextComponent(const TextComponent&& other) = delete;
	TextComponent& operator=(const TextComponent& other) = delete;
	TextComponent& operator=(const TextComponent&& other) = delete;


	void Update(float deltaTime) override;
	void SetText(std::string newText);
	std::shared_ptr<Texture2D> GetTexture()const { return m_Texture; }
	FLOAT2 GetOffset()const { return m_Offset; }
private:
	std::shared_ptr<Font>m_Font;
	FLOAT2 m_Offset;
	std::string m_Text;
	std::shared_ptr<Texture2D> m_Texture;
	const SDL_Color m_Color;
	bool m_ShouldUpdate = true;
};

