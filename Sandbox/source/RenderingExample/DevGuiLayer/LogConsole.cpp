#include "LogConsole.h"
#include "imgui.h"
#include "misc/cpp/imgui_stdlib.h"

LogConsole::LogConsole()
{
}

void LogConsole::Draw(bool* p_opened)
{
	ImGui::Begin("Log", p_opened);

	ImGui::InputTextMultiline("##LogText", &m_log_text, ImVec2(ImGui::GetWindowSize().x - 20,0), ImGuiInputTextFlags_ReadOnly);
	ImGui::End();
}

void LogConsole::OnEvent()
{
}
