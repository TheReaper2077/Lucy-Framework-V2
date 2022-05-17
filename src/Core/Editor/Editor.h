#pragma once

#include <imgui.h>
#include <imgui_internal.h>
#include <imgui_stdlib.h>
#include <imgui_impl_sdl.h>
#include <imgui_impl_opengl3.h>

#include <string>

#include "Panels/Panels.h"

namespace lf {
	class EditorPropeties {
	public:
		uint32_t selected_entity = 0;

		void Init() {

		}
	};
}