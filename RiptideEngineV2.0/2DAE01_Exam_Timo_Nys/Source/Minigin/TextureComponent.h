#pragma once
#include "BaseComponent.h"
#include "Texture2D.h"
#include "Structs.h"


class TextureComponent final : public BaseComponent
{
public:
	explicit TextureComponent(const std::string& filepath, bool visible,const FLOAT2& posOffset);
	explicit TextureComponent(const std::string& filepath, bool visible);
	explicit TextureComponent(const std::string& filepath);
	~TextureComponent();

	TextureComponent(const TextureComponent& other) = delete;
	TextureComponent(const TextureComponent&& other) = delete;
	TextureComponent& operator=(const TextureComponent& other) = delete;
	TextureComponent& operator=(const TextureComponent&& other) = delete;

	void Update(float deltaTime) override { UNREFERENCED_PARAMETER(deltaTime); };

	std::shared_ptr<Texture2D> GetTexture()const { return m_spTexture; }
	int GetWidth()const { return m_Width; }
	int GetHeight() const { return m_Height; }
	FLOAT2 GetOffset() const{ return m_PosOffset; }

	void SetVisible(bool visible) { m_IsVisible = visible; };
private:
	std::string m_FilePath;
	std::shared_ptr<Texture2D> m_spTexture;
	FLOAT2 m_PosOffset;
	bool m_IsVisible;
	int m_Width, m_Height;
};

