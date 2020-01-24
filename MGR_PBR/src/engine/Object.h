#pragma once
#include "Container.h"
#include "render/Shader.h"
#include "render/VertexArray.h"
#include "render/Texture.h"
#include "render/Helpers.h"
#include "vendor/glm/glm.hpp"

namespace CAT{
	class Object : public Container
	{
	public:
		VertexArray vertexArray;
		Shader shader;
		Texture texture;
		float verticies[71040];
		unsigned int verticiesNumber;
		unsigned int trianglesNumber;
		glm::mat4 MVP;

		Object();
		Object(const std::string& path);
		Object(Properties props);
		~Object();

		//engine stuff
		CAT::Container* AddChild(CAT::Container &container);
		void LoadObjectFromFile(const std::string & path);
		void UpdateTransform(glm::mat4 projection, glm::mat4 view, glm::mat4 model) override;
		void Draw() override;
	};

}
