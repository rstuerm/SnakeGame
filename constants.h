#include <SDL.h>

namespace Colors 
{
	const SDL_Color BLACK = {0, 0, 0, SDL_ALPHA_OPAQUE};
	const SDL_Color WHITE = {255, 255, 255, SDL_ALPHA_OPAQUE};
}

const int SQUARE_DIM = 32;

const int WIDTH_BLOCKS = 16;
const int HEIGHT_BLOCKS = 8;

const int WINDOW_WIDTH = SQUARE_DIM * WIDTH_BLOCKS;
const int WINDOW_HEIGHT = SQUARE_DIM * HEIGHT_BLOCKS;

const int START_X = WINDOW_WIDTH/2;
const int START_Y = WINDOW_HEIGHT/2;

const Uint32 DELAY = 150;

const int RANDOM_MODULO = 17;

