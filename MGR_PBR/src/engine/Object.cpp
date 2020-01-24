#include "Object.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "render/VertexBuffer.h"
#include "render/VertexBufferLayout.h"
#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include "vendor/glm/gtx/rotate_vector.hpp"

CAT::Object::Object()
	:shader("res/shaders/basic.shader"),
	texture("res/objects/triangle.png")
{
	std::cout << "create CAT::OBJECT" << std::endl;
}

CAT::Object::Object(const std::string & path)
	: shader("res/shaders/basic.shader"), 
	verticiesNumber(0), 
	texture("res/objects/triangle.png")
{
	shader.Unbind();
	LoadObjectFromFile(path);

	VertexBuffer vb(verticies, verticiesNumber * sizeof(float));
	VertexBufferLayout layout;
	layout.Push<float>(2);
	layout.Push<float>(2);
	vertexArray.AddBuffer(vb, layout);
	vertexArray.Unbind();
}
CAT::Object::Object(Properties props)
	:shader(props.shaderPath == "" ?"res/shaders/basic.shader": props.shaderPath),
	texture(props.texturePath)
{
	shader.Unbind();

	VertexBufferLayout layout;
	layout.Push<float>(3);
	layout.Push<float>(2);

	LoadObjectFromFile(props.objectPath);
	VertexBuffer vb(verticies, verticiesNumber * sizeof(float));

	vertexArray.AddBuffer(vb, layout);
	vertexArray.Unbind();
}

CAT::Object::~Object()
{
}

CAT::Container * CAT::Object::AddChild(CAT::Container & container)
{
	std::cout << "UNABLE TO ADD CHILD!" << std::endl;
	return nullptr;
}

void CAT::Object::LoadObjectFromFile(const std::string & path)
{
	std::ifstream file(path);
	std::string output;
	std::string content;
	if (!file.is_open()) {
		std::cout << path << std::endl;
	}
	while (std::getline(file, content)) {
		output += content;
		trianglesNumber++;
	}
	verticiesNumber = trianglesNumber * 5;
	std::vector<std::string> result;
	std::istringstream iss(output);
	for (std::string output; iss >> output; )
		result.push_back(output);

	for (int i = 0; i < verticiesNumber; i++) {
		verticies[i] = (float)atof(result[i].c_str()); 
	}
}

void CAT::Object::UpdateTransform(glm::mat4 projection, glm::mat4 view, glm::mat4 model)
{
	MVP = projection * view * GetMVPMatrix(model);
}

void CAT::Object::Draw()
{
	texture.Bind();
	shader.Bind();
	shader.SetUniformMat4f("u_MVP", MVP);
	vertexArray.Bind();
	GLCall(glDrawArrays(GL_TRIANGLES, 0, trianglesNumber));
}
