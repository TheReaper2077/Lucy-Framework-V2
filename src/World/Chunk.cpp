// #include "Chunk.h"
// #include "BlockRegistry.h"

// #include <glm/glm.hpp>

// template <typename T>
// void rect_FAR(std::vector<T> &vertices, const uint8_t& x, const uint8_t& y, const uint8_t& z, const uint8_t& w, const uint8_t& h, const uint8_t& d, const glm::u8vec3& color) {
// 	vertices.reserve(4 + vertices.size());

// 	auto A = glm::u8vec3(x + w, y + h, z + d);
// 	auto B = glm::u8vec3(x + w, y, z + d);
// 	auto C = glm::u8vec3(x, y, z + d);
// 	glm::vec3 normal = (B - A).cross(C - A).normalize();

// 	vertices.emplace_back(T{ A, normal, color});
// 	vertices.emplace_back(T{ B, normal, color});
// 	vertices.emplace_back(T{ C, normal, color});
// 	vertices.emplace_back(T{ glm::u8vec3(x, y + h, z + d), normal, color});
// };

// template <typename T>
// void rect_NEAR(std::vector<T> &vertices, const uint8_t& x, const uint8_t& y, const uint8_t& z, const uint8_t& w, const uint8_t& h, const uint8_t& d, const glm::u8vec3& color) {
// 	vertices.reserve(4 + vertices.size());

// 	auto A = glm::u8vec3(x + w, y + h, z);
// 	auto B = glm::u8vec3(x + w, y, z);
// 	auto C = glm::u8vec3(x, y, z);
// 	glm::vec3 normal = (B - A).cross(C - A).normalize();

// 	vertices.emplace_back(T{ A, normal, color});
// 	vertices.emplace_back(T{ B, normal, color});
// 	vertices.emplace_back(T{ C, normal, color});
// 	vertices.emplace_back(T{ glm::u8vec3(x, y + h, z), normal, color});
// };
	
// template <typename T>
// void rect_TOP(std::vector<T> &vertices, const uint8_t& x, const uint8_t& y, const uint8_t& z, const uint8_t& w, const uint8_t& h, const uint8_t& d, const glm::u8vec3& color) {
// 	vertices.reserve(4 + vertices.size());

// 	auto A = glm::u8vec3(x + w, y + h, z + d);
// 	auto B = glm::u8vec3(x + w, y + h, z);
// 	auto C = glm::u8vec3(x, y + h, z);
// 	glm::vec3 normal = (B - A).cross(C - A).normalize();

// 	vertices.emplace_back(T{ A, normal, color});
// 	vertices.emplace_back(T{ B, normal, color});
// 	vertices.emplace_back(T{ C, normal, color});
// 	vertices.emplace_back(T{ glm::u8vec3(x, y + h, z + d), normal, color});
// };
	
// template <typename T>
// void rect_BOTTOM(std::vector<T> &vertices, const uint8_t& x, const uint8_t& y, const uint8_t& z, const uint8_t& w, const uint8_t& h, const uint8_t& d, const glm::u8vec3& color) {
// 	vertices.reserve(4 + vertices.size());

// 	auto A = glm::u8vec3(x + w, y, z + d);
// 	auto B = glm::u8vec3(x + w, y, z);
// 	auto C = glm::u8vec3(x, y, z);
// 	glm::vec3 normal = (B - A).cross(C - A).normalize();

// 	vertices.emplace_back(T{ A, normal, color});
// 	vertices.emplace_back(T{ B, normal, color});
// 	vertices.emplace_back(T{ C, normal, color});
// 	vertices.emplace_back(T{ glm::u8vec3(x, y, z + d), normal, color});
// };

// template <typename T>
// void rect_LEFT(std::vector<T> &vertices, const uint8_t& x, const uint8_t& y, const uint8_t& z, const uint8_t& w, const uint8_t& h, const uint8_t& d, const glm::u8vec3& color) {
// 	vertices.reserve(4 + vertices.size());

