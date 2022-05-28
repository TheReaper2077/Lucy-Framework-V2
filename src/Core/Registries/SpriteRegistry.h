#pragma once

#include <LucyGL/API.h>
#include <unordered_map>
#include <string>
#include "../Components/Components.h"

namespace lucy {
	struct SpriteRegistry {
		std::unordered_map<std::string, lucy::Component::TextureRaw*> texture_store;
		std::unordered_map<std::string, lucy::Component::Sprite> sprite_store;

		lucy::Component::TextureRaw* GetTexture(const std::string& filename);
		lucy::Component::TextureRaw* GetTextureById(const std::string& id);

		lucy::Component::TextureRaw* LoadTexture(const std::string& name, const std::string& filename, const std::string& id);

		lucy::Component::Sprite* LoadSprite();
		lucy::Component::Sprite* GetSprite(std::string id);
	};
}