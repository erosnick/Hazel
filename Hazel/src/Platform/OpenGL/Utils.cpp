#include "HazelPCH.h"
#include "Hazel/Log.h"
#include "Utils.h"

#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x) glClearError();\
	x;\
ASSERT(GLLogCall(__FUNCTION__, __FILE__, __LINE__))

namespace Hazel
{
	void glClearError()
	{
		while (glGetError() != GL_NO_ERROR);
	}

	bool GLLogCall(const char* function, const char* file, int line)
	{
		while (GLenum error = glGetError())
		{
			HAZEL_CORE_ERROR("[OpenGL Error]({0}, {1}, {2}, line:{3})\n", error, function, file, line);
			return false;
		}

		return true;
	}
}