#pragma once

#include <imgui.h>
#include <set>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <vector>
#include <SDL2/SDL_scancode.h>

#include "Core/ECS.h"
#include "Engine.h"
#include "Window.h"

namespace lf {
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

		glm::vec3 mousepos_normalized;
		glm::vec2 mousepos;

		glm::vec3 game_normalized_mouse;
		glm::vec2 game_mouspos;

		std::set<unsigned int> mouse_pressed;

		Events() {}

		glm::vec3 GetMousePos(Window& window, bool normalized = false) {
			if (normalized)
				return glm::vec3(((mousepos.x - window.posx) / (window.width * 0.5)) - 1.0, ((mousepos.y - window.posy) / (window.height * 0.5)) - 1.0, 0);
			else
				return glm::vec3((1 + mousepos_normalized.x) * window.width / 2.0, (1 + mousepos_normalized.y) * window.height / 2.0, 0);
		}

		void Update(Registry& registry) {
			mouse_scrollup = false;
			mouse_scrolldown = false;

			auto& window = registry.store<Window>();
			auto& engine = registry.store<Engine>();

			while (SDL_PollEvent(&engine.event)) {
				#ifdef ENABLE_EDITOR
					ImGui_ImplSDL2_ProcessEvent(&engine.event);
				#endif

				if (engine.event.type == SDL_QUIT) {
					engine.quit = true;
				}
				if (engine.event.type == SDL_MOUSEMOTION) {
					posx += engine.event.motion.xrel;
					posy += engine.event.motion.yrel;
					
					relx = engine.event.motion.xrel;
					rely = engine.event.motion.yrel;

					mousepos_normalized.x = ((engine.event.motion.x - window.posx) / (window.width * 0.5)) - 1.0;
					mousepos_normalized.y = 1.0 - ((engine.event.motion.y - window.posy) / (window.height * 0.5));
					mousepos_normalized.z = 0;

					mousepos.x = (1 + mousepos_normalized.x) * window.width / 2.0;
					mousepos.y = (1 + mousepos_normalized.y) * window.height / 2.0;
				}
				if (engine.event.type == SDL_KEYDOWN) {
					key_pressed.insert(engine.event.key.keysym.scancode);
					if (key_chord.size() == 0)
						key_chord.push_back(engine.event.key.keysym.scancode);
					else if (key_chord.back() != engine.event.key.keysym.scancode)
						key_chord.push_back(engine.event.key.keysym.scancode);
				}
				if (engine.event.type == SDL_KEYUP) {
					if (key_pressed.contains(engine.event.key.keysym.scancode)) {
						if (!key_toggled.contains(engine.event.key.keysym.scancode))
							key_toggled.insert(engine.event.key.keysym.scancode);
						else
							key_toggled.erase(engine.event.key.keysym.scancode);
					}
					key_chord.clear();
					key_pressed.erase(engine.event.key.keysym.scancode);
				}
				if (engine.event.type == SDL_MOUSEBUTTONDOWN) {
					mouse_pressed.insert(engine.event.button.button);
				}
				if (engine.event.type == SDL_MOUSEBUTTONUP) {
					mouse_pressed.erase(engine.event.button.button);
				}
				if (engine.event.type == SDL_MOUSEWHEEL) {
					mouse_scrollup = (engine.event.wheel.y > 0);
					mouse_scrolldown = (engine.event.wheel.y < 0);
				}
			}
		}
	};
}