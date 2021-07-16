#pragma once

#include "common.hpp"
// This ignores all warnings raised inside External headers
#pragma warning(push, 0)
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#pragma warning(pop)

namespace SOMA_ENGINE {

	class  Logger {
	public:
		Logger();
		~Logger();

		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}
#define SOMA_CORE_TRACE(...)    ::SOMA_ENGINE::Logger::GetCoreLogger()->trace(__VA_ARGS__)
#define SOMA_CORE_INFO(...)     ::SOMA_ENGINE::Logger::GetCoreLogger()->info(__VA_ARGS__)
#define SOMA_CORE_WARN(...)     ::SOMA_ENGINE::Logger::GetCoreLogger()->warn(__VA_ARGS__)
#define SOMA_CORE_ERROR(...)    ::SOMA_ENGINE::Logger::GetCoreLogger()->error(__VA_ARGS__)
#define SOMA_CORE_CRITICAL(...) ::SOMA_ENGINE::Logger::GetCoreLogger()->critical(__VA_ARGS__)
#define SOMA_CORE_DEBUG(...)	::SOMA_ENGINE::Logger::GetCoreLogger()->debug(__VA_ARGS__)

// Client log macros
#define SOMA_TRACE(...)         ::SOMA_ENGINE::Logger::GetClientLogger()->trace(__VA_ARGS__)
#define SOMA_INFO(...)          ::SOMA_ENGINE::Logger::GetClientLogger()->info(__VA_ARGS__)
#define SOMA_WARN(...)          ::SOMA_ENGINE::Logger::GetClientLogger()->warn(__VA_ARGS__)
#define SOMA_ERROR(...)         ::SOMA_ENGINE::Logger::GetClientLogger()->error(__VA_ARGS__)
#define SOMA_CRITICAL(...)      ::SOMA_ENGINE::Logger::GetClientLogger()->critical(__VA_ARGS__)
#define SOMA_DEBUG(...)			::SOMA_ENGINE::Logger::GetClientLogger()->debug(__VA_ARGS__)
