#pragma once
#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/ostr.h"
#include <memory>


namespace StepWay
{
	class Log
	{
	private:
		static std::shared_ptr<spdlog::logger> m_CoreLogger;
		static std::shared_ptr<spdlog::logger> m_ClientLogger;
	public:
		static void Init();
		static void ShutDown();//mainly for testing
		static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return m_CoreLogger; };
		static std::shared_ptr<spdlog::logger>& GetClientLogger() { return m_ClientLogger; };
	};

}



#define SW_CORE_TRACE(...)		StepWay::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define SW_CORE_INFO(...)		StepWay::Log::GetCoreLogger()->info(__VA_ARGS__)
#define SW_CORE_WARNING(...)	StepWay::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define SW_CORE_ERROR(...)		StepWay::Log::GetCoreLogger()->error(__VA_ARGS__)
#define SW_CORE_FATAL(...)		StepWay::Log::GetCoreLogger()->critical(__VA_ARGS__)

#define SW_CORE_LEVEL_TRACE()	StepWay::Log::GetCoreLogger()->set_level(spdlog::level::trace)
#define SW_CORE_LEVEL_INFO()	StepWay::Log::GetCoreLogger()->set_level(spdlog::level::info)
#define SW_CORE_LEVEL_WARNING()	StepWay::Log::GetCoreLogger()->set_level(spdlog::level::warn)
#define SW_CORE_LEVEL_ERROR()	StepWay::Log::GetCoreLogger()->set_level(spdlog::level::err)
#define SW_CORE_LEVEL_FATAL()	StepWay::Log::GetCoreLogger()->set_level(spdlog::level::critical)



#define SW_TRACE(...)			StepWay::Log::GetClientLogger()->trace(__VA_ARGS__)
#define SW_INFO(...)			StepWay::Log::GetClientLogger()->info(__VA_ARGS__)
#define SW_WARNING(...)			StepWay::Log::GetClientLogger()->warn(__VA_ARGS__)
#define SW_ERROR(...)			StepWay::Log::GetClientLogger()->error(__VA_ARGS__)
#define SW_FATAL(...)			StepWay::Log::GetClientLogger()->critical(__VA_ARGS__)

#define SW_LEVEL_TRACE()		StepWay::Log::GetClientLogger()->set_level(spdlog::level::trace)
#define SW_LEVEL_INFO()			StepWay::Log::GetClientLogger()->set_level(spdlog::level::info)
#define SW_LEVEL_WARNING()		StepWay::Log::GetClientLogger()->set_level(spdlog::level::warn)
#define SW_LEVEL_ERROR()		StepWay::Log::GetClientLogger()->set_level(spdlog::level::err)
#define SW_LEVEL_FATAL()		StepWay::Log::GetClientLogger()->set_level(spdlog::level::critical)
