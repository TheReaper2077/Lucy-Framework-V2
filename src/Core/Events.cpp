#include "Events.h"
#include <iostream>

glm::vec3 lf::Events::GetMousePos(const Window* window, bool normalized) {
	auto norm = glm::vec3(((window_mousepos.x - window->posx) / (window->width * 0.5)) - 1.0, ((window_mousepos.y - window->posy) / (window->height * 0.5)) - 1.0, 0);
	
	if (normalized)
		return norm;
	
	glm::vec3 pos;
	pos.x = (1 + norm.x) * window->width / 2.0;
	pos.y = (1 - norm.y) * window->height / 2.0;
	return pos;
}

void lf::Events::Update(Registry& registry) {
	mouse_scrollup = false;
	mouse_scrolldown = false;

	auto& window = registry.store<Window>();
	auto& engine = registry.store<Engine>();

	while (SDL_PollEvent(&engine.event)) {
		if (engine.event.type == SDL_QUIT) {
			engine.quit = true;
		}
		if (engine.event.type == SDL_MOUSEMOTION) {
			posx += engine.event.motion.xrel;
			posy += engine.event.motion.yrel;
			
			relx = engine.event.motion.xrel;
			rely = engine.event.motion.yrel;

			window_mousepos.x = engine.event.motion.x;
			window_mousepos.y = engine.event.motion.y;

			mousepos_normalized.x = ((window_mousepos.x - window.posx) / (window.width * 0.5)) - 1.0;
			mousepos_normalized.y = 1.0 - ((window_mousepos.y - window.posy) / (window.height * 0.5));
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
		if (engine.event.type == SDL_DROPFILE) {
			std::cout << engine.event.drop.file << '\n';
		}
		
		#ifdef ENABLE_EDITOR
			ImGui_ImplSDL2_ProcessEvent(&engine.event);
			
			if (ImGui::IsMouseDragging(ImGuiPopupFlags_MouseButtonLeft) && !relative) {
				SDL_SetRelativeMouseMode(SDL_TRUE);
				relative = true;
			}
			if (!ImGui::IsMouseDragging(ImGuiPopupFlags_MouseButtonLeft) && relative) {
				SDL_SetRelativeMouseMode(SDL_FALSE);
				relative = false;
			}
		#endif
	}
}
