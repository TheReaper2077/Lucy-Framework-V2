#pragma once

#include <SDL2/SDL.h>

#define ENABLE_EDITOR

#ifdef ENABLE_EDITOR
	#ifndef ENABLE_DEBUG
		#define ENABLE_DEBUG
	#endif
#endif

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