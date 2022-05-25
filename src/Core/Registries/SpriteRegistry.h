#pragma once

#include <LucyGL/API.h>
#include <unordered_map>
#include <string>
#include "../Components/Components.h"

namespace lf {
	struct SpriteRegistry {
		std::unordered_map<std::string, lf::Component::TextureRaw*> texture_store;
		std::unordered_map<std::string, lf::Component::Sprite> sprite_store;

		lf::Component::TextureRaw* GetTexture(const std::string& filename);

		lf::Component::Sprite& GetSprite(const std::string& filename);
	};
}