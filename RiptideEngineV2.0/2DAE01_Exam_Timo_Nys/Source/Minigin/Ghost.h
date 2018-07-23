#pragma once
#include "GameObject.h"

class Ghost : public GameObject
{
public:
	explicit Ghost(const glm::vec2& pos, const std::string texturePath);
	virtual ~Ghost();

	void Init()override;
	void Move(glm::vec2 futurePos, float deltaTime);

private:
	std::string mTexturePath;
	glm::vec2 mCurrentPos;
	glm::vec2 mFuturePos;

	float mMoveTimer = 0.0f;
	bool mGoToNext = true;
};

