#pragma once

#include "../ECS.h"
#include "../Window.h"
#include <imgui.h>

namespace lf {
	namespace Editor {
		void GamePanel(Registry& registry) {
			auto& window = registry.store<Window>();
			auto& gamewindow = registry.store<GameWindow>();
			
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
			ImGui::Begin(gamewindow.title.c_str());
			ImGui::PopStyleVar();

			gamewindow.posx = ImGui::GetWindowPos().x;
			gamewindow.posy = ImGui::GetWindowPos().y;
			gamewindow.width = ImGui::GetWindowSize().x;
			gamewindow.height = ImGui::GetWindowSize().y;

			ImGui::GetWindowDrawList()->AddImage((void*)gamewindow.framebuffer->texture, ImVec2(gamewindow.posx, gamewindow.posy), ImVec2(gamewindow.posx + gamewindow.width, gamewindow.posy + gamewindow.height), ImVec2(0, (float)gamewindow.height / window.height), ImVec2((float)gamewindow.width / window.width, 0));
			ImGui::End();
		}
	}
}