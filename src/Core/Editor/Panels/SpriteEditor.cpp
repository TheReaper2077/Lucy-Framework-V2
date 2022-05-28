#include "Import.h"
#include <uuid.h>

template <>
void lucy::Panel::GuiPanel<lucy::Panel::SpriteEditor>::Render() {
	auto& events = registry->store<Events>();
	auto& spriteregistry = registry->store<lucy::SpriteRegistry>();

	static lucy::Component::TextureRaw* texture_raw;
	static std::string texture_raw_id;
	static bool push;

	ImGui::Begin("Sprite Editor");
	{
		auto pos = ImGui::GetWindowPos();
		auto size = ImGui::GetWindowSize();
		bool is_over_window = (events.window_mousepos.x > pos.x && events.window_mousepos.y > pos.y && events.window_mousepos.x < pos.x + size.x && events.window_mousepos.y < pos.y + size.y);

		if (is_over_window && !events.mouse_pressed.contains(SDL_BUTTON_LEFT) && push)
			push = false;
		if (!is_over_window && push) {
			texture_raw_id = "";
			texture_raw = nullptr;
			push = false;
		}

		if (texture_raw_id != "") texture_raw = spriteregistry.GetTextureById(texture_raw_id);

		if (events.payload != nullptr && events.payload_type == "raw_texture_id" && is_over_window) {
			texture_raw = (lucy::Component::TextureRaw*)events.payload;
			texture_raw_id = texture_raw->id;
			push = true;
		}

		if (texture_raw != nullptr) {
			auto pos = ImGui::GetWindowPos();

			glm::vec2 rel_mouse;
			static glm::vec2 scale = { 1, 1 };

			rel_mouse.x = events.window_mousepos.x - pos.x;
			rel_mouse.y = events.window_mousepos.y - pos.y;

			// std::cout << 2 * rel_mouse.x / size.x - 1 << ' ' << 2 * rel_mouse.y / size.y - 1 << '\n';

			static bool is_panning;			
			static ImVec2 offset, delta, init_pos;

			if (is_panning) {
				delta.x = events.window_mousepos.x - init_pos.x;
				delta.y = events.window_mousepos.y - init_pos.y;
			}

			if (events.mouse_pressed.contains(SDL_BUTTON_RIGHT) && !is_panning && is_over_window) {
				init_pos.x = events.window_mousepos.x;
				init_pos.y = events.window_mousepos.y;
				is_panning = true;
			} else if (is_panning && !events.mouse_pressed.contains(SDL_BUTTON_RIGHT) || !is_over_window) {
				offset.x += delta.x;
				offset.y += delta.y;
				is_panning = false;

				delta = { 0, 0 };
			}

            ImDrawList* draw_list = ImGui::GetWindowDrawList();
			
			draw_list->AddImage((void*)texture_raw->texture->id, { pos.x + offset.x + delta.x, pos.y + offset.y + delta.y }, { pos.x + offset.x + delta.x + texture_raw->texture->width, pos.y + offset.y + delta.y + texture_raw->texture->height }, { 0, 0 }, { 1, 1 });

			if (ImGui::Begin("Sprite Tools")) {
				static bool opt_enable_grid = true;

				ImGui::DragFloat2("Scale", &scale[0], 0.01);
				ImGui::Checkbox("Enable Grid", &opt_enable_grid);

				static glm::vec2 grid_step = { 80, 80 };
				static glm::vec2 cell_size = { 80, 80 };
				static glm::vec2 cell_offset = { 0, 0 };
				
				ImGui::DragFloat2("Cell Offset", &cell_offset[0], 0.1, 1.0);
				ImGui::DragFloat2("Cell Size", &cell_size[0], 0.1, 1.0);
				ImGui::DragFloat2("Grid Size", &grid_step[0], 0.1, 1.0);

				bool apply = ImGui::Button("Apply");

				float pos_x = pos.x + offset.x + delta.x;
				float pos_y = pos.y + offset.y + delta.y;

				if (opt_enable_grid) {
					if (apply) {
						std::vector<std::string> erase_id;
						for (auto& pair: spriteregistry.sprite_store) {
							if (pair.second.raw_texture_id == texture_raw_id) {
								erase_id.push_back(pair.first);
							}
						}

						for (int i = 0; i < erase_id.size(); i++) {
							spriteregistry.sprite_store.erase(erase_id[i]);
						}
					}

					int idx = 0;
					for (float y = 0; y < texture_raw->texture->height; y += grid_step.y) {
						for (float x = 0; x < texture_raw->texture->width; x += grid_step.x) {
							draw_list->AddRect(ImVec2(x + cell_offset.x + pos_x, y + cell_offset.y + pos_y), ImVec2(x + pos_x + cell_size.x, y + pos_y + cell_size.y), IM_COL32(255, 255, 0, 255));

							if (events.window_mousepos.x > x + cell_offset.x + pos_x && events.window_mousepos.y > y + cell_offset.y + pos_y && events.window_mousepos.x < x + pos_x + cell_size.x && events.window_mousepos.y < y + pos_y + cell_size.y) {
								draw_list->AddRectFilled(ImVec2(x + cell_offset.x + pos_x, y + cell_offset.y + pos_y), ImVec2(x + pos_x + cell_size.x, y + pos_y + cell_size.y), IM_COL32(255, 255, 0, 40));
							}

							if (apply) {
								lucy::Component::Sprite sprite;
								sprite.id = uuids::to_string(uuids::uuid_system_generator{}());
								sprite.raw_texture_id = texture_raw_id;
								sprite.uv0 = { (x + cell_offset.x) / texture_raw->texture->width, (y + cell_offset.y) / texture_raw->texture->height };
								sprite.uv1 = { (x + cell_size.x) / texture_raw->texture->width, (y + cell_size.y) / texture_raw->texture->height };
								sprite.name = texture_raw->name + "_" + std::to_string(idx);
								sprite.idx = idx;
								spriteregistry.sprite_store[sprite.id] = sprite;
								idx++;
							}
						}
					}
				} else {
					for (auto& pair: spriteregistry.sprite_store) {
						if (pair.second.raw_texture_id == texture_raw_id) {
							ImVec2 p0 = { pair.second.uv0.x * texture_raw->texture->width, pair.second.uv0.y * texture_raw->texture->height };
							ImVec2 p1 = { pair.second.uv1.x * texture_raw->texture->width, pair.second.uv1.y * texture_raw->texture->height };

							draw_list->AddRect(ImVec2(p0.x + pos_x, p0.y + pos_y), ImVec2(p1.x + pos_x, p1.y + pos_y), IM_COL32(0, 0, 255, 255));

							if (events.window_mousepos.x > p0.x + pos_x && events.window_mousepos.y > p0.y + pos_y && events.window_mousepos.x < p1.x + pos_x && events.window_mousepos.y < p1.y + pos_y) {
								draw_list->AddRectFilled(ImVec2(p0.x + pos_x, p0.y + pos_y), ImVec2(p1.x + pos_x, p1.y + pos_y), IM_COL32(0, 0, 255, 40));

								ImGui::BeginTooltip();
								ImGui::Text("Name -");
									ImGui::SameLine();
									ImGui::Text(pair.second.name.c_str());
								ImGui::Text("Index -");
									ImGui::SameLine();
									ImGui::Text(std::to_string(pair.second.idx).c_str());
								ImGui::Text("Offset -");
									ImGui::SameLine();
									ImGui::Text(std::to_string(int(p0.x)).c_str());
									ImGui::SameLine();
									ImGui::Text(std::to_string(int(p0.y)).c_str());
								ImGui::Text("Size -");
									ImGui::SameLine();
									ImGui::Text(std::to_string(int(p1.x - p0.x)).c_str());
									ImGui::SameLine();
									ImGui::Text(std::to_string(int(p1.y - p0.y)).c_str());
								ImGui::EndTooltip();
							}
						}
					}
				}
			}
			ImGui::End();

			draw_list->AddLine({ events.window_mousepos.x, events.window_mousepos.y - 10 }, { events.window_mousepos.x, events.window_mousepos.y + 10 }, IM_COL32(200, 200, 200, 255), 1);
			draw_list->AddLine({ events.window_mousepos.x - 10, events.window_mousepos.y }, { events.window_mousepos.x + 10, events.window_mousepos.y }, IM_COL32(200, 200, 200, 255), 1);
		} else {
			ImGui::GetWindowDrawList()->AddImage((void*)registry->store<lgl::Texture>().id, pos, { pos.x + size.x, pos.y + size.y });
		}
	}
	ImGui::End();
}
