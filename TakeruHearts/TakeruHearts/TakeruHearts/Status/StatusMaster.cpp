#include "StatusMaster.h"

Status::StatusMaster::StatusMaster()
	:HitPoint(0.0f)
	, MagicPoint(0.0f)
{
}

void Status::StatusMaster::Init()
{
	HitPoint = 0.0f;
	MagicPoint = 0.0f;
}
