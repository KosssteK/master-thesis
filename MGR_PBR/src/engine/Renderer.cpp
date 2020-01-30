#include "Renderer.h"
#include <iostream>
#include "render/Helpers.h"

CAT::Renderer::Renderer() {

	/* Initialize the library */
	if (!glfwInit())
		std::cout << "error during glfwInit()" << std::endl;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(1280, 720, "Hello World", NULL, NULL);
	if (!window)
	{
		std::cout << "glfwTerminate()" << std::endl;
		glfwTerminate();
	}

	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK) {
		std::cout << "error" << std::endl;
	}

	std::cout << glGetString(GL_VERSION) << std::endl;




	GLCall(glEnable(GL_DEPTH_TEST));
	GLCall(glDepthFunc(GL_LEQUAL));
	//GLCall(glEnable(GL_CULL_FACE));
	GLCall(glFrontFace(GL_CW));
	GLCall(glCullFace(GL_BACK));
	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	GLCall(glClearColor(0.2f, 0.3f, 0.8f, 1.0f));
}

CAT::Renderer::~Renderer()
{
	glfwTerminate();
}

void CAT::Renderer::StartMainLoop()
{
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		Camera::getSingleton().UpdateCamera(window);

		UpdateTransform();
		Draw();
		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

}

CAT::Container * CAT::Renderer::AddChild(CAT::Container &container)
{
	children.push_back(&container);

	return &container;
}

void CAT::Renderer::UpdateTransform()
{
	//std::cout << "UPDATE TRANSFORM RENDERER" << std::endl;
	r += 0.01;
	glm::mat4 projection = Camera::getSingleton().GetProjectionMatrix();
	glm::mat4 view = Camera::getSingleton().GetViewMatrix();
	glm::mat4 model(1.0f);


	for (int i = 0; i < children.size(); i++) {
		children[i]->UpdateTransform(projection, view, model);
	}
}

void CAT::Renderer::Draw()
{
	for (int i = 0; i < children.size(); i++) {
		children[i]->Draw();
	}
}
