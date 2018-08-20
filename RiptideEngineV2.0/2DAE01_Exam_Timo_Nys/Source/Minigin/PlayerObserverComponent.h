#pragma once
#include "ObserverComponent.h"

class PlayerObserverComponent : public ObserverComponent
{
public:
	PlayerObserverComponent();
	~PlayerObserverComponent();

	void OnNotify(std::shared_ptr<GameObject> entity, Event e) override;
};

