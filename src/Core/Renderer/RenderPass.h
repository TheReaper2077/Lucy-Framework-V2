#pragma once

#include "../ECS.h"

namespace lucy {
	class RenderPass {
	public:
		Registry *registry = nullptr;
		bool init = false;

		virtual void Init() = 0;
		virtual void Render() = 0;
	};
}