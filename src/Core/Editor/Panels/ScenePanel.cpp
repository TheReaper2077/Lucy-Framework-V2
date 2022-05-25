#include "ScenePanel.h"
#include <iostream>

// void lf::RenderTree(const Entity& entity, Registry& registry, std::unordered_map<Entity, Node>& scene_tree, Node& node) {
// 	auto* name = registry.get<lf::Component::Tag>(entity).name.c_str();

// 	static Entity selected_entity;
// 	static bool drag, toggle;

// 	if (node.children.size()) {
// 		if (ImGui::TreeNode(name)) {
// 			if (ImGui::IsItemHovered() && drag) {
// 				drag = false;
// 				registry.get<lf::Component::ParentEntity>(selected_entity) = entity;
// 			}

// 			while (node.children.size()) {
// 				RenderTree(node.children.back(), registry, scene_tree, scene_tree[node.children.back()]);
// 				node.children.pop_back();
// 			}

// 			ImGui::TreePop();
// 		}
// 	} else if (ImGui::TreeNodeEx(name, ImGuiTreeNodeFlags_Leaf)) {
// 		if (ImGui::IsItemClicked()) {
// 			registry.store<EditorPropeties>().selected_entity = entity;
// 		}

// 		if (ImGui::IsItemHovered() && registry.store<Events>().mouse_pressed.contains(SDL_BUTTON_RIGHT)) {
// 			ImGui::OpenPopup("Entity SHMenu");
// 		}

// 		if (ImGui::BeginDragDropSource()) {
// 			ImGui::SetDragDropPayload("_TREENODE", NULL, 0);
// 			ImGui::Text(name);
// 			ImGui::EndDragDropSource();
// 			drag = true;
// 			selected_entity = entity;
// 		}

// 		ImGui::TreePop();
// 	}
	
// 	if (ImGui::IsWindowHovered() && drag) {
// 		drag = false;
// 		auto& parent = registry.get<lf::Component::ParentEntity>(selected_entity);
		
// 		for (int i = 0; i < scene_tree[parent].children.size(); i++) {
// 			if (scene_tree[parent].children[i] == selected_entity) {
// 				scene_tree[parent].children.erase(scene_tree[parent].children.begin() + i);
// 				break;
// 			}
// 		}

// 		parent = (Entity)0;
// 	}
// };

void lf::Panel::ScenePanel(Registry& registry) {
	auto& events = registry.store<Events>();

	if (ImGui::Begin("Scene")) {
		static bool open, toggle;
		// std::unordered_map<Entity, Node> scene_tree;
		auto& selected_entity = registry.store<Editor>().selected_entity;
		
		ImGui::PopupOpenLogic(registry, open, toggle);

		for (auto [entity, tag]: registry.view<lf::Component::Tag>().each()) {
			auto parent = registry.try_get<lf::Component::ParentEntity>(entity);

			// if (scene_tree.find(entity) == scene_tree.end())
			// 	scene_tree[entity] = Node{};

			// if (parent != nullptr) {
			// 	scene_tree[entity].parent = *parent;

			// 	if (scene_tree.find(*parent) == scene_tree.end())
			// 		scene_tree[*parent] = Node{};

			// 	scene_tree[*parent].children.push_back(entity);
			// }
			if (ImGui::TreeNodeEx(tag.name.c_str(), ImGuiTreeNodeFlags_Leaf)) {
				if (ImGui::IsItemClicked()) {
					selected_entity = entity;
				}

				if (ImGui::IsItemHovered() && registry.store<Events>().mouse_pressed.contains(SDL_BUTTON_RIGHT)) {
					// registry.store<Events>().mouse_pressed.c
					ImGui::OpenPopup("Entity SHMenu");
					open = false;
				}

				if (ImGui::BeginPopup("Entity SHMenu")) {
					auto& functions = registry.store<Functions>();

					if (ImGui::Selectable("Delete")) {
						if (selected_entity == entity) {
							selected_entity = (Entity)0;
						}
						registry.destroy(entity);
					}
					ImGui::EndPopup();
				}
				
				ImGui::TreePop();
			}
		}

		if (open) {
			ImGui::OpenPopup("Scene Shortcut");
		}

		// for (auto& pair: scene_tree) {
		// 	if ((uint32_t)pair.second.parent == 0)
		// 		RenderTree(pair.first, registry, scene_tree, scene_tree[pair.first]);
		// }

		if (ImGui::BeginPopup("Scene Shortcut")) {
			auto& functions = registry.store<Functions>();

			if (ImGui::Selectable("New Entity")) {
				selected_entity = functions.CreateEmptyEntity();
			}
			if (ImGui::Selectable("New Camera")) {
				selected_entity = functions.CreateCameraEntity();
			}
			if (ImGui::Selectable("New Sprite")) {
				selected_entity = functions.CreateSpriteEntity();
			}
			if (ImGui::Selectable("New Light")) {
				selected_entity = functions.CreateLightEntity();
			}
			ImGui::EndPopup();
		}
	}
	ImGui::End();
}
