#pragma once

#include "spdlog/spdlog.h"

class Log
{
public:
	static void Init();

	inline static std::shared_ptr<spdlog::logger>& GetLogger() { return s_Logger; }

private:
	static std::shared_ptr<spdlog::logger> s_Logger;
};

//Core log macros
#define BM_LOG_TRACE(...) ::Log::GetLogger()->trace(__VA_ARGS__)
#define BM_LOG_INFO(...)  ::Log::GetLogger()->info(__VA_ARGS__)
#define BM_LOG_WARN(...)  ::Log::GetLogger()->warn(__VA_ARGS__)
#define BM_LOG_ERROR(...) ::Log::GetLogger()->error(__VA_ARGS__)
#define BM_LOG_CRITICAL(...) ::Log::GetLogger()->critical(__VA_ARGS__)