#pragma once

#include "../ECS.h"
#include <RenderAPI.h>

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
		std::vector<std::vector<Entity>> drawn_sprite_entities;

		int drawcount = 0;
		int vertexcount = 0;
		int indexcount = 0;

		void SetModel(const glm::mat4& model);
		void SetView(const glm::mat4& view);
		void SetProjection(const glm::mat4& projection);
		void SetViewPosition(const glm::vec3& view_position);

		void Init(lf::Registry* registry);

		void Render(int width, int height, bool debug = false);
		
		void Render(FrameBuffer* framebuffer, Entity camera_entity, int width, int height, bool debug = false);
		
		void Render(Window& window, Entity camera_entity, bool debug = false) {
			Render(window.framebuffer, camera_entity, window.width, window.height, debug);
		}

		void Render(Window& window, bool debug = false) {
			Render(window, window.camera, debug);
		}

		bool DrawIndexed(GLenum mode, int count, GLenum type, void* indices) {
			return DrawCmd(INDEXED, mode, type, 0, 0, 0, 0, count, 0, 0, 0, 0, 0, indices, nullptr, nullptr);
		}

		bool Draw(GLenum mode, int first, int count) {
			return DrawCmd(NONE, mode, 0, 0, first, 0, 0, count, 0, 0, 0, 0, 0, nullptr, nullptr, nullptr);
		}
		
		bool DrawCmd(DrawMode drawmode, GLenum mode, GLenum type, GLenum format, int first, int start, int end, int count, int basevertex, int baseinstance, int instancecount, int width, int height, void* indices, void* indirect, void* pixels) {
			shader->SetUniformi("drawcount", drawcount);

			switch (drawmode) {
				case NONE:
					glDrawArrays(mode, first, count);
					break;
				case INDIRECT:
					glDrawArraysIndirect(mode, indirect);
					break;
				case INSTANCED:
					glDrawArraysInstanced(mode, first, count, instancecount);
					break;
				case INSTANCED_BASEINSTANCE:
					glDrawArraysInstancedBaseInstance(mode, first, count, instancecount, baseinstance);
					break;
					
				case INDEXED:
					glDrawElements(mode, count, type, indices);
					break;
				case INDEXED_INDIRECT:
					glDrawElementsIndirect(mode, type, indirect);
					break;
				case INDEXED_INSTANCED:
					glDrawElementsInstanced(mode, count, type, indices, instancecount);
					break;
				case INDEXED_BASEVERTEX:
					glDrawElementsBaseVertex(mode, count, type, indices, basevertex);
					break;
				case INDEXED_INSTANCED_BASEINSTANCE:
					glDrawElementsInstancedBaseVertex(mode, count, type, indices, instancecount, basevertex);
					break;
				case INDEXED_INSTANCED_BASEVERTEX:
					glDrawElementsInstancedBaseVertex(mode, count,  type, indices, instancecount, basevertex);
					break;
				case INDEXED_INSTANCED_BASEVERTEX_BASEINSTANCE:
					glDrawElementsInstancedBaseVertexBaseInstance(mode, count, type, indices, instancecount, basevertex, baseinstance);
					break;
				
				case RANGE_INDEXED:
					glDrawRangeElements(mode, start, end, count, type, indices);
					break;
				case RANGE_INDEXED_BASEVERTEX:
					glDrawRangeElementsBaseVertex(mode, start, end, count, type, indices, basevertex);
					break;

				case PIXELS:
					glDrawPixels(width, height, format, type, pixels);
					break;
				
				default:
					return false;
			}

			drawcount++;
			drawn_sprite_entities.push_back(std::vector<Entity>());

			return true;
		}

		void SetLighting();
		void RenderSprite();
		void RenderMesh();
		void RenderCamera();

		IndexBuffer* GetQuadIndices(VertexArray* vertexarray, int vertexcount);
	private:
		void Test();
	};
}