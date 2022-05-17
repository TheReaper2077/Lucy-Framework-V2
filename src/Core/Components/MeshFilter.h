#pragma once

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <string>
#include <vector>

#include "../Enumerations.h"

namespace lf {
	namespace Component {
		struct MeshFilter {
			std::string mesh_id;

			bool enable = false;
		};
	}
}