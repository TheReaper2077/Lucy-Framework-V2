#pragma once

#include "../../ECS.h"
#include <iostream>

namespace lucy {
	namespace Panel {
		struct SpriteRegistry;
		struct TextureRegistry;
		struct TilePaletteRegistry;

		struct Inspector;
		struct SceneHeirarchy;
		
		struct MaterialEditor;
		struct SpriteEditor;
		
		struct DebugEditor;
		struct DebugGame;

		template <typename T>
		struct GuiPanel {
			bool window_open = true;
			std::string name;

			Registry* registry = nullptr;

		public:
			GuiPanel() {}
			GuiPanel(std::string name): name(name) {}
			GuiPanel(std::string name, bool open): name(name), window_open(open) {}
			GuiPanel(Registry* registry): registry(registry) {}
			GuiPanel(Registry* registry, std::string name): registry(registry), name(name) {}
			GuiPanel(Registry* registry, std::string name, bool open): registry(registry), name(name), window_open(open) {}

		private:
			void Render();

		public:
			void RenderWindow() {
				Render();
			}
		};
	}
}