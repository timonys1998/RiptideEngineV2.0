#pragma once
#include "BaseComponent.h"

class AIComponent : public BaseComponent
{
	
public:
	enum MoveInstruction
	{
		UP = 0,
		DOWN = 1,
		LEFT = 2,
		RIGHT = 3
	};
	explicit AIComponent();
	virtual ~AIComponent();

	void Update(float deltaTime) override { UNREFERENCED_PARAMETER(deltaTime); }
	void GenerateNewMoveInstruction();
	MoveInstruction GetInstruction()const { return mMoveInstruction; }

private:
	MoveInstruction mMoveInstruction = UP;
};

