#pragma once
#include "engine/Container.h"
#include "engine/Object.h"
#include "Earth.h"

class Sun : public CAT::Container
{
public:
	CAT::Object sun;
	Earth earth;
	float rotation;

	Sun();
	~Sun();
	void Update() override;
};

