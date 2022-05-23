#pragma once

#include "../ECS.h"
#include <LucyGL/API.h>

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

#include "../Window.h"
#include "../Components/Components.h"

#include "../Registries/VertexArrayRegistry.h"

#include "assert.h"

namespace lf {
	class Renderer {
		lf::Registry* registry = nullptr;

		lgl::Shader* shader = nullptr;
		lgl::UniformBuffer* uniformbuffer = nullptr;

		glm::mat4 model;
		glm::mat4 view;
		glm::mat4 projection;
		glm::vec3 view_position;

	public:
		std::vector<std::vector<Entity>> drawn_sprite_entities;

		glm::vec4 wireframe_color = glm::vec4(1, 1, 0, 1);

		int drawcount = 0;
		int vertexcount = 0;
		int indexcount = 0;

		void SetModel(const glm::mat4& model);
		void SetView(const glm::mat4& view);
		void SetProjection(const glm::mat4& projection);
		void SetViewPosition(const glm::vec3& view_position);

		void Init(lf::Registry* registry);

		void Render(int width, int height, bool debug = false);
		
		void Render(lgl::FrameBuffer* framebuffer, Entity camera_entity, int width, int height, bool debug = false);
		
		void Render(Window& window, Entity camera_entity, bool debug = false) {
			Render(window.framebuffer, camera_entity, window.width, window.height, debug);
		}

		void Render(Window& window, bool debug = false) {
			Render(window, window.camera, debug);
		}

		void RenderLines(const std::vector<glm::vec3>& vertices, const glm::vec4& color) {
			shader->Bind();

			shader->SetUniformi("wireframe_mode", 1);

			static lgl::VertexBuffer* vertexbuffer;
			lgl::VertexArray* vertexarray = registry->store<VertexArrayRegistry>().GetVertexArray(VertexArrayAttribFlag_POSITION);

			if (vertexbuffer == nullptr)
				vertexbuffer = new lgl::VertexBuffer();
			
			vertexbuffer->Allocate(sizeof(glm::vec3)*vertices.size());
			vertexbuffer->AddDataDynamic((void*)vertices.data(), sizeof(glm::vec3)*vertices.size());

			vertexarray->Bind();
			vertexarray->BindVertexBuffer(vertexbuffer);

			lgl::Draw(lgl::LINES, 0, vertices.size());

			shader->SetUniformi("wireframe_mode", 0);
		}
		
		void SetLighting();
		void RenderSprite();
		void RenderMesh();
		void RenderCamera();

		lgl::IndexBuffer* GetQuadIndices(lgl::VertexArray* vertexarray, int vertexcount);
	private:
		void Test();
	};
}