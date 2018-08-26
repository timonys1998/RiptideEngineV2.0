#include "MiniginPCH.h"
#include "InputManager.h"
#include <SDL.h>
#include "InputComponent.h"
#include <cassert>
#include "SceneManager.h"
#include "Scene.h"


void InputManager::HandleInput()
{
	ZeroMemory(&currentState, sizeof(XINPUT_STATE));
	XInputGetState(0, &currentState);

	auto activeScene = SceneManager::GetInstance().GetActiveScene();
	auto sceneObjects = activeScene->GetObjects();
	for (unsigned int i = 0; i < sceneObjects.size(); ++i)
	{
		auto inpCom = sceneObjects.at(i)->GetComponent<InputComponent>();
		if (inpCom)
			inpCom->HandleInput();
	}
	
}

bool InputManager::IsPressed(InputComponent::Button button) const
{
	switch(button)
	{
	case InputComponent::Button::DPAD_UP:
		return currentState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP;
	case InputComponent::Button::DPAD_DOWN:
		return currentState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN;
	case InputComponent::Button::DPAD_RIGHT:
		return currentState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT;
	case InputComponent::Button::DPAD_LEFT:
		return currentState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT;
	case InputComponent::Button::Button_X:
		return currentState.Gamepad.wButtons & XINPUT_GAMEPAD_X; 
	case InputComponent::Button::Button_B:
		return currentState.Gamepad.wButtons & XINPUT_GAMEPAD_B;
	case InputComponent::Button::UPARROW:
		if (GetAsyncKeyState(VK_UP) & 0x8000)return true;
		return false;
	case InputComponent::Button::DOWNARROW:
		if (GetAsyncKeyState(VK_DOWN) & 0x8000)return true;
		return false;
	case InputComponent::Button::RIGHTARROW:
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000)return true;
		return false;
	case InputComponent::Button::LEFTARROW:
		if (GetAsyncKeyState(VK_LEFT) & 0x8000)return true;
		return false;
	case InputComponent::Button::SPACE:
		if (GetAsyncKeyState(VK_SPACE) & 0x8000)return true;
		return false;
	case InputComponent::Button::ENTER:
		if (GetAsyncKeyState(VK_RETURN) & 0x8000)return true;
		return false;
	case InputComponent::Button::NUM1:
		if (GetAsyncKeyState(SDLK_1) & 0x8000)return true;
		return false;
	case InputComponent::Button::NUM2:
		if (GetAsyncKeyState(SDLK_2) & 0x8000)return true;
		return false;
	case InputComponent::Button::NUM3:
		if (GetAsyncKeyState(SDLK_3) & 0x8000)return true;
		return false;
	case InputComponent::Button::LeftMouseButton:
		if (GetAsyncKeyState(SDL_BUTTON_LEFT) & 0x8000)return true;
		return false;
	default: return false;
	}
}

