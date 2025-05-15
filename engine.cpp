#include <SDL2/SDL.h>
#include <iostream>
#include <tuple>
#include <utility>
#include <vector>
#include <functional>

#include "engine.hpp"
#include "vec3.hpp"

const float INF = 1e10;

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

	vec3 camera(0., 0., 0.);
	struct sphere {
		vec3 center;
		float radius;
	};
	std::vector<sphere> spheres = {
		{vec3(0,-1,3),1},
		{vec3(2,0,4),1},
		{vec3(-2,0,4),1}
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
						camera.sety(camera.y() - 0.2f);
						break;
					case SDLK_w:
						camera.sety(camera.y() + 0.2f);
						break;
					case SDLK_a:
						camera.setx(camera.x() - 0.2f);
						break;
					case SDLK_d:
						camera.setx(camera.x() + 0.2f);
						break;
					case SDLK_MINUS:
						camera.setz(camera.z() - 0.2f);
						break;
					case SDLK_PLUS:
						camera.setz(camera.z() + 0.2f);
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
				vec3 D(
					(-GE_WIDTH/2.f + x)/GE_WIDTH, 
					-(-GE_HEIGHT/2.f + y)/GE_HEIGHT,
					1
				);

				std::function<float(vec3,sphere,float&)> deter = [](vec3 D, sphere s, float& t) {
					float a = D.x()*D.x() + D.y()*D.y() + D.z()*D.z();
					float b = 2*D.x()*s.center.x() + 2*D.y()*s.center.y() + 2*D.z()*s.center.z();
					float c = s.center.x()*s.center.x() + s.center.y()*s.center.y() + s.center.z()*s.center.z() - s.radius*s.radius;

					float d = b*b - 4*a*c;
					if(d < 0.) return false;

					t = (-b - sqrt(d)) / (2.*a);
					return true;
				};


				float t;
				float min_t = INF;

				std::vector<sphere> OC = spheres;

				for(sphere& oc : OC) {
					oc.center = oc.center - camera;
				}

				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
				if(deter(D,OC[0],t) && t < min_t) {
					SDL_SetRenderDrawColor(renderer, 255/2, 0, 0, 255);
					min_t = t;
				}
				if(deter(D,OC[1],t) && t < min_t) {
					SDL_SetRenderDrawColor(renderer, 0, 0, 255/2, 255);
					min_t = t;
				}
				if(deter(D,OC[2],t) && t < min_t) {
					SDL_SetRenderDrawColor(renderer, 0, 255/2, 0, 255);
					min_t = t;
				}
				
				this->drawPixel(x,y);
			}
		}

		SDL_RenderPresent(renderer);
		std::clog << "\rFPS: " << 1000. / (SDL_GetTicks() - startTick) << std::flush;
		//SDL_Delay(1000 / 50);
		//isrun=false;
	}
}
