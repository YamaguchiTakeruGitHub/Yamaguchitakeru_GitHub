#pragma once
#include "ColliderData.h"
#include "DxLib.h"

namespace TKRLib
{
	class ColliderData;
	class ColliderDataBox : public ColliderData
	{
	public:
		ColliderDataBox();

		VECTOR center;
		VECTOR u[3];
		VECTOR e;

	};
}

