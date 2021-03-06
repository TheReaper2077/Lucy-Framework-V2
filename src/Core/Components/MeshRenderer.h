#pragma once

#include <string>

namespace lf {
	namespace Component {
		struct MeshRenderer {
			std::string material_id;

			uint32_t custom_flags = 0;

			bool visible = true;
		};
	}
}