class Window
{
	private:
		bool running = true;
		SDL_Window* window;
		SDL_Renderer* renderer;

	public:
		void Run() {running = 1;}
		void Stop() {running = 0;}
		bool Status() {return running;}

		bool InitScreen();
		void ClearScreen();
		void ShutdownScreen();
		void UpdateScreen();

		SDL_Renderer* GetScreen() {return renderer;}
};
