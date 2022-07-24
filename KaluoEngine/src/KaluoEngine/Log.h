#pragma once
#include "Core.h"
#include "spdlog/spdlog.h"

namespace KaluoEngine {
	class KALUO_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger;}

		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger;}

	private:
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
		static std::shared_ptr<spdlog::logger> s_CoreLogger;

		
	};
}

//define macro for easy core error log
#define KALUO_CORE_ERROR(...)	::KaluoEngine::Log::GetCoreLogger()->error(__VA_ARGS__)
#define KALUO_CORE_WARN(...)	::KaluoEngine::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define KALUO_CORE_INFO(...)	::KaluoEngine::Log::GetCoreLogger()->info(__VA_ARGS__)
#define KALUO_CORE_TRACE(...)	::KaluoEngine::Log::GetCoreLogger()->trace(__VA_ARGS__)
//#define KALUO_CORE_FATAL:(...)	::KaluoEngine::Log::GetCoreLogger()->fatal(__VA_ARGS__)


//define macro for easy client error log
#define KALUO_ERROR(...)	::KaluoEngine::Log::GetClientLogger()->error(__VA_ARGS__)
#define KALUO_WARN(...)		::KaluoEngine::Log::GetClientLogger()->warn(__VA_ARGS__)
#define KALUO_INFO(...)		::KaluoEngine::Log::GetClientLogger()->info(__VA_ARGS__)
#define KALUO_TRACE(...)	::KaluoEngine::Log::GetClientLogger()->trace(__VA_ARGS__)
//#define KALUO_FATAL:(...)	::KaluoEngine::Log::GetClientLogger()->fatal(__VA_ARGS__)
