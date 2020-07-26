#pragma once

#ifdef HAZEL_EXPORTS
#define HAZEL_API __declspec(dllexport) 
#else
#define HAZEL_API __declspec(dllimport)
#endif // HAZEL_EXPORTS

#define BIT(x) (1 << x)

#ifdef HAZEL_ENABLE_ASSERTS
#define HAZEL_ASSERT(x, ...) { if (!(x)) { HAZEL_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define HAZEL_CORE_ASSERT(x, ...) { if (!(x)) { HAZEL_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
#define HAZEL_ASSERT(x, ...)
#define HAZEL_ASSERT(x, ...)
#endif // HAZEL_ENABLE_ASSERTS
