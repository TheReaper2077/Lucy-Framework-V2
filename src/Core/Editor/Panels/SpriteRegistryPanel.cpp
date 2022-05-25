#include "Import.h"

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
