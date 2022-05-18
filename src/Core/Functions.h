#pragma once

#include "ECS.h"
#include "Components/Components.h"

namespace lf {
	struct Functions {
		Registry* registry = nullptr;

		bool save_entities = false;
		bool runtime_creation = false;

		Functions() {}
		Functions(Registry* registry) {
			this->registry = registry;
		}

		std::string GetName(std::string name);
		
		Entity CreateEmptyEntity();
		Entity CreateCameraEntity();
		Entity CreateMeshEntity();
		Entity CreateSpriteEntity();
		Entity CreateLightEntity();

		void CreateRenderTarget();
	};
}