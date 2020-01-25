#include "Earth.h"

Earth::Earth()
	:earth(CAT::Properties(
		"res/objects/piramid.txt",
		"res/objects/multicolor.png",
		"res/shaders/texture.shader"
	)),
	rotation(0)
{
	earth.SetScale(glm::vec3(2.0f, 2.0f, 2.0f));
	SetRotation(glm::vec3(0.0f, 90.0f, 0.0f));
	SetPosition(glm::vec3(40.0f, 0.0f, 0.0f));
	AddChild(earth);
	AddChild(moon);
}

Earth::~Earth()
{
}

void Earth::Update()
{
	rotation -= 0.09;
	SetRotation(glm::vec3(0.0f, rotation, 0.0f));
	if (rotation == 6.28) {
		rotation = 0;
	}
	for (int i = 0; i < children.size(); i++) {
		children[i]->Update();
	}
}
