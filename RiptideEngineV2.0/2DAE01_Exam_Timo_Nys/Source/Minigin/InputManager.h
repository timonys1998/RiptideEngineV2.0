#pragma once
#include <XInput.h>
#include "Singleton.h"
#include "InputComponent.h"


	class InputManager final : public Singleton<InputManager>
	{
	public:
		void HandleInput();
		bool IsPressed(InputComponent::Button button) const;
	private:
		XINPUT_STATE currentState{};
	};

