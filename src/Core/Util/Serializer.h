#pragma once

#include "../ECS.h"

namespace lucy {
	namespace Util {
		bool SerializeEntities(Registry* registry, const std::string& filename);
		void DeserializeEntities(Registry* registry, const std::string& filename);
		
		bool SerializeSpriteRegistry(Registry* registry, const std::string& filename);
		void DeserializeSpriteRegistry(Registry* registry, const std::string& filename);
	}
}