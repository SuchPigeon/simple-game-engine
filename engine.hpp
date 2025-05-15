#ifndef GAME_ENGINE_HPP
#define GAME_ENGINE_HPP

#include <SDL2/SDL.h>

class GameEngine {
public:
	GameEngine();
	~GameEngine();

	void drawPixel(const int, const int);
	int init();
	void run();
private:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	const int GE_HEIGHT = 220;
	const int GE_WIDTH  = 220;
};

#endif
