#include "StepWayPCH.h"
#include "Log.h"


std::shared_ptr<spdlog::logger> StepWay::Log::m_CoreLogger = nullptr;
std::shared_ptr<spdlog::logger> StepWay::Log::m_ClientLogger = nullptr;

void StepWay::Log::Init()
{
	SW_CORE_ASSERT(m_CoreLogger == nullptr || m_ClientLogger == nullptr, "multiple initialization");
	m_CoreLogger = spdlog::stdout_color_mt("CORE");
	m_ClientLogger = spdlog::stdout_color_mt("APP");

	m_CoreLogger->set_level(spdlog::level::trace);
	m_ClientLogger->set_level(spdlog::level::trace);

	m_CoreLogger->set_pattern("%^[%H:%M:%S.%e](%n)%$: %v");
	m_ClientLogger->set_pattern("%^[%H:%M:%S.%e](%n)%$: %v");
}

void StepWay::Log::ShutDown()
{
	spdlog::drop(m_CoreLogger->name());
	spdlog::drop(m_ClientLogger->name());
	m_CoreLogger = nullptr;
	m_ClientLogger = nullptr;
}
