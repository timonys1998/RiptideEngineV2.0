#pragma once
#include "BaseComponent.h"

class FPSCalculatorComponent : public BaseComponent
{
public:
	FPSCalculatorComponent();
	~FPSCalculatorComponent();

	void Update(float deltaTime) override;
	int GetFps()const { return m_Fps; }
private:
	float m_FpsUpdateTimer = 0.0f;
	float m_FpsMaxTimer = 1.0f;
	int m_Fps = 0;
	
};

