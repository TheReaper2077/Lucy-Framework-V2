#include "Editor.h"
#include "../Events.h"
#include <imgui.h>

bool ImGui::in_expections(std::string value, const std::vector<std::string>& exceptions) {
	if (!exceptions.size()) return false;

	for (const auto& str: exceptions) {
		if (str == value)
			return true;
	}

	return false;
}

void ImGui::PopupOpenLogic(lucy::Registry* registry, bool& open, bool& toggle) {
	auto& events = registry->store<lucy::Events>();

	if ((!ImGui::IsWindowHovered() && events.mouse_pressed.size() != 0) || (ImGui::IsWindowHovered() && !events.mouse_pressed.contains(SDL_BUTTON_RIGHT) && events.mouse_pressed.size() != 0)) {
		open = false;
	}

	if (toggle && ImGui::IsWindowHovered() && events.mouse_pressed.contains(SDL_BUTTON_RIGHT)) {
		open = true;
	}
	
	toggle = (ImGui::IsWindowHovered() && !events.mouse_pressed.contains(SDL_BUTTON_RIGHT));
}