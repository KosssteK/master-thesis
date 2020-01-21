#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include <fstream>
#include <string>
#include <sstream>

#include "engine/Renderer.h"
#include "engine/Container.h"
#include "engine/Object.h"

#include "engine/render/Helpers.h"
#include "Stage.h"


int main() {
	
	CAT::Renderer renderer;
	Stage stage;
	renderer.AddChild(stage);		
	renderer.StartMainLoop();

	return 0;
}