#include "Import.h"

template <>
void lucy::Panel::GuiPanel<lucy::Panel::SpriteEditor>::Render() {
	auto& events = registry->store<Events>();
	auto& spriteregistry = registry->store<lucy::SpriteRegistry>();

	static lucy::Component::TextureRaw* texture_raw;
	static std::string raw_texture_id;
	static bool push;

	ImGui::Begin("Sprite Editor");
	{
		auto pos = ImGui::GetWindowPos();
		auto size = ImGui::GetWindowSize();
		bool is_over_window = (events.window_mousepos.x > pos.x && events.window_mousepos.y > pos.y && events.window_mousepos.x < pos.x + size.x && events.window_mousepos.y < pos.y + size.y);

		if (is_over_window && !events.mouse_pressed.contains(SDL_BUTTON_LEFT) && push)
			push = false;
		if (!is_over_window && push) {
			raw_texture_id = "";
			texture_raw = nullptr;
			push = false;
		}

		if (raw_texture_id != "") texture_raw = spriteregistry.GetTextureById(raw_texture_id);

		if (events.payload != nullptr && events.payload_type == "raw_texture_id" && is_over_window) {
			texture_raw = (lucy::Component::TextureRaw*)events.payload;
			raw_texture_id = texture_raw->id;
			push = true;
		}

		if (texture_raw != nullptr) {
			auto pos = ImGui::GetWindowPos();

			static bool is_panning;
			
			static ImVec2 offset, delta, init_pos;

			if (is_panning) {
				delta.x = events.window_mousepos.x - init_pos.x;
				delta.y = events.window_mousepos.y - init_pos.y;
			}

			if (events.mouse_pressed.contains(SDL_BUTTON_MIDDLE) && !is_panning && is_over_window) {
				init_pos.x = events.window_mousepos.x;
				init_pos.y = events.window_mousepos.y;
				is_panning = true;
			
				delta = { 0, 0 };
			} else if (is_panning && !events.mouse_pressed.contains(SDL_BUTTON_MIDDLE) || !is_over_window) {
				offset.x += delta.x;
				offset.y += delta.y;
				is_panning = false;

				delta = { 0, 0 };
			}

            ImDrawList* draw_list = ImGui::GetWindowDrawList();
			
			draw_list->AddImage((void*)texture_raw->texture->id, { pos.x + offset.x + delta.x, pos.y + offset.y + delta.y }, { pos.x + offset.x + delta.x + texture_raw->texture->width, pos.y + offset.y + delta.y + texture_raw->texture->height }, { 0, 0 }, { 1, 1 });
			
			if (ImGui::Begin("Sprite Tools")) {
				static bool opt_enable_grid = true;
				static glm::ivec2 grid_size = { 32, 32 };

				ImGui::Checkbox("Enable Grid", &opt_enable_grid);

				if (opt_enable_grid) {
					ImGui::DragInt2("Grid Size", &grid_size[0], 1, 1);

					float pos_x = pos.x + offset.x + delta.x;
					float pos_y = pos.y + offset.y + delta.y;

					pos_x -= ((int)pos_x / grid_size.x) * grid_size.x;
					pos_y -= ((int)pos_y / grid_size.y) * grid_size.y;

					for (int y = -grid_size.y; y <= size.y * 2; y += grid_size.y) {
						draw_list->AddLine({ pos_x - size.x*2, (float)y + pos_y }, { pos_x + size.x*2, (float)y + pos_y }, IM_COL32(200, 200, 200, 255), 1);
					}

					for (int x = -grid_size.x; x <= size.x * 2; x += grid_size.x) {
						draw_list->AddLine({ (float)x + pos_x, pos_y - size.y*2 }, { (float)x + pos_x, pos_y + size.y*2 }, IM_COL32(200, 200, 200, 255), 1);
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
