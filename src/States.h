#pragma once

/**
	State is an abstract class of a game state, from which other states inherit. Instances of those
	are stored inside of the stack container of Game class. Find more at: 
	http://gamedevgeek.com/tutorials/managing-game-states-in-c/
*/

class State
{
public:
	virtual void Init() = 0;
	virtual void Cleanup() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Input() = 0;
};

class MenuState : public State
{
public:
	
	/**
		Initialization of menu state, background graphic and etc TBI
	*/
	void Init();

	/**
		Deletes  all the allocated data and other yet to be implemented stuff
	*/
	void Cleanup();

	/**
		Interprets input from the mouse/keyboard regarding button clicks and mouseovers
	*/
	void Update();

	/**
		Draws menu background and buttons.
	*/
	void Render();

	/**
		Mouse/keyboard interpretation of movement inside of the menu
	*/
	void Input();
};

class GameState : public State
{
public:
	/**
		Resetting all meaningful variables to its default values (stored inside xxx.xxx file)
	*/
	void Init();

	/**
		Deletes objects created by the use of dynamic memory allocation. (Ships and lightings if they did persist)
	*/
	void Cleanup();

	/**
		Update loop going through the object list, and updating each of them.
		http://gameprogrammingpatterns.com/update-method.html
	*/
	void Update();

	/**
		Draws Ships and lightings (and background).
	*/
	void Render();

	/**
		Passes the Game::_pressedKeys to the player for further interpretation.
	*/
	void Input();
};