#include "Moon.h"

Moon::Moon()
	:moon(CAT::Properties(
		"res/objects/sphere.obj",
		"res/objects/moon.jpg",
		"res/objects/moon.jpg",
		"res/objects/moon.jpg",
		"res/objects/moon.jpg",
		"res/shaders/blin_phong.shader"
	))
{
	SetPosition(glm::vec3(10.0f, 0.0f, 0.0f));
	AddChild(moon);
}

Moon::~Moon()
{
}
