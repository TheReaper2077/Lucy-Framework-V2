#pragma once

#include <string>
#include <glm/vec2.hpp>

#include <LucyGL/API.h>

namespace lucy {
	namespace Component {
		struct Sprite {
			std::string id;
			std::string raw_texture_id;
			std::string name;

			glm::vec2 uv0 = glm::vec2(0, 0);
			glm::vec2 uv1 = glm::vec2(1, 1);

			int idx;
		};
	}
}