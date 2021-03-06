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
		Texture roughness;
		Texture metallic;
		Texture normals;
		float* verticies;
		unsigned int verticiesNumber;
		unsigned int trianglesNumber;
		glm::mat4 m_Projection;
		glm::mat4 m_View;
		glm::mat4 m_Model;
		float rotate = 0;

		Object();
		Object(const std::string& path);
		Object(Properties props);
		~Object();

		//engine stuff
		CAT::Container* AddChild(CAT::Container &container);
		void LoadObj(const std::string & path);

		void Update() override;
		void UpdateTransform(glm::mat4 projection, glm::mat4 view, glm::mat4 model) override;
		void Draw() override;
	};

}
