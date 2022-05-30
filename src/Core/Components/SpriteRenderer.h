#pragma once

#include <string>
#include <glm/vec4.hpp>

namespace lucy {
	namespace Component {
		struct SpriteRenderer {
			std::string material_id;
			std::string sprite_id;

			glm::vec4 color = glm::vec4(1, 1, 1, 1);
			
			glm::vec2 uv0 = glm::vec2(0, 0);
			glm::vec2 uv1 = glm::vec2(1, 1);

			uint32_t custom_flags = 0;

			bool visible = true;
		};
	}
}