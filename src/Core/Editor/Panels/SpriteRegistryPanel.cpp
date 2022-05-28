#include "Import.h"

template <>
void lucy::Panel::GuiPanel<lucy::Panel::SpriteRegistry>::Render() {
	auto& editor = registry->store<Editor>();
	auto& events = registry->store<Events>();
	auto* texture_raw = registry->store<lucy::SpriteRegistry>().GetTextureById(registry->store<Editor>().selected_texture);

	if (ImGui::Begin("Sprite Registry")) {		
		if (texture_raw != nullptr) {
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
			
			for (auto pair_sprite: registry->store<lucy::SpriteRegistry>().sprite_store) {
				if (pair_sprite.second.raw_texture_id != registry->store<Editor>().selected_texture)
					continue;

				auto pos = ImGui::GetCursorPos();

				pos.x += win_pos.x;
				pos.y += win_pos.y;

				if (ImGui::ImageButton((void*)texture_raw->texture->id, { thumbnail_size, thumbnail_size }, { pair_sprite.second.uv0.x, pair_sprite.second.uv0.y }, { pair_sprite.second.uv1.x, pair_sprite.second.uv1.y }, 1)) {
					
				}

				bool button_hovered = ImGui::IsItemHovered();

				ImGui::Text(pair_sprite.second.name.c_str());

				if (ImGui::IsItemHovered() || button_hovered) {
					ImVec2 p0 = { pair_sprite.second.uv0.x * texture_raw->texture->width, pair_sprite.second.uv0.y * texture_raw->texture->height };
					ImVec2 p1 = { pair_sprite.second.uv1.x * texture_raw->texture->width, pair_sprite.second.uv1.y * texture_raw->texture->height };
					
					ImGui::BeginTooltip();
					ImGui::Text("Name -");
						ImGui::SameLine();
						ImGui::Text(pair_sprite.second.name.c_str());
					ImGui::Text("Index -");
						ImGui::SameLine();
						ImGui::Text(std::to_string(pair_sprite.second.idx).c_str());
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

				if (panel_width > cell_size) ImGui::NextColumn();
			}
			if (panel_width > cell_size) ImGui::Columns(1);

			ImGui::DragFloat("Padding", &padding, 0.1, 1);
			ImGui::DragFloat("Thumbnail", &thumbnail_size, 0.1, 1);
		}
	}
	ImGui::End();
}
