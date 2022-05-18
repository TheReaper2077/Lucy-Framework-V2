#pragma once

#include <imgui.h>
#include <imgui_internal.h>
#include <imgui_stdlib.h>
#include <imgui_impl_sdl.h>
#include <imgui_impl_opengl3.h>

#include <string>

#include "../ECS.h"

void PopupOpenLogic(lf::Registry& registry, bool& open, bool& toggle);

namespace lf {
	class EditorPropeties {
	public:
		Entity selected_entity;
	};
}