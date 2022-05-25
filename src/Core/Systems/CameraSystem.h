#pragma once

#include "../ECS.h"
#include "../Components/Components.h"
#include "../Engine.h"
#include "../Events.h"
#include "../Window.h"

namespace lucy {
	void EditorCamera(Registry& registry);

	void CameraSystem(Registry& registry);
}