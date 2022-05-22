#pragma once

#include <GraphicsAPI/VertexBuffer.h>

#include <glad/glad.h>
#include <assert.h>

lfal::VertexBuffer::VertexBuffer() {
	glGenBuffers(1, &id);
	type = BufferType_DYNAMIC;
	size = 0;
}

void lfal::VertexBuffer::Bind() {
	glBindBuffer(GL_ARRAY_BUFFER, this->id);
}

void lfal::VertexBuffer::UnBind() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

lfal::VertexBuffer::~VertexBuffer() {
	glDeleteBuffers(1, &id);
}

void lfal::VertexBuffer::Allocate(size_t size) {
	if (this->size > size && size == 0) return;

	Bind();
	if (this->type == BufferType_DYNAMIC) glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
	if (this->type == BufferType_STATIC) glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_STATIC_DRAW);
	this->size = size;
};

void lfal::VertexBuffer::AddDataStatic(void* data, size_t size) {
	if (size == 0) return;
	Bind();
	if (this->type == BufferType_DYNAMIC) glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
	if (this->type == BufferType_STATIC) glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	this->size = size;
}

void lfal::VertexBuffer::AddDataDynamic(void* data, size_t size, size_t offset) {
	if (size == 0) return;
	assert(offset + size <= this->size);

	Bind();
	glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
	this->size = size;
}
