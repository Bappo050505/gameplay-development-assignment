#include "Input.h"
#include "InputManager.h"

bool Input::GetKeyDown(char key) { return GetKeyDown(SDL_Keycode(key)); }
bool Input::GetKeyDown(int key)
{
	return InputManager::Get()->GetKeyDown(SDL_Keycode(key));
}

bool Input::GetKeyHeld(char key) { return GetKeyHeld(SDL_Keycode(key)); }
bool Input::GetKeyHeld(int key)
{
	return InputManager::Get()->GetKeyHeld(SDL_Keycode(key));
}

bool Input::GetKeyUp(char key) { return GetKeyUp(SDL_Keycode(key)); }
bool Input::GetKeyUp(int key)
{
	return InputManager::Get()->GetKeyUp(SDL_Keycode(key));
}

bool Input::GetMouseDown(int buttonId)
{
	return InputManager::Get()->GetMouseDown(buttonId);
}

bool Input::GetMouseHeld(int buttonId)
{
	return InputManager::Get()->GetMouseHeld(buttonId);
}

bool Input::GetMouseUp(int buttonId)
{
	return InputManager::Get()->GetMouseUp(buttonId);
}

void Input::GetMousePos(float& x, float& y)
{
	InputManager::Get()->GetMousePos(x, y);
}

float Input::GetDeltaTime()
{
	return InputManager::Get()->GetDeltaTime();
}
