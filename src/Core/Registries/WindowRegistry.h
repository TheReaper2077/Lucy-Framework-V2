#pragma once

#include <unordered_map>
#include "../Window.h"
#include "../Enumerations.h"

namespace lucy {
	struct WindowRegistry {
		std::unordered_map<std::uint32_t, Window> window_registry;

		void Create(uint32_t key, Window window) {
			
		}

		Window& Get(std::uint32_t key) {
			return window_registry[key];
		}
	};
}