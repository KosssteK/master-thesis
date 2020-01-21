#pragma once
#include "Container.h"
#include "render/Shader.h"
#include "render/VertexArray.h"
#include "render/Texture.h"
#include "render/Helpers.h"

namespace CAT{
	class Object : public Container
	{
	private:
		VertexArray vertexArray;
		Shader shader;
		Texture texture;
		float verticies[71040];
		unsigned int verticiesNumber;
		unsigned int trianglesNumber;

		glm::vec3 position;
		glm::vec3 rotation;
		glm::vec3 scale;

	public:
		Object();
		Object(const std::string& path);
		Object(Properties props);
		~Object();

		//engine stuff
		CAT::Container* addChild(CAT::Container &container);
		void LoadObjectFromFile(const std::string & path);
		void UpdateTransform(glm::mat4 parentMVP) override;
		void Draw() override;
	};

}
