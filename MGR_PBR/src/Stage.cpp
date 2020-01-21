#include "Stage.h"

Stage::Stage()
	:klaudiaSign(CAT::Properties(
			"res/objects/triangle.txt",
			"res/objects/triangle.png",
			"res/shaders/texture.shader"
		)),
	piramidObj(CAT::Properties(
			"res/objects/piramid.txt",
			"res/objects/multicolor.png",
			"res/shaders/texture.shader"
		)),
	bananaObj(CAT::Properties(
			"res/objects/banana.txt",
			"res/objects/banana.jpg",
			"res/shaders/texture.shader"
		))
{
	//klaudiaSign.SetRotation(glm::vec3(0.0f, 180.0f, 0.0f));
	//piramidObj.SetRotation(glm::vec3(45.0f, 45.0f, 45.0f));
	piramidObj.SetPosition(glm::vec3(2.0f, 0.0f, 0.0f));

	//AddChild(klaudiaSign);
	AddChild(piramidObj);
	//AddChild(bananaObj);
}


Stage::~Stage()
{
}
