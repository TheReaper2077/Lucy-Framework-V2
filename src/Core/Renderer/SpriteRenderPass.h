#pragma once

#include "RenderPass.h"

namespace lucy {
	class SpriteRenderPass: public RenderPass {
		void Init() override;
		void Render() override;
	};
}