#pragma once

#ifdef KALUO_PLATFORM_WINDOWS
	#ifdef KALUO_BUILD_DLL
		#define KALUO_API _declspec(dllexport)
	#else
		#define KALUO_API _declspec(dllimport)
	#endif // KZ_BUILD_DLL
#else
	#error KALUO Engine only supports windows;
#endif

#ifdef KALUO_ENABLE_ASSERTS
	//checks for certain conditions
	#define KALUO_ASSERT(x, ...) { if(!(x)) { KALUO_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define KALUO_CORE_ASSERT(x, ...) {if(!(x)) { KALUO_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }
#else
	#define KALUO_ASSERT(x, ...)
	#define KALUO_CORE_ASSERT(x, ...)
#endif //KALUO_ENBALE_ASSERTS


#define BIT(x) (1 << x)