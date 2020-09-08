#include "Stage.h"

Stage::Stage()
	:
	klaudiaSign(CAT::Properties(
		"res/objects/sphereHi1.obj",
		"res/objects/rustediron2_basecolor.png",
		"res/objects/rustediron2_roughness.png",
		"res/objects/rustediron2_metallic.png",
		"res/objects/rustediron2_normal.png",
		"res/shaders/pbr.shader"
	)),
	originLine("res/objects/originLines.txt"),
	skybox("res/skybox/glacier")
{
	klaudiaSign.SetPosition(glm::vec3(0.0f, 1.0f, -8.0f));
	//klaudiaSign.SetScale(glm::vec3(2.0f, 2.0f, 2.0f));

	//AddChild(skybox);
	AddChild(originLine);
	AddChild(klaudiaSign);
}


Stage::~Stage()
{
}
