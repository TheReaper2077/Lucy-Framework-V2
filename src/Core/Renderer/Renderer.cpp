#include "Renderer.h"
#include "../Events.h"
#include "../Engine.h"
#include "../Components/Components.h"
#include "../Registries/ShaderRegistry.h"
#include "../Registries/VertexArrayRegistry.h"

#include <iostream>
#include <glad/glad.h>

void lf::Renderer::SetModel(const glm::mat4& model) {
	if (this->model == model) return;
	this->model = model;
	uniformbuffer->AddDataDynamic(&this->model[0][0], sizeof(glm::mat4), sizeof(glm::mat4) * 0);
}
void lf::Renderer::SetView(const glm::mat4& view) {
	if (this->view == view) return;
	this->view = view;
	uniformbuffer->AddDataDynamic(&this->view[0][0], sizeof(glm::mat4), sizeof(glm::mat4) * 1);
}
void lf::Renderer::SetProjection(const glm::mat4& projection) {
	if (this->projection == projection) return;
	this->projection = projection;
	uniformbuffer->AddDataDynamic(&this->projection[0][0], sizeof(glm::mat4), sizeof(glm::mat4) * 2);
}
void lf::Renderer::SetViewPosition(const glm::vec3& view_position) {
	if (this->view_position == view_position) return;
	this->view_position = view_position;
	uniformbuffer->AddDataDynamic(&this->view_position[0], sizeof(glm::vec3), sizeof(glm::mat4) * 3);
}

void lf::Renderer::Init(lf::Registry* registry) {
	this->registry = registry;

	uniformbuffer = new lgl::UniformBuffer();
	uniformbuffer->Allocate(sizeof(glm::mat4)*4);
	uniformbuffer->BindRange(0, sizeof(glm::mat4)*4, 0);

	// shader = Shader("test1", "D:\\C++\\Lucy Framework V2\\src\\Core\\Renderer\\Shaders\\default.vs", "D:\\C++\\Lucy Framework V2\\src\\Core\\Renderer\\Shaders\\color.fs");
}

