#pragma once

#include "glad/glad.h"

namespace Hazel
{
#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x) glClearError();\
			x;\
		ASSERT(GLLogCall(__FUNCTION__, __FILE__, __LINE__))

	void glClearError();

	bool GLLogCall(const char* function, const char* file, int line);
}