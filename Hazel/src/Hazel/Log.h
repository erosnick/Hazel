#pragma once

#include "Core.h"
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace Hazel
{
	// C4251 workaround
	template class HAZEL_API std::shared_ptr<spdlog::logger>;

	class HAZEL_API Log
	{
	public:
		Log();
		~Log();

		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return coreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return clientLogger; }

	private:

		static std::shared_ptr<spdlog::logger> coreLogger;
		static std::shared_ptr<spdlog::logger> clientLogger;
	};
}

// Core log macros
#define HAZEL_CORE_TRACE(...)		::Hazel::Log::GetCoreLogger()->trace(__VA_ARGS__);
#define HAZEL_CORE_INFO(...)		::Hazel::Log::GetCoreLogger()->info(__VA_ARGS__);
#define HAZEL_CORE_WARN(...)		::Hazel::Log::GetCoreLogger()->warn(__VA_ARGS__);
#define HAZEL_CORE_ERROR(...)		::Hazel::Log::GetCoreLogger()->error(__VA_ARGS__);
#define HAZEL_CORE_CRITICAL(...)	::Hazel::Log::GetCoreLogger()->critical(__VA_ARGS__);

// Client log macros
#define HAZEL_CLIENT_TRACE(...)		::Hazel::Log::GetClientLogger()->trace(__VA_ARGS__);
#define HAZEL_CLIENT_INFO(...)		::Hazel::Log::GetClientLogger()->info(__VA_ARGS__);
#define HAZEL_CLIENT_WARN(...)		::Hazel::Log::GetClientLogger()->warn(__VA_ARGS__);
#define HAZEL_CLIENT_ERROR(...)		::Hazel::Log::GetClientLogger()->error(__VA_ARGS__);
#define HAZEL_CLIENT_CRITICAL(...)	::Hazel::Log::GetClientLogger()->critical(__VA_ARGS__);