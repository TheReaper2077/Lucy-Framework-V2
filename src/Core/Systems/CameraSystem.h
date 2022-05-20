#pragma once

#include "../ECS.h"
#include "../Components/Components.h"
#include "../Engine.h"
#include "../Events.h"
#include "../Window.h"

namespace lf {
	void EditorCamera(Registry& registry) {
		using namespace lf::Component;

		auto& engine = registry.store<Engine>();
		auto& editorwindow = registry.store<EditorWindow>();

		auto& eventhandler = registry.store<Events>();

		auto normalized_pos = eventhandler.GetMousePos(editorwindow, true);

		if ((uint32_t)editorwindow.camera == 0) {
			editorwindow.camera = registry.create();
			registry.emplace<Transform>(editorwindow.camera);
			registry.emplace<Camera>(editorwindow.camera, lf::PERSPECTIVE, true, Default);
		}

		auto& transform = registry.get_or_emplace<Transform>(editorwindow.camera);
		auto& camera = registry.get_or_emplace<Camera>(editorwindow.camera);

		if (camera.width != editorwindow.width || camera.height != editorwindow.height) {
			camera.width = editorwindow.width;
			camera.height = editorwindow.height;

			camera.lastX = camera.width / 2;
			camera.lastY = camera.height / 2;

			camera.first_mouse = true;

			if (camera.mode == PERSPECTIVE)
				camera.projection = glm::perspective(glm::radians(camera.fov), (float)camera.width / camera.height, camera.camera_near, camera.camera_far);
			
			if (!camera.init) camera.Position = glm::vec3(0, 0, 10);
			camera.init = true;
		}

		// if (!editorwindow.window_focus) return;
		// if ( return;
		if (!editorwindow.mouse_hover && registry.store<GameWindow>().window_focus) return;

		if (eventhandler.mouse_pressed.contains(SDL_BUTTON_MIDDLE)) {
			if (camera.first_mouse) {
				camera.lastX = eventhandler.posx;
				camera.lastY = eventhandler.posy;
				camera.first_mouse = false;
			}

			transform.rotation.y -= (eventhandler.posx - camera.lastX) * camera.sensitivity;
			transform.rotation.x += (camera.lastY - eventhandler.posy) * camera.sensitivity;

			camera.lastX = eventhandler.posx;
			camera.lastY = eventhandler.posy;
		} else {
			camera.first_mouse = true;
		}

		const auto& quaternion = transform.GetRotationQuat();

		camera.Front = glm::normalize(quaternion * camera.WorldFront);
		camera.Up = glm::normalize(quaternion * camera.WorldUp);


		if (eventhandler.mouse_scrollup) {
			camera.Position += camera.Front * float(camera.scrollspeed * engine.dt);
		}
		if (eventhandler.mouse_scrolldown) {
			camera.Position -= camera.Front * float(camera.scrollspeed * engine.dt);
		}

		auto distance = glm::length(camera.Position - camera.Center);
		camera.scrollspeed = distance / 10;
		camera.Position = distance * -camera.Front;

		static glm::vec3 delta;
		static glm::vec3 initpos;
		static bool toggle;

		if (eventhandler.mouse_pressed.contains(SDL_BUTTON_LEFT) && eventhandler.key_pressed.contains(SDL_SCANCODE_LALT)) {
			glm::vec3 pos;
			glm::vec4 ray_clip = glm::vec4(normalized_pos.x, -normalized_pos.y, -1.0, 1.0);
			glm::vec4 ray_eye = glm::inverse(camera.projection) * ray_clip;
			ray_eye = glm::vec4(ray_eye.x, ray_eye.y, -1.0, 0.0);
			glm::vec3 ray_wor = glm::inverse(camera.view) * ray_eye;
			ray_wor = glm::normalize(ray_wor);

			float denom = glm::dot(camera.Front, ray_wor);
			float t = -glm::dot((camera.Front * distance), camera.Front) / denom;
			pos = ray_wor * t + (camera.Offset + camera.Position);

			if (!toggle) {
				initpos = pos;
			}

			delta = pos - initpos;
			toggle = true;
		}

		transform.translation = camera.Position + camera.Offset + delta;

		camera.view = glm::lookAt(transform.translation, transform.translation + camera.Front, camera.Up);

		if (toggle && !eventhandler.mouse_pressed.contains(SDL_BUTTON_LEFT) && eventhandler.key_pressed.contains(SDL_SCANCODE_LALT)) {
			camera.Offset += delta;
			toggle = false;
			delta = glm::vec3();
		}
	}

	void CameraSystem(Registry& registry) {
		using namespace lf::Component;

		EditorCamera(registry);

		auto& engine = registry.store<Engine>();
		auto& gamewindow = registry.store<GameWindow>();

		if (!gamewindow.window_focus) return;

		for (auto [entity, tag, transform, camera]: registry.view<Tag, Transform, Camera>().each()) {
			if (!camera.enable || camera.type == Default) continue;

			if (camera.width != gamewindow.width || camera.height != gamewindow.height) {
				camera.width = gamewindow.width;
				camera.height = gamewindow.height;

				camera.lastX = camera.width / 2;
				camera.lastY = camera.height / 2;

				camera.first_mouse = true;

				if (camera.mode == PERSPECTIVE)
					camera.projection = glm::perspective(glm::radians(camera.fov), (float)camera.width / camera.height, camera.camera_near, camera.camera_far);
				if (camera.mode == ORTHOGRAPHIC) {
					int widen = std::tan(glm::radians(camera.fov/2.0)) * camera.camera_far;
					int highten = std::tan(glm::radians((float)(camera.fov / 2.0) / (float)(camera.width/camera.height))) * camera.camera_far;

					// std::cout << highten << ' ' << widen << ' ' << camera.width / camera.height << '\n';

					camera.projection = glm::ortho<float>(-10, 10, -10, 10, -1, 1);
					// camera.projection = glm::ortho<float>(-gamewindow.width, gamewindow.width, -gamewindow.height, gamewindow.height, -1, 1);
				}
				if (!camera.init) camera.Position = glm::vec3(0, 0, 10);
				camera.init = true;
			}
		}
	}
}