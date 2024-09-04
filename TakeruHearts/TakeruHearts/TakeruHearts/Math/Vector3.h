#pragma once
#include "DxLib.h"

namespace math
{
	class Vector3
	{
	public:
		VECTOR vec;

		Vector3() : vec({ 0,0,0 }) {}
		Vector3(float x, float y, float z);

		static Vector3 FromDxVector(const VECTOR& v);

		VECTOR ToDxVector() const;

		Vector3 Normalize() const;

		Vector3 operator+(const Vector3& other)const;

		Vector3 operator*(float scalar)const;

		float Dot(const Vector3& other) const;

		Vector3 Cross(const Vector3& other)const;

		float Length()const;

	};

}
