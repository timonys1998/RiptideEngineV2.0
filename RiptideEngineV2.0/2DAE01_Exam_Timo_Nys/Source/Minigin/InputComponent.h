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

		//Keyboard
		LEFTARROW,
		UPARROW,
		DOWNARROW,
		RIGHTARROW,
		NUM1,
		NUM2,
		NUM3
	};

	explicit InputComponent();
	virtual ~InputComponent();

	void Update(float deltaTime) override;
	void AddInput(const Button& button, const std::shared_ptr<Command> command);
	void RemoveInput(const Button& button);
	void HandleInput();
private:
	std::map<Button, std::shared_ptr<Command>> mInputMap;
};

