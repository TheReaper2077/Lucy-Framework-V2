#pragma once

#include <string>
#include <glm/vec2.hpp>

#include <GraphicsAPI/API.h>

namespace lf {
	namespace Component {
		struct Sprite {
			std::string id;

			lfal::Texture* texture = nullptr;
			glm::vec2 uv0 = glm::vec2(0, 0);
			glm::vec2 uv1 = glm::vec2(0, 0);
		};
	}
}