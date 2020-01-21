#include "Container.h"
#include <iostream>

CAT::Container::Container()
	:position(glm::vec3(0.0f, 0.0f, 0.0f)),
	rotation(glm::vec3(0.0f, 0.0f, 0.0f)),
	scale(glm::vec3(1.0f, 1.0f, 1.0f))
{
}

CAT::Container::~Container()
{
}

void CAT::Container::SetPosition(glm::vec3 newPosition)
{
	std::cout << "Set position" << std::endl;
	position = newPosition;
}

void CAT::Container::SetRotation(glm::vec3 newRotation)
{
	std::cout << "Set rotation" << std::endl;
	rotation = newRotation;
}

void CAT::Container::SetScale(glm::vec3 newScale)
{
	scale = newScale;
}


CAT::Container * CAT::Container::AddChild(CAT::Container & container)
{
	children.push_back(&container);

	return &container;
}

glm::mat4 CAT::Container::GetMVPMatrix(glm::mat4 parentMVP)
{
	glm::mat4 projection = glm::mat4(1.0f);

	glm::mat4 view = glm::mat4(1.0f);

	glm::mat4 modelTranslate = glm::translate(glm::mat4(1.0f), position);
	glm::mat4 modelRotateX = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.x), glm::vec3(1, 0, 0));
	glm::mat4 modelRotateY = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.y), glm::vec3(0, 1, 0));
	glm::mat4 modelRotateZ = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.z), glm::vec3(0, 0, 1));
	glm::mat4 modelScaleX = glm::scale(glm::mat4(1.0f), glm::vec3(scale.x, 1, 1));
	glm::mat4 modelScaleY = glm::scale(glm::mat4(1.0f), glm::vec3(1, scale.y, 1));
	glm::mat4 modelScaleZ = glm::scale(glm::mat4(1.0f), glm::vec3(1, 1, scale.z));

	glm::mat4 model =
		modelTranslate *
		modelRotateX * modelRotateY * modelRotateZ *
		modelScaleX* modelScaleY* modelScaleZ;

	glm::mat4 mvp = projection * view * model;

	//debug 

	return parentMVP * model;
}

void CAT::Container::UpdateTransform(glm::mat4 parentMVP)
{
	glm::mat4 mvp = GetMVPMatrix(parentMVP);
	//std::cout << "UPDATE TRANSFORM CONTAINER" << std::endl;
	for (int i = 0; i < children.size(); i++) {
		children[i]->UpdateTransform(mvp);
	}
}

void CAT::Container::Draw()
{
	//std::cout << "draw CAT::CONTAINER" << std::endl;
	for (int i = 0; i < children.size(); i++) {
		children[i]->Draw();
	}
}
