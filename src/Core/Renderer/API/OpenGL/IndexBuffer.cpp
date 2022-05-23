#include <LucyGL/VertexArray.h>
#include <LucyGL/IndexBuffer.h>

#include <glad/glad.h>
#include <assert.h>

lgl::IndexBuffer::IndexBuffer(VertexArray* vertexarray) {
	glGenBuffers(1, &id);
	size = 0;

	this->vertexarray = vertexarray;
}

void lgl::IndexBuffer::Bind() {
	vertexarray->Bind();
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->id);
}

void lgl::IndexBuffer::UnBind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}


lgl::IndexBuffer::~IndexBuffer() {
	glDeleteBuffers(1, &id);
}

void lgl::IndexBuffer::Allocate(std::size_t size) {
	if (this->size > size) return;

	this->Bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
	this->size = size;
};

void lgl::IndexBuffer::AddData(void* data, std::size_t size, std::size_t offset) {
	if (size == 0) return;

	if (offset == 0 && size > this->size) {
		Bind();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
		this->size = size;
		return;
	}

	assert(offset + size <= this->size);

	Bind();
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, size, data);
	this->size = size;
}
