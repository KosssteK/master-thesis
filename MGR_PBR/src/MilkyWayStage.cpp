#include "MilkyWayStage.h"

MilkyWayStage::MilkyWayStage()
	:originLine("res/objects/originLines.txt"),
	skybox("res/skybox/vr")
{
	AddChild(skybox);
	AddChild(sun);
	AddChild(originLine);
}

MilkyWayStage::~MilkyWayStage()
{
}
