#include "MiniginPCH.h"
#include "Pill.h"
#include "TextureComponent.h"
#include "RenderComponent.h"

int Pill::mCount = 0;

Pill::Pill(const glm::vec2& pos, bool isBig)
	:mIsBig(isBig)
{
	++mCount;
	GetComponent<Transform>()->SetPosition(pos.x, pos.y);
}

Pill::~Pill()
{
}

void Pill::Init()
{
	if(!mIsBig)
	{
		AddComponent(std::make_shared<TextureComponent>("SmallPillPickup.png"));
	}
	else
	{
		AddComponent(std::make_shared<TextureComponent>("LargePillPickup.png"));
	}
	AddComponent(std::make_shared<RenderComponent>(GetComponent<TextureComponent>()->GetTexture()));
}
