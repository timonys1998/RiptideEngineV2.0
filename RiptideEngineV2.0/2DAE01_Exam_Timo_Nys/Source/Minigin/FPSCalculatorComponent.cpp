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
	m_FpsUpdateTimer += deltaTime;
	if(m_FpsUpdateTimer >= m_FpsMaxTimer)
	{
		m_FpsUpdateTimer = 0.0f;
		m_Fps = int(1 / deltaTime);
	}
	
}
