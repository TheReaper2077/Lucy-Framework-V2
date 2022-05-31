#pragma once

#include "../ECS.h"
#include <LucyGL/API.h>

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <memory>

#include "../Window.h"
#include "../Components/Components.h"

#include "../Registries/VertexArrayRegistry.h"
#include "RenderPass.h"
#include "assert.h"

namespace lucy {
	class RenderContext {
		lucy::Registry* registry = nullptr;

	public:
		lgl::Shader* shader = nullptr;
		lgl::UniformBuffer* uniformbuffer = nullptr;

		glm::mat4 model;
		glm::mat4 view;
		glm::mat4 projection;
		glm::vec3 view_position;

		std::vector<std::vector<Entity>> drawn_sprite_entities;

		glm::vec4 wireframe_color = glm::vec4(1, 1, 0, 1);

		std::vector<std::shared_ptr<RenderPass>> renderpass;

		int drawcount = 0;
		int vertexcount = 0;
		int indexcount = 0;

		void SetModel(const glm::mat4& model);
		void SetView(const glm::mat4& view);
		void SetProjection(const glm::mat4& projection);
		void SetViewPosition(const glm::vec3& view_position);

		void Init(lucy::Registry* registry);

		void Render(int width, int height, bool debug = false);
		
		void Render(lgl::FrameBuffer* framebuffer, Entity camera_entity, int width, int height, bool debug = false);
		
		void Render(Window& window, Entity camera_entity, bool debug = false) {
			Render(window.framebuffer, camera_entity, window.width, window.height, debug);
		}

		void Render(Window& window, bool debug = false) {
			Render(window, window.camera, debug);
		}
		
		void SetLighting();
		void RenderMesh();
		void RenderCamera();

		template <typename T>
		void InsertRenderPass() {
			auto ptr = std::make_shared<T>();
			ptr->registry = registry;
			renderpass.push_back(std::static_pointer_cast<RenderPass>(ptr));
		}
		
		void RenderLines(const std::vector<glm::vec3>& vertices, const glm::vec4& color) {
			shader->Bind();

			shader->SetUniformi("wireframe_mode", 1);

			static lgl::VertexBuffer* vertexbuffer;
			lgl::VertexArray* vertexarray = registry->store<VertexArrayRegistry>().GetVertexArray(VertexArrayAttribFlag_POSITION);

			if (vertexbuffer == nullptr)
				vertexbuffer = new lgl::VertexBuffer();
			
			vertexbuffer->Bind();
			vertexbuffer->Allocate(sizeof(glm::vec3)*vertices.size());
			vertexbuffer->AddDataDynamic((void*)vertices.data(), sizeof(glm::vec3)*vertices.size());

			vertexarray->Bind();
			vertexarray->BindVertexBuffer(vertexbuffer);

			lgl::Draw(lgl::LINE, 0, vertices.size());

			shader->SetUniformi("wireframe_mode", 0);
		}
	private:
		void Test();
	};
}