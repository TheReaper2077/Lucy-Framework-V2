#include "VertexArrayRegistry.h"
#include <iostream>
#include <bitset>
       
lfal::VertexArray* lf::VertexArrayRegistry::GetVertexArray(uint32_t flags) {
	if (bit_layout.find(flags) == bit_layout.end()) {
		std::vector<lfal::VertexArrayAttribDescriptor> descriptor;
		std::array<bool, VertexArrayAttrib_COUNT> attrib_present;
		std::array<uint32_t, VertexArrayAttrib_COUNT> attrib_offset;

		uint32_t offset = 0;

		for (uint32_t i = 0; i < VertexArrayAttrib_COUNT; i++) {
			if ((flags >> i) & 1) {
				attrib_offset[i] = offset;
				attrib_present[i] = true;

				descriptor.push_back({ i, (uint32_t)VertexArrayAttribSizeMap_[i], lfal::FLOAT });
				offset += VertexArrayAttribSizeMap_[i];
			} else {
				attrib_present[i] = false;
			}
		}

		auto* vertexarray = new lfal::VertexArray(descriptor);
		bit_layout[flags] = vertexarray;
		this->offset[vertexarray] = attrib_offset;
		this->is_present[vertexarray] = attrib_present;
	}

	return bit_layout[flags];
}
