#include "BMpch.h"
#include "Log.h"

#include "spdlog/sinks/stdout_color_sinks.h"

std::shared_ptr<spdlog::logger> Log::s_Logger;

void Log::Init()
{
	auto Consolesink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
	s_Logger = std::make_shared<spdlog::logger>("BotMasterConsole", Consolesink);
	spdlog::register_logger(s_Logger);
	s_Logger->set_pattern("%^[%T] %n: %v%$");
	s_Logger->set_level(spdlog::level::trace);
	
}
