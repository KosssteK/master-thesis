#include "Helpers.h"
#include <iostream>

void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "[OPENGL ERROR]: " << "(" << error << "): " << function << " " << file << ":" << line << std::endl;
		std::cout << error << std::endl;
		return false;
	}
	return true;
}