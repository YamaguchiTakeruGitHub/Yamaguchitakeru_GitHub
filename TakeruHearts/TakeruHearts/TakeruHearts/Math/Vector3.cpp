#include "Vector3.h"

math::Vector3::Vector3(float x, float y, float z)
	: vec({x,y,z})
{
}
/// <summary>
/// Dxlib::VECTORからVector3へ変換
/// </summary>
/// <param name="v"></param>
/// <returns></returns>
math::Vector3 math::Vector3::FromDxVector(const VECTOR& v)
{
	return Vector3(v.x, v.y, v.z);
}
/// <summary>
///Vetor3からDxlib::VECTORへ変換
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
/// ベクトルの正規化
/// </summary>
/// <returns></returns>
math::Vector3 math::Vector3::Normalize() const
{
	VECTOR normalized = VNorm(vec);
	return Vector3(normalized.x, normalized.y, normalized.z);
}
/// <summary>
/// ベクトルの加算
/// </summary>
/// <param name="other"></param>
/// <returns></returns>
math::Vector3 math::Vector3::operator+(const Vector3& other) const
{
	VECTOR result = VAdd(vec, other.vec);
	return Vector3(result.x, result.y, result.z);
}
/// <summary>
/// ベクトルのスカラー乗算
/// </summary>
/// <param name="scalar"></param>
/// <returns></returns>
math::Vector3 math::Vector3::operator*(float scalar) const
{
	
	VECTOR result = VScale(vec, scalar);
	return Vector3(result.x, result.y, result.z);
}
/// <summary>
/// ベクトル内積
/// </summary>
/// <param name="other"></param>
/// <returns></returns>
float math::Vector3::Dot(const Vector3& other) const
{
	return VDot(vec, other.vec);
}
/// <summary>
/// ベクトル外積
/// </summary>
/// <param name="other"></param>
/// <returns></returns>
math::Vector3 math::Vector3::Cross(const Vector3& other) const
{
	VECTOR result = VCross(vec, other.vec);
	return Vector3(result.x, result.y, result.z);
}
/// <summary>
/// ベクトルの長さ
/// </summary>
/// <returns></returns>
float math::Vector3::Length() const
{
	return VSize(vec);
}
