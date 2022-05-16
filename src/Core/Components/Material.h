#pragma once

#include <string>
#include <glm/vec3.hpp>

namespace lf {
	namespace Component {
		struct Material {
			std::string id;

			glm::vec3 albedo;
			glm::vec3 diffuse;
			glm::vec3 ambient;
			glm::vec3 specular;

			float roughness;
			float metallic;

			Texture albedo_map;
			Texture diffuse_map;
			Texture ambient_map;
			Texture specular_map;
			Texture emission_map;
			Texture roughness_map;
			Texture metallic_map;
			Texture normal_map;

			int illum_model;
		};
	}
}