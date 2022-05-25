#pragma once

#include <imgui.h>
#include <imgui_internal.h>
#include <imgui_stdlib.h>
#include <imgui_impl_sdl.h>
#include <imgui_impl_opengl3.h>

#include <string>

#include "../ECS.h"
#include "../Registries/SpriteRegistry.h"
namespace ImGui {
	void PopupOpenLogic(lf::Registry& registry, bool& open, bool& toggle);

	bool in_expections(std::string value, const std::vector<std::string>& exceptions = {});

	template <typename T>
	void EnumComboLogic(const char* name, const std::vector<std::string>& total_modes, T& idx, const std::vector<std::string>& exceptions = {}, ImGuiComboFlags flags = ImGuiComboFlags_NoArrowButton) {
		if (ImGui::BeginCombo(name, total_modes[idx].c_str(), flags)) {
			for (int i = 0; i < total_modes.size(); i++) {
				if (!in_expections(total_modes[i], exceptions))
					if (total_modes[i] != total_modes[idx])
						if (ImGui::Selectable(total_modes[i].c_str(), true))
							idx = (T)i;
			}
			ImGui::EndCombo();
		}
	}
}

namespace lf {

	class Editor {
	public:
		Entity selected_entity = (Entity)0;
		lf::Component::TextureRaw* selected_texture = nullptr;
	};
}