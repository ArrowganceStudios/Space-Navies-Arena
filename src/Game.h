#pragma once
#include <stack>
#include <forward_list>
#include <memory>

#include <allegro5/allegro.h>

#include "States.h"

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
	typedef std::unique_ptr<State> UniquePointerState; //not sure if this is really right place to put it

	/**
		Sets up allegro initialization
	*/
	Game();

	/**
		Performs cleaning of allegro objects
	*/
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

	/**
		Performs a conversion from State to UniquePointerState, and pushes it on top of the stack
		so that it becomes a current state
	*/
	void ChangeState(State* newState);

	/**
		Pops current state out of the stack, so that we return to the previous state
	*/
	void LeaveState();

private:
	//state related
	std::stack <UniquePointerState> _states;
	void StatesCleanup();

	//input related
	std::forward_list <int> _pressedKeys;

	//loop related
	void Exit() { _isRunning = false; }

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