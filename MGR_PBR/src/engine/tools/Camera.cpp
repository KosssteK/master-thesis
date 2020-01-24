#include "Camera.h"

#include "../vendor/glm/gtc/matrix_transform.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include "../vendor/glm/gtx/rotate_vector.hpp"


CAT::Camera::Camera()
	: m_CameraSpeed(0.2f)
{
	m_CameraPosition = glm::vec3(0.0f, 0.0f, 4.0f);
	m_ViewDirection = glm::vec3(0.0f, 0.0f, -1.0f);
	m_UP = glm::vec3(0.0f, 1.0f, 0.0f);
	m_SideDirection = glm::cross(m_ViewDirection, m_UP);
}


CAT::Camera::~Camera()
{
}

glm::mat4 CAT::Camera::GetViewMatrix()
{
	return glm::lookAt(m_CameraPosition, m_CameraPosition + m_ViewDirection, m_UP);
}

void CAT::Camera::UpdateCamera(GLFWwindow * window)
{
	int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
	if (state == GLFW_PRESS)
	{
		float sensitivity = 10;
		double xpos, ypos;
		glm::vec2 delta;
		glfwGetCursorPos(window, &xpos, &ypos);
		glm::vec2 newMousePosition(xpos, ypos);

		if (mouseButtonJustPressed) {
			delta = glm::vec2(0);
			mouseButtonJustPressed = false;
		}
		else {
			delta = newMousePosition - m_OldMousePosition;
		}
		delta *= sensitivity;
		SetCameraView(delta);
		m_OldMousePosition = newMousePosition;
	}

	if (state == GLFW_RELEASE)
	{
		mouseButtonJustPressed = true;
	}

	state = glfwGetKey(window, GLFW_KEY_W);
	if (state == GLFW_PRESS)
	{
		MoveForward();
	}
	state = glfwGetKey(window, GLFW_KEY_S);
	if (state == GLFW_PRESS)
	{
		MoveBackward();
	}
	state = glfwGetKey(window, GLFW_KEY_D);
	if (state == GLFW_PRESS)
	{
		MoveRight();
	}
	state = glfwGetKey(window, GLFW_KEY_A);
	if (state == GLFW_PRESS)
	{
		MoveLeft();
	}

}

glm::mat4 CAT::Camera::GetProjectionMatrix()
{
	return glm::perspective(glm::radians(90.0f), 4.0f / 3.0f, 0.1f, 1000.f);
}

void CAT::Camera::SetCameraView(glm::vec2 & delta)
{
	m_ViewDirection = glm::mat3(glm::rotate(-delta.x * 0.0012f, m_UP)) * m_ViewDirection;
	m_SideDirection = glm::cross(m_UP, m_ViewDirection);
	m_ViewDirection = glm::mat3(glm::rotate(delta.y * 0.0012f, m_SideDirection)) * m_ViewDirection;

		//FREE CAMERA
	//m_ViewDirection = glm::mat3(glm::rotate(-delta.x * 0.002f, m_UP)) * m_ViewDirection;
	//m_SideDirection = glm::cross(m_ViewDirection, m_UP);
	//m_ViewDirection = glm::mat3(glm::rotate(delta.y * 0.002f, m_SideDirection)) * m_ViewDirection;
	//m_UP = glm::cross(m_SideDirection, m_ViewDirection);
	

}

void CAT::Camera::MoveForward()
{
	m_CameraPosition += m_ViewDirection * m_CameraSpeed;
}

void CAT::Camera::MoveBackward()
{
	m_CameraPosition -= m_ViewDirection * m_CameraSpeed;
}

void CAT::Camera::MoveLeft()
{
	m_CameraPosition += m_SideDirection * m_CameraSpeed;
}

void CAT::Camera::MoveRight()
{
	m_CameraPosition -= m_SideDirection * m_CameraSpeed;
}

void CAT::Camera::MoveUp()
{
	m_CameraPosition -= m_UP * m_CameraSpeed;
}

void CAT::Camera::MoveDown()
{
	m_CameraPosition += m_UP * m_CameraSpeed;
}
