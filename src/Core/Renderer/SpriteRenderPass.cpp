#pragma once

#include <iostream>
#include <glad/glad.h>

#include "../Components/Components.h"
#include "../Registries/VertexArrayRegistry.h"
#include "SpriteRenderPass.h"
#include "RenderUtil.h"
#include "Renderer.h"

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

using namespace lucy::Component;

static struct Vertex {
	glm::vec3 position;
	glm::vec4 color;
	glm::vec3 uv;
};

static std::vector<Vertex> vertices;
static lgl::VertexArray* vertexarray = nullptr;
// static std::set<TextureId> vertexarray;

void RenderRect(const Transform& transform, const SpriteRenderer& spriterenderer, const glm::quat& quaternion) {
	vertices.reserve(4 + vertices.size());

	vertices.emplace_back(Vertex{ (quaternion * glm::vec3(-transform.scale.x / 2.0, -transform.scale.y / 2.0, 0.0)) + transform.translation, spriterenderer.color, glm::vec3(spriterenderer.uv0.x, spriterenderer.uv0.y, 0.0) });
	vertices.emplace_back(Vertex{ (quaternion * glm::vec3(+transform.scale.x / 2.0, -transform.scale.y / 2.0, 0.0)) + transform.translation, spriterenderer.color, glm::vec3(spriterenderer.uv0.x, spriterenderer.uv1.y, 0.0) });
	vertices.emplace_back(Vertex{ (quaternion * glm::vec3(+transform.scale.x / 2.0, +transform.scale.y / 2.0, 0.0)) + transform.translation, spriterenderer.color, glm::vec3(spriterenderer.uv1.x, spriterenderer.uv0.y, 0.0) });
	vertices.emplace_back(Vertex{ (quaternion * glm::vec3(-transform.scale.x / 2.0, +transform.scale.y / 2.0, 0.0)) + transform.translation, spriterenderer.color, glm::vec3(spriterenderer.uv1.x, spriterenderer.uv1.y, 0.0) });
}

void Flush(lucy::Registry* registry) {
	if (!vertices.size()) return;

	static lgl::VertexBuffer vertexbuffer;

	vertexbuffer.Bind();
	vertexbuffer.Allocate(vertices.size()*sizeof(Vertex));
	vertexbuffer.AddDataDynamic(vertices.data(), vertices.size()*sizeof(Vertex));

	vertexarray->Bind();
	vertexarray->BindVertexBuffer(&vertexbuffer);
	vertexarray->BindIndexBuffer(lucy::GetQuadIndices(int(vertices.size() * 1.5)));

	lgl::DrawIndexed(lgl::TRIANGLE, vertices.size() * 1.5, lgl::UNSIGNED_INT, nullptr);
	registry->store<lucy::RenderContext>().drawn_sprite_entities.push_back(std::vector<lucy::Entity>());

	vertices.clear();
}

void lucy::SpriteRenderPass::Init() {
	if (vertexarray == nullptr) {
		vertexarray = registry->store<VertexArrayRegistry>().SetVertexArray<Vertex>({
			{ VertexArrayAttrib_POSITION, VertexArrayAttribSize_POSITION, lgl::FLOAT },
			{ VertexArrayAttrib_COLOR, VertexArrayAttribSize_COLOR, lgl::FLOAT },
			{ VertexArrayAttrib_UVW, VertexArrayAttribSize_UVW, lgl::FLOAT },
		});
	}
}

void lucy::SpriteRenderPass::Render() {
	auto& renderer = registry->store<RenderContext>();

	renderer.shader->Bind();
	renderer.shader->SetUniformi("has_texture", 1);

	for (auto entity: registry->view<Tag, Transform, SpriteRenderer>()) {
		auto& spriterenderer = registry->get<SpriteRenderer>(entity);

		if (!spriterenderer.visible) continue;

		auto& transform = registry->get<Transform>(entity);
		auto quaternion = transform.GetRotationQuat();

		RenderRect(transform, spriterenderer, quaternion);
		registry->store<lucy::RenderContext>().drawn_sprite_entities[renderer.drawcount].push_back(entity);
	}

	Flush(registry);

	renderer.shader->SetUniformi("has_texture", 1);
}
