#pragma once
#include "engine/Container.h"
#include "engine/Object.h"
#include "engine/render/Helpers.h"
#include "engine/Line.h"

class Stage :public CAT::Container
{
public:
	CAT::Object klaudiaSign;
	CAT::Object piramidObj;
	CAT::Object bananaObj;
	CAT::Object lightSource;
	CAT::Line originLine;

	Stage();
	~Stage();
};