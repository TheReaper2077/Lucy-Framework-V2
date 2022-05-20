#include "InspectorPanel.h"
#include <imgui_stdlib.h>

using namespace lf::Component;

template <>
void lf::ComponentHeader<Tag>::Render(Registry& registry, Entity entity) {
	auto& tag = registry.get<Tag>(entity);

	ImGui::InputText("Name", &tag.name);
	ImGui::TextWrapped(tag.id.c_str());
}

template <>
void lf::ComponentHeader<Transform>::Render(Registry& registry, Entity entity) {
	auto& transform = registry.get<Transform>(entity);

	ImGui::DragFloat3("Translation", &transform.translation[0], 0.1);
	ImGui::DragFloat3("Rotation", &transform.rotation[0], 0.1);
	ImGui::DragFloat3("Scale", &transform.scale[0], 0.1);
}

template <>
void lf::ComponentHeader<Camera>::Render(Registry& registry, Entity entity) {
	auto& camera = registry.get<Camera>(entity);

	ImGui::Checkbox("Enable", &camera.enable);

	ImGui::Spacing();

	ImGui::DragFloat("Sensitivity", &camera.sensitivity, 0.001);
	ImGui::DragFloat("Speed", &camera.speed, 0.001);
	ImGui::DragFloat("ScrollSpeed", &camera.scrollspeed, 0.001);

	ImGui::Spacing();

	EnumComboLogic("projection", { "ORTHOGRAPHIC", "PERSPECTIVE" }, camera.mode);
}

template <>
void lf::ComponentHeader<Light>::Render(Registry& registry, Entity entity) {
	auto& light = registry.get<Light>(entity);

	EnumComboLogic("mode", { "Point", "Spot", "Area", "Directional" }, light.mode);

	ImGui::Spacing();

	ImGui::Checkbox("Active", &light.active);

	ImGui::Spacing();

	ImGui::ColorEdit3("Color", &light.color[0], ImGuiColorEditFlags_NoInputs);
}

template <>
void lf::ComponentHeader<SpriteRenderer>::Render(Registry& registry, Entity entity) {
	auto& spriterenderer = registry.get<SpriteRenderer>(entity);

	ImGui::Spacing();

	ImGui::Checkbox("Visible", &spriterenderer.visible);

	ImGui::Spacing();

	ImGui::ColorEdit4("Color", &spriterenderer.color[0], ImGuiColorEditFlags_NoInputs);
}

template <>
void lf::ComponentHeader<MeshRenderer>::Render(Registry& registry, Entity entity) {
	auto& meshrenderer = registry.get<MeshRenderer>(entity);
}

void lf::Editor::InspectorPanel(Registry& registry) {
	if (ImGui::Begin("Inspector")) {
		Entity entity = registry.store<EditorPropeties>().selected_entity;

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
					registry.emplace<Transform>(entity);
					transform.open = true;
				}
				if (ImGui::Selectable("Camera") && !camera.has_component) {
					registry.emplace<Camera>(entity);
					camera.open = true;
				}
				if (ImGui::Selectable("Light") && !light.has_component) {
					registry.emplace<Light>(entity);
					light.open = true;
				}
				if (ImGui::Selectable("SpriteRenderer") && !spriterenderer.has_component) {
					registry.emplace<SpriteRenderer>(entity);
					spriterenderer.open = true;
				}
				if (ImGui::Selectable("MeshRenderer") && !meshrenderer.has_component) {
					registry.emplace<MeshRenderer>(entity);
					meshrenderer.open = true;
				}

				ImGui::EndPopup();
			}
		}
		ImGui::End();
	}
}
