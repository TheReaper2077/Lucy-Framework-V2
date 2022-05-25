#pragma once

#include <glm/glm.hpp>

#include "../Enumerations.h"

namespace lucy {
	namespace Component {
		struct Light {
			glm::vec3 color = glm::vec3(1, 1, 1);

			LightMode mode = Directional;

			bool active = true;

			Light() {}
		};
	}
}