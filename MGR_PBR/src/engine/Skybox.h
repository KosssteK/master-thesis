#pragma once
#include "Container.h"

#include "render/VertexArray.h"
#include "render/SkyboxTexture.h"
#include "render/Shader.h"

namespace CAT {
	class Skybox : public Container
	{
	public:
		VertexArray vertexArray;
		Shader shader;
		SkyboxTexture texture;
		float verticies[500];
		unsigned int verticiesNumber;
		unsigned int trianglesNumber;
		const float m_Size;
		const float m_PositionsCount;
		float m_Positions[108];
		glm::mat4 MVP;

		Skybox();
		~Skybox();

		CAT::Container* AddChild(CAT::Container &container);
		void UpdateTransform(glm::mat4 projection, glm::mat4 view, glm::mat4 model) override;
		void Draw() override;
		float* GetPositions();
		float GetPositionsSize();
	};
}