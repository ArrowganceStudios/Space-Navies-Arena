#pragma once
#include <vector>
#include <allegro5/allegro.h>

/*
	The general purpose game engine class.
	It's main functionality is contained inside the following diagram:
	http://i.imgur.com/tXcgjDk.png

	There should be only a single instance of the Game at the time.

	NOTE: It should still be decided whether it will be a singleton, a local main variable or global.

*/

class Game
{
public:
	Game();
	~Game();

	/**
		TBI

		Processing Input contains a series of if statements used to determine what keys have been pressed
		and for creation of vector containg enumartion values of aforementioned keys inside pressedKeys container
	*/
	void ProcessInput();

	/**
		TBI
		The following description is a subject to change
		Render function iterates through the container of GameObjects calling render on each of them.
		
	*/
	void Render();

	/**
		TBI

		Update function iterates through the container of GameObjects calling update on each of them.
	*/
	void Update();

	/**
		Used for the gameloop condition control, when done = true, the loop is stopped, and program terminated.
	*/
	bool Running() const { return _isRunning; }

	/**
		Used for Allegro event queue flushing and loading a new event into the queue
	*/
	void Flush();

private:
	void Exit() { _isRunning = false; }

	std::vector <int> _pressedKeys;
	bool _isRunning;

	//Allegro related
	void SetupAllegroInitialization();
	void SetupDisplay();
	void SetupEventQueue();
	void SetupTimer();

	void SwapBuffers();

	void AllegroCleanup();

	ALLEGRO_DISPLAY *_display;
	ALLEGRO_EVENT_QUEUE *_eventQueue;
	ALLEGRO_EVENT _event;
	ALLEGRO_TIMER *_timer;

	//copying disabled
	Game(const Game&);
	const Game& operator=(const Game&);
};

