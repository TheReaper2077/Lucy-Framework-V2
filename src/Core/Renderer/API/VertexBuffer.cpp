#pragma once

#include <RenderAPI.h>

VertexBuffer::VertexBuffer() {
	glGenBuffers(1, &id);
	type = DYNAMIC;
	size = 0;
}

void VertexBuffer::Bind() {
	glBindBuffer(GL_ARRAY_BUFFER, this->id);
}

void VertexBuffer::UnBind() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

VertexBuffer::~VertexBuffer() {
	glDeleteBuffers(1, &id);
}

void VertexBuffer::Allocate(std::size_t size) {
	if (this->size > size && size == 0) return;

	Bind();
	if (this->type == DYNAMIC) glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
	if (this->type == STATIC) glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_STATIC_DRAW);
	this->size = size;
};

void VertexBuffer::AddDataStatic(void* data, std::size_t size) {
	if (size == 0) return;
	Bind();
	if (this->type == DYNAMIC) glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
	if (this->type == STATIC) glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	this->size = size;
}

void VertexBuffer::AddDataDynamic(void* data, std::size_t size, std::size_t offset) {
	if (size == 0) return;
	assert(offset + size <= this->size);

	Bind();
	glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
	this->size = size;
}
