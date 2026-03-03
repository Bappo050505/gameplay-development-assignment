#include "InputManager.h"
#include <SDL.h>
#include <iostream>
#include <chrono>

InputManager* InputManager::s_instance = nullptr;

void InputManager::Create()
{
	if (!s_instance)
	{
		s_instance = new InputManager();
	}
	else
	{
		std::cout << "Instance of InputManager already exists!\n";
	}
}
void InputManager::Destroy()
{
	if (s_instance)
	{
		delete s_instance;
		s_instance = nullptr;
	}
}

InputManager::InputManager():m_mouseX(0),m_mouseY(0),m_deltaTime(0), m_lastTime(0), m_startTime(std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count())
{
	m_keys = new int[SDL_SCANCODE_ENDCALL] {0};
	m_mouseButtons = new int[5]{0}; // Unsafe? Can a mosue have more buttons?
	
}

InputManager::~InputManager()
{
	delete[] m_keys;
	delete[] m_mouseButtons;
}

RETURN_CODE InputManager::Update()
{
	// Bad place to do this but it's internal so...
	float now = Now();
	m_deltaTime = (now - m_lastTime)/1000;
	m_lastTime = now;

	m_keyDownEvents.clear();
	m_keyUpEvents.clear();

	for (int i = 0; i < 5; ++i)
	{
		if (m_mouseButtons[i] == 2) m_mouseButtons[i] = 1;
		if (m_mouseButtons[i] == -1) m_mouseButtons[i] = 0;
	}

	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		switch (e.type)
		{
		case SDL_KEYDOWN:
		{
			m_keyDownEvents.push_back(e.key.keysym.sym);
			m_keys[e.key.keysym.scancode] = 1;
			break;
		}
		case SDL_KEYUP:
		{
			m_keyUpEvents.push_back(e.key.keysym.sym);
			m_keys[e.key.keysym.scancode] = 0;
			break;
		}

		case SDL_MOUSEMOTION:
		{
			m_mouseX = e.motion.x;
			m_mouseY = e.motion.y;

			break;
		}

		case SDL_MOUSEBUTTONDOWN:
		{
			m_mouseButtons[e.button.button] = 2;
			break;
		}
		case SDL_MOUSEBUTTONUP:
		{
			m_mouseButtons[e.button.button] = -1;
			break;
		}
		case SDL_QUIT:
		{
			return QUIT;
		}
		}
	}
	return NONE;
}

bool InputManager::GetKeyDown(SDL_Keycode key)
{
	for (SDL_Keycode k : m_keyDownEvents)
	{
		if (key == k)
			return true;
	}
	return false;
}

bool InputManager::GetKeyHeld(SDL_Keycode key)
{
	return (bool)m_keys[SDL_GetScancodeFromKey(key)];
}

bool InputManager::GetKeyUp(SDL_Keycode key)
{
	for (SDL_Keycode k : m_keyUpEvents)
	{
		if (key == k)
			return true;
	}
	return false;
}

bool InputManager::GetMouseDown(int buttonId)
{
	return m_mouseButtons[buttonId] == 2;
}

bool InputManager::GetMouseHeld(int buttonId)
{
	return m_mouseButtons[buttonId] > 0;
}

bool InputManager::GetMouseUp(int buttonId)
{
	return m_mouseButtons[buttonId] == -1;
}

void InputManager::GetMousePos(int& x, int& y)
{
	x = m_mouseX; 
	y = m_mouseY;
	return;
}

float InputManager::GetDeltaTime()
{
	return m_deltaTime;
}

float InputManager::Now()
{
	return (std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count() - m_startTime) / 1000.f;
}
