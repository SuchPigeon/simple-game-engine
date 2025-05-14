#include <SDL2/SDL.h>
#include <iostream>
#include <tuple>
#include <utility>
#include <vector>
#include <functional>

#include "engine.hpp"

GameEngine::GameEngine() {};

GameEngine::~GameEngine() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void GameEngine::drawPixel(const int cx, const int cy) {
	SDL_RenderDrawPoint(renderer, cx, cy);
}

int GameEngine::init() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << "\n";
		return 1;
	}

	window = SDL_CreateWindow("simple-game-engine",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		GE_WIDTH, GE_HEIGHT,
		SDL_WINDOW_SHOWN);

	if (!window) {
		std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << "\n";
		SDL_Quit();
		return 1;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer) {
		std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << "\n";
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}

	return 0;
}

void GameEngine::run() {
	int isrun = 1;
	SDL_Event event;

	std::vector<float> camera = {0., 0., 0.};
	static std::vector<std::vector<float>> center = {
		{0,-1,3,1},
		{2,0,4,1},
		{-2,0,4,1}
	};

	while(isrun) {
		int startTick = SDL_GetTicks();

		if(SDL_PollEvent(&event)) {
			if(event.type == SDL_QUIT) {
				isrun = 0;
			}
			if (event.type == SDL_KEYDOWN) {
                std::cout << "Key pressed: " << SDL_GetKeyName(event.key.keysym.sym) << std::endl;
				switch(event.key.keysym.sym) {
					case SDLK_s:
						camera[1] -= 0.2;
						break;
					case SDLK_w:
						camera[1] += 0.2;
						break;
					case SDLK_a:
						camera[0] -= 0.2;
						break;
					case SDLK_d:
						camera[0] += 0.2;
						break;
					case SDLK_MINUS:
						camera[2] -= 0.2;
						break;
					case SDLK_PLUS:
						camera[2] += 0.2;
						break;
					default:
						break;
				}
				std::cout << "Camera now: " << camera[0] << ' ' << camera[1] << ' ' << camera[2] << std::endl;
            }
		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		for(int x = 0;  x < GE_WIDTH; x++) {
			for(int y = 0; y < GE_HEIGHT; y++) {
				std::vector<float> D = {
					(-GE_WIDTH/2. + x)/GE_WIDTH, 
					-(-GE_HEIGHT/2. + y)/GE_HEIGHT,
					1
				};

				std::function<float(std::vector<float>,std::vector<float>,float&)> deter = [](std::vector<float> D, std::vector<float> sphere, float& t) {
					float a = D[0]*D[0] + D[1]*D[1] + D[2]*D[2];
					float b = 2*D[0]*sphere[0] + 2*D[1]*sphere[1] + 2*D[2]*sphere[2];
					float c = sphere[0]*sphere[0] + sphere[1]*sphere[1] + sphere[2]*sphere[2] - sphere[3]*sphere[3];

					float d = b*b - 4*a*c;
					if(d < 0.) return false;

					t = (-b - sqrt(d)) / (2.*a);
					return true;
				};


				float t = 0.;

				std::vector<std::vector<float>> OC = center;

				for(std::vector<float>& oc : OC) {
					oc[0] -= camera[0];
					oc[1] -= camera[1];
					oc[2] -= camera[2];
				}

				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
				if(deter(D,OC[0],t))
					SDL_SetRenderDrawColor(renderer, 255/2, 0, 0, 255);
				if(deter(D,OC[1],t))
					SDL_SetRenderDrawColor(renderer, 0, 0, 255/2, 255);
				if(deter(D,OC[2],t))
					SDL_SetRenderDrawColor(renderer, 0, 255/2, 0, 255);
				
				this->drawPixel(x,y);
			}
		}

		SDL_RenderPresent(renderer);
		std::clog << "\rFPS: " << 1000. / (SDL_GetTicks() - startTick) << std::flush;
		//SDL_Delay(1000 / 50);
	}
}