void lf::Renderer::Render(lgl::FrameBuffer* framebuffer, Entity camera_entity, int width, int height, bool debug) {
	if (camera_entity == (Entity)0) return;
	if (!registry->valid(camera_entity)) return;

	auto [transform, camera] = registry->try_get<lf::Component::Transform, lf::Component::Camera>(camera_entity);

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

void lf::Renderer::Test() {
	static std::vector<glm::vec3> vertices = {
		{1.0, 1.0, 0.0},
		{1.0, 0.0, 0.0},
		{0.0, 0.0, 0.0},
		{0.0, 1.0, 0.0},
	};
	static lgl::VertexBuffer* vertexbuffer;
	lgl::VertexArray* vertexarray = registry->store<VertexArrayRegistry>().GetVertexArray(VertexArrayAttribFlag_POSITION);

	shader->SetUniformi("has_texture", 1);

	if (vertexbuffer == nullptr) {
		vertexbuffer = new lgl::VertexBuffer();

		vertexbuffer->AddDataStatic(vertices.data(), vertices.size()*vertexarray->stride);
	}

	vertexarray->Bind();
	vertexarray->BindVertexBuffer(vertexbuffer, vertexarray->stride);
	vertexarray->BindIndexBuffer(GetQuadIndices(vertexarray, 4));

	lgl::DrawIndexed(lgl::TRIANGLES, 6, lgl::UNSIGNED_INT, nullptr);

	shader->SetUniformi("has_texture", 0);
}

void lf::Renderer::Render(int width, int height, bool debug) {
	using namespace lf::Component;

	drawcount = 0;
	drawn_sprite_entities.clear();
	drawn_sprite_entities.push_back(std::vector<Entity>());
	
	glEnable(GL_DEPTH_TEST);
	glViewport(0, 0, width, height);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shader = registry->store<ShaderRegistry>().GetShader(0, registry);
	shader->Bind();

	RenderSprite();
	RenderMesh();

	if (debug) {
		RenderCamera();
	}
}

void lf::Renderer::RenderSprite() {
	using namespace lf::Component;

	int vertexcount = registry->view<Tag, Transform, SpriteRenderer>().size_hint() * 4;
	if (!vertexcount) return;

	uint32_t flags = VertexArrayAttribFlag_POSITION | VertexArrayAttribFlag_COLOR | VertexArrayAttribFlag_UV0;

	SetModel(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0)));

	auto& vertexarrayregistry = registry->store<VertexArrayRegistry>();

	lgl::VertexArray* vertexarray = vertexarrayregistry.GetVertexArray(flags);

	auto position_offset = vertexarrayregistry.GetOffset(vertexarray, VertexArrayAttrib_POSITION);
	auto color_offset = vertexarrayregistry.GetOffset(vertexarray, VertexArrayAttrib_COLOR);
	auto uv0_offset = vertexarrayregistry.GetOffset(vertexarray, VertexArrayAttrib_UV0);

	static lgl::VertexBuffer* vertexbuffer;

	if (vertexbuffer == nullptr)
		vertexbuffer = new lgl::VertexBuffer();

	float* vertices = (float*)malloc(sizeof(float) * (3 + 4 + 2) * vertexcount);

	int i = 0;
	for (auto entity: registry->view<Tag, Transform, SpriteRenderer>()) {
		auto& transform = registry->get<Transform>(entity);
		auto& spriterenderer = registry->get<SpriteRenderer>(entity);
		auto quaternion = transform.GetRotationQuat();

		auto* sprite = registry->try_get<Sprite>(entity);

		if (!spriterenderer.visible) {
			vertexcount -= 4;
			continue;
		}

		// drawn_sprite_entities[drawcount].push_back(entity);

		glm::vec3 pos00 = (quaternion * glm::vec3(-transform.scale.x / 2.0, -transform.scale.y / 2.0, 0)) + transform.translation;
		glm::vec3 pos01 = (quaternion * glm::vec3(+transform.scale.x / 2.0, -transform.scale.y / 2.0, 0)) + transform.translation;
		glm::vec3 pos10 = (quaternion * glm::vec3(+transform.scale.x / 2.0, +transform.scale.y / 2.0, 0)) + transform.translation;
		glm::vec3 pos11 = (quaternion * glm::vec3(-transform.scale.x / 2.0, +transform.scale.y / 2.0, 0)) + transform.translation;

		vertices[i * vertexarray->elem_stride + position_offset + 0] = pos00.x;
		vertices[i * vertexarray->elem_stride + position_offset + 1] = pos00.y;
		vertices[i * vertexarray->elem_stride + position_offset + 2] = pos00.z;

		vertices[i * vertexarray->elem_stride + color_offset + 0] = spriterenderer.color.x;
		vertices[i * vertexarray->elem_stride + color_offset + 1] = spriterenderer.color.y;
		vertices[i * vertexarray->elem_stride + color_offset + 2] = spriterenderer.color.z;
		vertices[i * vertexarray->elem_stride + color_offset + 3] = spriterenderer.color.w;

		vertices[i * vertexarray->elem_stride + uv0_offset + 0] = 0;
		vertices[i * vertexarray->elem_stride + uv0_offset + 1] = 0;
		i++;

		vertices[i * vertexarray->elem_stride + position_offset + 0] = pos01.x;
		vertices[i * vertexarray->elem_stride + position_offset + 1] = pos01.y;
		vertices[i * vertexarray->elem_stride + position_offset + 2] = pos01.z;

		vertices[i * vertexarray->elem_stride + color_offset + 0] = spriterenderer.color.x;
		vertices[i * vertexarray->elem_stride + color_offset + 1] = spriterenderer.color.y;
		vertices[i * vertexarray->elem_stride + color_offset + 2] = spriterenderer.color.z;
		vertices[i * vertexarray->elem_stride + color_offset + 3] = spriterenderer.color.w;

		vertices[i * vertexarray->elem_stride + uv0_offset + 0] = 0;
		vertices[i * vertexarray->elem_stride + uv0_offset + 1] = 1;
		i++;

		vertices[i * vertexarray->elem_stride + position_offset + 0] = pos10.x;
		vertices[i * vertexarray->elem_stride + position_offset + 1] = pos10.y;
		vertices[i * vertexarray->elem_stride + position_offset + 2] = pos10.z;

		vertices[i * vertexarray->elem_stride + color_offset + 0] = spriterenderer.color.x;
		vertices[i * vertexarray->elem_stride + color_offset + 1] = spriterenderer.color.y;
		vertices[i * vertexarray->elem_stride + color_offset + 2] = spriterenderer.color.z;
		vertices[i * vertexarray->elem_stride + color_offset + 3] = spriterenderer.color.w;

		vertices[i * vertexarray->elem_stride + uv0_offset + 0] = 1;
		vertices[i * vertexarray->elem_stride + uv0_offset + 1] = 0;
		i++;

		vertices[i * vertexarray->elem_stride + position_offset + 0] = pos11.x;
		vertices[i * vertexarray->elem_stride + position_offset + 1] = pos11.y;
		vertices[i * vertexarray->elem_stride + position_offset + 2] = pos11.z;

		vertices[i * vertexarray->elem_stride + color_offset + 0] = spriterenderer.color.x;
		vertices[i * vertexarray->elem_stride + color_offset + 1] = spriterenderer.color.y;
		vertices[i * vertexarray->elem_stride + color_offset + 2] = spriterenderer.color.z;
		vertices[i * vertexarray->elem_stride + color_offset + 3] = spriterenderer.color.w;

		vertices[i * vertexarray->elem_stride + uv0_offset + 0] = 1;
		vertices[i * vertexarray->elem_stride + uv0_offset + 1] = 1;
		i++;
	}

	shader->SetUniformi("has_texture", 1);

	vertexbuffer->Allocate(sizeof(float) * (3 + 4 + 2) * vertexcount);
	vertexbuffer->AddDataDynamic(vertices, sizeof(float) * (3 + 4 + 2) * vertexcount);

	vertexarray->Bind();
	vertexarray->BindVertexBuffer(vertexbuffer, vertexarray->stride);
	vertexarray->BindIndexBuffer(GetQuadIndices(vertexarray, vertexcount));

	lgl::DrawIndexed(lgl::TRIANGLES, vertexcount * 1.5, lgl::UNSIGNED_INT, nullptr);
	
	auto& engine = registry->store<Engine>();
	engine.drawcalls++;
	engine.vertexcount += vertexcount;
	engine.indexcount += vertexcount * 1.5;

	free(vertices);
	vertices = nullptr;

	shader->SetUniformi("has_texture", 0);
}

