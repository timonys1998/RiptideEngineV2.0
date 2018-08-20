#pragma once
#include "BaseComponent.h"
#include "Enums.h"

class ObserverComponent : public BaseComponent
{
public:
	ObserverComponent();
	virtual ~ObserverComponent();

	ObserverComponent(const ObserverComponent& other) = delete;
	ObserverComponent(const ObserverComponent&& other) = delete;
	ObserverComponent& operator=(const ObserverComponent& other) = delete;
	ObserverComponent& operator=(const ObserverComponent&& other) = delete;

	void Update(float deltaTime) override { UNREFERENCED_PARAMETER(deltaTime); };
	virtual void OnNotify(std::shared_ptr<GameObject> entity, Event e) = 0;
};

