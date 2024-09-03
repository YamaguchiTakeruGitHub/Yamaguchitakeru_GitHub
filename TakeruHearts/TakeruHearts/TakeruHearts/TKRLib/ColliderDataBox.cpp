#include "ColliderDataBox.h"

TKRLib::ColliderDataBox::ColliderDataBox()
	: TKRLib::ColliderData(ColliderData::Kind::Box)
	, center(VGet(0.0f,0.0f,0.0f))
	, e(VGet(0.0f,0.0f,0.0f))
{
	u[0] = VGet(1.0f, 0.0f, 0.0f);//XŽ²•ûŒü
	u[1] = VGet(0.0f, 1.0f, 0.0f);//YŽ²•ûŒü
	u[2] = VGet(0.0f, 0.0f, 1.0f);//ZŽ²•ûŒü
}
