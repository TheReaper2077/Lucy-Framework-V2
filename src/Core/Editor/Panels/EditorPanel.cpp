#include "EditorPanel.h"

void lf::Panel::EditorPanel(Registry& registry) {
	auto& window = registry.store<Window>();
	auto& editorwindow = registry.store<EditorWindow>();

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

	ImGui::Begin(editorwindow.title.c_str());
	ImGui::PopStyleVar();

	editorwindow.window_focus = ImGui::IsWindowFocused();
	editorwindow.mouse_hover = ImGui::IsWindowHovered();

	editorwindow.posx = ImGui::GetWindowPos().x;
	editorwindow.posy = ImGui::GetWindowPos().y;
	editorwindow.width = ImGui::GetWindowSize().x;
	editorwindow.height = ImGui::GetWindowSize().y;

	ImGui::GetWindowDrawList()->AddImage((void*)editorwindow.framebuffer->texture, ImVec2(editorwindow.posx, editorwindow.posy), ImVec2(editorwindow.posx + editorwindow.width, editorwindow.posy + editorwindow.height), ImVec2(0, (float)editorwindow.height / window.height), ImVec2((float)editorwindow.width / window.width, 0));

	ImGui::End();
}
