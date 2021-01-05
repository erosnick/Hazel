#pragma once

#include "glad/glad.h"

namespace Hazel
{
#define ASSERT(x) if(!(x)) __debugbreak();

void glClearError();

bool GLLogCall(const char* function, const char* file, int line);

#define GLCall(x) glClearError();\
			x;\
		ASSERT(GLLogCall(__FUNCTION__, __FILE__, __LINE__))
}