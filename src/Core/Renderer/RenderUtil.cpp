#pragma once

#include "RenderUtil.h"
#include <memory>

lgl::IndexBuffer* lucy::GetQuadIndices(int vertexcount) {
	static lgl::IndexBuffer indexbuffer;
	static int indexcount;

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

		indexbuffer.Bind();
		indexbuffer.AddData(indices.data(), indices.size()*sizeof(uint32_t));

		indices.clear();
		indexcount = vertexcount*1.5;
	}

	return &indexbuffer;
}
