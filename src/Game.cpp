#include "Game.h"

#include <iostream>

#define internal static

const double Game::MS_PER_UPDATE = (1.0 / FPS) * 1000;

internal inline bool IsReadyToRender(ALLEGRO_EVENT_QUEUE *eventQueue, ALLEGRO_EVENT event)
{
	return al_is_event_queue_empty(eventQueue) && event.type == ALLEGRO_EVENT_TIMER;
}

internal inline bool IsReadyToUpdate(ALLEGRO_EVENT event)
{
	return event.type == ALLEGRO_EVENT_TIMER;
}

internal inline bool WindowGotClosed(ALLEGRO_EVENT event)
{
	return event.type == ALLEGRO_EVENT_DISPLAY_CLOSE;
}

void Game::SetupAllegroInitialization()
{
	//Init and install input devices
	al_init();
	al_install_keyboard();
	al_install_mouse();
}

void Game::SetupDisplay()
{
	//set display flags for anti-aliasing
	al_set_new_display_flags(ALLEGRO_RESIZABLE);
	al_set_new_display_option(ALLEGRO_VSYNC, 1, ALLEGRO_SUGGEST);
	al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR);
	al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
	al_set_new_display_option(ALLEGRO_SAMPLES, 6, ALLEGRO_SUGGEST);

	//create display and give it a name
	_display = al_create_display(WIDTH, HEIGHT);
	al_set_window_title(_display, "Space Navies Arena");
}

void Game::SetupEventQueue()
{
	_eventQueue = al_create_event_queue();
	//register events from display, keyboard and mouse
	al_register_event_source(_eventQueue, al_get_display_event_source(_display));
	al_register_event_source(_eventQueue, al_get_keyboard_event_source());
	al_register_event_source(_eventQueue, al_get_mouse_event_source());
}

void Game::SetupTimer()
{
	_timer = al_create_timer(MS_PER_UPDATE);
	al_register_event_source(_eventQueue, al_get_timer_event_source(_timer));
	al_start_timer(_timer);
}

void Game::AllegroCleanup()
{
	al_destroy_display(_display);
	al_destroy_event_queue(_eventQueue);
	al_destroy_timer(_timer);
}

void Game::SwapBuffers() //and clear color
{
	al_flip_display();
	al_clear_to_color(al_map_rgb(0, 0, 0));
}

Game::Game() : _isRunning(true)
{
	//Allegro initializations
	SetupAllegroInitialization();
	SetupDisplay();
	SetupEventQueue();
	SetupTimer();
}

Game::~Game()
{
	AllegroCleanup();
	StatesCleanup();
}

void Game::ProcessInput()
{
}


void Game::Render()
{
	if (IsReadyToRender(_eventQueue, _event))
	{
		//Render
		//stuff

		//swap buffers and clear to color
		SwapBuffers();
	}
}


void Game::Update()
{
	if (IsReadyToUpdate(_event))
	{
		//Temporary assertion
		if (_states.size())
		{
			_states.top()->Update();
		}
		else
		{
			//TODO: Handle this in a different way, as this is just bullshit
			std::cerr << "_states stack is left empty" << std::endl;
			std::cin.get();
			Exit(); 
		}
	}
	else if (WindowGotClosed(_event))
	{
		Exit();
	}
}

void Game::Flush()
{
	al_wait_for_event(_eventQueue, &_event);
	al_flush_event_queue(_eventQueue);
}

void Game::ChangeState(State* newState)
{
	if (newState)
	{
		//conversion to unique pointer
		UniquePointerState uniquePointerNewState = std::unique_ptr<State>(newState);

		//push to _states container with the use of std::move neccessary when performing 
		//unq_ptr operations, since they have no copy constructor
		_states.push(std::move(uniquePointerNewState));
	}
	else
	{
		//TODO: Handle exception when the provided state is a nullptr
	}
}

void Game::LeaveState()
{
	_states.pop();
}

void Game::StatesCleanup()
{
	//iterates through each state, cleans up any memory allocations
	//and removes states from the stack as well.
	while (_states.size())
	{
		_states.top()->Cleanup();
		_states.pop();
	}
}