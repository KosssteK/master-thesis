#pragma once
#include "../vendor/glm/glm.hpp"
#include "GLFW/glfw3.h"


namespace CAT {
	class Camera
	{
	private: 
		Camera();
		Camera(const Camera &);
	public:
		static Camera & getSingleton()
		{
			static Camera singleton;
			return singleton;
		}

		float m_CameraSpeed;
		glm::vec3 m_CameraPosition;
		glm::vec3 m_ViewDirection;
		glm::vec3 m_SideDirection;
		glm::vec3 m_UP;

		glm::vec2 m_OldMousePosition;

		bool mouseButtonJustPressed = true;

		glm::mat4 GetProjectionMatrix();
		glm::mat4 GetViewMatrix();
		void UpdateCamera(GLFWwindow* window);
		void SetCameraView(glm::vec2& delta);
		glm::vec3 GetCameraPosition();

		void MoveForward();
		void MoveBackward();
		void MoveLeft();
		void MoveRight();
		void MoveUp();
		void MoveDown();
	};
}
