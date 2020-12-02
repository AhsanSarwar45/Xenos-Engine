#pragma once

#include <memory>

#ifdef  XENOS_PLATFORM_WINDOWS
#if XENOS_DYNAMIC_LINK
	#ifdef XENOS_BUILD_DLL
		#define XENOS_API _declspec(dllexport)
	#else 
		#define XENOS_API _declspec(dllimport)
	#endif // XENOS_BUILD_DLL
#else
	#define XENOS_API
#endif
#else
	#error Xenos only supports Windows!
#endif //  XENOS_PLATFORM_WINDOWS

#ifdef XENOS_DEBUG
	#define XENOS_ENABLE_ASSERTS
#endif

#ifdef  XENOS_ENABLE_ASSERTS
	#define XS_ASSERT(x, ...) {if(!(x)) {XS_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
	#define XS_CORE_ASSERT(x, ...) {if(!(x)) {XS_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
#else
	#define XS_ASSERT(x, ...)
	#define XS_CORE_ASSERT(x, ...)
#endif //  XENOS_ENABLE_ASSERTS


#define BIT(x) (1<<x)

#define XS_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

namespace Xenos
{
	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}