#include "Quaternion.h"
#include "Vector3.h"

math::Quaternion::Quaternion()
    :x(0)
    ,y(0)
    ,z(0)
    ,w(1)
{
}

math::Quaternion::Quaternion(float x, float y, float z, float w)
    :x(x)
    ,y(y)
    ,z(z)
    ,w(w)
{
}
math::Quaternion math::Quaternion::Identity()
{
    return Quaternion(1.0, 0.0f, 0.0f,0.0f);
}
/// <summary>
/// 正規化
/// </summary>
/// <returns></returns>
math::Quaternion math::Quaternion::Normalize() const
{
    float length = sqrt(x * x + y * y + z * z + w * w);
    return Quaternion(x / length, y / length, z / length, w / length);
}
/// <summary>
/// 逆クオータニオン
/// </summary>
/// <returns></returns>
math::Quaternion math::Quaternion::Inverse() const
{
    return Quaternion(-x, -y, -z, w).Normalize();
}

/// <summary>
/// <summary>
/// クオータニオンの積
/// </summary>
/// <param name="q"></param>
/// <returns></returns>
math::Quaternion math::Quaternion::operator*(const Quaternion& q) const
{
    return Quaternion(
        w * q.x + x * q.w + y * q.z - z * q.y,
        w * q.y - x * q.z + y * q.w + z * q.x,
        w * q.z + x * q.y - y * q.x + z * q.w,
        w * q.w - x * q.x - y * q.y - z * q.z
    
    );
}

math::Quaternion math::Quaternion::VectorToQuaternion(const math::Vector3& v)
{
    return Quaternion(v.vec.x, v.vec.y, v.vec.z, 0.0f);
}

/// 回転の適用
/// </summary>
/// <param name="v"></param>
/// <returns></returns>
math::Vector3 math::Quaternion::Apply(const Vector3& v) const
{
    /*VECTOR vVector = v.vec;
    VECTOR qVector = { x,y,z };
    VECTOR qConjugete = { -x, -y, -z };
    VECTOR qW = { w,w,w };

    VECTOR rotated = VRotQ(vVector, qVector, qConjugete, qW);
    return Vector3(qr.x, qr.y, qr.z);*/
    
    Quaternion q_v = math::Quaternion::VectorToQuaternion(v);
    Quaternion q_conj = Inverse();
    Quaternion q_rotated = *this * q_v * q_conj;

    return Vector3(q_rotated.x, q_rotated.y, q_rotated.z );
}

/// <summary>
/// クオータニオンから回転行列を作成
/// </summary>
/// <returns></returns>
MATRIX math::Quaternion::ToMatrix() const
{
    return MATRIX();
}
/// <summary>
/// 回転を生成
/// </summary>
/// <param name="axis"></param>
/// <param name="angle"></param>
/// <returns></returns>
math::Quaternion math::Quaternion::FromAxisAngle(const VECTOR& axis, float angle)
{
    float halfAngle = angle * 0.5f;
    float s = sin(halfAngle);
    return Quaternion(axis.x * s, axis.y * s, axis.z * s, cos(halfAngle));
}
