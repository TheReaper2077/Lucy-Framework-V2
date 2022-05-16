// #pragma once

// #include <vector>
// #include <glm/vec3.hpp>

// #define CHUNK_SIZE 16
// #define INDEX(x, y, z) (x) + (y) * CHUNK_SIZE + (z) * CHUNK_SIZE * CHUNK_SIZE
// #define INDEX_VEC(pos) (pos.x & (CHUNK_SIZE - 1)) + (pos.y & (CHUNK_SIZE - 1)) * CHUNK_SIZE + (pos.z & (CHUNK_SIZE - 1)) * CHUNK_SIZE * CHUNK_SIZE

// struct Vertex {
// 	glm::u8vec3 position;
// 	glm::vec3 normal;
// 	glm::vec3 color;
// };

// struct Chunk {
// 	glm::ivec3 offset;
// 	uint32_t blocks[CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE];

// 	std::vector<Vertex> vertices;

// 	bool visible = false;
// 	bool meshed = false;

// 	uint32_t Get(const glm::ivec3& pos) {
// 		return blocks[INDEX_VEC(pos)];
// 	}

// 	void Add(const glm::ivec3& pos, uint32_t id) {
// 		blocks[INDEX_VEC(pos)] = id;
// 	}
// };

// void MeshChunk(Chunk* chunk, Chunk* top, Chunk* bottom, Chunk* left, Chunk* right, Chunk* near, Chunk* far);