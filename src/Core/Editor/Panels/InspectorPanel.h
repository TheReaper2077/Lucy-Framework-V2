#pragma once

#include "Import.h"
#include "../Editor.h"
#include <iostream>

namespace lf {
	template <typename T>
	class ComponentHeader {
	public:
		bool open = true;
		ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_DefaultOpen;
		Entity last_entity;
		std::string name;
		bool has_component = false;
		bool permanent = false;

		ComponentHeader() {}
		ComponentHeader(std::string name, bool permanent = false) {
			this->name = name;
			this->permanent = permanent;
		}

		void Render(Registry& registry, Entity entity);
		void Header(Registry& registry, Entity entity) {
			if (entity != last_entity) open = true;
			last_entity = entity;
			has_component = (registry.try_get<T>(entity) != nullptr);

			if (has_component) {
				if (permanent) {
					if (ImGui::CollapsingHeader(name.c_str()))
						Render(registry, entity);
				} else if (ImGui::CollapsingHeader(name.c_str(), &open, flags)) {
					Render(registry, entity);
				} else if (!open) {
					registry.remove<T>(entity);
				}
			}
		}
	};

	namespace Panel {
		void InspectorPanel(Registry& registry);
	}
}