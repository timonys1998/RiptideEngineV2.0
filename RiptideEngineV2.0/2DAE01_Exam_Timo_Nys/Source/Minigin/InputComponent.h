#pragma once
#include "BaseComponent.h"
#include <map>
#include "Command.h"

class InputComponent final : public BaseComponent
{
public:
	enum class Button
	{
		//Controller
		DPAD_UP,
		DPAD_DOWN,
		DPAD_RIGHT,
		DPAD_LEFT,
		Button_X,
		Button_B,


		//Keyboard
		LEFTARROW,
		UPARROW,
		DOWNARROW,
		RIGHTARROW,
		SPACE,
		ENTER,
		NUM1,
		NUM2,
		NUM3,

		//Mouse
		LeftMouseButton
	};

	explicit InputComponent();
	virtual ~InputComponent();

	InputComponent(const InputComponent& other) = delete;
	InputComponent& operator=(const InputComponent& other) = delete;
	InputComponent(const InputComponent&& other) = delete;
	InputComponent& operator=(const InputComponent&& other) = delete;

	void Update(float deltaTime) override;
	void AddInput(const Button& button, const std::shared_ptr<Command> command);
	void RemoveInput(const Button& button);
	void HandleInput();
private:
	std::map<Button, std::shared_ptr<Command>> m_InputMap;
};

