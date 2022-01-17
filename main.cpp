// TO DO:
// draw background in green if won, red if lost
// record number of moves or longest length as high score

#include <iostream>
#include <SDL.h>
#include "objects.h"
#include "setup.h"
#include "constants.h"

void EventRoutine(SDL_Event *event, Window *window, Player *player);
void SetScreen(Window *window, Player *player, Item *item, Uint32 *game_time);

int main()
{
	SDL_Event event;
	
	Window *window = new Window[1];
	
	if (window->InitScreen() == false) {window->ShutdownScreen();}

	Item *item = new Item[1];


	while (window->Status()) 
	{
		Uint32 game_time = SDL_GetTicks();
		Player *player = new Player[1];

		// Loop of singlr game, exiting this loop starts a new game.
		do {
			// Look for user input events.
			if (SDL_PollEvent(&event))
			{
				EventRoutine(&event, window, player);
			}

			// Clear screen for subsequently redrawing player positions and
			// updating the screen.
			window->ClearScreen();
			SetScreen(window, player, item, &game_time);
			window->UpdateScreen();

		// Leave loop if state is RESTART which then restarts the game, or leave
		// loop if window status is set to stop, which will than leave the
		// larger loop as well, ending the game.
		} while (player->GetState() != RESTART && window->Status());

		delete [] player;

	}

	window->ShutdownScreen();

	delete [] window;
	delete [] item;

	return EXIT_SUCCESS;
}


void SetScreen(Window *window, Player *player, Item *item, Uint32 *game_time)
{
	bool placed_item = 0;

	// Wait certain delay before moving.
	if (SDL_GetTicks() - *game_time > DELAY)
	{
		// Save the time for checking next loop.
		*game_time = SDL_GetTicks(); 

		player->MovePlayer();

		// Check if the player obtained the item.
		if ( (player->Get_x() == item->Get_x()) 
			&& (player->Get_y() == item->Get_y()) )
		{
			do {
				// Player did obtain the item, so place new item.
				item->PlaceRandom();
				// Checks if any player location collides with placed item.
				for (int i = player->GetLength(); i > 0; i--)
				{
					player->OccupiedToCoord(i);
					if ( (player->Get_x() == item->Get_x()) 
						&& (player->Get_y() == item->Get_y()) )
					{
						// Item was placed under player, so mark as food not
						// placed leave inner loop
						break;
					}
					// Check if reached end of player length without item being
					// under player, if yes than item was placed successfully
					// and player length should be increased.
					else if (i == 1)
					{
						placed_item = 1;
						player->Grow();
					}
				}
			} while (!placed_item);
		}
	}
	player->DrawPlayer(window->GetScreen());
	item->Draw(window->GetScreen());
}


void EventRoutine(SDL_Event *event, Window *window, Player *player)
{
	// If there was a collision look for return to restart the game, or escape
	// to cancel the game.
	if (player->GetState() == COLLISION)
	{
		if (event->type == SDL_KEYDOWN)
		{
			if (event->key.keysym.scancode == SDL_SCANCODE_RETURN)
			{
				player->SetState(RESTART);
			}

			if (event->key.keysym.scancode == SDL_SCANCODE_ESCAPE)
			{
				window->Stop();
			}
		}
	}

	// While their is no collision yet, look for player control commands. Also
	// stop the player flashing which occurs in the idle state.
	else if (event->type == SDL_KEYDOWN)
	{
		if (event->key.keysym.scancode == SDL_SCANCODE_ESCAPE)
		{
			window->Stop();
		}

		if (event->key.keysym.scancode == SDL_SCANCODE_UP)
		{
			player->SetState(MOVING_UP);
		}

		if (event->key.keysym.scancode == SDL_SCANCODE_DOWN)
		{
			player->SetState(MOVING_DOWN);
		}

		if (event->key.keysym.scancode == SDL_SCANCODE_LEFT)
		{
			player->SetState(MOVING_LEFT);
		}

		if (event->key.keysym.scancode == SDL_SCANCODE_RIGHT)
		{
			player->SetState(MOVING_RIGHT);
		}
		player->StopFlash();
	}

	// Manually close window
	if (event->type == SDL_QUIT)
	{
		window->Stop();
	}
}


