#pragma once

#include "Import.h"

	void PopupOpenLogic(lf::Registry& registry, bool& open, bool& toggle) {
		auto& events = registry.store<lf::Events>();

		if ((!ImGui::IsWindowHovered() && events.mouse_pressed.size() != 0) || (ImGui::IsWindowHovered() && !events.mouse_pressed.contains(SDL_BUTTON_RIGHT) && events.mouse_pressed.size() != 0)) {
			open = false;
		}

		if (toggle && ImGui::IsWindowHovered() && events.mouse_pressed.contains(SDL_BUTTON_RIGHT)) {
			open = true;
		}
		
		toggle = (ImGui::IsWindowHovered() && !events.mouse_pressed.contains(SDL_BUTTON_RIGHT));
	}

namespace lf {
	namespace Editor {
		void ScenePanel(Registry& registry) {
			auto& events = registry.store<Events>();

			ImGui::Begin("Scene");

			static bool open, toggle;
			
			PopupOpenLogic(registry, open, toggle);

			if (open) {
				ImGui::OpenPopup("Scene Shortcut");
			}

			for (auto [entity, tag]: registry.view<lf::Component::Tag>().each()) {
				if (ImGui::TreeNodeEx(tag.name.c_str())) {
					ImGui::TreePop();
				}
			}

			if (ImGui::BeginPopup("Scene Shortcut")) {

				ImGui::EndPopup();
			}

			ImGui::End();
		}
	}
}