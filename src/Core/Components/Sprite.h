#pragma once

#include <string>
#include <glm/vec2.hpp>

namespace lf {
	namespace Component {
		struct Sprite {
			std::string id;

			Texture* texture = nullptr;
			glm::vec2 uv0 = glm::vec2(0, 0);
			glm::vec2 uv1 = glm::vec2(0, 0);
		};
	}
}