// #pragma once

// #include "Column.h"

// class World {
// 	std::unordered_map<glm::ivec2, std::shared_ptr<Column>> column_map;

// public:
// 	Chunk* Get(const glm::ivec3& pos) {
// 		auto id = glm::ivec2(pos.x & ~(CHUNK_SIZE - 1), pos.z & ~(CHUNK_SIZE - 1));

// 		if (column_map.find(id) == column_map.end()) {
// 			auto column = std::shared_ptr<Column>();
// 			column->offset = glm::ivec3(id.x, 0, id.y);
// 			column_map[id] = column;
// 		}

// 		return column_map[id]->Get(pos);
// 	}

// 	Chunk* GetAvailable(const glm::ivec3& pos) {
// 		auto id = glm::ivec2(pos.x & ~(CHUNK_SIZE - 1), pos.z & ~(CHUNK_SIZE - 1))

// 		if (column_map.find(id) == column_map.end()) {
// 			return nullptr;
// 		}

// 		return column_map[id]->GetAvailable(pos);
// 	}

// 	void Add(const glm::ivec3& pos, uint32_t id) {
// 		Get(pos)->Add(pos, id);
// 	}

// 	void AddAvailable(const glm::ivec3& pos, uint32_t id) {
// 		auto* chunk = GetAvailable(pos);

// 		if (chunk != nullptr) {
// 			chunk->Add(pos, id);
// 		}
// 	}
// };
