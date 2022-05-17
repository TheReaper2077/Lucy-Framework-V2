#pragma once

#include "../ECS.h"
#include <OpenGL.h>

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

#include "../Window.h"
#include "../Components/Components.h"

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

		void RenderEditor(int width, int height);
		void Render(int width, int height);
		
		void Render(Window& window, Entity camera_entity) {
			Render(window.framebuffer, camera_entity, window.width, window.height);
		}

		void Render(FrameBuffer* framebuffer, Entity camera_entity, int width, int height) {
			auto [transform, camera] = registry->try_get<lf::Component::Transform, lf::Component::Camera>(camera_entity);

			if (transform == nullptr || camera == nullptr) return;

			SetProjection(camera->projection);
			SetModel(glm::mat4(1.0));
			SetView(camera->view);
			SetViewPosition(transform->translation);

			if (framebuffer != nullptr) framebuffer->Bind();
			
			Render(width, height);

			if (framebuffer != nullptr) framebuffer->UnBind();
		}

		void SetLighting();

		IndexBuffer* GetQuadIndices(VertexArray* vertexarray, int vertexcount);
	};
}