#include "Serializer.h"
#include "ToYAML.h"
#include "FileIO.h"
#include <iostream>

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

lf::Entity is_entity_present(const lf::Registry* registry, const std::string& id) {
	for (auto [entity, tag]: registry->view<lf::Component::Tag>().each()) {
		if (tag.id == id) return entity;
	}

	return (lf::Entity)0;
}

template<>
struct YAML::convert<glm::bvec2> {
	static Node encode(const glm::bvec2& rhs) {
		Node node;
		node.push_back(rhs.x);
		node.push_back(rhs.y);
		return node;
	}

	static bool decode(const Node& node, glm::bvec2& rhs) {
		if(!node.IsSequence() || node.size() != 2) {
			return false;
		}

		rhs.x = node[0].as<bool>();
		rhs.y = node[1].as<bool>();

		return true;
	}
};

template<>
struct YAML::convert<glm::bvec3> {
	static Node encode(const glm::bvec3& rhs) {
		Node node;
		node.push_back(rhs.x);
		node.push_back(rhs.y);
		node.push_back(rhs.z);
		return node;
	}

	static bool decode(const Node& node, glm::bvec3& rhs) {
		if(!node.IsSequence() || node.size() != 3) {
			return false;
		}

		rhs.x = node[0].as<bool>();
		rhs.y = node[1].as<bool>();
		rhs.z = node[2].as<bool>();

		return true;
	}
};

template<>
struct YAML::convert<glm::bvec4> {
	static Node encode(const glm::bvec4& rhs) {
		Node node;
		node.push_back(rhs.x);
		node.push_back(rhs.y);
		node.push_back(rhs.z);
		node.push_back(rhs.w);
		return node;
	}

	static bool decode(const Node& node, glm::bvec4& rhs) {
		if(!node.IsSequence() || node.size() != 4) {
			return false;
		}

		rhs.x = node[0].as<bool>();
		rhs.y = node[1].as<bool>();
		rhs.z = node[2].as<bool>();
		rhs.w = node[4].as<bool>();

		return true;
	}
};

template<>
struct YAML::convert<glm::vec2> {
	static Node encode(const glm::vec2& rhs) {
		Node node;
		node.push_back(rhs.x);
		node.push_back(rhs.y);
		return node;
	}

	static bool decode(const Node& node, glm::vec2& rhs) {
		if(!node.IsSequence() || node.size() != 2) {
			return false;
		}

		rhs.x = node[0].as<float>();
		rhs.y = node[1].as<float>();

		return true;
	}
};

template<>
struct YAML::convert<glm::vec3> {
	static Node encode(const glm::vec3& rhs) {
		Node node;
		node.push_back(rhs.x);
		node.push_back(rhs.y);
		node.push_back(rhs.z);
		return node;
	}

	static bool decode(const Node& node, glm::vec3& rhs) {
		if(!node.IsSequence() || node.size() != 3) {
			return false;
		}

		rhs.x = node[0].as<float>();
		rhs.y = node[1].as<float>();
		rhs.z = node[2].as<float>();

		return true;
	}
};

template<>
struct YAML::convert<glm::vec4> {
	static Node encode(const glm::vec4& rhs) {
		Node node;
		node.push_back(rhs.x);
		node.push_back(rhs.y);
		node.push_back(rhs.z);
		node.push_back(rhs.w);
		return node;
	}

	static bool decode(const Node& node, glm::vec4& rhs) {
		if(!node.IsSequence() || node.size() != 4) {
			return false;
		}

		rhs.x = node[0].as<float>();
		rhs.y = node[1].as<float>();
		rhs.z = node[2].as<float>();
		rhs.w = node[3].as<float>();

		return true;
	}
};

template<>
struct YAML::convert<lf::Component::Tag> {
	static Node encode(const lf::Component::Tag& rhs) {
		Node node;
		node["name"] = rhs.name;
		node["id"] = rhs.id;
		return node;
	}

	static bool decode(const Node& node, lf::Component::Tag& rhs) {
		if (!node.IsMap()) {
			return false;
		}
		
		rhs.id = node["id"].as<std::string>();
		rhs.name = node["name"].as<std::string>();

		return true;
	}
};

template<>
struct YAML::convert<lf::Component::Transform> {
	static Node encode(const lf::Component::Transform& rhs) {
		Node node;
		node["translation"] = rhs.translation;
		node["rotation"] = rhs.rotation;
		node["scale"] = rhs.scale;
		return node;
	}

	static bool decode(const Node& node, lf::Component::Transform& rhs) {
		if (!node.IsMap()) {
			return false;
		}

		rhs.translation = node["translation"].as<glm::vec3>();
		rhs.rotation = node["rotation"].as<glm::vec3>();
		rhs.scale = node["scale"].as<glm::vec3>();

		return true;
	}
};

