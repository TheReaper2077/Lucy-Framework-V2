#include "Components/Components.h"
#include "Functions.h"
#include <uuid.h>
#include "Util/Serializer.h"
#include "Window.h"

bool is_name_present(lf::Registry* registry, std::string name) {
	for (auto entity: registry->view<lf::Component::Tag>()) {
		if (registry->get<lf::Component::Tag>(entity).name == name) {
			return true;
		}
	}

	return false;
}

std::string lf::Functions::GetName(std::string name) {
	std::string result = name;

	for (int i = 1; is_name_present(registry, result); i++) {
		result = name + '(' + std::to_string(i) + ')';
	}

	return result;
}

lf::Entity lf::Functions::CreateEmptyEntity() {
	auto entity = registry->create();
	registry->emplace<lf::Component::Tag>(entity, GetName("Empty"), uuids::to_string(uuids::uuid_system_generator{}()));
	registry->emplace<lf::Component::Transform>(entity);
	if (!runtime_creation) save_entities = true;

	return entity;
}

lf::Entity lf::Functions::CreateCameraEntity() {
	auto entity = registry->create();

	registry->emplace<lf::Component::Tag>(entity, GetName("Camera"), uuids::to_string(uuids::uuid_system_generator{}()));
	registry->emplace<lf::Component::Transform>(entity);
	registry->emplace<lf::Component::Camera>(entity, PERSPECTIVE, false, None);
	if (!runtime_creation) save_entities = true;

	return entity;
}

lf::Entity lf::Functions::CreateSpriteEntity() {
	auto entity = registry->create();

	registry->emplace<lf::Component::Tag>(entity, GetName("Sprite"), uuids::to_string(uuids::uuid_system_generator{}()));
	registry->emplace<lf::Component::Transform>(entity);
	registry->emplace<lf::Component::SpriteRenderer>(entity);
	if (!runtime_creation) save_entities = true;

	return entity;
}

lf::Entity lf::Functions::CreateLightEntity() {
	auto entity = registry->create();

	registry->emplace<lf::Component::Tag>(entity, GetName("Light"), uuids::to_string(uuids::uuid_system_generator{}()));
	registry->emplace<lf::Component::Transform>(entity);
	registry->emplace<lf::Component::Light>(entity);
	if (!runtime_creation) save_entities = true;

	return entity;
}

void lf::Functions::SaveEntities() {
	Util::SerializeEntities(registry, "scene.yaml");
}

void lf::Functions::LoadEntities() {
	Util::DeserializeEntities(registry, "scene.yaml");
}

void lf::Functions::SaveSprites() {
	Util::SerializeSpriteRegistry(registry, "sprites.yaml");
}

void lf::Functions::LoadSprites() {
	Util::DeserializeSpriteRegistry(registry, "sprites.yaml");
}

void lf::Functions::SetMainCamera(Entity camera) {
	registry->store<GameWindow>().camera = camera;
}

lf::Entity lf::Functions::GetMainCamera() {
	return registry->store<GameWindow>().camera;
}
