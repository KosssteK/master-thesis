#pragma once
#include "engine/Container.h"
#include "engine/Skybox.h"
#include "engine/Line.h"
#include "Sun.h"

class MilkyWayStage : public CAT::Container
{
public:
	Sun sun;
	CAT::Skybox skybox;
	CAT::Line originLine;

	MilkyWayStage();
	~MilkyWayStage();
};

