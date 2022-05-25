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

		for (auto pair: registry->store<lucy::SpriteRegistry>().texture_store) {
			if (ImGui::ImageButton((void*)pair.second->texture->id, { thumbnail_size, thumbnail_size }, { 0, 0 }, { 1, 1 }, 1)) {
				if (editor.selected_entity != (Entity)0)
					editor.selected_entity = (Entity)0;
				if (editor.selected_texture != pair.second->id)
					editor.selected_texture = pair.second->id;
			}

			if (ImGui::IsItemHovered() && events.dragging) {
				events.payload = (void*)pair.second;
				events.payload_type = "raw_texture_id";
			}
			ImGui::Text(pair.second->name.c_str());

			if (panel_width > cell_size) ImGui::NextColumn();
		}
		if (panel_width > cell_size) ImGui::Columns(1);

		ImGui::DragFloat("Padding", &padding, 0.1, 1);
		ImGui::DragFloat("Thumbnail", &thumbnail_size, 0.1, 1);
	}
	ImGui::End();
}