template<>
struct YAML::convert<lf::Component::Camera> {
	static Node encode(const lf::Component::Camera& rhs) {
		Node node;
		node["Up"] = rhs.Up;
		node["Front"] = rhs.Front;
		node["Right"] = rhs.Right;
		node["WorldUp"] = rhs.WorldUp;
		node["WorldFront"] = rhs.WorldFront;
		node["Projection"] = (uint32_t)rhs.mode;
		node["CameraType"] = (uint32_t)rhs.type;
		return node;
	}

	static bool decode(const Node& node, lf::Component::Camera& rhs) {
		if (!node.IsMap()) {
			return false;
		}

		rhs.Up = node["Up"].as<glm::vec3>();
		rhs.Front = node["Front"].as<glm::vec3>();
		rhs.Right = node["Right"].as<glm::vec3>();
		rhs.WorldUp = node["WorldUp"].as<glm::vec3>();
		rhs.WorldFront = node["WorldFront"].as<glm::vec3>();
		rhs.mode = (lf::Projection)node["Projection"].as<uint32_t>();
		rhs.type = (lf::CameraType)node["CameraType"].as<uint32_t>();

		return true;
	}
};

template<>
struct YAML::convert<lf::Component::Light> {
	static Node encode(const lf::Component::Light& rhs) {
		Node node;
		node["active"] = rhs.active;
		node["color"] = rhs.color;
		node["mode"] = (uint32_t)rhs.mode;
		return node;
	}

	static bool decode(const Node& node, lf::Component::Light& rhs) {
		if (!node.IsMap()) {
			return false;
		}

		rhs.active = node["active"].as<bool>();
		rhs.color = node["color"].as<glm::vec4>();
		rhs.mode = (lf::LightMode)node["mode"].as<uint32_t>();

		return true;
	}
};

template<>
struct YAML::convert<lf::Component::SpriteRenderer> {
	static Node encode(const lf::Component::SpriteRenderer& rhs) {
		Node node;
		node["visible"] = rhs.visible;
		node["color"] = rhs.color;
		node["material_id"] = rhs.material_id;
		node["uv0"] = rhs.uv0;
		node["uv1"] = rhs.uv1;
		node["custom_flags"] = rhs.custom_flags;
		return node;
	}

	static bool decode(const Node& node, lf::Component::SpriteRenderer& rhs) {
		if (!node.IsMap()) {
			return false;
		}

		rhs.visible = node["visible"].as<bool>();
		rhs.color = node["color"].as<glm::vec4>();
		rhs.material_id = node["material_id"].as<std::string>();
		rhs.uv0 = node["uv0"].as<glm::vec2>();
		rhs.uv1 = node["uv1"].as<glm::vec2>();
		rhs.custom_flags = node["custom_flags"].as<uint32_t>();

		return true;
	}
};

template<>
struct YAML::convert<lf::Component::MeshRenderer> {
	static Node encode(const lf::Component::MeshRenderer& rhs) {
		Node node;
		node["visible"] = rhs.visible;
		node["material_id"] = rhs.material_id;
		node["custom_flags"] = rhs.custom_flags;
		return node;
	}

	static bool decode(const Node& node, lf::Component::MeshRenderer& rhs) {
		if (!node.IsMap()) {
			return false;
		}

		rhs.visible = node["visible"].as<bool>();
		rhs.material_id = node["material_id"].as<std::string>();
		// rhs.custom_flags = node["custom_flags"].as<uint32_t>();

		return true;
	}
};

void lf::Util::Deserializer(Registry* registry, const std::string& filename) {
	using namespace lf::Component;

	std::string src = ReadFile(filename);

	if (src == "") return;

	YAML::Node scene = YAML::LoadFile(filename);

	for (std::size_t i = 0; i < scene.size(); i++) {
		Entity entity;

		if (scene[i]["Tag"]) {
			auto tag = scene[i]["Tag"].as<Tag>();

			entity = is_entity_present(registry, tag.id);
			
			if (entity == (Entity)0)
				entity = registry->create();

			registry->emplace<Tag>(entity, tag);
		} else continue;

		if (scene[i]["Transform"]) {
			registry->emplace<Transform>(entity, scene[i]["Transform"].as<Transform>());
		}
		if (scene[i]["Camera"]) {
			registry->emplace<Camera>(entity, scene[i]["Camera"].as<Camera>());
		}
		if (scene[i]["Light"]) {
			registry->emplace<Light>(entity, scene[i]["Light"].as<Light>());
		}
		if (scene[i]["SpriteRenderer"]) {
			registry->emplace<SpriteRenderer>(entity, scene[i]["SpriteRenderer"].as<SpriteRenderer>());
		}
		if (scene[i]["MeshRenderer"]) {
			registry->emplace<MeshRenderer>(entity, scene[i]["MeshRenderer"].as<MeshRenderer>());
		}
	}
}
