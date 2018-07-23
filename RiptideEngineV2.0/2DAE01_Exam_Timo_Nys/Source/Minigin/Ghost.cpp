#include "MiniginPCH.h"
#include "Ghost.h"
#include "TextureComponent.h"
#include "RenderComponent.h"
#include "AIComponent.h"
#include "Maths.h"


Ghost::Ghost(const glm::vec2& pos, const std::string texturePath)
	:mTexturePath(texturePath)
{
	GetComponent<Transform>()->SetPosition(pos.x, pos.y);
}


Ghost::~Ghost()
{
}

void Ghost::Init()
{
	AddComponent(std::make_shared<TextureComponent>(mTexturePath));
	AddComponent(std::make_shared<RenderComponent>(GetComponent<TextureComponent>()->GetTexture()));
	AddComponent(std::make_shared<AIComponent>());
}

void Ghost::Move(glm::vec2 futurePos, float deltaTime)
{
	if (mGoToNext)
	{
		mGoToNext = false;
		mCurrentPos = GetComponent<Transform>()->GetPosition();
		mFuturePos = futurePos;
	}
	auto pos = Lerp(mCurrentPos, mFuturePos, mMoveTimer);
	mMoveTimer += deltaTime;
	GetComponent<Transform>()->SetPosition(pos.x, pos.y);
	if (mMoveTimer >= 1.0f)
	{
		mMoveTimer = 0.0f;
		mGoToNext = true;
	}
}
