#pragma once

#include "Import.h"




namespace lf {
	struct Node {
		Entity parent = (Entity)0;
		std::vector<Entity> children;
	};

	void RenderTree(const Entity& entity, Registry& registry, std::unordered_map<Entity, Node>& scene_tree, Node& node);

	namespace Panel {
		void ScenePanel(Registry& registry);
	}
}