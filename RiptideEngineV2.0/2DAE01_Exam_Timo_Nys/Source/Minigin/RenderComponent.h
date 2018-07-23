#pragma once
#include "BaseComponent.h"
#include "GameObject.h"


	class Texture2D;


class RenderComponent final : public BaseComponent
{
public:

	RenderComponent(std::shared_ptr<Texture2D> textureToRender);
	~RenderComponent();

	

	void Update(float deltaTime) override { UNREFERENCED_PARAMETER(deltaTime); };

	void RenderTexture() const;
	
	void EnableRendering(bool enable)
	{
		m_ShouldRender = enable;

	}
	void ChangeRenderingTexture(std::shared_ptr<Texture2D> texture) { mTextureToRender = texture; }
	bool ShouldRender()const { return m_ShouldRender; }
	std::shared_ptr<Texture2D> GetTextureToRender()const { return mTextureToRender; }
private:
	
	bool m_ShouldRender = true;
	std::shared_ptr<Texture2D> mTextureToRender;
};

