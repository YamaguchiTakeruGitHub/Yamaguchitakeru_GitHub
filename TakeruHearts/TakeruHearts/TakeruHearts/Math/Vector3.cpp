#include "Vector3.h"

math::Vector3::Vector3(float x, float y, float z)
	: vec({x,y,z})
{
}
/// <summary>
/// Dxlib::VECTOR����Vector3�֕ϊ�
/// </summary>
/// <param name="v"></param>
/// <returns></returns>
math::Vector3 math::Vector3::FromDxVector(const VECTOR& v)
{
	return Vector3(v.x, v.y, v.z);
}
/// <summary>
///Vetor3����Dxlib::VECTOR�֕ϊ�
/// </summary>
/// <returns></returns>
VECTOR math::Vector3::ToDxVector() const
{
	VECTOR v;
	v.x = vec.x;
	v.y = vec.y;
	v.z = vec.z;

	return v;
}

/// <summary>
/// �x�N�g���̐��K��
/// </summary>
/// <returns></returns>
math::Vector3 math::Vector3::Normalize() const
{
	VECTOR normalized = VNorm(vec);
	return Vector3(normalized.x, normalized.y, normalized.z);
}
/// <summary>
/// �x�N�g���̉��Z
/// </summary>
/// <param name="other"></param>
/// <returns></returns>
math::Vector3 math::Vector3::operator+(const Vector3& other) const
{
	VECTOR result = VAdd(vec, other.vec);
	return Vector3(result.x, result.y, result.z);
}
/// <summary>
/// �x�N�g���̃X�J���[��Z
/// </summary>
/// <param name="scalar"></param>
/// <returns></returns>
math::Vector3 math::Vector3::operator*(float scalar) const
{
	
	VECTOR result = VScale(vec, scalar);
	return Vector3(result.x, result.y, result.z);
}
/// <summary>
/// �x�N�g������
/// </summary>
/// <param name="other"></param>
/// <returns></returns>
float math::Vector3::Dot(const Vector3& other) const
{
	return VDot(vec, other.vec);
}
/// <summary>
/// �x�N�g���O��
/// </summary>
/// <param name="other"></param>
/// <returns></returns>
math::Vector3 math::Vector3::Cross(const Vector3& other) const
{
	VECTOR result = VCross(vec, other.vec);
	return Vector3(result.x, result.y, result.z);
}
/// <summary>
/// �x�N�g���̒���
/// </summary>
/// <returns></returns>
float math::Vector3::Length() const
{
	return VSize(vec);
}
