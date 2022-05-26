#include "Import.h"

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

			if (events.mouse_pressed.contains(SDL_BUTTON_MIDDLE) && !is_panning && is_over_window) {
				init_pos.x = events.window_mousepos.x;
				init_pos.y = events.window_mousepos.y;
				is_panning = true;
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

				ImGui::DragFloat2("Scale", &scale[0], 0.01);
				ImGui::Checkbox("Enable Grid", &opt_enable_grid);

				if (opt_enable_grid) {
					static glm::ivec2 grid_step = { 32, 32 };
					
					ImGui::DragInt2("Grid Size", &grid_step[0], 1, 2);

					for (float x = fmodf(offset.x + delta.x, (float)grid_step.x); x < size.x; x += grid_step.x)
						draw_list->AddLine(ImVec2(pos.x + x, pos.y), ImVec2(pos.x + x, pos.y + size.y), IM_COL32(200, 200, 200, 40));
					for (float y = fmodf(offset.y + delta.y, (float)grid_step.y); y < size.y; y += grid_step.y)
						draw_list->AddLine(ImVec2(pos.x, pos.y + y), ImVec2(pos.x + size.x, pos.y + y), IM_COL32(200, 200, 200, 40));
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