// 	auto A = glm::u8vec3(x, y + h, z + d);
// 	auto B = glm::u8vec3(x, y, z + d);
// 	auto C = glm::u8vec3(x, y, z);
// 	glm::vec3 normal = (B - A).cross(C - A).normalize();

// 	vertices.emplace_back(T{ A, normal, color});
// 	vertices.emplace_back(T{ B, normal, color});
// 	vertices.emplace_back(T{ C, normal, color});
// 	vertices.emplace_back(T{ glm::u8vec3(x, y + h, z), normal, color});
// };
	
// template <typename T>
// void rect_RIGHT(std::vector<T> &vertices, const uint8_t& x, const uint8_t& y, const uint8_t& z, const uint8_t& w, const uint8_t& h, const uint8_t& d, const glm::u8vec3& color) {
// 	vertices.reserve(4 + vertices.size());

// 	auto A = glm::u8vec3(x + w, y + h, z + d);
// 	auto B = glm::u8vec3(x + w, y, z + d);
// 	auto C = glm::u8vec3(x + w, y, z);
// 	glm::vec3 normal = (B - A).cross(C - A).normalize();

// 	vertices.emplace_back(T{ A, normal, color});
// 	vertices.emplace_back(T{ B, normal, color});
// 	vertices.emplace_back(T{ C, normal, color});
// 	vertices.emplace_back(T{ glm::u8vec3(x + w, y + h, z), normal, color});
// };

// void MeshChunk(Chunk* chunk, Chunk* top, Chunk* bottom, Chunk* left, Chunk* right, Chunk* near, Chunk* far) {
// 	if (chunk->meshed) return;
// 	chunk->meshed = true;

// 	auto* block_registry = BlockRegistry::SharedInstance();
	
// 	for (uint8_t z = 0; z < CHUNK_SIZE; z++) {
// 		for (uint8_t y = 0; y < CHUNK_SIZE; y++) {
// 			for (uint8_t x = 0; x < CHUNK_SIZE; x++) {
// 				auto& id = chunk->blocks[INDEX(x, y, z)];
// 				auto& block = block_registry->GetBlock(id);

// 				if (block.type == AIR || block.type == TRANSPARENT)
// 					continue;
				
// 				glm::vec3 color = block.color;

// 				if (z + 1 < CHUNK_SIZE) {//
// 					int a = INDEX(x, y, z + 1);//
// 					if (block_registry->GetBlock(chunk->blocks[INDEX(x, y, z + 1)]).type == AIR)//
// 						rect_FAR(chunk->vertices, chunk->offset.x + x, chunk->offset.y + y, chunk->offset.z + z, 1, 1, 1, color);//block.far);
// 				} else if (far != nullptr) {//
// 					if (block_registry->GetBlock(far->blocks[INDEX(x, y, 0)]).type == AIR)//
// 						rect_FAR(chunk->vertices, chunk->offset.x + x, chunk->offset.y + y, chunk->offset.z + z, 1, 1, 1, color);//block.far);//
// 				} else {//
// 					rect_FAR(chunk->vertices, chunk->offset.x + x, chunk->offset.y + y, chunk->offset.z + z, 1, 1, 1, color);//block.far);//
// 				}

// 				if (z - 1 >= 0) {//
// 					int a = INDEX(x, y, z - 1);
// 					if (block_registry->GetBlock(chunk->blocks[INDEX(x, y, z - 1)]).type == AIR) {//
// 						rect_NEAR(chunk->vertices, chunk->offset.x + x, chunk->offset.y + y, chunk->offset.z + z, 1, 1, 1, color);//block.near);
// 					}//
// 				} else if (near != nullptr) {//
// 					if (block_registry->GetBlock(near->blocks[INDEX(x, y, CHUNK_SIZE - 1)]).type == AIR)//
// 						rect_NEAR(chunk->vertices, chunk->offset.x + x, chunk->offset.y + y, chunk->offset.z + z, 1, 1, 1, color);//block.near);//
// 				} else {//
// 					rect_NEAR(chunk->vertices, chunk->offset.x + x, chunk->offset.y + y, chunk->offset.z + z, 1, 1, 1, color);//block.near);//
// 				}

