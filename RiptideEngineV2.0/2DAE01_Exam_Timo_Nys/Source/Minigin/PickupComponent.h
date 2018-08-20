#pragma once
#include "BaseComponent.h"
#include "Enums.h"

class PickupComponent final : public BaseComponent
{
public:
	PickupComponent(PickupType type);
	~PickupComponent();

	void Update(float deltaTime) override { UNREFERENCED_PARAMETER(deltaTime); };
	PickupType GetType()const { return m_Type; }

	PickupComponent(const PickupComponent& other) = delete;
	PickupComponent(const PickupComponent&& other) = delete;
	PickupComponent& operator=(const PickupComponent& other) = delete;
	PickupComponent& operator=(const PickupComponent&& other) = delete;

private:
	PickupType m_Type;
};

