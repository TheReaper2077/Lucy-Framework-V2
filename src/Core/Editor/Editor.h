#pragma once

#include <imgui.h>
#include <imgui_internal.h>
#include <imgui_stdlib.h>
#include <imgui_impl_sdl.h>
#include <imgui_impl_opengl3.h>

#include <string>

#include "../ECS.h"

void PopupOpenLogic(lf::Registry& registry, bool& open, bool& toggle);


template <typename T>
void EnumComboLogic(const std::string& name, const std::vector<std::string>& total_modes, T& idx, ImGuiComboFlags flags = ImGuiComboFlags_NoArrowButton) {
	EnumComboLogic<T>(name.c_str(), total_modes, flags);
}

template <typename T>
void EnumComboLogic(const char* name, const std::vector<std::string>& total_modes, T& idx, ImGuiComboFlags flags = ImGuiComboFlags_NoArrowButton) {
	if (ImGui::BeginCombo(name, total_modes[idx].c_str(), flags)) {
		for (int i = 0; i < total_modes.size(); i++) {
			if (total_modes[i] != total_modes[idx])
				if (ImGui::Selectable(total_modes[i].c_str(), true))
					idx = (T)i;
		}
		ImGui::EndCombo();
	}
}

namespace lf {
	class Editor {
	public:
		Entity selected_entity;
	};
}