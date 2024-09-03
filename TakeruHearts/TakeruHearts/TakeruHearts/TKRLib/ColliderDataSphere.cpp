#include "ColliderDataSphere.h"
#include "../TKRLib/TKRLib.h"
#include <DxLib.h>

TKRLib::ColliderDataSphere::ColliderDataSphere()
	:TKRLib::ColliderData(ColliderData::Kind::Sphere)
	, radius(0.0f)
{
}
