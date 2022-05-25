#pragma once

#include <LucyGL/API.h>
#include <unordered_map>
#include <string>
#include "../Components/Components.h"

namespace lucy {
	struct SpriteRegistry {
		std::unordered_map<std::string, lucy::Component::TextureRaw*> texture_store;
		std::unordered_map<std::string, lucy::Component::Sprite> sprite_store;

		std::unordered_map<std::string, std::string> id_filemname_map;

		lucy::Component::TextureRaw* GetTexture(const std::string& filename);
		lucy::Component::TextureRaw* GetTextureById(const std::string& id);

		lucy::Component::Sprite& GetSprite(const std::string& filename);
	};
}