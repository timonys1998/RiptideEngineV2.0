#pragma once
#include "BaseComponent.h"
#include "ObserverComponent.h"

enum class Event;

class SubjectComponent final : public BaseComponent
{
public:
	SubjectComponent();
	~SubjectComponent();

	SubjectComponent(const SubjectComponent& other) = delete;
	SubjectComponent(const SubjectComponent&& other) = delete;
	SubjectComponent& operator=(const SubjectComponent& other) = delete;
	SubjectComponent& operator=(const SubjectComponent&& other) = delete;

	void Attach(std::shared_ptr<ObserverComponent> observer);
	void Detach(std::shared_ptr<ObserverComponent> observer);

	void Update(float deltaTime) override { UNREFERENCED_PARAMETER(deltaTime); };
	void Notify(std::shared_ptr<GameObject> entity, Event e);
private:
	std::vector<std::shared_ptr<ObserverComponent>> m_spObservers;
};

