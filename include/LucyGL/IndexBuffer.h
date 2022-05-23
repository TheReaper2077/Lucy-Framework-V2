#pragma once

namespace lgl {
	struct VertexArray;

	typedef unsigned int IndexBufferId;

	struct IndexBuffer {
		IndexBufferId id;
		size_t size;
		VertexArray* vertexarray;
		
		IndexBuffer(VertexArray* vertexarray);
		~IndexBuffer();

		void Bind();
		void UnBind();
		void Allocate(size_t size);
		void AddData(void* data, size_t size, size_t offset = 0);
	};
}