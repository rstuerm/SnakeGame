#include <iostream>
#include <SDL.h>
#include "objects.h"
#include "constants.h"

void Square::Draw(SDL_Renderer *renderer)
{
	rect.x = x;
	rect.y = y;
	rect.w = SQUARE_DIM;
	rect.h = SQUARE_DIM;

	SDL_SetRenderDrawColor(
		renderer, 
		Colors::WHITE.r,
		Colors::WHITE.g,
		Colors::WHITE.b,
		255
	);
	SDL_RenderFillRect(renderer, &rect);
}

// Place a random item at some coordinate on the board.
void Item::PlaceRandom()
{
	seed_x = LehmerRandom(seed_x, RANDOM_MODULO, scaling_x);
	int new_x = SQUARE_DIM * ( (seed_x - 1) % WIDTH_BLOCKS );
	Square::Set_x(new_x);

	seed_y = LehmerRandom(seed_y, RANDOM_MODULO, scaling_y);
	int new_y = SQUARE_DIM * ( (seed_y - 1) % HEIGHT_BLOCKS );
	Square::Set_y(new_y);
}

Player::Player()
{
	x = START_X;
	y = START_Y;

	const int MAX_POSITIONS = HEIGHT_BLOCKS*WIDTH_BLOCKS;
	occupied_positions = new int[MAX_POSITIONS];

	CoordToOccupied(1);
}

Player::~Player()
{
	delete [] occupied_positions;
}

// Converts the location of the nth component of the player to an x and y
// coordinate for graphical processing.
void Player::OccupiedToCoord(int n)
{
	x = ( occupied_positions[n] % WIDTH_BLOCKS ) * SQUARE_DIM;
	y = ( occupied_positions[n] - x/SQUARE_DIM ) * SQUARE_DIM / WIDTH_BLOCKS;
}

// Converts the current x and y coordinate of the player to a single value
// stored at the nth index of an array, representing the location of the nth
// component of the player.
void Player::CoordToOccupied(int n)
{
	occupied_positions[n] = x/SQUARE_DIM + y/SQUARE_DIM*WIDTH_BLOCKS;
}

// Moves player, considers collisions.
void Player::MovePlayer()
{
	if (state != COLLISION)
	{
		// Checks which direction the latest input was and moves the player in
		// that direction. If it reaches the screen boundary a collision is
		// indicated and the function is returned to avoid shifting the players
		// locations.
		switch (state)
		{
			case MOVING_UP:
			{
				y -= SQUARE_DIM;
				if (y < 0)
				{
					state = COLLISION;
					return;
				}
				break;
			}
			case MOVING_DOWN:
			{
				y += SQUARE_DIM;
				if (y >= WINDOW_HEIGHT)
				{
					state = COLLISION;
					return;
				}
				break;
			}
			case MOVING_LEFT:
			{
				x -= SQUARE_DIM;
				if (x < 0)
				{
					state = COLLISION;
					return;
				}
				break;
			}
			case MOVING_RIGHT:
			{
				x += SQUARE_DIM;
				if (x >= WINDOW_WIDTH)
				{
					state = COLLISION;
					return;
				}
				break;
			}
			default:
				break;
		}
		if (state != IDLE)
		{
			// Add location of new player piece to first index of array.
			CoordToOccupied(0);
			// Shift all locations over by one, simultaneously checking if the
			// new location collides with any of the other locations.
			for (int i = player_length; i > 0; i--)
			{
				occupied_positions[i + 1] = occupied_positions[i];
				if (occupied_positions[0] == occupied_positions[i])
				{
					state = COLLISION;
				}
			}
			occupied_positions[1] = occupied_positions[0];
		}
		
	}
	// If there is a collision, alternate the draw player enable each turn so
	// that the player will flash.
	if (state == COLLISION || state == IDLE)
	{	
		draw_player = !draw_player;
	}
}

// Draws the full player.
void Player::DrawPlayer(SDL_Renderer *renderer)
{
	if (draw_player)
	{
		for (int i = player_length; i > 0; i--)
		{
			OccupiedToCoord(i);
			Square::Draw(renderer);
		}	
	}
}


// Initializes item with randomized seeds for location spawining.
Item::Item()
{
	// Calculate valid scaling parameters for required modulo.
	int *valid = LehmerTest(RANDOM_MODULO);

	// Get seed from timer to select which scaling and initial input to use.
	int seed_time = SDL_GetTicks(); 

	scaling_x = valid[(seed_time % valid[0]) + 1];
	seed_x = seed_time % RANDOM_MODULO;
	if (seed_x == 0) seed_x++;

	scaling_y = valid[((seed_time + 7) % valid[0]) + 1];
	seed_y = (seed_time + 13) % RANDOM_MODULO;
	if (seed_y == 0) seed_y++;

	std::cout << scaling_x << " ";
	std::cout << seed_x << " ";
	std::cout << scaling_y << " ";
	std::cout << seed_y << std::endl;

	delete [] valid;

	// Place initial item.
	Item::PlaceRandom();

	// Check edge case if initial item placed under player starting point, if so
	// place again which will guarantee a different position.
	if (x == START_X && y == START_Y)
	{
		Item::PlaceRandom();
	}
}

// Generates a random number using carefully selected parameters.
// https://lpuguidecom.files.wordpress.com/2017/05/lehmer-random-number-generators.pdf
int LehmerRandom(int input, int modulo, int scaling)
{
	return (input * scaling) % modulo;
}

// Calculates the valid scaling that will cover the full range of values for a
// given modulo 
int *LehmerTest(int modulo)
{
	int *valid_scaling = new int[modulo];
	int num = 0;
	for (int scaling = 1; scaling < modulo; scaling++)
	{
		int input = scaling;
		int counter = 1;
		while (input != 1)
		{
			input = LehmerRandom(input, modulo, scaling);
			counter++;
		}
		if (counter == modulo - 1)
		{
			num++;
			valid_scaling[num] = scaling;
		}
	}
	// Indicate number of valid scaling options with length in first index of
	// array.
	valid_scaling[0] = num;

	return valid_scaling;
}

