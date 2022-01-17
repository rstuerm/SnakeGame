enum PlayerState {IDLE, MOVING_UP, MOVING_DOWN, MOVING_LEFT, MOVING_RIGHT, COLLISION, RESTART};

class Square
{
	private:
		SDL_Rect rect;

	protected:
		int x;
		int y;

	public:
		void Draw(SDL_Renderer *renderer);
		void Set_x(int pos_x) {x = pos_x;}
		void Set_y(int pos_y) {y = pos_y;}
		int Get_x() {return x;}
		int Get_y() {return y;}
};

class Item: public Square
{
	private:
		int seed_x; 
		int seed_y;
		int scaling_x;
		int scaling_y;
	public:
		Item();
		void PlaceRandom();
};

class Player: public Square
{
	private:
		PlayerState state = IDLE;
		int *occupied_positions;
		int player_length = 1;
		bool draw_player = 1; // for flashing player

	public:
		Player();
		~Player();
		void SetState(PlayerState new_state) {state = new_state;}
		PlayerState GetState() {return state;};
		void MovePlayer();
		void CoordToOccupied(int n);
		void OccupiedToCoord(int n);
		void DrawPlayer(SDL_Renderer *renderer);
		void Grow() {player_length++;}
		int GetLength() {return player_length;}
		void StopFlash() {draw_player = 1;}
};

int LehmerRandom(int input, int modulo, int scaling);
int *LehmerTest(int modulo);
