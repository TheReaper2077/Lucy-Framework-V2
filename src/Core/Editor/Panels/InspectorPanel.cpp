#include "Import.h"
#include <imgui_stdlib.h>
#include <iostream>
#include <LucyGL/API.h>

namespace lucy {
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

		void Render(Registry* registry, Entity entity);
		void Header(Registry* registry, Entity entity) {
			if (entity != last_entity) open = true;
			last_entity = entity;
			has_component = (registry->try_get<T>(entity) != nullptr);

			if (has_component) {
				if (permanent) {
					if (ImGui::CollapsingHeader(name.c_str()))
						Render(registry, entity);
				} else if (ImGui::CollapsingHeader(name.c_str(), &open, flags)) {
					Render(registry, entity);
				} else if (!open) {
					registry->remove<T>(entity);
				}
			}
		}
	};
}

using namespace lucy::Component;

template <>
void lucy::ComponentHeader<Tag>::Render(Registry* registry, Entity entity) {
	auto& tag = registry->get<Tag>(entity);

	ImGui::InputText("Name", &tag.name);
	ImGui::TextWrapped(tag.id.c_str());
}

template <>
void lucy::ComponentHeader<Transform>::Render(Registry* registry, Entity entity) {
	auto& transform = registry->get<Transform>(entity);

	ImGui::DragFloat3("Translation", &transform.translation[0], 0.1);
	ImGui::DragFloat3("Rotation", &transform.rotation[0], 0.1);
	ImGui::DragFloat3("Scale", &transform.scale[0], 0.1);
}

template <>
void lucy::ComponentHeader<Camera>::Render(Registry* registry, Entity entity) {
	auto& camera = registry->get<Camera>(entity);
	auto& gamewindow = registry->store<GameWindow>();

	camera.enable = (gamewindow.camera == entity || camera.enable);

	ImGui::Checkbox("Enable", &camera.enable);
	
	if (camera.enable && gamewindow.camera != entity) {
		gamewindow.camera = entity;
	}
	if (!camera.enable && gamewindow.camera == entity) {
		gamewindow.camera = (Entity)0;
	}

	if (camera.mode == ORTHOGRAPHIC) {
		
	}
	if (camera.mode == PERSPECTIVE) {
		ImGui::DragFloat("Near", &camera.camera_near, 0.1);
		ImGui::DragFloat("Far", &camera.camera_far, 0.1);
		ImGui::DragFloat("Fov", &camera.fov, 0.1, 0.0, 180.0);
	}

	ImGui::ColorEdit4("ClearColor", &camera.clear_color[0], ImGuiColorEditFlags_NoInputs);

	ImGui::EnumComboLogic("Projection", { "ORTHOGRAPHIC", "PERSPECTIVE" }, camera.mode);
	ImGui::EnumComboLogic("Type", { "FPS", "TPS", "Default", "None" }, camera.type);
}

template <>
void lucy::ComponentHeader<Light>::Render(Registry* registry, Entity entity) {
	auto& light = registry->get<Light>(entity);

	ImGui::EnumComboLogic("Mode", { "Point", "Spot", "Area", "Directional" }, light.mode);

	ImGui::Spacing();

	ImGui::Checkbox("Active", &light.active);

	ImGui::Spacing();

	ImGui::ColorEdit3("Color", &light.color[0], ImGuiColorEditFlags_NoInputs);
}

template <>
void lucy::ComponentHeader<SpriteRenderer>::Render(Registry* registry, Entity entity) {
	auto& spriterenderer = registry->get<SpriteRenderer>(entity);

	ImGui::Spacing();

	ImGui::Checkbox("Visible", &spriterenderer.visible);

	ImGui::Spacing();

	ImGui::ColorEdit4("Color", &spriterenderer.color[0], ImGuiColorEditFlags_NoInputs);
}

template <>
void lucy::ComponentHeader<MeshRenderer>::Render(Registry* registry, Entity entity) {
	auto& meshrenderer = registry->get<MeshRenderer>(entity);
}

