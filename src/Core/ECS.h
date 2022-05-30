#pragma once

#include <entt/entt.hpp>
#include <unordered_map>

namespace lucy {
	typedef entt::entity Entity;

	class Registry: public entt::registry {
		std::unordered_map<size_t, Entity> singleton_instances;
	
	public:
		template <typename T, typename ...Args>
		inline T& store(Args ...params) {
			if (singleton_instances.find(typeid(T).hash_code()) == singleton_instances.end()) {
				singleton_instances[typeid(T).hash_code()] = create();
				emplace<T>(singleton_instances[typeid(T).hash_code()], params...);
			}

			return get<T>(singleton_instances[typeid(T).hash_code()]);
		}

		// template <typename T>
		// inline void destroy() {
		// 	assert(singleton_instances.find(typeid(T).hash_code()) == singleton_instances.end());

		// 	this->destroy(singleton_instances[typeid(T).hash_code()]);
		// 	singleton_instances.erase(typeid(T).hash_code());
		// }
	};
}