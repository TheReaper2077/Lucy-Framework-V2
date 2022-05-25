#pragma once

#include <glm/glm.hpp>
#include <LucyGL/API.h>

#include "../Registries/VertexArrayRegistry.h"

namespace lucy {
	lgl::IndexBuffer* GetQuadIndices(lgl::VertexArray* vertexarray, int vertexcount);
}