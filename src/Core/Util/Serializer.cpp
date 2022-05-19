#include "Serializer.h"
#include "ToYAML.h"
#include "FileIO.h"

bool lf::Util::Serializer(Registry* registry, const std::string& filename) {
	using namespace lf::Component;

	YAML::Emitter out;
	out << YAML::BeginSeq;
	for (auto entity: registry->view<Tag>()) {
		out << YAML::BeginMap;

		auto* tag = registry->try_get<Tag>(entity);
		if (tag != nullptr) {
			out << YAML::Key << "Tag";
			out << YAML::Value << tag;
		}
		auto* transform = registry->try_get<Transform>(entity);
		if (transform != nullptr) {
			out << YAML::Key << "Transform";
			out << YAML::Value << transform;
		}
		auto* camera = registry->try_get<Camera>(entity);
		if (camera != nullptr) {
			out << YAML::Key << "Camera";
			out << YAML::Value << camera;
		}
		auto* light = registry->try_get<Light>(entity);
		if (light != nullptr) {
			out << YAML::Key << "Light";
			out << YAML::Value << light;
		}
		auto* spriterenderer = registry->try_get<SpriteRenderer>(entity);
		if (spriterenderer != nullptr) {
			out << YAML::Key << "SpriteRenderer";
			out << YAML::Value << spriterenderer;
		}
		auto* meshrenderer = registry->try_get<MeshRenderer>(entity);
		if (meshrenderer != nullptr) {
			out << YAML::Key << "MeshRenderer";
			out << YAML::Value << meshrenderer;
		}
		out << YAML::EndMap;
	}
	out << YAML::EndSeq;

	return WriteFile(filename, out.c_str());
}

void lf::Util::Deserializer(Registry* registry, const std::string& source) {
	
}
