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

		template<typename FormatString, typename... Args>
		inline static void coreTrace(const FormatString& fmt, const Args&... args)
		{
			coreLogger->trace(fmt, args...);
		}

		template<typename FormatString, typename... Args>
		inline static void coreInfo(const FormatString& fmt, const Args&... args)
		{
			coreLogger->info(fmt, args...);
		}

		template<typename FormatString, typename... Args>
		inline static void coreWarn(const FormatString& fmt, const Args&... args)
		{
			coreLogger->warn(fmt, args...);
		}

		template<typename FormatString, typename... Args>
		inline static void coreError(const FormatString& fmt, const Args&... args)
		{
			coreLogger->error(fmt, args...);
		}

		template<typename FormatString, typename... Args>
		inline static void coreCritical(const FormatString& fmt, const Args&... args)
		{
			coreLogger->critical(fmt, args...);
		}

		inline static auto& GetCoreLogger() { return coreLogger; }
		inline static auto& GetClientLogger() { return clientLogger; }

	private:

		static std::shared_ptr<spdlog::logger> coreLogger;
		static std::shared_ptr<spdlog::logger> clientLogger;
	};
}

// Core log macros
#define HAZEL_CORE_TRACE(...)		::Hazel::Log::coreTrace(__VA_ARGS__);
#define HAZEL_CORE_INFO(...)		::Hazel::Log::coreInfo(__VA_ARGS__);
#define HAZEL_CORE_WARN(...)		::Hazel::Log::coreWarn(__VA_ARGS__);
#define HAZEL_CORE_ERROR(...)		::Hazel::Log::coreError(__VA_ARGS__);
#define HAZEL_CORE_CRITICAL(...)	::Hazel::Log::coreCritical(__VA_ARGS__);

// Client log macros
#define HAZEL_TRACE(...)		::Hazel::Log::GetClientLogger()->trace(__VA_ARGS__);
#define HAZEL_INFO(...)		::Hazel::Log::GetClientLogger()->info(__VA_ARGS__);
#define HAZEL_WARN(...)		::Hazel::Log::GetClientLogger()->warn(__VA_ARGS__);
#define HAZEL_ERROR(...)		::Hazel::Log::GetClientLogger()->error(__VA_ARGS__);
#define HAZEL_CRITICAL(...)	::Hazel::Log::GetClientLogger()->critical(__VA_ARGS__);