#pragma once
#include "../../usings.h"


class LogConsole
{
public:
	LogConsole();

	void Draw(bool* p_opened);
	void OnEvent();
public:
private:
	std::string m_log_text;
};