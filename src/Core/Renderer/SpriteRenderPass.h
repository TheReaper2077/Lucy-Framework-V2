#pragma once

#include "RenderPass.h"
#include "../Components/Components.h"

namespace lf {
	class SpriteRenderPass: public RenderPass {
		void Init();
		void Render();

		void RenderRect(const lf::Component::Transform& transform, const lf::Component::SpriteRenderer& spriterenderer, const glm::quat& quaternion);
		void Flush();
	};
}