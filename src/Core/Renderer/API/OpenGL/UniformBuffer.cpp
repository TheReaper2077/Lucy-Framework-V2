#include <GraphicsAPI/UniformBuffer.h>

#include <glad/glad.h>
#include <assert.h>

lfal::UniformBuffer::UniformBuffer() {
	glGenBuffers(1, &id);
	size = 0;
}

lfal::UniformBuffer::~UniformBuffer() {
	glDeleteBuffers(1, &id);
}

void lfal::UniformBuffer::Allocate(size_t size) {
	if (this->size > size) return;

	Bind();
	glBufferData(GL_UNIFORM_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
	this->size = size;
};

void lfal::UniformBuffer::AddDataDynamic(void* data, size_t size, size_t offset) {
	assert(offset + size <= this->size);

	Bind();
	glBufferSubData(GL_UNIFORM_BUFFER, offset, size, data);
}

void lfal::UniformBuffer::BindRange(unsigned int index, size_t size, size_t offset) {
	Bind();
	glBindBufferRange(GL_UNIFORM_BUFFER, index, this->id, offset, size);
}

void lfal::UniformBuffer::Bind() {
	// if (gl_context->binding_uniformbuffer == this->id) return;
	// gl_context->binding_uniformbuffer = this->id;
	glBindBuffer(GL_UNIFORM_BUFFER, this->id);
}

void lfal::UniformBuffer::UnBind() {
	// gl_context->binding_uniformbuffer = 0;
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}