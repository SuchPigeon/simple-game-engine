#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include <SDL2/SDL.h>
#include <tuple>
#include <utility>

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
	const int GE_HEIGHT = 480;
	const int GE_WIDTH  = 640;
};

#endif
