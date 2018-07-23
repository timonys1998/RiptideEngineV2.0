#pragma once
#include "BaseComponent.h"

class FPSCalculatorComponent : public BaseComponent
{
public:
	FPSCalculatorComponent();
	~FPSCalculatorComponent();

	void Update(float deltaTime) override;
	int GetFps()const { return mFps; }
private:
	int mFps = 0;
};

