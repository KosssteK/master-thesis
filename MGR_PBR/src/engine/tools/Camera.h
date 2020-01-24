#pragma once
#include "../vendor/glm/glm.hpp"
#include "GLFW/glfw3.h"


namespace CAT {
	class Camera
	{
	public:
		float m_CameraSpeed;
		glm::vec3 m_CameraPosition;
		glm::vec3 m_ViewDirection;
		glm::vec3 m_SideDirection;
		glm::vec3 m_UP;

		glm::vec2 m_OldMousePosition;

		bool mouseButtonJustPressed = true;

		Camera();
		~Camera();

		glm::mat4 GetProjectionMatrix();
		glm::mat4 GetViewMatrix();
		void UpdateCamera(GLFWwindow* window);
		void SetCameraView(glm::vec2& delta);

		void MoveForward();
		void MoveBackward();
		void MoveLeft();
		void MoveRight();
		void MoveUp();
		void MoveDown();
	};
}
