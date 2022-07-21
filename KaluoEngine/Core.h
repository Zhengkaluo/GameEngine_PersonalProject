#pragma once

#ifdef KALUO_PLATFORM_WINDOWS
	#ifdef KALUO_BUILD_DLL
		#define KALUO_API _declspec(dllexport)
	#else
		#define KALUO_API _declspec(dllimport)
	#endif // KZ_BUILD_DLL
#else
	#error KALUO Engine only support windows;
#endif