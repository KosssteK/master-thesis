#include "Stage.h"

Stage::Stage()
	:
	klaudiaSign(CAT::Properties(
			"res/objects/cube.obj",
			"res/objects/sun.jpg",
			"res/shaders/blin_phong.shader"
		)),
	//piramidObj(CAT::Properties(
	//		"res/objects/piramid.txt",
	//		"res/objects/multicolor.png",
	//		"res/shaders/texture.shader"
	//	)),
	//bananaObj(CAT::Properties(
	//	"res/objects/piramid.txt",
	//	"res/objects/banana.jpg",
	//	"res/shaders/texture.shader"
	//)),
	//lightSource(CAT::Properties(
	//	"res/objects/piramid.txt",
	//	"res/objects/multicolor.png",
	//	"res/shaders/texture.shader"
	//)),
	originLine("res/objects/originLines.txt"),
	skybox("res/objects/skybox/glacier")
{
	klaudiaSign.SetPosition(glm::vec3(0.0f, 1.0f, -4.0f));
	//klaudiaSign.SetRotation(glm::vec3(0.0f, 0.0f, -45.0f));
	//klaudiaSign.SetScale(glm::vec3(2.0f, 2.0f, 2.0f));
	//
	//piramidObj.SetPosition(glm::vec3(2.0f, 0.0f, 0.0f));
	//piramidObj.SetRotation(glm::vec3(1.0f, 1.0f, 45.0f));
	//
	//bananaObj.SetPosition(glm::vec3(-2.0f, 0.0f, 0.0f));
	//bananaObj.SetRotation(glm::vec3(-1.0f, -1.0f, -45.0f));
	//
	//lightSource.SetPosition(glm::vec3(2.0f, 0.0f, 3.0f));
	//lightSource.SetRotation(glm::vec3(0.0f, 0.0f, 0.0f));
	//lightSource.SetScale(glm::vec3(0.3f, 0.3f, 0.3f));


	AddChild(skybox);
	AddChild(originLine);
	AddChild(klaudiaSign);
	//AddChild(piramidObj);
	//AddChild(bananaObj);
	//AddChild(lightSource);
}


Stage::~Stage()
{
}
