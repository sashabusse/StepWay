#include "LogConsole.h"
#include "imgui.h"

LogConsole::LogConsole()
{
}

void LogConsole::Draw(bool* p_opened)
{
	ImGui::Begin("Log", p_opened);

	ImGui::InputTextMultiline("##LogText", (char*)m_log_text.c_str(), m_log_text.size(), ImVec2(ImGui::GetWindowSize().x - 20,0), ImGuiInputTextFlags_ReadOnly);
	ImGui::End();
}

void LogConsole::OnEvent()
{
}
