#pragma once
#include <cmath>
#include "DxLib.h"


namespace math
{
	class Vector3;
	class Quaternion
	{
	public:
		float w, x, y, z;

		Quaternion();
		Quaternion(float x, float y, float z, float w);
		
		static Quaternion Identity();

		Quaternion Normalize() const;

		Quaternion Inverse() const;

		Quaternion operator*(const Quaternion& q)const;
		
		static Quaternion VectorToQuaternion(const math::Vector3& v);

		Vector3 Apply(const Vector3& v)const;


		MATRIX ToMatrix() const;

		static Quaternion FromAxisAngle(const VECTOR& axis, float angle);

	};
}

