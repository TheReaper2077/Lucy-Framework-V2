#pragma once

#include "Types.h"

namespace lfal {
	enum DrawMode {
		NONE,
		INDIRECT,
		INSTANCED,
		INSTANCED_BASEINSTANCE,
		
		INDEXED,
		INDEXED_INDIRECT,
		INDEXED_INSTANCED,
		INDEXED_BASEVERTEX,
		INDEXED_INSTANCED_BASEINSTANCE,
		INDEXED_INSTANCED_BASEVERTEX,
		INDEXED_INSTANCED_BASEVERTEX_BASEINSTANCE,

		RANGE_INDEXED,
		RANGE_INDEXED_BASEVERTEX,

		PIXELS,

		COUNT
	};

	int& Draw(Primitive mode, int first, int count);
	int& DrawIndexed(Primitive mode, int count, Type type, void* indices);

	int& DrawCmd(DrawMode drawmode, Primitive mode, Type type, Format format, int first, int start, int end, int count, int basevertex, int baseinstance, int instancecount, int width, int height, void* indices, void* indirect, void* pixels);
}