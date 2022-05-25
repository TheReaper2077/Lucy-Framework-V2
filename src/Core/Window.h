#pragma once

#include "ECS.h"
#include <LucyGL/API.h>

namespace lucy {
	struct Window {
		std::string title = "Lucy V2";
		int width = 1280, height = 640, posx = 50, posy = 50;

		lgl::FrameBuffer* framebuffer = nullptr;
		Entity camera = (Entity)0;

		bool window_focus = true;
		bool mouse_hover = true;

		void SetCamera(Entity camera) {
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