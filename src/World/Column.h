// #pragma once

// #include "Chunk.h"
// #include <unordered_map>
// #include <memory>

// class Column {
// public:
// 	std::unordered_map<int32_t, std::shared_ptr<Chunk>> chunk_map;
// 	glm::ivec3 offset;

// 	Chunk* Get(const glm::ivec3& pos) {
// 		if (chunk_map.find(pos.y) == chunk_map.end()) {
// 			auto chunk = std::shared_ptr<Chunk>();
// 			chunk->offset = pos & ~(CHUNK_SIZE - 1);
// 			chunk_map[pos.y] = chunk;
// 		}

// 		return chunk_map[pos.y].get();
// 	}

// 	Chunk* GetAvailable(const glm::ivec3& pos) {
// 		if (chunk_map.find(pos.y) == chunk_map.end()) {
// 			return nullptr;
// 		}

// 		return chunk_map[pos.y].get();
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