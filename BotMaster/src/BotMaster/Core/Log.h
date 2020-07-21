#pragma once

#include "spdlog/spdlog.h"

class Log
{
public:
	static void Init();

	inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }

private:
	static std::shared_ptr<spdlog::logger> s_CoreLogger;
};

//Core log macros
#define CORE_TRACE(...) ::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define CORE_INFO(...)  ::Log::GetCoreLogger()->info(__VA_ARGS__)
#define CORE_WARN(...)  ::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define CORE_ERROR(...) ::Log::GetCoreLogger()->error(__VA_ARGS__)
#define CORE_CRITICAL(...) ::Log::GetCoreLogger()->critical(__VA_ARGS__)