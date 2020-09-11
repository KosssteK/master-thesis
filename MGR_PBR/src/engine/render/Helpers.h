#pragma once
#include <GL/glew.h>
#include <string>

#define ASSERT(x) if (!(x)) __debugbreak();

#define LOG(x) std::cout << x << std::endl;

#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x, __FILE__, __LINE__))


void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

namespace CAT {
	struct Properties {
		std::string objectPath;
		std::string texturePath;
		std::string shaderPath;
		std::string rghPath;
		std::string mtlPath;
		std::string nrmPath;


		Properties(	const std::string & object,
					const std::string & texture,
					const std::string & rgh,
					const std::string & mtl,
					const std::string & nrm,
					const std::string & shader) {
			objectPath = object;
			texturePath = texture;
			rghPath = rgh;
			mtlPath = mtl;
			nrmPath = nrm;
			shaderPath = shader;
		}
	};
}