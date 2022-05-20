#pragma once

#include <RenderAPI.h>
#include <unordered_map>

namespace lf {
	struct VertexArrayRegistry {
		std::unordered_map<std::size_t, VertexArray*> bit_layout;
		std::unordered_map<std::size_t, VertexArray*> custom_layout;

		VertexArrayRegistry() {}

		template <typename T>
		void SetVertexArray(std::vector<VertexArrayAttribDescriptor> descriptor) {
			custom_layout[typeid(T).hash_code()] = new VertexArray(descriptor);
		}

		template <typename T>
		VertexArray* GetVertexArray() {
			assert(custom_layout.find(typeid(T).hash_code()) != custom_layout.end());

			return custom_layout[typeid(T).hash_code()];
		}

		VertexArray* GetVertexArray(uint32_t flags);
	};
}