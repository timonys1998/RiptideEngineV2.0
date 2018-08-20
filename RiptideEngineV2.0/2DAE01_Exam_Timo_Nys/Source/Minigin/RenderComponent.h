#pragma once
#include "BaseComponent.h"
#include "GameObject.h"


struct FLOAT2;
class Texture2D;

class RenderComponent final : public BaseComponent
{
public:

	RenderComponent();
	~RenderComponent();

	RenderComponent(const RenderComponent& other) = delete;
	RenderComponent& operator=(const RenderComponent& other) = delete;
	RenderComponent(const RenderComponent&& other) = delete;
	RenderComponent& operator=(const RenderComponent&& other) = delete;

	void Update(float deltaTime) override { UNREFERENCED_PARAMETER(deltaTime); };
	void Render()const;
	void RenderTexture(std::shared_ptr<Texture2D> texture, const float x, const float y) const;
	void RenderTexture(std::shared_ptr<Texture2D> texture, const FLOAT2& pos) const;
	void RenderTexturesOfObject(FLOAT2& position,std::shared_ptr<GameObject> object)const;
	void RenderPlainText(FLOAT2& position, std::shared_ptr<GameObject> object)const;
	
	void EnableRendering(bool enable)
	{
		m_ShouldRender = enable;

	}
	bool ShouldRender()const { return m_ShouldRender; }
	std::shared_ptr<Texture2D> GetTextureToRender()const { return mTextureToRender; }
private:
	
	bool m_ShouldRender = true;
	std::shared_ptr<Texture2D> mTextureToRender;
};

