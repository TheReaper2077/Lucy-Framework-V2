#include "SpriteRegistry.h"
#include <iostream>
#include <uuid.h>

lucy::Component::TextureRaw* lucy::SpriteRegistry::GetTexture(const std::string& filename) {
	return LoadTexture(filename.substr(filename.find_last_of('\\') + 1, filename.find_last_of(".") - 1 - filename.find_last_of('\\')), filename, uuids::to_string(uuids::uuid_system_generator{}()));
}

lucy::Component::TextureRaw* lucy::SpriteRegistry::GetTextureById(const std::string& id) {
	if (texture_store.find(id) == texture_store.end()) {
		return nullptr;
	}

	return texture_store[id];
}

lucy::Component::TextureRaw* lucy::SpriteRegistry::LoadTexture(const std::string& name, const std::string& filename, const std::string& id) {
	texture_store[id] = new lucy::Component::TextureRaw();

	texture_store[id]->name = name;
	texture_store[id]->filename = filename;
	texture_store[id]->id = id;

	texture_store[id]->texture = new lgl::Texture();
	texture_store[id]->texture->LoadFile(filename.c_str());

	return texture_store[id];
}
