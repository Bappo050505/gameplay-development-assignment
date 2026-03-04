#pragma once
#define KEY Sint32

/// Note: These have been known to change from SDL version to version.
/// If the mouse input isn't working, change these to 1 and 2 respectively. 
#define LEFTMOUSEBUTTON 1
#define RIGHTMOUSEBUTTON 3

#define KEY_LEFT (80 | (1<<30))
#define KEY_RIGHT (79 | (1<<30))
#define KEY_DOWN (81 | (1<<30))
#define KEY_UP (82 | (1<<30))
#define KEY_SPACE ' '

class Input final
{
public:
	// Get if a key was pressed this frame
	// key: can be any keyboard char ('a', '2', '?') or KEY_LEFT/RIGHT/DOWN/UP or KEY_SPACE
	bool GetKeyDown(char key);
	// Get if a key was pressed this frame
	// key: can be any keyboard char ('a', '2', '?') or KEY_LEFT/RIGHT/DOWN/UP or KEY_SPACE
	bool GetKeyDown(int key);
	// Get if a key is held this frame
	// key: can be any keyboard char ('a', '2', '?') or KEY_LEFT/RIGHT/DOWN/UP or KEY_SPACE
	bool GetKeyHeld(char key);
	// Get if a key is held this frame
	// key: can be any keyboard char ('a', '2', '?') or KEY_LEFT/RIGHT/DOWN/UP or KEY_SPACE
	bool GetKeyHeld(int key);
	// Get if a key was released this frame
	// key: can be any keyboard char ('a', '2', '?') or KEY_LEFT/RIGHT/DOWN/UP or KEY_SPACE
	bool GetKeyUp(char key);
	// Get if a key was released this frame
	// key: can be any keyboard char ('a', '2', '?') or KEY_LEFT/RIGHT/DOWN/UP or KEY_SPACE
	bool GetKeyUp(int key);

	// Get if a mouse button was pressed this frame
	// buttonId can be LEFTMOUSEBUTTON or RIGHTMOUSEBUTTON. Other buttons may be bound to numbers (3, 4, 5 etc.)
	bool GetMouseDown(int buttonId);
	// Get if a mouse button is held this frame
	// buttonId can be LEFTMOUSEBUTTON or RIGHTMOUSEBUTTON. Other buttons may be bound to numbers (3, 4, 5 etc.)
	bool GetMouseHeld(int buttonId);
	// Get if a mouse button was released this frame
	// buttonId can be LEFTMOUSEBUTTON or RIGHTMOUSEBUTTON. Other buttons may be bound to numbers (3, 4, 5 etc.)
	bool GetMouseUp(int buttonId);

	// Gets the pixel location of the mouse on screen.
	void GetMousePos(float& x, float& y);

	// Gets the time between this frame and the previous one in seconds
	float GetDeltaTime();
};

