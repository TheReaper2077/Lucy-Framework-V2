#include "yaml-cpp/yaml.h"
#include "yaml-cpp/emitter.h"
#include "../Components/Components.h"

YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec2& v);
YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec3& v);
YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec4& v);
YAML::Emitter& operator<<(YAML::Emitter& out, const glm::bvec2& v);
YAML::Emitter& operator<<(YAML::Emitter& out, const glm::bvec3& v);
YAML::Emitter& operator<<(YAML::Emitter& out, const glm::bvec4& v);

YAML::Emitter& operator<<(YAML::Emitter& out, const lf::Component::Tag* v);
YAML::Emitter& operator<<(YAML::Emitter& out, const lf::Component::Transform* v);
YAML::Emitter& operator<<(YAML::Emitter& out, const lf::Component::Camera* v);
YAML::Emitter& operator<<(YAML::Emitter& out, const lf::Component::Light* v);
YAML::Emitter& operator<<(YAML::Emitter& out, const lf::Component::SpriteRenderer* v);
YAML::Emitter& operator<<(YAML::Emitter& out, const lf::Component::MeshRenderer* v);

template<> struct YAML::convert<glm::bvec2>;
template<> struct YAML::convert<glm::bvec3>;
template<> struct YAML::convert<glm::bvec4>;
template<> struct YAML::convert<glm::vec2>;
template<> struct YAML::convert<glm::vec3>;
template<> struct YAML::convert<glm::vec4>;

template<> struct YAML::convert<lf::Component::Tag>;
template<> struct YAML::convert<lf::Component::Transform>;
template<> struct YAML::convert<lf::Component::Camera>;
template<> struct YAML::convert<lf::Component::Light>;
template<> struct YAML::convert<lf::Component::SpriteRenderer>;
template<> struct YAML::convert<lf::Component::MeshRenderer>;