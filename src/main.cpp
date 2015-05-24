#include "Game.h"

#define internal static

//Main function
int main(int argc, char **argv)
{
	Game game;

	/*
		TODO: All this mess below may be enclosed in a while loop and a single method
		Description of how does the loop work - http://gameprogrammingpatterns.com/game-loop.html#play-catch-up	
	*/
	long int previous = GetCurrentTime();
	long int lag = 0;

	while (game.Running())
	{
		long int current = GetCurrentTime();
		long int elapsed = current - previous;
		previous = current;
		lag += elapsed;

		game.ProcessInput();

		while (lag >= Game::MS_PER_UPDATE)
		{
			game.Update(); //MS_PER_UPDATE is used as a time constant
			lag -= Game::MS_PER_UPDATE;
		}

		game.Render();
		game.Flush();
	}

	return 0;
}