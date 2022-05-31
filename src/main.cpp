#ifndef STB_IMAGE_IMPLEMENTATION
	#define STB_IMAGE_IMPLEMENTATION
#endif

#include <iostream>

#include <chrono>

#include "Core/Editor/Editor.h"
#include "Core/Systems/CameraSystem.h"
#include "Core/ECS.h"
#include "Core/Engine.h"
#include "Core/Window.h"
#include "Core/Events.h"
#include "Core/Functions.h"
#include "Core/Editor/Panels/GuiPanel.h"

#include "Core/Renderer/Renderer.h"

#include "Core/Registries/ShaderRegistry.h"
#include "Core/Registries/VertexArrayRegistry.h"
#include "Core/Registries/SpriteRegistry.h"

#include <glm/gtx/string_cast.hpp>

#include <glad/glad.h>

#include "ImGuiStyles.h"

int main(int ArgCount, char **Args) {
	lucy::Registry registry;

	registry.create();

	auto& engine = registry.store<lucy::Engine>();
	auto& events = registry.store<lucy::Events>();
	auto& window = registry.store<lucy::Window>();

	auto& renderer = registry.store<lucy::RenderContext>();

	engine.quit = false;


	SDL_Init(SDL_INIT_VIDEO);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	engine.window = SDL_CreateWindow(window.title.c_str(), window.posx, window.posy, window.width, window.height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	assert(engine.window);
	engine.context = SDL_GL_CreateContext(engine.window);

	gladLoadGLLoader(SDL_GL_GetProcAddress);

	auto& gamewindow = registry.store<lucy::GameWindow>();

	#ifdef ENABLE_DEBUG
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableSetMousePos;
		io.ConfigWindowsMoveFromTitleBarOnly = true;
		io.ConfigDockingWithShift = true;

		ImGui_ImplSDL2_InitForOpenGL(engine.window, (void*)engine.context);
		ImGui_ImplOpenGL3_Init("#version 400");

		ImGui::StyleColorsDark();
		VS_Theme();
		
		auto& editorwindow = registry.store<lucy::EditorWindow>();

		#ifdef ENABLE_EDITOR
			editorwindow.framebuffer = new lgl::FrameBuffer(editorwindow.width, editorwindow.height, true);
			gamewindow.framebuffer = new lgl::FrameBuffer(gamewindow.width, gamewindow.height, true);
		#endif
	#endif

	renderer.Init(&registry);

	auto& null_texture = registry.store<lgl::Texture>();

	null_texture.Bind();

	null_texture.LoadFile("");

	null_texture.UnBind();

	auto& functions = registry.store<lucy::Functions>(&registry);

	functions.LoadEntities();
	functions.LoadSprites();

	int fps = 0;
	float frametime = 0;
	int ups = 0;
	float updatetime = 0;

	const int MAX_UPS = 60;

	auto& spriteregistry_panel = registry.store<lucy::Panel::GuiPanel<lucy::Panel::SpriteRegistry>>(&registry, "Sprite Registry");
	auto& textureregistry_panel = registry.store<lucy::Panel::GuiPanel<lucy::Panel::TextureRegistry>>(&registry, "Texture Registry");
	auto& spriteeditor_panel = registry.store<lucy::Panel::GuiPanel<lucy::Panel::SpriteEditor>>(&registry, "Sprite Editor");
	auto& inspector_panel = registry.store<lucy::Panel::GuiPanel<lucy::Panel::Inspector>>(&registry, "Inspector");
	auto& sceneheirarchy_panel = registry.store<lucy::Panel::GuiPanel<lucy::Panel::SceneHeirarchy>>(&registry, "Scene Heirarchy");
	// auto& materialeditor_panel = registry.store<lucy::Panel::GuiPanel<lucy::Panel::MaterialEditor>>(&registry, "Material Editor");
	auto& debuggame_panel = registry.store<lucy::Panel::GuiPanel<lucy::Panel::DebugGame>>(&registry);
	auto& debugeditor_panel = registry.store<lucy::Panel::GuiPanel<lucy::Panel::DebugEditor>>(&registry, "Editor");

	spriteeditor_panel.window_open = false;
	
	while (!engine.quit) {
		const auto& start_time = std::chrono::high_resolution_clock::now();

		events.Update(registry);

		lucy::CameraSystem(registry);

		glViewport(0, 0, window.width, window.height);
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		renderer.Render(gamewindow);

		#ifdef ENABLE_DEBUG
			if (editorwindow.framebuffer != nullptr) renderer.Render(editorwindow, true);

			if (editorwindow.framebuffer != nullptr) {
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
						auto& selected_entity = registry.store<lucy::Editor>().selected_entity;

						if (int(pixel.z) < renderer.drawn_sprite_entities.size())
							if (idx < renderer.drawn_sprite_entities[int(pixel.z)].size())
								selected_entity = renderer.drawn_sprite_entities[int(pixel.z)][idx];
					}
				}

				glReadBuffer(GL_NONE);

				editorwindow.framebuffer->UnBind();

				toggle = !events.mouse_pressed.contains(SDL_BUTTON_LEFT);
			}
			
			if (events.dropped_file != "") {
				auto& spriteregistry = registry.store<lucy::SpriteRegistry>();

				spriteregistry.GetTexture(events.dropped_file);
			}

			if (events.key_pressed.contains(SDL_SCANCODE_LCTRL) && events.key_pressed.contains(SDL_SCANCODE_S)) {
				functions.SaveSprites();
				functions.SaveEntities();
			}
			
			static bool show_demo = true;
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplSDL2_NewFrame();
			ImGui::NewFrame();

			#ifdef ENABLE_EDITOR
				static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

				ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

				ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
				ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
				ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

				ImGui::SetNextWindowPos(ImVec2(0, 0));
				ImGui::SetNextWindowSize(ImVec2(window.width, window.height));


				static bool p_open;

				ImGui::Begin("DockSpace", &p_open, window_flags);
				if (ImGui::BeginMainMenuBar()) {
                    if (ImGui::BeginMenu("File")) {
                        if (ImGui::MenuItem("Save Entities")) {
							
                        }
						if (ImGui::MenuItem("Save Sprites")) {
							functions.SaveSprites();
                        }
						if (ImGui::MenuItem("Load Scene")) {
							functions.SaveEntities();
						}
                        ImGui::EndMenu();
                    }

					if (ImGui::BeginMenu("Windows")) {
                        if (ImGui::MenuItem("Sprite Editor")) {
							spriteeditor_panel.window_open = true;
                        }
						if (ImGui::MenuItem("Texture Registry")) {
							textureregistry_panel.window_open = true;
                        }
						if (ImGui::MenuItem("Sprite Registry")) {
							spriteregistry_panel.window_open = true;
                        }
						if (ImGui::MenuItem("Inspector")) {
							inspector_panel.window_open = true;
						}
						if (ImGui::MenuItem("Scene Heirarchy")) {
							sceneheirarchy_panel.window_open = true;
						}
						if (ImGui::MenuItem("Editor")) {
							debugeditor_panel.window_open = true;
						}
						if (ImGui::MenuItem("Game")) {
							debuggame_panel.window_open = true;
						}
						if (ImGui::MenuItem("Demo")) {
							show_demo = true;
						}
                        ImGui::EndMenu();
                    }

                    ImGui::EndMainMenuBar();
                }

				ImGui::PopStyleVar(3);
				if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_DockingEnable) {
					
					ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
					ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
				}
				ImGui::End();
				
				// if (gamewindow.framebuffer != nullptr) lucy::Panel::GamePanel(registry);
				// if (editorwindow.framebuffer != nullptr) lucy::Panel::EditorPanel(registry);
			#endif

			spriteregistry_panel.RenderWindow();
			spriteeditor_panel.RenderWindow();
			inspector_panel.RenderWindow();
			sceneheirarchy_panel.RenderWindow();
			// materialeditor_panel.RenderWindow();
			debuggame_panel.RenderWindow();
			debugeditor_panel.RenderWindow();
			textureregistry_panel.RenderWindow();

			ImGui::ShowDemoWindow(&show_demo);

			ImGui::EndFrame();
			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		#endif

		SDL_GL_SwapWindow(engine.window);

		const auto& end_time = std::chrono::high_resolution_clock::now();
		engine.dt = std::chrono::duration<double, std::ratio<1, MAX_UPS>>(end_time - start_time).count();
	}

	#ifdef ENABLE_DEBUG
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplSDL2_Shutdown();
	#endif

	return 0;
}
