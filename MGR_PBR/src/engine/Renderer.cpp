#include "Renderer.h"
#include <iostream>
#include "render/Helpers.h"

CAT::Renderer::Renderer() {

	/* Initialize the library */
	if (!glfwInit())
		std::cout << "error during glfwInit()" << std::endl;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
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
	GLCall(glFrontFace(GL_CCW));
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

		//glDrawArrays(GL_TRIANGLES, 0, 3);
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
	glm::mat4 projection = glm::perspective(glm::radians(90.0f), 4.0f / 3.0f, 0.1f, 1000.f);
	//glm::mat4 view = glm::lookAt(glm::vec3(glm::sin(r)*4, 0,glm::cos(r)*4), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	glm::mat4 view = glm::lookAt(glm::vec3(0, 0,4), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	//projection = glm::mat4(1.0f);
	//view = glm::mat4(1.0f);



	glm::mat4 mvp = projection * view;
	for (int i = 0; i < children.size(); i++) {
		children[i]->UpdateTransform(mvp);
	}
}

void CAT::Renderer::Draw()
{
	for (int i = 0; i < children.size(); i++) {
		children[i]->Draw();
	}
}
