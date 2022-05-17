#pragma once

#include <glm/glm.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/geometric.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_cross_product.hpp>
#include "../Enumerations.h"

namespace lf {
	namespace Component {
		struct Camera {
			glm::mat4 projection = glm::mat4(1.0);
			glm::mat4 view = glm::mat4(1.0);

			glm::vec3 Up;
			glm::vec3 Right;
			glm::vec3 Position = glm::vec3(0, 0, 0);
			glm::vec3 Front = glm::vec3(0.0f, 0.0f, -1.0f);
			glm::vec3 WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);
			glm::vec3 WorldFront = glm::vec3(0.0f, 0.0f, -1.0f);
			glm::vec3 Center = glm::vec3(0, 0, 0);
			glm::vec3 Offset = glm::vec3(0, 0, 0);

			Projection mode = PERSPECTIVE;
			CameraType type = FPS;

			bool enable = false;

			bool first_mouse = true;
			float speed = 0;
			float scrollspeed = 0;
			float lastX, lastY;
			float sensitivity = 0.1f;

			int initx, inity;

			float width = 0;
			float height = 0;
			float fov = 45.0;
			float camera_near = 0.001f;
			float camera_far = 1000.0f;

			bool changed = true;
			bool init = false;

			glm::vec4 clear_color = glm::vec4(0, 0, 0, 0);

			Camera() {}
			Camera(Projection mode, bool enable = false, CameraType type = Default) {
				this->enable = enable;
				this->mode = mode;
				this->type = type;
				this->speed = 0.256f;
				this->scrollspeed = 0.750f;
				this->sensitivity = 0.5f;
			}
		};
	}
}