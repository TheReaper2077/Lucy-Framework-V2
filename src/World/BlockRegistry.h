// #pragma once

// #include <unordered_map>
// #include <glm/vec3.hpp>

// enum BlockType {
// 	AIR,
// 	TRANSPARENT,
// 	GRASS,
// 	DIRT,
// 	STONE	
// };

// struct BlockRegistry {
// private:
// 	std::unordered_map<uint32_t, glm::vec3> blockid_map;

// public:
// 	BlockRegistry() {
// 		Add(GRASS, glm::vec3(0, 1, 0));
// 		Add(DIRT, glm::vec3(0.6078, 0.4627, 0.3255));
// 		Add(STONE, glm::vec3(0, 0, 1));
// 	}

// 	void Add(uint32_t id, glm::vec3 color) {
// 		blockid_map[id] = color;
// 	}

// 	glm::vec3& Get(uint32_t id) {
// 		return blockid_map[id];
// 	}
// };