template <>
void lucy::Panel::GuiPanel<lucy::Panel::Inspector>::Render() {
	if (ImGui::Begin("Inspector")) {
		Entity entity = registry->store<Editor>().selected_entity;
		auto* texture_raw = registry->store<Editor>().selected_texture;

		if (entity != (Entity)0) {
			static ComponentHeader<Tag> tag("Tag", true);
			static ComponentHeader<Transform> transform("Transform");
			static ComponentHeader<Camera> camera("Camera");
			static ComponentHeader<Light> light("Light");
			static ComponentHeader<SpriteRenderer> spriterenderer("SpriteRenderer");
			static ComponentHeader<MeshRenderer> meshrenderer("MeshRenderer");
			
			tag.Header(registry, entity);
			transform.Header(registry, entity);
			camera.Header(registry, entity);
			light.Header(registry, entity);
			spriterenderer.Header(registry, entity);
			meshrenderer.Header(registry, entity);

			ImGui::Spacing();
			if (ImGui::Button("Add Component", ImVec2(ImGui::GetColumnWidth(), 0))) {
				ImGui::OpenPopup("Component Menu");
			}

			if (ImGui::BeginPopup("Component Menu")) {
				if (ImGui::Selectable("Transform") && !transform.has_component) {
					registry->emplace<Transform>(entity);
					transform.open = true;
				}
				if (ImGui::Selectable("Camera") && !camera.has_component) {
					registry->emplace<Camera>(entity);
					camera.open = true;
				}
				if (ImGui::Selectable("Light") && !light.has_component) {
					registry->emplace<Light>(entity);
					light.open = true;
				}
				if (ImGui::Selectable("SpriteRenderer") && !spriterenderer.has_component) {
					registry->emplace<SpriteRenderer>(entity);
					spriterenderer.open = true;
				}
				if (ImGui::Selectable("MeshRenderer") && !meshrenderer.has_component) {
					registry->emplace<MeshRenderer>(entity);
					meshrenderer.open = true;
				}

				ImGui::EndPopup();
			}
		} else if (texture_raw != nullptr) {
			static const std::vector<std::string> wrap_str_valid = { "None", "CLAMP_TO_EDGE", "CLAMP_TO_BORDER", "MIRRORED_REPEAT", "REPEAT", "MIRROR_CLAMP_TO_EDGE" };
			static const std::vector<std::string> wrap_str_except = { "None" };
			static const std::vector<std::string> filter_str_valid = { "None", "LINEAR", "NEAREST" };
			static const std::vector<std::string> filter_str_except = { "None" };

			ImGui::Spacing();

			ImGui::InputText("Name", &texture_raw->name);

			ImGui::Spacing();

			auto min = texture_raw->texture->min;
			auto mag = texture_raw->texture->mag;
			ImGui::EnumComboLogic("Filter min", filter_str_valid, min, filter_str_except);
			ImGui::EnumComboLogic("Filter mag", filter_str_valid, mag, filter_str_except);
			
			ImGui::Spacing();

			auto wrap_s = texture_raw->texture->wrap_s;
			auto wrap_t = texture_raw->texture->wrap_t;
			auto wrap_r = texture_raw->texture->wrap_r;
			ImGui::EnumComboLogic("Wrap s", wrap_str_valid, wrap_s, wrap_str_except);
			ImGui::EnumComboLogic("Wrap t", wrap_str_valid, wrap_t, wrap_str_except);
			ImGui::EnumComboLogic("Wrap r", wrap_str_valid, wrap_r, wrap_str_except);

			ImGui::Spacing();

			texture_raw->texture->SetFilteringMode(mag, min);
			texture_raw->texture->SetWrapMode(wrap_s, wrap_t, wrap_r);

			if (ImGui::Button("Generate Mipmap")) {
				texture_raw->texture->GenerateMimmap();
			}
		}
	}
	ImGui::End();
}
