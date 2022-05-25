#include "Components/Components.h"
#include "Functions.h"
#include <uuid.h>
#include "Util/Serializer.h"
#include "Window.h"

bool is_name_present(lucy::Registry* registry, std::string name) {
	for (auto entity: registry->view<lucy::Component::Tag>()) {
		if (registry->get<lucy::Component::Tag>(entity).name == name) {
			return true;
		}
	}

	return false;
}

std::string lucy::Functions::GetName(std::string name) {
	std::string result = name;

	for (int i = 1; is_name_present(registry, result); i++) {
		result = name + '(' + std::to_string(i) + ')';
	}

	return result;
}

lucy::Entity lucy::Functions::CreateEmptyEntity() {
	auto entity = registry->create();
	registry->emplace<lucy::Component::Tag>(entity, GetName("Empty"), uuids::to_string(uuids::uuid_system_generator{}()));
	registry->emplace<lucy::Component::Transform>(entity);
	if (!runtime_creation) save_entities = true;

	return entity;
}

lucy::Entity lucy::Functions::CreateCameraEntity() {
	auto entity = registry->create();

	registry->emplace<lucy::Component::Tag>(entity, GetName("Camera"), uuids::to_string(uuids::uuid_system_generator{}()));
	registry->emplace<lucy::Component::Transform>(entity);
	registry->emplace<lucy::Component::Camera>(entity, PERSPECTIVE, false, None);
	if (!runtime_creation) save_entities = true;

	return entity;
}

lucy::Entity lucy::Functions::CreateSpriteEntity() {
	auto entity = registry->create();

	registry->emplace<lucy::Component::Tag>(entity, GetName("Sprite"), uuids::to_string(uuids::uuid_system_generator{}()));
	registry->emplace<lucy::Component::Transform>(entity);
	registry->emplace<lucy::Component::SpriteRenderer>(entity);
	if (!runtime_creation) save_entities = true;

	return entity;
}

lucy::Entity lucy::Functions::CreateLightEntity() {
	auto entity = registry->create();

	registry->emplace<lucy::Component::Tag>(entity, GetName("Light"), uuids::to_string(uuids::uuid_system_generator{}()));
	registry->emplace<lucy::Component::Transform>(entity);
	registry->emplace<lucy::Component::Light>(entity);
	if (!runtime_creation) save_entities = true;

	return entity;
}

void lucy::Functions::SaveEntities() {
	Util::SerializeEntities(registry, "scene.yaml");
}

void lucy::Functions::LoadEntities() {
	Util::DeserializeEntities(registry, "scene.yaml");
}

void lucy::Functions::SaveSprites() {
	Util::SerializeSpriteRegistry(registry, "sprites.yaml");
}

void lucy::Functions::LoadSprites() {
	Util::DeserializeSpriteRegistry(registry, "sprites.yaml");
}

void lucy::Functions::SetMainCamera(Entity camera) {
	registry->store<GameWindow>().camera = camera;
}

lucy::Entity lucy::Functions::GetMainCamera() {
	return registry->store<GameWindow>().camera;
}
