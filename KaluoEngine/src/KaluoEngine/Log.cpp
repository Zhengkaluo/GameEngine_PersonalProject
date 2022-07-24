#include "Log.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace KaluoEngine {

	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;


	void Log::Init() {
		//Customizing format of log
		//Format can be applied globally to all registered loggers:
		//some_logger->set_pattern(">>>>>>>>> %H:%M:%S %z %v <<<<<<<<<");
		//%^ color range, %T time, %n logger's name, %v actual text,  %$ end color range
		spdlog::set_pattern("%^[%T] %n: %v%$");
		// create color multi threaded logger
		// example: 
		// auto console = spdlog::stdout_color_mt("console");
		// file_sink->set_level(spdlog::level::trace);
		s_CoreLogger = spdlog::stdout_color_mt("Engine");
		s_CoreLogger->set_level(spdlog::level::trace);

		s_ClientLogger = spdlog::stdout_color_mt("ClientAPP");
		s_ClientLogger->set_level(spdlog::level::trace);

	}

}
