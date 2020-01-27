#include "Object.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
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
	LoadObj(path);

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
	LoadObj(props.objectPath);

	VertexBufferLayout layout;
	layout.Push<float>(3);
	layout.Push<float>(2);
	layout.Push<float>(3);

	VertexBuffer vb(verticies, verticiesNumber * sizeof(float));

	vertexArray.AddBuffer(vb, layout);
	vertexArray.Unbind();
}

CAT::Object::~Object()
{
	delete[] verticies;
}

CAT::Container * CAT::Object::AddChild(CAT::Container & container)
{
	std::cout << "UNABLE TO ADD CHILD!" << std::endl;
	return nullptr;
}

void CAT::Object::LoadObj(const std::string & path)
{
	std::ifstream file(path);
	std::string output;
	std::string content;
	if (!file.is_open()) {
		std::cout << path << std::endl;
	}
	while (std::getline(file, content)) {
		output += content + " end ";
	}
	std::vector<std::string> vert;
	std::vector<std::string> texture;
	std::vector<std::string> norm;
	std::vector<std::string> assembly;
	std::istringstream iss(output);

	float it = 4;

	for (std::string output; iss >> output; ) {
		if (output == "v") {
			it = 0;
		}
		else if (output == "vt") {
			it = 1;
		}
		else if (output == "vn") {
			it = 2;
		}
		else if (output == "f") {
			it = 3;
		}
		else if (output == "end") {
			it = 4;
		}
		else if (it == 0) {
			vert.push_back(output);
		}
		else if (it == 1) {
			texture.push_back(output);
		}
		else if (it == 2) {
			norm.push_back(output);
		}
		else if (it == 3) {
			assembly.push_back(output);
		}
	}

	verticies = new float[assembly.size() * 8];
	verticiesNumber = 0;
	trianglesNumber = assembly.size();
	for (int i = 0; i < assembly.size(); i++) {
		std::replace(assembly[i].begin(), assembly[i].end(), '/', ' ');

		std::vector<int> array;
		std::stringstream ss(assembly[i]);
		int temp;
		while (ss >> temp)
			array.push_back(temp);
		
		int startIt, j;
		for (j = 0, startIt = 0; j < 3; j++, startIt++) {
			verticies[i * 8 + startIt] = (float)atof(vert[(array[0] - 1)*3 + j].c_str());
			verticiesNumber++;
		}
		for (j = 0; j < 2; j++, startIt++) {
			verticies[i * 8 + startIt] = (float)atof(texture[(array[1] - 1) * 2 + j].c_str());
			verticiesNumber++;
		}
		for (j = 0; j < 3; j++, startIt++) {
			verticies[i * 8 + startIt] = (float)atof(norm[(array[2] - 1) * 3 + j].c_str());
			verticiesNumber++;
		}
	}
}

void CAT::Object::Update()
{
	rotate += 0.02;
	SetRotation(glm::vec3(0.0, rotate, 0.0));
}

void CAT::Object::UpdateTransform(glm::mat4 projection, glm::mat4 view, glm::mat4 model)
{
	m_Projection = projection;
	m_View = view;
	m_Model = GetMVPMatrix(model);
}

void CAT::Object::Draw()
{
	texture.Bind();
	shader.Bind();
	shader.SetUniformMat4f("u_Projection", m_Projection);
	shader.SetUniformMat4f("u_View", m_View);
	shader.SetUniformMat4f("u_Model", m_Model);

	vertexArray.Bind();
	GLCall(glDrawArrays(GL_TRIANGLES, 0, trianglesNumber));
}
