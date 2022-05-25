#pragma once

#include "ECS.h"

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

		void SaveEntities();
		void LoadEntities();
		
		void SaveSprites();
		void LoadSprites();

		void SetMainCamera(Entity camera);
		Entity GetMainCamera();
	};
}