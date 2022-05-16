#pragma once

#include "ECS.h"
#include <OpenGL.h>

namespace lf {
	struct Window {
		const char* title = "Lucy V2";
		int width = 1280, height = 640, posx = 50, posy = 50;

		FrameBuffer* framebuffer = nullptr;
	};
}