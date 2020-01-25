#include "Moon.h"

Moon::Moon()
	:moon(CAT::Properties(
		"res/objects/piramid.txt",
		"res/objects/multicolor.png",
		"res/shaders/texture.shader"
	))
{
	SetPosition(glm::vec3(10.0f, 0.0f, 0.0f));
	AddChild(moon);
}

Moon::~Moon()
{
}