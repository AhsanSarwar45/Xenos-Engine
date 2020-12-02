#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include <spdlog/fmt/ostr.h>

namespace Xenos
{
	class XENOS_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};


}

// Core log macros
#define XS_CORE_ERROR(...)      ::Xenos::Log::GetCoreLogger()->error(__VA_ARGS__)
#define XS_CORE_WARN(...)       ::Xenos::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define XS_CORE_INFO(...)       ::Xenos::Log::GetCoreLogger()->info(__VA_ARGS__)
#define XS_CORE_TRACE(...)      ::Xenos::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define XS_CORE_CRITICAL(...)   ::Xenos::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define XS_ERROR(...)           ::Xenos::Log::GetClientLogger()->error(__VA_ARGS__)
#define XS_WARN(...)            ::Xenos::Log::GetClientLogger()->warn(__VA_ARGS__)
#define XS_INFO(...)            ::Xenos::Log::GetClientLogger()->info(__VA_ARGS__)
#define XS_TRACE(...)           ::Xenos::Log::GetClientLogger()->trace(__VA_ARGS__)
#define XS_CRITICAL(...)        ::Xenos::Log::GetClientLogger()->critical(__VA_ARGS__)

