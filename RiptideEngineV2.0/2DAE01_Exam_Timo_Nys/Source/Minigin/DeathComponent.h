#pragma once
#include "BaseComponent.h"

class DeathComponent : public BaseComponent
{
public:
	DeathComponent();
	~DeathComponent();

	void Update(float deltaTime) override { UNREFERENCED_PARAMETER(deltaTime); };
	void Die()const;

	DeathComponent(const DeathComponent& other) = delete;
	DeathComponent(const DeathComponent&& other) = delete;
	DeathComponent& operator=(const DeathComponent& other) = delete;
	DeathComponent& operator=(const DeathComponent&& other) = delete;

};

