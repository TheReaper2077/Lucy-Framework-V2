#pragma once

#include "ECS.h"
#include <OpenGL.h>

namespace lf {
	struct Window {
		std::string title = "Lucy V2";
		int width = 1280, height = 640, posx = 50, posy = 50;

		FrameBuffer* framebuffer = nullptr;
		Entity camera = 0;

		bool mouse_in_window = false;

		void SetCamera(uint32_t camera) {
			this->camera = camera;
		}
	};

	struct GameWindow: public Window {};

	struct EditorWindow: public Window {
		EditorWindow() {
			title = "Editor";
		}
	};
}