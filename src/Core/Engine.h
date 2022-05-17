#pragma once

#include <SDL2/SDL.h>

#define ENABLE_EDITOR

namespace lf {
	struct Engine {
		bool quit = false;

		double dt;

		// status
		int indexcount;
		int vertexcount;
		int drawcalls;
		int framerate;

		SDL_Window* window;
		SDL_GLContext context;
		SDL_Event event;

		bool playing = true;
	};
};