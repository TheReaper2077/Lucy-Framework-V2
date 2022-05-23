#pragma once

#include <glad/glad.h>

#include "../Components/Components.h"
#include "../Registries/VertexArrayRegistry.h"
#include "SpriteRenderer.h"

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

static struct Vertex {
	glm::vec3 position;
	glm::vec4 color;
	glm::vec2 uv;
};

static std::vector<Vertex> vertices;

void lf::SpriteRenderer::Init() {
	
}

void lf::SpriteRenderer::Render() {
	
}
