#include "Game.h"
#include <time.h>
#define internal static

//Miliseconds used per single update, a time constant
//TODO: Should be moved somewhere where we will hold constant project values at.
const int MS_PER_UPDATE = 16;

//Returns time elapsed since the launch of the program in miliseconds
internal clock_t GetCurrentTime()
{
	clock_t time = clock();
	return (time * 1000) / CLOCKS_PER_SEC; //that is set for system compatibility
}

//Main function
int main(int argc, char **argv)
{
	Game game;
	/*
		Description of how does the loop work - http://gameprogrammingpatterns.com/game-loop.html#play-catch-up	
	*/

	long int previous = GetCurrentTime();
	long int lag = 0;

	while (true)
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
	}

	return 0;
}