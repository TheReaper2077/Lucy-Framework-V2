#pragma once

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <string>
#include <vector>

#include <LucyGL/API.h>
#include "../Enumerations.h"

namespace lf {
	namespace Component {
		struct Mesh {
			std::string id;

			std::vector<glm::vec3> position;
			std::vector<glm::vec3> normal;
			std::vector<glm::vec4> color;
			std::vector<glm::vec2> uv0;
			std::vector<glm::vec2> uv1;
			std::vector<glm::vec2> uv2;
			std::vector<glm::vec2> uv3;
			std::vector<glm::vec2> uv4;
			std::vector<glm::vec2> uv5;
			std::vector<glm::vec2> uv6;
			std::vector<glm::vec2> uv7;

			std::vector<uint32_t> indices;

			// lgl::Primitive primitive = Primitive;

			lgl::VertexBuffer* vertexbuffer = nullptr;
			lgl::IndexBuffer* indexbuffer = nullptr;

			uint32_t vertexcount = 0;
			uint32_t indexcount = 0;
		};
	}
}