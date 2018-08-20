#pragma once
#include "BaseComponent.h"
#include "Enums.h"

class GameModeSelectorComponent final : public BaseComponent
{
public:
	GameModeSelectorComponent();
	virtual ~GameModeSelectorComponent();

	GameModeSelectorComponent(const GameModeSelectorComponent& other) = delete;
	GameModeSelectorComponent(const GameModeSelectorComponent&& other) = delete;
	GameModeSelectorComponent& operator=(const GameModeSelectorComponent& other) = delete;
	GameModeSelectorComponent& operator=(const GameModeSelectorComponent&& other) = delete;

	void Update(float deltaTime) override
	{
		UNREFERENCED_PARAMETER(deltaTime);
	};

	void LoadGame(GameMode mode);
};

