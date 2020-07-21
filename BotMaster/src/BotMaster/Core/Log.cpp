#include "BMpch.h"
#include "Log.h"

#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"

std::shared_ptr<spdlog::logger> Log::s_CoreLogger;

void Log::Init()
{
	auto sharedFileSink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("BotMaster.log");

	s_CoreLogger = std::make_shared<spdlog::logger>("Botmaster", sharedFileSink);
	spdlog::set_pattern("%^[%T]: %v%$");
	s_CoreLogger = spdlog::stdout_color_mt("BotMaster");
	s_CoreLogger->set_level(spdlog::level::trace);
	s_CoreLogger->flush_on(spdlog::level::trace);
}
