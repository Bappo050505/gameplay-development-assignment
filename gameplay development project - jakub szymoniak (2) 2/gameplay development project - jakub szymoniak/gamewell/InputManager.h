#pragma once
#include <vector>
#include <SDL_keycode.h>
#include <SDL_events.h>

#define KEY SDL_Keycode

/// For detecting system events. Currently just Quit, but can be expanded easily - see Update.
enum RETURN_CODE {NONE, QUIT};

class InputManager
{
public:
	static void Create();
	static void Destroy();
	static InputManager* Get() { return s_instance; };
	~InputManager();

	RETURN_CODE Update();

	bool GetKeyDown(KEY key);
	bool GetKeyHeld(KEY key);
	bool GetKeyUp(KEY key);

	bool GetMouseDown(int buttonId);
	bool GetMouseHeld(int buttonId);
	bool GetMouseUp	 (int buttonId);

	void GetMousePos(float& x, float& y);

	// Seconds
	float GetDeltaTime();

	// Get the current time relative to the game start in milliseconds
	float Now();

private:
	static InputManager* s_instance;
	InputManager();

	int* m_keys;
	std::vector<SDL_Keycode> m_keyDownEvents, m_keyUpEvents;
	int* m_mouseButtons;
	int m_mouseX, m_mouseY;
	double m_deltaTime, m_lastTime, m_startTime;
};

