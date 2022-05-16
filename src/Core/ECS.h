#pragma once

#include <entt/entt.hpp>
#include <unordered_map>

namespace lf {
	class Registry: public entt::registry {
		std::unordered_map<std::size_t, entt::entity> singleton_instances;
	
	public:
		template <typename T, typename ...Args>
		inline T& store(Args ...params) {
			if (singleton_instances.find(typeid(T).hash_code()) == singleton_instances.end()) {
				singleton_instances[typeid(T).hash_code()] = this->create();
				this->emplace<T>(singleton_instances[typeid(T).hash_code()], params...);
			}

			return this->get<T>(singleton_instances[typeid(T).hash_code()]);
		}
	};
}