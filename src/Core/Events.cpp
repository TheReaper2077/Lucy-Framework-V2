#include "Events.h"
#include <iostream>

glm::vec3 lucy::Events::GetMousePos(const Window* window, bool normalized) {
	auto norm = glm::vec3(((window_mousepos.x - window->posx) / (window->width * 0.5)) - 1.0, ((window_mousepos.y - window->posy) / (window->height * 0.5)) - 1.0, 0);
	
	if (normalized)
		return norm;
	
	glm::vec3 pos;
	pos.x = (1 + norm.x) * window->width / 2.0;
	pos.y = (1 - norm.y) * window->height / 2.0;
	return pos;
}

void lucy::Events::Update(Registry& registry) {
	mouse_scrollup = false;
	mouse_scrolldown = false;

	auto& window = registry.store<Window>();
	auto& engine = registry.store<Engine>();

	dropped_file = "";
	drag_begin = false;
	static bool drag_end;
	static int drag_count;

	if (drag_count > 1) {
		payload = nullptr;
		payload_type = "";
		drag_end = false;
	}

	if (drag_end) {
		drag_count++;
	} else {
		drag_count = 0;
	}

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
			if (engine.event.button.button == SDL_BUTTON_LEFT) {
				drag_begin = true;
			}
		}
		if (engine.event.type == SDL_MOUSEBUTTONUP) {
			mouse_pressed.erase(engine.event.button.button);
			if (engine.event.button.button == SDL_BUTTON_LEFT) {
				drag_end = true;
			}
		}
		if (engine.event.type == SDL_MOUSEWHEEL) {
			mouse_scrollup = (engine.event.wheel.y > 0);
			mouse_scrolldown = (engine.event.wheel.y < 0);
		}
		if (engine.event.type == SDL_DROPFILE) {
			dropped_file = std::string(engine.event.drop.file);
		}
		
		#ifdef ENABLE_DEBUG
			ImGui_ImplSDL2_ProcessEvent(&engine.event);
		#endif
	}
}
