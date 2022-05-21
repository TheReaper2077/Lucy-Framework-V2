#pragma once

#include <RenderAPI.h>
#include <unordered_map>
#include <string>
#include "../Components/Components.h"

namespace lf {
	struct SpriteRegistry {
		std::unordered_map<std::string, lf::Component::Sprite> sprite_store;
	};
}