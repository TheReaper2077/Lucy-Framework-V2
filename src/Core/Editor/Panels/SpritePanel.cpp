#include "Import.h"

template <>
void lucy::Panel::GuiPanel<lucy::Panel::TextureRegistry>::Render() {
	auto& editor = registry->store<Editor>();

	if (ImGui::Begin("Texture Registry")) {
		static float padding = 10.0f;
		static float thumbnail_size = 80;
		float cell_size = padding + thumbnail_size;

		float panel_width = ImGui::GetContentRegionAvail().x;
		int column_count = (int)(panel_width / cell_size);
		ImGui::Columns(column_count, 0, false);

		for (auto pair: registry->store<lucy::SpriteRegistry>().texture_store) {
			if (ImGui::ImageButton((void*)pair.second->texture->id, { thumbnail_size, thumbnail_size }, { 0, 0 }, { 1, 1 }, 1)) {
				if (editor.selected_entity != (Entity)0)
					editor.selected_entity = (Entity)0;
				if (editor.selected_texture != pair.second)
					editor.selected_texture = pair.second;
			}
			ImGui::Text(pair.second->name.c_str());
			ImGui::NextColumn();
		}
		ImGui::Columns(1);
	}
	ImGui::End();
}

template <>
void lucy::Panel::GuiPanel<lucy::Panel::SpriteRegistry>::Render() {
	if (ImGui::Begin("Sprite Registry")) {
		static float padding = 16.0f;
		static float thumbnail_size = 80;
		float cell_size = padding + thumbnail_size;

		float panel_width = ImGui::GetContentRegionAvail().x;
		int column_count = (int)(panel_width / cell_size);
		ImGui::Columns(column_count, 0, false);

		for (auto pair: registry->store<lucy::SpriteRegistry>().sprite_store) {
			
		}
		ImGui::Columns(1);
	}
	ImGui::End();
}

template <>
void lucy::Panel::GuiPanel<lucy::Panel::TilePaletteRegistry>::Render() {
	if (ImGui::Begin("TilePalette Registry")) {
		static float padding = 16.0f;
		static float thumbnail_size = 80;
		float cell_size = padding + thumbnail_size;

		float panel_width = ImGui::GetContentRegionAvail().x;
		int column_count = (int)(panel_width / cell_size);

		for (auto pair: registry->store<lucy::SpriteRegistry>().sprite_store) {
			
		}
	}
	ImGui::End();
}

template <>
void lucy::Panel::GuiPanel<lucy::Panel::SpriteEditor>::Render() {
	if (ImGui::Begin("Sprite Editor")) {
		
	}
	ImGui::End();
}