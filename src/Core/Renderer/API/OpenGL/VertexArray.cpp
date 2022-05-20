#pragma once

#include <RenderAPI.h>

VertexArray::VertexArray(std::vector<VertexArrayAttribDescriptor> layouts) {
	glGenVertexArrays(1, &this->id);
	this->Bind();

	uint32_t relativeoffset = 0;
	uint32_t elem_relativeoffset = 0;

	for (auto& attrib: layouts) {
		GL_ASSERT(attrib.attr_type < VertexArrayAttrib_COUNT);

		if (attrib.attr_type == position) {
			this->position_offset = elem_relativeoffset;
			GL_ASSERT(!this->has_position);
			this->has_position = true;
		}
		if (attrib.attr_type == normal) {
			this->normal_offset = elem_relativeoffset;
			GL_ASSERT(!this->has_normal);
			this->has_normal = true;
		}
		if (attrib.attr_type == color) {
			this->color_offset = elem_relativeoffset;
			GL_ASSERT(!this->has_color);
			this->has_color = true;
		}
		if (attrib.attr_type == uv0) {
			this->uv0_offset = elem_relativeoffset;
			GL_ASSERT(!this->has_uv0);
			this->has_uv0 = true;
		}
		if (attrib.attr_type == uv1) {
			this->uv1_offset = elem_relativeoffset;
			GL_ASSERT(!this->has_uv1);
			this->has_uv1 = true;
		}
		if (attrib.attr_type == uv2) {
			this->uv2_offset = elem_relativeoffset;
			GL_ASSERT(!this->has_uv2);
			this->has_uv2 = true;
		}
		if (attrib.attr_type == uv3) {
			this->uv3_offset = elem_relativeoffset;
			GL_ASSERT(!this->has_uv3);
			this->has_uv3 = true;
		}
		if (attrib.attr_type == uv4) {
			this->uv4_offset = elem_relativeoffset;
			GL_ASSERT(!this->has_uv4);
			this->has_uv4 = true;
		}
		if (attrib.attr_type == uv5) {
			this->uv5_offset = elem_relativeoffset;
			GL_ASSERT(!this->has_uv5);
			this->has_uv5 = true;
		}
		if (attrib.attr_type == uv6) {
			this->uv6_offset = elem_relativeoffset;
			GL_ASSERT(!this->has_uv6);
			this->has_uv6 = true;
		}
		if (attrib.attr_type == uv7) {
			this->uv7_offset = elem_relativeoffset;
			GL_ASSERT(!this->has_uv7);
			this->has_uv7 = true;
		}

		glVertexArrayAttribFormat(this->id, attrib.idx, attrib.size, attrib.type, false, relativeoffset);
		glVertexArrayAttribBinding(this->id, attrib.idx, 0);
		glEnableVertexArrayAttrib(this->id, attrib.idx);

		switch(attrib.type) {
			case GL_FLOAT:
				relativeoffset += sizeof(GLfloat)*attrib.size;
				break;
			
			// case GL_FIXED:
			// 	relativeoffset += sizeof(GLfixed)*attrib.size;
			// 	break;
			
			case GL_BYTE:
				relativeoffset += sizeof(GLbyte)*attrib.size;
				break;
			
			case GL_UNSIGNED_BYTE:
				relativeoffset += sizeof(GLubyte)*attrib.size;
				break;
			
			default:
				GL_ASSERT(false);
		}
		
		elem_relativeoffset += attrib.size;
	}

	this->stride = relativeoffset;
	this->elem_stride = elem_relativeoffset;
}

void VertexArray::Bind() {
	glBindVertexArray(id);
}

void VertexArray::UnBind() {
	glBindVertexArray(0);
}

void VertexArray::BindVertexBuffer(VertexBuffer *vertexbuffer, std::size_t stride, std::size_t offset) {
	glVertexArrayVertexBuffer(id, 0, vertexbuffer->id, offset, (stride == 0) ? stride : stride);
}

void VertexArray::BindIndexBuffer(IndexBuffer *indexbuffer) {
	glVertexArrayElementBuffer(id, indexbuffer->id);
}