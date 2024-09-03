#pragma once
#include "../TKRLib/ColliderData.h"


namespace TKRLib
{
	class ColliderData;

	class ColliderDataSphere : public ColliderData
	{
	public:
		ColliderDataSphere();

		float radius;
	};
}

