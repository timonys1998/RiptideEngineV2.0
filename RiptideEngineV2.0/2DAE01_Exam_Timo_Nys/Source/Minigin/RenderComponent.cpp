#include "MiniginPCH.h"
#include "RenderComponent.h"
#include "SDL.h"
#include "Texture2D.h"
#include "GameObject.h"
#include "RenderSystem.h"
#include "Structs.h"
#include "TextureComponent.h"
#include "TextComponent.h"


RenderComponent::RenderComponent()
{
	
}


RenderComponent::~RenderComponent()
{

}

void RenderComponent::Render() const
{
	if(m_ShouldRender)
	{
		auto objectToRender = GetOwner();
		FLOAT2 position{0.0f,0.0f};
		auto transform = objectToRender.lock()->GetComponent<Transform>();

		position.xVal = transform->GetPosition().xVal;
		position.yVal = transform->GetPosition().yVal;

		RenderTexturesOfObject(position, objectToRender.lock());
		RenderPlainText(position, objectToRender.lock());
	}
}

void RenderComponent::RenderTexture(std::shared_ptr<Texture2D> texture, const float x, const float y) const
{
	SDL_Rect dst;
	SDL_QueryTexture(texture->GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	dst.w = int(dst.w);
	dst.h = int(dst.h);
	dst.x = int(x);
	dst.y = int(y);

	//dst.x = static_cast<int>(x - (float)dst.w / 2.0f);
	//dst.y = static_cast<int>(y - (float)dst.h / 2.0f);

	SDL_RenderCopyEx(RenderSystem().GetInstance().GetSDLRenderer(), texture->GetSDLTexture(), nullptr, &dst, 0, NULL, SDL_FLIP_NONE);
}

void RenderComponent::RenderTexturesOfObject(FLOAT2& position, std::shared_ptr<GameObject> object)const 
{
	auto textures = object->GetAllComponentsOfType<TextureComponent>();
	auto renderPos{ position };
	if(!textures.size() == 0)
	{
		for(const auto t : textures)
		{
			renderPos = position;
			RenderTexture(t->GetTexture(), renderPos += t->GetOffset());
		}

	}

	
}

void RenderComponent::RenderPlainText(FLOAT2& position, std::shared_ptr<GameObject> object) const
{

	auto texts = object->GetAllComponentsOfType<TextComponent>();
	auto renderPos{ position };
	if (!texts.size() == 0)
	{
		for (const auto t : texts)
		{
			renderPos = position;
			RenderTexture(t->GetTexture(), renderPos += t->GetOffset());
		}
	}
}



void RenderComponent::RenderTexture(std::shared_ptr<Texture2D> texture, const FLOAT2& pos) const
{
	RenderTexture(texture, pos.xVal, pos.yVal);
}

