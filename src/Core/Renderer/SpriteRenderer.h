#pragma once

#include "RenderPass.h"

namespace lf {
	class SpriteRenderer: public RenderPass {
		void Init();
		void Render();
	};
}