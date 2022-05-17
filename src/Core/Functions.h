#pragma once

#include "ECS.h"
#include "Components/Components.h"

namespace lf {
	struct Functions {
		std::unordered_map<std::string, Entity> entity_store;

		Entity CreateEmptyEntity();
		Entity CreateCameraEntity();
		Entity CreateMeshEntity();
		Entity CreateSpriteEntity();
		Entity CreateLightEntity();

		void CreateRenderTarget();
	};
}