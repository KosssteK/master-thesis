#include "Line.h"
#include "GL/glew.h"
#include "render/Helpers.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "render/VertexBufferLayout.h"

CAT::Line::Line()
	: shader("res/shaders/color.shader")
{
}

CAT::Line::Line(const std::string & path)
	:verticiesNumber(0),
	shader("res/shaders/color.shader")
{
	shader.Unbind();
	VertexBufferLayout layout;
	layout.Push<float>(3);
	layout.Push<float>(3);

	LoadObjectFromFile(path);
	VertexBuffer vb(verticies, verticiesNumber * sizeof(float));

	vertexArray.AddBuffer(vb, layout);
	vertexArray.Unbind();
}

CAT::Line::~Line()
{
}

CAT::Container * CAT::Line::AddChild(CAT::Container & container)
{
	return nullptr;
}

void CAT::Line::LoadObjectFromFile(const std::string & path)
{
	std::ifstream file(path);
	std::string output;
	std::string content;
	if (!file.is_open()) {
		std::cout << path << std::endl;
	}
	while (std::getline(file, content)) {
		output += content;
		linesNumber++;
	}
	verticiesNumber = linesNumber * 6;
	std::vector<std::string> result;
	std::istringstream iss(output);
	for (std::string output; iss >> output; )
		result.push_back(output);

	for (int i = 0; i < verticiesNumber; i++) {
		verticies[i] = (float)atof(result[i].c_str());
	}
}

void CAT::Line::Update()
{
}

void CAT::Line::UpdateTransform(glm::mat4 projection, glm::mat4 view, glm::mat4 model)
{
	MVP = projection * view * GetMVPMatrix(model);
}

void CAT::Line::Draw()
{
	vertexArray.Bind();
	shader.Bind();
	shader.SetUniformMat4f("u_MVP", MVP);
	glLineWidth(3);
	GLCall(glDrawArrays(GL_LINES, 0, linesNumber));
}