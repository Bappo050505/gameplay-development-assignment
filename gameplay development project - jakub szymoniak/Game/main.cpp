/// Note: 
/// This is the entry point for your game, should you choose to build from this solution.
/// The files in Gamewell are included in the additional directories for you, for the Game project
/// so #include "Gamewell_api.h" for example should just work anywhere.

#include "Gamewell_api.h"
#include "Game.h"
#include "entity.h"


int main()
{
	
	Game* game = new Game;
	game->initialize();


	do
	{
		game->Update();
		
	} while (game->GetScreen()->IsRunning());

	return 0;



}