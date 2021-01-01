#include "HazelPCH.h"
#include "Renderer.h"
#include "Hazel/Log.h"

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