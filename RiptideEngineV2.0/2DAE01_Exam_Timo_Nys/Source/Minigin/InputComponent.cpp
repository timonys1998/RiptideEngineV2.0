#include "MiniginPCH.h"
#include "InputComponent.h"
#include "InputManager.h"


InputComponent::InputComponent()
{
}


InputComponent::~InputComponent()
{
}

void InputComponent::AddInput(const Button& button, const std::shared_ptr<Command> command)
{
	mInputMap[button] = command;
}

void InputComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
	HandleInput();
}

void InputComponent::RemoveInput(const Button& button)
{
	mInputMap.erase(button);
}

void InputComponent::HandleInput()
{
	for(auto b : mInputMap)
	{
		if(InputManager::GetInstance().IsPressed(b.first))
		{
			b.second->Execute();
		}
	}
}