// 				if (y + 1 < CHUNK_SIZE) {//
// 					if (block_registry->GetBlock(chunk->blocks[INDEX(x, y + 1, z)]).type == AIR) {//
// 						rect_TOP(chunk->vertices, chunk->offset.x + x, chunk->offset.y + y, chunk->offset.z + z, 1, 1, 1, color);//block.top);
// 					}//
// 				} else if (top != nullptr) {//
// 					if (block_registry->GetBlock(top->blocks[INDEX(x, 0, z)]).type == AIR)//
// 						rect_TOP(chunk->vertices, chunk->offset.x + x, chunk->offset.y + y, chunk->offset.z + z, 1, 1, 1, color);//block.top);//
// 				} else {//
// 					rect_TOP(chunk->vertices, chunk->offset.x + x, chunk->offset.y + y, chunk->offset.z + z, 1, 1, 1, color);//block.top);//
// 				}

// 				if (y - 1 >= 0) {//
// 					if (block_registry->GetBlock(chunk->blocks[INDEX(x, y - 1, z)]).type == AIR) {//
// 						rect_BOTTOM(chunk->vertices, chunk->offset.x + x, chunk->offset.y + y, chunk->offset.z + z, 1, 1, 1, color);//block.bottom);
// 					}//
// 				} else if (bottom != nullptr) {//
// 					if (block_registry->GetBlock(bottom->blocks[INDEX(x, CHUNK_SIZE - 1, z)]).type == AIR)//
// 						rect_BOTTOM(chunk->vertices, chunk->offset.x + x, chunk->offset.y + y, chunk->offset.z + z, 1, 1, 1, color);//block.bottom);//
// 				} else {//
// 					rect_BOTTOM(chunk->vertices, chunk->offset.x + x, chunk->offset.y + y, chunk->offset.z + z, 1, 1, 1, color);//block.bottom);//
// 				}

// 				if (x + 1 < CHUNK_SIZE) {//
// 					if (block_registry->GetBlock(chunk->blocks[INDEX(x + 1, y, z)]).type == AIR) {//
// 						rect_RIGHT(chunk->vertices, chunk->offset.x + x, chunk->offset.y + y, chunk->offset.z + z, 1, 1, 1, color);//block.right);
// 					}//
// 				} else if (right != nullptr) {//
// 					if (block_registry->GetBlock(right->blocks[INDEX(0, y, z)]).type == AIR)//
// 						rect_RIGHT(chunk->vertices, chunk->offset.x + x, chunk->offset.y + y, chunk->offset.z + z, 1, 1, 1, color);//block.right);//
// 				} else {//
// 					rect_RIGHT(chunk->vertices, chunk->offset.x + x, chunk->offset.y + y, chunk->offset.z + z, 1, 1, 1, color);//block.right);//
// 				}

// 				if (x - 1 >= 0) {//
// 					if (block_registry->GetBlock(chunk->blocks[INDEX(x - 1, y, z)]).type == AIR) {//
// 						rect_LEFT(chunk->vertices, chunk->offset.x + x, chunk->offset.y + y, chunk->offset.z + z, 1, 1, 1, color);//block.left);
// 					}//
// 				} else if (left != nullptr) {//
// 					if (block_registry->GetBlock(left->blocks[INDEX(CHUNK_SIZE - 1, y, z)]).type == AIR)//
// 						rect_LEFT(chunk->vertices, chunk->offset.x + x, chunk->offset.y + y, chunk->offset.z + z, 1, 1, 1, color);//block.left);//
// 				} else {//
// 					rect_LEFT(chunk->vertices, chunk->offset.x + x, chunk->offset.y + y, chunk->offset.z + z, 1, 1, 1, color);//block.left);//
// 				}
// 			}
// 		}
// 	}
// }
