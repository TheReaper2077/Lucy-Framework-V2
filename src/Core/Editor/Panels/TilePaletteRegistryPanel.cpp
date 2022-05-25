#include "Import.h"

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