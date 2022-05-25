#pragma once

#include "RenderPass.h"
#include "../Components/Components.h"

namespace lucy {
	class SpriteRenderPass: public RenderPass {
		void Init();
		void Render();

		void RenderRect(const lucy::Component::Transform& transform, const lucy::Component::SpriteRenderer& spriterenderer, const glm::quat& quaternion);
		void Flush();
	};
}