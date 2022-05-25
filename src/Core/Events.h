#pragma once

#include <imgui.h>
#include <set>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <vector>
#include <SDL2/SDL_scancode.h>
#include <imgui_impl_sdl.h>

#include "Core/ECS.h"
#include "Engine.h"
#include "Window.h"

namespace lucy {
	struct Events {
		bool mouse_scrollup;
		bool mouse_scrolldown;
		
		int relx = 0;
		int rely = 0;
		int posx = 0;
		int posy = 0;

		std::set<SDL_Scancode> key_pressed;
		std::vector<SDL_Scancode> key_chord;
		std::set<SDL_Scancode> key_toggled;

		bool dragging = false;
		void* payload = nullptr;
		std::string payload_type;

		bool relative = false;

		glm::vec3 mousepos_normalized;
		glm::vec2 mousepos;
		glm::vec2 window_mousepos;
		glm::vec2 drag_mousepos;

		std::string dropped_file;

		std::set<unsigned int> mouse_pressed;

		Events() {}

		glm::vec3 GetMousePos(Window& window, bool normalized = false) {
			return GetMousePos(&window, normalized);
		}

		glm::vec3 GetMousePos(const Window* window, bool normalized = false);

		void Update(Registry& registry);
	};
}