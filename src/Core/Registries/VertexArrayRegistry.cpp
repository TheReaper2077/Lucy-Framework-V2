#include "VertexArrayRegistry.h"
       
VertexArray* lf::VertexArrayRegistry::GetVertexArray(uint32_t flags) {
	if (bit_layout.find(flags) == bit_layout.end()) {
		std::vector<VertexArrayAttribDescriptor> descriptor;

		if (flags & POSITION_ATTRIB_BIT) {
			descriptor.push_back({ position, 0, 3, GL_FLOAT });
		}
		if (flags & NORMAL_ATTRIB_BIT) {
			descriptor.push_back({ normal, 1, 3, GL_FLOAT });
		}
		if (flags & COLOR_ATTRIB_BIT) {
			descriptor.push_back({ color, 2, 4, GL_FLOAT });
		}
		if (flags & UV0_ATTRIB_BIT) {
			descriptor.push_back({ uv0, 3, 2, GL_FLOAT });
		}
		if (flags & UV1_ATTRIB_BIT) {
			descriptor.push_back({ uv1, 4, 2, GL_FLOAT });
		}
		if (flags & UV2_ATTRIB_BIT) {
			descriptor.push_back({ uv2, 5, 2, GL_FLOAT });
		}
		if (flags & UV3_ATTRIB_BIT) {
			descriptor.push_back({ uv3, 6, 2, GL_FLOAT });
		}
		if (flags & UV4_ATTRIB_BIT) {
			descriptor.push_back({ uv4, 7, 2, GL_FLOAT });
		}
		if (flags & UV5_ATTRIB_BIT) {
			descriptor.push_back({ uv5, 8, 2, GL_FLOAT });
		}
		if (flags & UV6_ATTRIB_BIT) {
			descriptor.push_back({ uv6, 9, 2, GL_FLOAT });
		}
		if (flags & UV7_ATTRIB_BIT) {
			descriptor.push_back({ uv7, 10, 2, GL_FLOAT });
		}

		bit_layout[flags] = VertexArray_Create(descriptor);
	}

	return bit_layout[flags];
}
