#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "Container.h"
#include "tools/Camera.h"

namespace CAT {
	class Renderer {

	private:
		GLFWwindow* window;
		Camera camera;
		std::vector<CAT::Container*> children;
		float r = 0;
	public:
		Renderer();
		~Renderer();

		void StartMainLoop();
		CAT::Container* AddChild(CAT::Container &container);
		void UpdateTransform();
		void Draw();
	};
}