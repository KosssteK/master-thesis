#include "MilkyWayStage.h"

MilkyWayStage::MilkyWayStage()
	:originLine("res/objects/originLines.txt"),
	skybox("res/objects/skybox/vr")
{
	AddChild(skybox);
	AddChild(sun);
	AddChild(originLine);
}

MilkyWayStage::~MilkyWayStage()
{
}
