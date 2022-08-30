#pragma once

#include <memory>

#ifdef KALUO_PLATFORM_WINDOWS
#if KALUO_DYNAMIC_LINK
	#ifdef KALUO_BUILD_DLL
		#define KALUO_API _declspec(dllexport)
	#else
		#define KALUO_API _declspec(dllimport)
	#endif // KZ_BUILD_DLL
#else
	#define KALUO_API
#endif
#else
	#error KALUO Engine only supports windows;
#endif


#ifdef KALUO_DEBUG
	#define KALUO_ENABLE_ASSERTS
#endif

#ifdef KALUO_ENABLE_ASSERTS
	//checks for certain conditions
	#define KALUO_ASSERT(x, ...) { if(!(x)) { KALUO_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define KALUO_CORE_ASSERT(x, ...) { if(!(x)) { KALUO_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define KALUO_ASSERT(x, ...)
	#define KALUO_CORE_ASSERT(x, ...)
#endif //KALUO_ENBALE_ASSERTS


#define BIT(x) (1 << x)

//The std::placeholders namespace contains the placeholder objects [_1, ..., _N] 
//where N is an implementation defined maximum number. 
//fn example Applilcation::onxxxevent
#define KALUO_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)
//#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

namespace KaluoEngine { 
	
	template <typename T>
	using Scope = std::unique_ptr<T>;

	template <typename T>
	using Ref = std::shared_ptr<T>;

}