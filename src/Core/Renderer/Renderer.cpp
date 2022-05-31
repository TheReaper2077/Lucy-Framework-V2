#include "Renderer.h"
#include "../Events.h"
#include "../Engine.h"
#include "../Components/Components.h"
#include "../Registries/ShaderRegistry.h"
#include "../Registries/VertexArrayRegistry.h"

#include "SpriteRenderPass.h"
#include "RenderUtil.h"

#include <iostream>
#include <glad/glad.h>

void lucy::RenderContext::SetModel(const glm::mat4& model) {
	if (this->model == model) return;
	this->model = model;
	uniformbuffer->AddDataDynamic(&this->model[0][0], sizeof(glm::mat4), sizeof(glm::mat4) * 0);
}
void lucy::RenderContext::SetView(const glm::mat4& view) {
	if (this->view == view) return;
	this->view = view;
	uniformbuffer->AddDataDynamic(&this->view[0][0], sizeof(glm::mat4), sizeof(glm::mat4) * 1);
}
void lucy::RenderContext::SetProjection(const glm::mat4& projection) {
	if (this->projection == projection) return;
	this->projection = projection;
	uniformbuffer->AddDataDynamic(&this->projection[0][0], sizeof(glm::mat4), sizeof(glm::mat4) * 2);
}
void lucy::RenderContext::SetViewPosition(const glm::vec3& view_position) {
	if (this->view_position == view_position) return;
	this->view_position = view_position;
	uniformbuffer->AddDataDynamic(&this->view_position[0], sizeof(glm::vec3), sizeof(glm::mat4) * 3);
}

void lucy::RenderContext::Init(lucy::Registry* registry) {
	this->registry = registry;

	uniformbuffer = new lgl::UniformBuffer();
	uniformbuffer->Allocate(sizeof(glm::mat4)*4);
	uniformbuffer->BindRange(0, sizeof(glm::mat4)*4, 0);

	InsertRenderPass<SpriteRenderPass>();
}

void lucy::RenderContext::Render(lgl::FrameBuffer* framebuffer, Entity camera_entity, int width, int height, bool debug) {
	if (camera_entity == (Entity)0) return;
	if (!registry->valid(camera_entity)) return;

	auto [transform, camera] = registry->try_get<lucy::Component::Transform, lucy::Component::Camera>(camera_entity);

	if (transform == nullptr || camera == nullptr) return;

	SetProjection(camera->projection);
	SetModel(glm::mat4(1.0));
	SetView(camera->view);
	SetViewPosition(transform->translation);

	if (framebuffer != nullptr) {
		framebuffer->Bind();

		assert(framebuffer->width >= width && framebuffer->height >= height);
	}
	
	glClearColor(camera->clear_color.x, camera->clear_color.y, camera->clear_color.z, camera->clear_color.w);
	Render(width, height, debug);

	if (framebuffer != nullptr) framebuffer->UnBind();
}

void lucy::RenderContext::Test() {
	static std::vector<glm::vec3> vertices = {
		{1.0, 1.0, 0.0},
		{1.0, 0.0, 0.0},
		{0.0, 0.0, 0.0},
		{0.0, 1.0, 0.0},
	};
	static lgl::VertexBuffer* vertexbuffer;
	lgl::VertexArray* vertexarray = registry->store<VertexArrayRegistry>().GetVertexArray(VertexArrayAttribFlag_POSITION);

	shader->SetUniformi("wireframe_mode", 1);

	if (vertexbuffer == nullptr) {
		vertexbuffer = new lgl::VertexBuffer();

		vertexbuffer->AddDataStatic(vertices.data(), vertices.size()*vertexarray->stride);
	}

	vertexarray->Bind();
	vertexarray->BindVertexBuffer(vertexbuffer, vertexarray->stride);
	vertexarray->BindIndexBuffer(GetQuadIndices(4));

	lgl::DrawIndexed(lgl::TRIANGLE, 6, lgl::UNSIGNED_INT, nullptr);

	shader->SetUniformi("wireframe_mode", 0);
}

void lucy::RenderContext::Render(int width, int height, bool debug) {
	using namespace lucy::Component;

	drawcount = 0;
	drawn_sprite_entities.clear();
	drawn_sprite_entities.push_back(std::vector<Entity>());
	
	glEnable(GL_DEPTH_TEST);
	glViewport(0, 0, width, height);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shader = registry->store<ShaderRegistry>().GetShader(0, registry);
	shader->Bind();

	for (auto& ptr: renderpass) {
		if (!ptr->init) {
			ptr->Init();
			ptr->init = true;
		}
		
		ptr->Render();
	}

	RenderMesh();

	if (debug) {
		RenderCamera();
	}
}

