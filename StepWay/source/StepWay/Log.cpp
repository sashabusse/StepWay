#include "StepWayPCH.h"
#include "Log.h"


std::shared_ptr<spdlog::logger> StepWay::Log::m_CoreLogger = nullptr;
std::shared_ptr<spdlog::logger> StepWay::Log::m_ClientLogger = nullptr;

void StepWay::Log::Init()
{
	m_CoreLogger = spdlog::stdout_color_mt("CORE");
	m_ClientLogger = spdlog::stdout_color_mt("APP");

	m_CoreLogger->set_level(spdlog::level::trace);
	m_ClientLogger->set_level(spdlog::level::trace);

	m_CoreLogger->set_pattern("%^[%H:%M:%S.%e](%n)%$: %v");
	m_ClientLogger->set_pattern("%^[%H:%M:%S.%e](%n)%$: %v");
}
