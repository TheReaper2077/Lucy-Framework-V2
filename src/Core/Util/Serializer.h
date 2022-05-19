#pragma once

#include "../ECS.h"

namespace lf {
	namespace Util {
		bool Serializer(Registry* registry, const std::string& filename);
		void Deserializer(Registry* registry, const std::string& filename);
	}
}