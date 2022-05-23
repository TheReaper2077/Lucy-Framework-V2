#pragma once

#include "../ECS.h"

namespace lf {
	class RenderPass {
		Registry *registry = nullptr;

	public:
		virtual void Init() = 0;
		virtual void Render() = 0;
	};
}