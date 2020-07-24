#pragma once

#ifdef HAZEL_EXPORTS
#define HAZEL_API __declspec(dllexport) 
#else
#define HAZEL_API __declspec(dllimport)
#endif // HAZEL_EXPORTS

namespace Hazel
{
	HAZEL_API void Print();
}