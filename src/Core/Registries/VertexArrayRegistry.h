#pragma once

#include <LucyGL/API.h>
#include <unordered_map>
#include <array>
#include <assert.h>

namespace lucy {
	enum VertexArrayAttrib_ {
		VertexArrayAttrib_POSITION = 0,
		VertexArrayAttrib_NORMAL = 1,
		VertexArrayAttrib_COLOR = 2,
		VertexArrayAttrib_UV0 = 3,
		VertexArrayAttrib_UV1 = 4,
		VertexArrayAttrib_UV2 = 5,
		VertexArrayAttrib_UV3 = 6,
		VertexArrayAttrib_UV4 = 7,
		VertexArrayAttrib_UV5 = 8,
		VertexArrayAttrib_UV6 = 9,
		VertexArrayAttrib_UV7 = 10,
		VertexArrayAttrib_UVW = 11,

		VertexArrayAttrib_COUNT
	};

	enum VertexArrayAttribSize_ {
		VertexArrayAttribSize_POSITION = 3,
		VertexArrayAttribSize_NORMAL = 3,
		VertexArrayAttribSize_COLOR = 4,
		VertexArrayAttribSize_UV0 = 2,
		VertexArrayAttribSize_UV1 = 2,
		VertexArrayAttribSize_UV2 = 2,
		VertexArrayAttribSize_UV3 = 2,
		VertexArrayAttribSize_UV4 = 2,
		VertexArrayAttribSize_UV5 = 2,
		VertexArrayAttribSize_UV6 = 2,
		VertexArrayAttribSize_UV7 = 2,
		VertexArrayAttribSize_UVW = 3,
	};

	enum VertexArrayAttribFlag_ {
		VertexArrayAttribFlag_POSITION = 1 << VertexArrayAttrib_POSITION,
		VertexArrayAttribFlag_NORMAL = 1 << VertexArrayAttrib_NORMAL,
		VertexArrayAttribFlag_COLOR = 1 << VertexArrayAttrib_COLOR,
		VertexArrayAttribFlag_UV0 = 1 << VertexArrayAttrib_UV0,
		VertexArrayAttribFlag_UV1 = 1 << VertexArrayAttrib_UV1,
		VertexArrayAttribFlag_UV2 = 1 << VertexArrayAttrib_UV2,
		VertexArrayAttribFlag_UV3 = 1 << VertexArrayAttrib_UV3,
		VertexArrayAttribFlag_UV4 = 1 << VertexArrayAttrib_UV4,
		VertexArrayAttribFlag_UV5 = 1 << VertexArrayAttrib_UV5,
		VertexArrayAttribFlag_UV6 = 1 << VertexArrayAttrib_UV6,
		VertexArrayAttribFlag_UV7 = 1 << VertexArrayAttrib_UV7,
		VertexArrayAttribFlag_UVW = 1 << VertexArrayAttrib_UVW,
	};

	struct VertexArrayRegistry {
	private:
		std::unordered_map<VertexArrayAttrib_, VertexArrayAttribFlag_> VertexArrayAttribFlagMap_ = {
			{ VertexArrayAttrib_POSITION, VertexArrayAttribFlag_POSITION },
			{ VertexArrayAttrib_NORMAL, VertexArrayAttribFlag_NORMAL },
			{ VertexArrayAttrib_COLOR, VertexArrayAttribFlag_COLOR },
			{ VertexArrayAttrib_UV0, VertexArrayAttribFlag_UV0 },
			{ VertexArrayAttrib_UV1, VertexArrayAttribFlag_UV1 },
			{ VertexArrayAttrib_UV2, VertexArrayAttribFlag_UV2 },
			{ VertexArrayAttrib_UV3, VertexArrayAttribFlag_UV3 },
			{ VertexArrayAttrib_UV4, VertexArrayAttribFlag_UV4 },
			{ VertexArrayAttrib_UV5, VertexArrayAttribFlag_UV5 },
			{ VertexArrayAttrib_UV6, VertexArrayAttribFlag_UV6 },
			{ VertexArrayAttrib_UV7, VertexArrayAttribFlag_UV7 },
			{ VertexArrayAttrib_UVW, VertexArrayAttribFlag_UVW },
		};

		std::unordered_map<VertexArrayAttrib_, VertexArrayAttribSize_> VertexArrayAttribSizeMap_= {
			{ VertexArrayAttrib_POSITION, VertexArrayAttribSize_POSITION },
			{ VertexArrayAttrib_NORMAL, VertexArrayAttribSize_NORMAL },
			{ VertexArrayAttrib_COLOR, VertexArrayAttribSize_COLOR },
			{ VertexArrayAttrib_UV0, VertexArrayAttribSize_UV0 },
			{ VertexArrayAttrib_UV1, VertexArrayAttribSize_UV1 },
			{ VertexArrayAttrib_UV2, VertexArrayAttribSize_UV2 },
			{ VertexArrayAttrib_UV3, VertexArrayAttribSize_UV3 },
			{ VertexArrayAttrib_UV4, VertexArrayAttribSize_UV4 },
			{ VertexArrayAttrib_UV5, VertexArrayAttribSize_UV5 },
			{ VertexArrayAttrib_UV6, VertexArrayAttribSize_UV6 },
			{ VertexArrayAttrib_UV7, VertexArrayAttribSize_UV7 },
			{ VertexArrayAttrib_UVW, VertexArrayAttribSize_UVW },
		};
		
	public:
		std::unordered_map<std::size_t, lgl::VertexArray*> bit_layout;
		std::unordered_map<std::size_t, lgl::VertexArray*> custom_layout;

		std::unordered_map<lgl::VertexArray*, std::array<uint32_t, VertexArrayAttrib_COUNT>> offset;
		std::unordered_map<lgl::VertexArray*, std::array<bool, VertexArrayAttrib_COUNT>> is_present;

		VertexArrayRegistry() {}

		template <typename T>
		lgl::VertexArray* SetVertexArray(std::vector<lgl::VertexArrayAttribDescriptor> descriptor) {
			if (custom_layout.find(typeid(T).hash_code()) == custom_layout.end())
				custom_layout[typeid(T).hash_code()] = new lgl::VertexArray(descriptor);

			return custom_layout[typeid(T).hash_code()];
		}

		template <typename T>
		lgl::VertexArray* GetVertexArray() {
			assert(custom_layout.find(typeid(T).hash_code()) != custom_layout.end());

			return custom_layout[typeid(T).hash_code()];
		}

		lgl::VertexArray* GetVertexArray(uint32_t flags);
		
		std::size_t GetOffset(lgl::VertexArray* vertexarray, VertexArrayAttrib_ attrib) {
			assert(attrib < VertexArrayAttrib_COUNT);

			return offset[vertexarray][attrib];
		}
		bool IsAttribPresent(lgl::VertexArray* vertexarray, VertexArrayAttrib_ attrib) {
			assert(attrib < VertexArrayAttrib_COUNT);
			
			return is_present[vertexarray][attrib];
		}

		std::size_t GetOffset(uint32_t flags);
		bool IsAttribPresent(uint32_t flags);
	};
}