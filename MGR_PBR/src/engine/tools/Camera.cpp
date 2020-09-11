#include "Camera.h"
#include <iostream>

#include "../vendor/glm/gtc/matrix_transform.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include "../vendor/glm/gtx/rotate_vector.hpp"


CAT::Camera::Camera()
	: m_CameraSpeed(0.01f)
{
	//m_CameraPosition = glm::vec3(4.0f, 4.0f, 4.0f);
	m_CameraPosition = glm::vec3(0.0f, 0.0f, 0.0f);
	m_ViewDirection = glm::vec3(0.0f, 0.0f, -1.0f);
	m_UP = glm::vec3(0.0f, 1.0f, 0.0f);
	m_SideDirection = -glm::cross(m_ViewDirection, m_UP);
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

	state = glfwGetKey(window, GLFW_KEY_K);
	if (state == GLFW_PRESS)
	{
		m_CameraPosition = glm::vec3(-4.77f,-2.60f,-10.0f);
		m_ViewDirection = glm::vec3(0.5955f,0.2377f, -0.7673f);
	}


	state = glfwGetKey(window, GLFW_KEY_L);
	if (state == GLFW_PRESS)
	{
		m_CameraPosition = glm::vec3(-1.0f, -1.0f, -9.0f);
		m_ViewDirection = glm::vec3(0.0f, 0.0f, -1.0f);
	}


	state = glfwGetKey(window, GLFW_KEY_I);
	if (state == GLFW_PRESS)
	{
		m_CameraPosition = glm::vec3(-0.2198f, 3.1057f, -11.0873f);
		m_ViewDirection = glm::vec3(-0.1535f, -0.5141f, -0.8438f);
	}

	//std::cout << m_CameraPosition.x << "  " << m_CameraPosition.y << "  " << m_CameraPosition.z << "  " << std::endl;

	//std::cout << m_ViewDirection.x << "  " << m_ViewDirection.y << "  " << m_ViewDirection.z << "  " << std::endl;
}

glm::mat4 CAT::Camera::GetProjectionMatrix()
{
	return glm::perspective(glm::radians(45.0f), 16.0f/ 9.0f, 0.1f, 1000.f);
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

glm::vec3 CAT::Camera::GetCameraPosition()
{
	return m_CameraPosition;
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
