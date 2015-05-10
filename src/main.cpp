#include "Game.h"
#include <time.h>
#define internal static

//Miliseconds used per single update, a time constant
//TODO: Should be moved somewhere where we will hold constant project values at.
const int MS_PER_UPDATE = 16;

//Main function
int main(int argc, char **argv)
{
	Game game;
	/*
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

		while (lag >= MS_PER_UPDATE)
		{
			game.Update(); //MS_PER_UPDATE is used as a time constant
			lag -= MS_PER_UPDATE;
		}

		game.Render();
		game.Flush();
	}

	return 0;
}