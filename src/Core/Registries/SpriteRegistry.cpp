#include "SpriteRegistry.h"
#include <uuid.h>

lucy::Component::TextureRaw* lucy::SpriteRegistry::GetTexture(const std::string& filename) {
	if (texture_store.find(filename) == texture_store.end()) {
		texture_store[filename] = new lucy::Component::TextureRaw();

		texture_store[filename]->filename = filename;
		texture_store[filename]->id = uuids::to_string(uuids::uuid_system_generator{}());
		texture_store[filename]->name = filename.substr(filename.find_last_of('\\') + 1, filename.find_last_of(".") - 1 - filename.find_last_of('\\'));
		texture_store[filename]->texture = new lgl::Texture();
		texture_store[filename]->texture->LoadFile(filename.c_str());
	}

	return texture_store[filename];
}

// lucy::Component::Sprite& lucy::SpriteRegistry::GetSprite(const std::string& filename) {
// 	lucy::Component::Sprite sprite;

// 	if (sprite_store.find(filename) == sprite_store.end()) {
// 		sprite.texture = GetTexture(filename);
// 		sprite.id = uuids::to_string(uuids::uuid_system_generator{}());

// 		sprite_store[filename] = sprite;
// 	}

// 	return sprite_store[filename];
// }

