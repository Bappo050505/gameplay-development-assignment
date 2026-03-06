#include "GameScreen.h"
#include "Renderer.h"
#include "InputManager.h"
#include "SDL.h"



GameScreen::GameScreen(): m_gameView(nullptr)
{
}

bool GameScreen::CreateScreen(const char* gameTitle, int width, int height, bool hideMouse)
{
	if (SDL_Init(SDL_INIT_EVERYTHING))
	{
		return false;
	}

	if (hideMouse)
	{
		SDL_ShowCursor(SDL_DISABLE);
	}

	m_gameView = SDL_CreateWindow(gameTitle, 20, 40, width, height, 0);
	SDL_Renderer* renderer = SDL_CreateRenderer(m_gameView, -1, 0);
	Renderer::Create(renderer);
	InputManager::Create();

	return true;
}

void GameScreen::CloseScreen()
{
	Renderer::Destroy();
	InputManager::Destroy();
	SDL_DestroyWindow(m_gameView);
	m_gameView = nullptr;
}

void GameScreen::Update()
{
	SDL_Delay(1000/60);
	Renderer::Get()->Update();


	// Do this last!
	if (InputManager::Get()->Update() == QUIT)
	{
		CloseScreen();
	}

}

bool GameScreen::IsRunning()
{
	return m_gameView != nullptr;
}

void GameScreen::SetBackgroundRGB(int r, int g, int b)
{
	Renderer::Get()->SetRenderDrawColour(r, g, b);
}

