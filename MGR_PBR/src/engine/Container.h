#pragma once
#include <vector>
#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include "vendor/glm/gtx/rotate_vector.hpp"

namespace CAT {
	class Container {

	private:
		std::vector<CAT::Container*> children;

		glm::vec3 position;
		glm::vec3 rotation;
		glm::vec3 scale;

	public:
		Container();
		~Container();
		//visual
		void SetPosition(glm::vec3 newPosition);
		void SetRotation(glm::vec3 newRotation);
		void SetScale(glm::vec3 newScale);

		//engine
		CAT::Container* AddChild(CAT::Container &container);
		glm::mat4 GetMVPMatrix(glm::mat4 parentMVP);
		virtual void UpdateTransform(glm::mat4 parentMVP);
		virtual void Draw();
	};
}