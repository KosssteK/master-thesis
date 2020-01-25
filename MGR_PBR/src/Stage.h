#pragma once
#include "engine/Container.h"
#include "engine/Object.h"
#include "engine/render/Helpers.h"
#include "engine/Line.h"
#include "engine/Skybox.h"

class Stage :public CAT::Container
{
public:
	CAT::Object klaudiaSign;
	CAT::Object piramidObj;
	CAT::Object bananaObj;
	CAT::Object lightSource;
	CAT::Line originLine;
	CAT::Skybox skybox;

	Stage();
	~Stage();
};