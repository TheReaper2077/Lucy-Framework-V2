#pragma once

#include "../ECS.h"
#include <OpenGL.h>

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

#include "../Window.h"
#include "../Components/Components.h"

#include "assert.h"

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
		std::vector<Entity> drawn_sprite_entities;
		int drawcount = 0;

		void SetModel(const glm::mat4& model);
		void SetView(const glm::mat4& view);
		void SetProjection(const glm::mat4& projection);
		void SetViewPosition(const glm::vec3& view_position);

		void Init(lf::Registry* registry);

		void RenderIndexed(VertexArray* vertexarray, VertexBuffer* vertexbuffer, IndexBuffer* indexbuffer, std::size_t size, std::size_t offset = 0, std::size_t basevertex = 0);

		void RenderEditor(int width, int height);
		void Render(int width, int height, bool debug = false);
		
		void Render(Window& window, Entity camera_entity) {
			Render(window.framebuffer, camera_entity, window.width, window.height);
		}

		void Render(Window& window) {
			Render(window, window.camera);
		}
		
		void DrawCall(DrawMode drawmode, GLenum mode, int first, int count, int instancecount, int baseinstance, GLenum type, void* indices, void* indirect) {
			switch (drawmode) {
				case NONE:
					glDrawArrays(mode, first, count);
				case INDIRECT:
					glDrawArraysIndirect(mode, indirect);
				case INSTANCED:
					glDrawArraysInstanced(mode, first, count, instancecount);
				case INSTANCED_BASE:
					glDrawArraysInstancedBaseInstance(mode, first, count, instancecount, baseinstance);
					
				case INDEXED:
					glDrawElements(mode, count, type, indices);
				
			}
		}

		void Render(FrameBuffer* framebuffer, Entity camera_entity, int width, int height);

		void SetLighting();
		void RenderSprite(int vertexcount);

		IndexBuffer* GetQuadIndices(VertexArray* vertexarray, int vertexcount);
	};
}