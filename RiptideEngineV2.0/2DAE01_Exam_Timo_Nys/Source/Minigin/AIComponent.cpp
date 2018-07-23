#include "MiniginPCH.h"
#include "AIComponent.h"


AIComponent::AIComponent()
{
	
}


AIComponent::~AIComponent()
{
}

void AIComponent::GenerateNewMoveInstruction()
{
	int instructionIdx = rand() % 4;
	mMoveInstruction = MoveInstruction(instructionIdx);
}
