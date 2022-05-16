#pragma once

#include <string>
#include <glm/vec4.hpp>

namespace lf {
	namespace Component {
		struct SpriteRenderer {
			std::string material_id;

			glm::vec4 color;
			
			glm::vec2 uv0 = glm::vec2(0, 0);
			glm::vec2 uv1 = glm::vec2(1, 1);

			uint32_t custom_flags = 0;

			bool visible = true;
		};
	}
}