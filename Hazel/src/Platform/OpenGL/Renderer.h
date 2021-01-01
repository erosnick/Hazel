#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Hazel
{
	#define ASSERT(x) if(!(x)) __debugbreak();
	#define GLCall(x) glClearError();\
			x;\
		ASSERT(GLLogCall(__FUNCTION__, __FILE__, __LINE__))

		void glClearError();

		bool GLLogCall(const char* function, const char* file, int line);

	struct Vertex
	{
		float x;
		float y;
		float z;
		float r;
		float g;
		float b;
		float a;
	};
}