void lucy::RenderContext::RenderMesh() {
	
}

void lucy::RenderContext::RenderCamera() {
	using namespace lucy::Component;

	std::vector<glm::vec3> vertices;

	for (auto [entity, tag, transform, camera]: registry->view<Tag, Transform, Camera>().each()) {
		auto quaternion = transform.GetRotationQuat();

		float aspect_ratio = camera.width / camera.height;
		float horizontal_fov = camera.fov;
		float vertical_fov = camera.fov / aspect_ratio;

		float far_highten = (std::tan(glm::radians(vertical_fov / 2)) * camera.camera_far) / (camera.camera_far - camera.camera_near);
		float far_widen = (std::tan(glm::radians(horizontal_fov / 2)) * camera.camera_far) / (camera.camera_far - camera.camera_near);

		float near_highten = (std::tan(glm::radians(vertical_fov / 2)) * camera.camera_near) / (camera.camera_far - camera.camera_near);
		float near_widen = (std::tan(glm::radians(horizontal_fov / 2)) * camera.camera_near) / (camera.camera_far - camera.camera_near);

		glm::vec3 near0 = quaternion * glm::vec3(-near_widen, -near_highten, 1) + transform.translation;
		glm::vec3 near1 = quaternion * glm::vec3(+near_widen, -near_highten, 1) + transform.translation;
		glm::vec3 near2 = quaternion * glm::vec3(+near_widen, +near_highten, 1) + transform.translation;
		glm::vec3 near3 = quaternion * glm::vec3(-near_widen, +near_highten, 1) + transform.translation;

		glm::vec3 far0 = quaternion * glm::vec3(-far_widen, -far_highten, 0) + transform.translation;
		glm::vec3 far1 = quaternion * glm::vec3(+far_widen, -far_highten, 0) + transform.translation;
		glm::vec3 far2 = quaternion * glm::vec3(+far_widen, +far_highten, 0) + transform.translation;
		glm::vec3 far3 = quaternion * glm::vec3(-far_widen, +far_highten, 0) + transform.translation;

		vertices.reserve(8 + 8 + 8 + vertices.size());

		vertices.emplace_back(near0);
		vertices.emplace_back(near1);
		vertices.emplace_back(near1);
		vertices.emplace_back(near2);
		vertices.emplace_back(near2);
		vertices.emplace_back(near3);
		vertices.emplace_back(near3);
		vertices.emplace_back(near0);
		
		vertices.emplace_back(far0);
		vertices.emplace_back(far1);
		vertices.emplace_back(far1);
		vertices.emplace_back(far2);
		vertices.emplace_back(far2);
		vertices.emplace_back(far3);
		vertices.emplace_back(far3);
		vertices.emplace_back(far0);

		vertices.emplace_back(far0);
		vertices.emplace_back(near0);
		vertices.emplace_back(far1);
		vertices.emplace_back(near1);
		vertices.emplace_back(far2);
		vertices.emplace_back(near2);
		vertices.emplace_back(far3);
		vertices.emplace_back(near3);
	}

	shader->SetUniformVec4("wireframe_color", &glm::vec4(1, 1, 0, 1)[0]);
	RenderLines(vertices, wireframe_color);
}

void lucy::RenderContext::SetLighting() {
	using namespace lucy::Component;

	int point_light = 0;
	int dir_light = 0;

	for (auto& entity : registry->view<Tag, Transform, Light>()) {
		auto& transform = registry->get<Transform>(entity);
		auto& light = registry->get<Light>(entity);

		if (!light.active) continue;

		if (light.mode == Directional) {
			auto direction = glm::normalize(transform.GetRotationQuat() * glm::vec3(0, -1.0, 0));

			shader->SetUniformVec3("dir_light" + std::to_string(dir_light) + ".color", &light.color[0]);
			shader->SetUniformVec3("dir_light" + std::to_string(dir_light) + ".direction", &direction[0]);

			dir_light++;
		}
		if (light.mode == Point) {
			shader->SetUniformVec3("point_light" + std::to_string(point_light) + ".color", &light.color[0]);
			shader->SetUniformVec3("point_light" + std::to_string(point_light) + ".position", &transform.translation[0]);

			point_light++;
		}
	}
}
