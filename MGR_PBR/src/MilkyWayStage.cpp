#include "MilkyWayStage.h"

MilkyWayStage::MilkyWayStage()
	:originLine("res/objects/originLines.txt")
{
	AddChild(skybox);
	AddChild(sun);
	AddChild(originLine);
}

MilkyWayStage::~MilkyWayStage()
{
}
