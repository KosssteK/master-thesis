#include "Sun.h"

Sun::Sun()
	:sun(CAT::Properties(
		"res/objects/piramid.txt",
		"res/objects/multicolor.png",
		"res/shaders/texture.shader"
	)),
	rotation(0)
{
	sun.SetScale(glm::vec3(4.0f, 4.0f, 4.0f));
	AddChild(sun);
	AddChild(earth);
	SetRotation(glm::vec3(0.0f, 90.0f, 0.0f));
}

Sun::~Sun()
{
}

void Sun::Update()
{
	rotation += 0.06;
	SetRotation(glm::vec3(0.0f, rotation, 0.0f));
	if (rotation == 6.28) {
		rotation = 0;
	}
	for (int i = 0; i < children.size(); i++) {
		children[i]->Update();
	}
}
