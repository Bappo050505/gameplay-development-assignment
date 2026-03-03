#pragma once

struct SDL_Window;
// The entry point for creating a game. Used to create the game window and perform the
// build in update routines for the engine.
class GameScreen
{
public:
	// Constructor
	GameScreen();

	/// Generates a new SDL Screen with a title (passed in). 
	/// Width and Height do not need to be passed in, but can be for a custom screen size
	virtual bool CreateScreen(const char* gameTitle, int width = 1280, int height = 720, bool hideMouse = false) final;

	// Closes and Deactivates the active screen
	virtual void CloseScreen() final;

	// Call this to ensure the screen refreshes and input is tracked. Should be called every frame
	// It should also be the LAST thing called every frame as it detects whether to close the game.
	virtual void Update();

	/// <summary>
	/// Checks to see is the game is running.
	/// </summary>
	/// <returns>True is there is a game view, false otherwise.</returns>
	virtual bool IsRunning();

	// Set the clear colour of the screen. This will be the "background" colour for your game. 
	virtual void SetBackgroundRGB(int r, int g, int b) final;

private:
	SDL_Window* m_gameView;
};

