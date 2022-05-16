#pragma once

#include "../ECS.h"
#include <OpenGL.h>

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

namespace lf {
	class Renderer {
		lf::Registry* registry = nullptr;

		Shader* shader = nullptr;
		UniformBuffer* uniformbuffer = nullptr;

		glm::mat4 model;
		glm::mat4 view;
		glm::mat4 projection;
		glm::vec3 view_position;

	public:
		void SetModel(const glm::mat4& model);
		void SetView(const glm::mat4& view);
		void SetProjection(const glm::mat4& projection);
		void SetViewPosition(const glm::vec3& view_position);

		void Init(lf::Registry* registry);

		void RenderIndexed(VertexArray* vertexarray, VertexBuffer* vertexbuffer, IndexBuffer* indexbuffer, std::size_t size, std::size_t offset = 0, std::size_t basevertex = 0);

		void Render();

		void SetLighting();

		IndexBuffer* GetQuadIndices(VertexArray* vertexarray, int vertexcount);
	};
}