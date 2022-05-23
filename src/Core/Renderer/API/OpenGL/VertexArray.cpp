#pragma once

#include <LucyGL/VertexArray.h>
#include <LucyGL/VertexBuffer.h>
#include <LucyGL/IndexBuffer.h>

#include <glad/glad.h>
#include <assert.h>

lgl::VertexArray::VertexArray(std::vector<VertexArrayAttribDescriptor> layouts) {
	glGenVertexArrays(1, &this->id);
	this->Bind();

	uint32_t relativeoffset = 0;
	uint32_t elem_relativeoffset = 0;

	for (auto& attrib: layouts) {
		glVertexArrayAttribFormat(this->id, attrib.idx, attrib.size, GetMap(attrib.type), false, relativeoffset);
		glVertexArrayAttribBinding(this->id, attrib.idx, 0);
		glEnableVertexArrayAttrib(this->id, attrib.idx);

		switch(GetMap(attrib.type)) {
			case GL_FLOAT:
				relativeoffset += sizeof(GLfloat)*attrib.size;
				break;
			
			case GL_FIXED:
				relativeoffset += sizeof(GLfixed)*attrib.size;
				break;
			
			case GL_BYTE:
				relativeoffset += sizeof(GLbyte)*attrib.size;
				break;
			
			case GL_UNSIGNED_BYTE:
				relativeoffset += sizeof(GLubyte)*attrib.size;
				break;
			
			default:
				assert(false);
		}
		
		elem_relativeoffset += attrib.size;
	}

	this->stride = relativeoffset;
	this->elem_stride = elem_relativeoffset;
}

void lgl::VertexArray::Bind() {
	glBindVertexArray(id);
}

void lgl::VertexArray::UnBind() {
	glBindVertexArray(0);
}

void lgl::VertexArray::BindVertexBuffer(VertexBuffer *vertexbuffer, std::size_t stride, std::size_t offset) {
	glVertexArrayVertexBuffer(id, 0, vertexbuffer->id, offset, (stride == 0) ? this->stride : stride);
}

void lgl::VertexArray::BindIndexBuffer(IndexBuffer *indexbuffer) {
	glVertexArrayElementBuffer(id, indexbuffer->id);
}