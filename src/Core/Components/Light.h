#pragma once

#include <glm/glm.hpp>

#include "../Enumerations.h"

namespace lf {
	namespace Component {
		struct Light {
			glm::vec3 color;

			LightMode mode = Directional;

			bool active = true;

			Light() {}
		};
	}
}