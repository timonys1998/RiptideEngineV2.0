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
	for(const auto i : m_InputMap)
	{
		if (i.second == command)
			return;
	}
	m_InputMap[button] = command;
}

void InputComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
	
}

void InputComponent::RemoveInput(const Button& button)
{
	m_InputMap.erase(button);
}

void InputComponent::HandleInput()
{
	
	for(auto i : m_InputMap)
	{
		if(InputManager::GetInstance().IsPressed(i.first))
		{
			i.second->Execute(m_wpOwner.lock());
		}
	}
}
