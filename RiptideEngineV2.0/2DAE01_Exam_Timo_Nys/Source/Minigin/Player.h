#pragma once
#include "GameObject.h"

class Player : public GameObject
{
	
public:
	enum Dir
	{
		RIGHT,
		LEFT,
		UP,
		DOWN
	};
	enum ControlsType
	{
		KEYBOARD,
		CONTROLLER
	};
	explicit Player(const glm::vec2& pos,const std::string texturePath,ControlsType controllerType = KEYBOARD);
	virtual ~Player();

	void Init() override;
	Dir GetDirection()const { return  mDirection; }
	void SetDirection(Dir direction);
	void Move( glm::vec2 futurePos,float deltaTime);
	void Die();

	bool IsAlive()const { return mIsAlive; }
	int GetLives()const { return mLives; }
private:
	void Respawn();

	glm::vec2 mCurrentPos;
	glm::vec2 mFuturePos;
	const std::string mTexturePath;
	Dir mDirection = LEFT;
	
	ControlsType mControllerType;
	float mMoveTimer = 0.0f;
	bool mGoToNext = true;
	bool mIsAlive = true;;
	int mLives = 3;
};

