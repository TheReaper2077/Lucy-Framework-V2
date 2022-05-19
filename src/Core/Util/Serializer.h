#pragma once

#include "../ECS.h"

namespace lf {
	namespace Util {
		std::string Serializer(Registry* registry);
		void SerializeToFile(Registry* registry, const std::string& filename);
		void Deserializer(Registry* registry, const std::string& source);
		void DeserializeFromFile(Registry* registry, const std::string& filename);
	}
}