#pragma once

#include "../ECS.h"

namespace lf {
	class RenderPass {
	public:
		Registry *registry = nullptr;
		bool init = false;

		virtual void Init() = 0;
		virtual void Render() = 0;
	};
}