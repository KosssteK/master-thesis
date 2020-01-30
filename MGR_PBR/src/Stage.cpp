#include "Stage.h"

Stage::Stage()
	:
	klaudiaSign(CAT::Properties(
		"res/objects/sphereHigh.obj",
		"res/objects/red.jpg",
		"res/shaders/pbr.shader"
	)),
	originLine("res/objects/originLines.txt"),
	skybox("res/skybox/glacier")
{
	klaudiaSign.SetPosition(glm::vec3(0.0f, 1.0f, -8.0f));

	AddChild(skybox);
	AddChild(originLine);
	AddChild(klaudiaSign);
}


Stage::~Stage()
{
}
