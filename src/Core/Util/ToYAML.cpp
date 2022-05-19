#include "ToYAML.h"

YAML::Emitter& operator<<(YAML::Emitter& out, const glm::bvec2& v) {
	out << YAML::Flow;
	out << YAML::BeginSeq << v.x << v.y << YAML::EndSeq;
	return out;
}

YAML::Emitter& operator<<(YAML::Emitter& out, const glm::bvec3& v) {
	out << YAML::Flow;
	out << YAML::BeginSeq << v.x << v.y << v.z << YAML::EndSeq;
	return out;
}

YAML::Emitter& operator<<(YAML::Emitter& out, const glm::bvec4& v) {
	out << YAML::Flow;
	out << YAML::BeginSeq << v.x << v.y << v.z << v.w << YAML::EndSeq;
	return out;
}

YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec2& v) {
	out << YAML::Flow;
	out << YAML::BeginSeq << v.x << v.y << YAML::EndSeq;
	return out;
}

YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec3& v) {
	out << YAML::Flow;
	out << YAML::BeginSeq << v.x << v.y << v.z << YAML::EndSeq;
	return out;
}

YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec4& v) {
	out << YAML::Flow;
	out << YAML::BeginSeq << v.x << v.y << v.z << v.w << YAML::EndSeq;
	return out;
}

YAML::Emitter& operator<<(YAML::Emitter& out, const lf::Component::Tag* v) {
	out << YAML::BeginMap;
	out << YAML::Key << "name";
	out << YAML::Value << v->name;
	out << YAML::Key << "id";
	out << YAML::Value << v->id;
	out << YAML::EndMap;
	return out;
}

YAML::Emitter& operator<<(YAML::Emitter& out, const lf::Component::Transform* v) {
	out << YAML::BeginMap;
	out << YAML::Key << "translation";
	out << YAML::Value << v->translation;
	out << YAML::Key << "rotation";
	out << YAML::Value << v->rotation;
	out << YAML::Key << "scale";
	out << YAML::Value << v->scale;
	out << YAML::EndMap;
	return out;
}

YAML::Emitter& operator<<(YAML::Emitter& out, const lf::Component::Camera* v) {
	out << YAML::BeginMap;
	out << YAML::Key << "Up";
	out << YAML::Value << v->Up;
	out << YAML::Key << "Front";
	out << YAML::Value << v->Front;
	out << YAML::Key << "Right";
	out << YAML::Value << v->Right;
	out << YAML::Key << "WorldUp";
	out << YAML::Value << v->WorldUp;
	out << YAML::Key << "WorldFront";
	out << YAML::Value << v->WorldFront;
	out << YAML::Key << "Projection";
	out << YAML::Value << v->mode;
	out << YAML::Key << "CameraType";
	out << YAML::Value << v->mode;
	out << YAML::EndMap;
	return out;
}

YAML::Emitter& operator<<(YAML::Emitter& out, const lf::Component::Light* v) {
	out << YAML::BeginMap;
	out << YAML::Key << "active";
	out << YAML::Value << v->active;
	out << YAML::Key << "color";
	out << YAML::Value << v->color;
	out << YAML::Key << "mode";
	out << YAML::Value << v->mode;
	out << YAML::EndMap;
	return out;
}

YAML::Emitter& operator<<(YAML::Emitter& out, const lf::Component::SpriteRenderer* v) {
	out << YAML::BeginMap;
	out << YAML::Key << "visible";
	out << YAML::Value << v->visible;
	out << YAML::Key << "color";
	out << YAML::Value << v->color;
	out << YAML::Key << "material_id";
	out << YAML::Value << v->material_id;
	out << YAML::Key << "uv0";
	out << YAML::Value << v->uv0;
	out << YAML::Key << "uv1";
	out << YAML::Value << v->uv1;
	out << YAML::Key << "custom_flags";
	out << YAML::Value << v->custom_flags;
	out << YAML::EndMap;
	return out;
}

YAML::Emitter& operator<<(YAML::Emitter& out, const lf::Component::MeshRenderer* v) {
	out << YAML::BeginMap;
	out << YAML::Key << "visible";
	out << YAML::Value << v->visible;
	out << YAML::Key << "material_id";
	out << YAML::Value << v->material_id;
	out << YAML::Key << "custom_flags";
	out << YAML::Value << v->custom_flags;
	out << YAML::EndMap;
	return out;
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
		rhs.id = node["name"].as<std::string>();
		rhs.name = node["id"].as<std::string>();

		return true;
	}
};