void lf::Renderer::RenderMesh() {
	
}

void lf::Renderer::RenderCamera() {
	using namespace lf::Component;

	shader->SetUniformi("wireframe_mode", 1);

	shader->SetUniformVec4("wireframe_color", &glm::vec4(1, 1, 0, 1)[0]);

	lgl::VertexArray* vertexarray = registry->store<VertexArrayRegistry>().GetVertexArray(VertexArrayAttribFlag_POSITION);

	for (auto [entity, tag, transform, camera]: registry->view<Tag, Transform, Camera>().each()) {
		float aspect_ratio = camera.width / camera.height;
		float horizontal_fov = camera.fov;
		float vertical_fov = camera.fov / aspect_ratio;

		float far_highten = (std::tan(glm::radians(vertical_fov / 2)) * camera.camera_far) / (camera.camera_far - camera.camera_near);
		float far_widen = (std::tan(glm::radians(horizontal_fov / 2)) * camera.camera_far) / (camera.camera_far - camera.camera_near);

		float near_highten = (std::tan(glm::radians(vertical_fov / 2)) * camera.camera_near) / (camera.camera_far - camera.camera_near);
		float near_widen = (std::tan(glm::radians(horizontal_fov / 2)) * camera.camera_near) / (camera.camera_far - camera.camera_near);

		
	}

	shader->SetUniformi("wireframe_mode", 0);
}

void lf::Renderer::SetLighting() {
	using namespace lf::Component;

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

lgl::IndexBuffer* lf::Renderer::GetQuadIndices(lgl::VertexArray* vertexarray, int vertexcount) {
	static lgl::IndexBuffer* indexbuffer;
	static int indexcount;

	if (indexbuffer == nullptr)
		indexbuffer = new lgl::IndexBuffer(vertexarray);

	if (vertexcount*1.5 > indexcount) {
		std::vector<uint32_t> indices;

		indices.reserve(vertexcount*1.5);

		for (int i = 0; i < vertexcount; i++) {
			indices.emplace_back(0 + i*4);
			indices.emplace_back(1 + i*4);
			indices.emplace_back(2 + i*4);
			indices.emplace_back(2 + i*4);
			indices.emplace_back(3 + i*4);
			indices.emplace_back(0 + i*4);
		}

		indexbuffer->AddData(indices.data(), indices.size()*sizeof(uint32_t));

		indices.clear();
		indexcount = vertexcount*1.5;
	}

	return indexbuffer;
}
