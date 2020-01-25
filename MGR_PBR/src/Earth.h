#pragma once
#include "engine/Container.h"
#include "engine/Object.h"
#include "Moon.h"

class Earth : public CAT::Container
{
public:
	CAT::Object earth;
	Moon moon;
	float rotation;

	Earth();
	~Earth();

	void Update() override;
};

