#include "MiniginPCH.h"
#include "FPSCalculatorComponent.h"


FPSCalculatorComponent::FPSCalculatorComponent()
{
}


FPSCalculatorComponent::~FPSCalculatorComponent()
{
}

void FPSCalculatorComponent::Update(float deltaTime)
{
	mFps = int(1 / deltaTime);
}
