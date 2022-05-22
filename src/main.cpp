#ifndef STB_IMAGE_IMPLEMENTATION
	#define STB_IMAGE_IMPLEMENTATION
#endif

#include <iostream>

#include <chrono>

#include "Core/Editor/Editor.h"
#include "Core/Editor/Panels/Panels.h"
#include "Core/Systems/CameraSystem.h"
#include "Core/ECS.h"
#include "Core/Engine.h"
#include "Core/Window.h"
#include "Core/Events.h"
#include "Core/Functions.h"

#include "Core/Renderer/Renderer.h"

#include "Core/Registries/ShaderRegistry.h"
#include "Core/Registries/VertexArrayRegistry.h"
#include "Core/Registries/SpriteRegistry.h"

#include <glm/gtx/string_cast.hpp>

#include <format>

int main(int ArgCount, char **Args) {
	lf::Registry registry;

	auto& engine = registry.store<lf::Engine>();
	auto& events = registry.store<lf::Events>();
	auto& window = registry.store<lf::Window>();

	auto& renderer = registry.store<lf::Renderer>();

	engine.quit = false;

	SDL_Init(SDL_INIT_VIDEO);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	engine.window = SDL_CreateWindow(window.title.c_str(), window.posx, window.posy, window.width, window.height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	assert(engine.window);
	engine.context = SDL_GL_CreateContext(engine.window);

	gladLoadGLLoader(SDL_GL_GetProcAddress);

	auto& gamewindow = registry.store<lf::GameWindow>();

	#ifdef ENABLE_EDITOR
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableSetMousePos;
		io.ConfigDockingWithShift = true;

		ImGui_ImplSDL2_InitForOpenGL(engine.window, (void*)engine.context);
		ImGui_ImplOpenGL3_Init("#version 400");

		ImGui::StyleColorsDark();
		auto& style = ImGui::GetStyle();
		style.TabRounding = 0;
		style.WindowRounding = 0;
		style.ScrollbarRounding = 0;
		style.FrameBorderSize = 1;
		
		auto& editorwindow = registry.store<lf::EditorWindow>();

		editorwindow.framebuffer = new FrameBuffer(editorwindow.width, editorwindow.height, true);
		gamewindow.framebuffer = new FrameBuffer(gamewindow.width, gamewindow.height, true);
	#endif

	renderer.Init(&registry);

	glViewport(0, 0, window.width, window.height);

	auto& functions = registry.store<lf::Functions>(&registry);

	functions.LoadEntities();
	
	while (!engine.quit) {
		const auto& start_time = std::chrono::high_resolution_clock::now();

		events.Update(registry);

		lf::CameraSystem(registry);

		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		renderer.Render(gamewindow);

		#ifdef ENABLE_EDITOR
			// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			renderer.Render(editorwindow, true);
			// glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

			{
				editorwindow.framebuffer->Bind();

				glReadBuffer(GL_COLOR_ATTACHMENT1);

				glm::vec3 pos = events.GetMousePos(editorwindow);
				
				glm::vec4 pixel;
				glReadPixels(pos.x, pos.y, 1, 1, GL_RGBA, GL_FLOAT, &pixel[0]);
				static bool toggle;

				if (pixel.w) {
					int idx = pixel.x / 2;
					if (idx % 2 != 0) {
						idx--;
					}
					idx /= 2;

					if (events.mouse_pressed.contains(SDL_BUTTON_LEFT) && toggle) {
						auto& selected_entity = registry.store<lf::Editor>().selected_entity;

						if (events.dropped_file != "") {
							selected_entity = renderer.drawn_sprite_entities[int(pixel.z)][idx];
							
							auto& spriterenderer = registry.get_or_emplace<lf::Component::SpriteRenderer>(selected_entity);
							auto& sprite = registry.get_or_emplace<lf::Component::Sprite>(selected_entity);

							// sprite.texture = new Texture(events.dropped_file.c_str());
						}
					}
				}

				glReadBuffer(GL_NONE);

				editorwindow.framebuffer->UnBind();

				toggle = !events.mouse_pressed.contains(SDL_BUTTON_LEFT);
			}

			if (events.key_pressed.contains(SDL_SCANCODE_LCTRL) && events.key_pressed.contains(SDL_SCANCODE_S))
				functions.SaveEntities();
			
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplSDL2_NewFrame();
			ImGui::NewFrame();

			// Docking
			static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

			ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

			ImGui::SetNextWindowPos(ImVec2(0, 0));
			ImGui::SetNextWindowSize(ImVec2(window.width, window.height));

			static bool p_open;

			ImGui::Begin("DockSpace", &p_open, window_flags);

			ImGui::PopStyleVar(3);
			if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_DockingEnable) {
				ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
				ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
			}
			ImGui::End();

			static bool show_demo = true;
			ImGui::ShowDemoWindow(&show_demo);
			
			lf::Panel::SpritePanel(registry);
			lf::Panel::ScenePanel(registry);
			lf::Panel::InspectorPanel(registry);

			lf::Panel::GamePanel(registry);
			lf::Panel::EditorPanel(registry);

			ImGui::EndFrame();
			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		#endif

		SDL_GL_SwapWindow(engine.window);

		const auto& end_time = std::chrono::high_resolution_clock::now();
		engine.dt = std::chrono::duration<double, std::ratio<1, 60>>(end_time - start_time).count();
	}

	return 0;
}
