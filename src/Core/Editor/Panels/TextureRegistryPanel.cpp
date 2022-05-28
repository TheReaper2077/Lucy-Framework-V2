#include "Import.h"

template <>
void lucy::Panel::GuiPanel<lucy::Panel::TextureRegistry>::Render() {
	auto& editor = registry->store<Editor>();
	auto& events = registry->store<Events>();

	if (ImGui::Begin("Texture Registry")) {		
		static float padding = 15.0f;
		static float thumbnail_size = 80;
		float cell_size = padding + thumbnail_size;

		float panel_width = ImGui::GetContentRegionAvail().x;
		int column_count = (int)(panel_width / cell_size);
		int width_delta = int(panel_width) - int(cell_size)*(int(panel_width)/int(cell_size));
		
		if (panel_width > cell_size) {
			ImGui::Columns(column_count, 0, false);
			
			for (int i = 1; i < column_count; i++)
				ImGui::SetColumnOffset(i, i*cell_size);
		}

		auto* draw_list = ImGui::GetWindowDrawList();
		auto win_pos = ImGui::GetWindowPos();
		
		int column_idx = 0;
		int row_idx = 1;

		float y_scroll = ImGui::GetScrollY();
		
		for (auto pair_texture: registry->store<lucy::SpriteRegistry>().texture_store) {
			auto pos = ImGui::GetCursorPos();

			pos.x += win_pos.x;
			pos.y += win_pos.y;

			// draw_list->AddRectFilled({ pos.x, pos.y + -y_scroll }, { pos.x + cell_size, pos.y + -y_scroll + cell_size }, IM_COL32(200, 0, 200, 255));

			if (ImGui::ImageButton((void*)pair_texture.second->texture->id, { thumbnail_size, thumbnail_size }, { 0, 0 }, { 1, 1 }, 1)) {
				if (editor.selected_entity != (Entity)0)
					editor.selected_entity = (Entity)0;
				if (editor.selected_texture != pair_texture.second->id)
					editor.selected_texture = pair_texture.second->id;
			}

			if (ImGui::IsItemHovered() && events.dragging) {
				events.payload = (void*)pair_texture.second;
				events.payload_type = "raw_texture_id";
			}

			bool button_hovered = ImGui::IsItemHovered();

			ImGui::Text(pair_texture.second->name.c_str());

			if (ImGui::IsItemHovered() || button_hovered) {
				ImGui::BeginTooltip();
				ImGui::Text("Filename -");
				ImGui::SameLine();
					ImGui::Text(pair_texture.second->filename.c_str());
				ImGui::Text("Name -");
				ImGui::SameLine();
					ImGui::Text(pair_texture.second->name.c_str());
				ImGui::Text("ID -");
				ImGui::SameLine();
					ImGui::Text(pair_texture.second->id.c_str());
				ImGui::EndTooltip();
			}

			if (panel_width > cell_size) ImGui::NextColumn();
			
			// {
			// 	static bool toggle, sprite_mode;

			// 	if (toggle && events.mouse_pressed.contains(SDL_BUTTON_RIGHT) && !sprite_mode) {
			// 		sprite_mode = true;
			// 		toggle = false;
			// 	}
			// 	if (toggle && events.mouse_pressed.contains(SDL_BUTTON_RIGHT) && sprite_mode) {
			// 		sprite_mode = false;
			// 		toggle = false;
			// 	}

			// 	if (!events.mouse_pressed.contains(SDL_BUTTON_RIGHT)) {
			// 		toggle = true;
			// 	}
			// 	if (events.mouse_pressed.contains(SDL_BUTTON_RIGHT)) {
			// 		toggle = false;
			// 	}

			// 	if (sprite_mode) {
			// 		for (auto& pair_sprite: registry->store<lucy::SpriteRegistry>().sprite_store) {
			// 			if (pair_sprite.second.raw_texture_id == pair_texture.first) {
			// 				pos = ImGui::GetCursorPos();

			// 				pos.x += win_pos.x;
			// 				pos.y += win_pos.y;
							
			// 				// draw_list->AddRectFilled({ pos.x, pos.y + -y_scroll }, { pos.x + cell_size, pos.y + -y_scroll + cell_size }, IM_COL32(200, 0, 200, 255));

			// 				ImGui::ImageButton((void*)pair_texture.second->texture->id, { thumbnail_size, thumbnail_size }, { pair_sprite.second.uv0.x, pair_sprite.second.uv0.y }, { pair_sprite.second.uv1.x, pair_sprite.second.uv1.y }, 1);
			// 				ImGui::Text(pair_sprite.second.name.c_str());

			// 				if (panel_width > cell_size) ImGui::NextColumn();
			// 			}
			// 		}
			// 	}
			// }
		}
		if (panel_width > cell_size) ImGui::Columns(1);

		ImGui::DragFloat("Padding", &padding, 0.1, 1);
		ImGui::DragFloat("Thumbnail", &thumbnail_size, 0.1, 1);
	}
	ImGui::End();
}
