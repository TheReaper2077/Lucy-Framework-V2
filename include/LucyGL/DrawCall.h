#pragma once

#include "Types.h"

namespace lgl {
	bool Draw(Primitive mode, int first, int count);
	bool DrawIndexed(Primitive mode, int count, Type type, void* indices);
}