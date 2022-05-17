#include <iostream>

#include <chrono>

#include "Core/Editor/Editor.h"
#include "Core/Systems/CameraSystem.h"
#include "Core/ECS.h"
#include "Core/Engine.h"
#include "Core/Window.h"
#include "Core/Events.h"

#include "Core/Renderer/Renderer.h"

#include "Core/Registries/ShaderRegistry.h"
#include "Core/Registries/VertexArrayRegistry.h"

int main(int ArgCount, char **Args) {
	lf::Registry registry;

	auto& engine = registry.store<lf::Engine>();
	auto& eventhandler = registry.store<lf::Events>();
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
	OpenGL_CreateContext();

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

		editorwindow.framebuffer = FrameBuffer_Create(editorwindow.width, editorwindow.height, true);
		gamewindow.framebuffer = FrameBuffer_Create(gamewindow.width, gamewindow.height, true);
	#endif

	renderer.Init(&registry);

	glViewport(0, 0, window.width, window.height);

	// auto camera = registry.create();
	// registry.emplace<lf::Component::Transform>(camera);
	// registry.emplace<lf::Component::Camera>(camera, lf::ORTHOGRAPHIC, true);

	auto entity_test = registry.create();
	registry.emplace<lf::Component::Tag>(entity_test, lf::Component::Tag{"dddddddddd", "ssssssssssss"});
	registry.emplace<lf::Component::Transform>(entity_test);
	registry.emplace<lf::Component::Camera>(entity_test, lf::ORTHOGRAPHIC, true);
	
	while (!engine.quit) {
		const auto& start_time = std::chrono::high_resolution_clock::now();

		eventhandler.Update(registry);

		lf::CameraSystem(registry);

		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		renderer.Render(gamewindow);
		renderer.Render(editorwindow);

		#ifdef ENABLE_EDITOR
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
			
			lf::Editor::ScenePanel(registry);
			lf::Editor::InspectorPanel(registry);

			lf::Editor::GamePanel(registry);
			lf::Editor::EditorPanel(registry);

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
