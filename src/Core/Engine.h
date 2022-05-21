#pragma once

#include <SDL2/SDL.h>

#define ENABLE_EDITOR
// https://us02web.zoom.us/j/83303389400?pwd=UnRDK3NuOWFveHZ1OHhTUTJGL3I0dz09

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