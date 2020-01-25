#pragma once
#include "Container.h"
#include "render/VertexArray.h"
#include "render/Shader.h"
#include "vendor/glm/glm.hpp"

namespace CAT {
	class Line : public Container
	{
	public:
		VertexArray vertexArray;
		Shader shader;
		float verticies[500];
		unsigned int verticiesNumber;
		unsigned int linesNumber;
		glm::mat4 MVP;

		Line();
		Line(const std::string& path);
		~Line();

		CAT::Container* AddChild(CAT::Container &container);
		void LoadObjectFromFile(const std::string & path);
		void UpdateTransform(glm::mat4 projection, glm::mat4 view, glm::mat4 model) override;
		void Draw();
	};
}

