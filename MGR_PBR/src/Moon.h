#pragma once
#include "engine/Container.h"
#include "engine/Object.h"

class Moon : public CAT::Container
{
public:
	CAT::Object moon;

	Moon();
	~Moon();
};

