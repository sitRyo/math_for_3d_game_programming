#pragma once

#include "./my_concepts.hpp"
#include "./Vector3.hpp"

// @note templateでN次の正方行列を宣言できるようにすると面白そう
// 3, 4次だけ特殊化して高速化する的な

class Matrix3x3
{
public:
    explicit Matrix3x3(float m11, float m12, float m13, float m21, float m22, float m23, float m31, float m32, float m33);

    // 行列同士の加減算
    Matrix3x3 operator+(const Matrix3x3 &);
    Matrix3x3 operator-(const Matrix3x3 &);
    Matrix3x3 operator*(const Matrix3x3 &);

    // 3x1ベクトルとの乗算
    Vector3 operator*(const Vector3 &);

    // 単位行列への初期化
    void toIdentity();

    // 行列式計算
    float det();

    // 逆行列計算
    Matrix3x3 inv();

    // スカラー演算
    template <IsArithmetic T>
    friend Matrix3x3 operator*(const T lhs, const Matrix3x3 &rhs);
    template <IsArithmetic T>
    friend Matrix3x3 operator/(const Matrix3x3 &lhs, const T rhs);

private:
    // 行列の成分 (行 / 列)
    float m11, m12, m13;
    float m21, m22, m23;
    float m31, m32, m33;
};

//=======================================================================
Matrix3x3::Matrix3x3(float m11, float m12, float m13, float m21, float m22, float m23, float m31, float m32, float m33)
    : m11(m11), m12(m12), m13(m13), m21(m21), m22(m22), m23(m23), m31(m31), m32(m32), m33(m33)
{
}

//=======================================================================
Matrix3x3 Matrix3x3::operator+(const Matrix3x3 &rhs)
{
    m11 += rhs.m11;
    m12 += rhs.m12;
    m13 += rhs.m13;
    m21 += rhs.m21;
    m22 += rhs.m22;
    m23 += rhs.m23;
    m31 += rhs.m31;
    m32 += rhs.m32;
    m33 += rhs.m33;

    return *this;
}

//=======================================================================
Matrix3x3 Matrix3x3::operator-(const Matrix3x3 &rhs)
{
    m11 -= rhs.m11;
    m12 -= rhs.m12;
    m13 -= rhs.m13;
    m21 -= rhs.m21;
    m22 -= rhs.m22;
    m23 -= rhs.m23;
    m31 -= rhs.m31;
    m32 -= rhs.m32;
    m33 -= rhs.m33;

    return *this;
}

//=======================================================================
Matrix3x3 Matrix3x3::operator*(const Matrix3x3 &rhs)
{
    m11 = m11 * rhs.m11 + m12 * rhs.m21 + m13 * rhs.m31;
    m12 = m11 * rhs.m12 + m12 * rhs.m22 + m13 * rhs.m32;
    m13 = m11 * rhs.m13 + m12 * rhs.m23 + m13 * rhs.m33;

    m21 = m21 * rhs.m11 + m22 * rhs.m21 + m23 * rhs.m31;
    m22 = m21 * rhs.m12 + m22 * rhs.m22 + m23 * rhs.m32;
    m23 = m21 * rhs.m13 + m22 * rhs.m23 + m23 * rhs.m33;

    m31 = m31 * rhs.m11 + m32 * rhs.m21 + m33 * rhs.m31;
    m32 = m31 * rhs.m12 + m32 * rhs.m22 + m33 * rhs.m32;
    m33 = m31 * rhs.m13 + m32 * rhs.m23 + m33 * rhs.m33;

    return *this;
}

//=======================================================================
Vector3 Matrix3x3::operator*(const Vector3 &rhs)
{
    const auto x = m11 * rhs.X() + m12 * rhs.Y() + m13 * rhs.Z();
    const auto y = m21 * rhs.X() + m22 * rhs.Y() + m23 * rhs.Z();
    const auto z = m31 * rhs.X() + m32 * rhs.Y() + m33 * rhs.Z();

    return Vector3{x, y, z};
}

//=======================================================================
void Matrix3x3::toIdentity()
{
    m11 = 1;
    m12 = 0;
    m13 = 0;
    m21 = 0;
    m22 = 1;
    m23 = 0;
    m31 = 0;
    m32 = 0;
    m33 = 1;
}

//=======================================================================
float Matrix3x3::det()
{
    return m11 * (m22 * m33 - m23 * m32) - m12 * (m21 * m33 - m23 * m31) + m13 * (m21 * m32 - m22 * m31);
}

//=======================================================================
Matrix3x3 Matrix3x3::inv()
{
    const auto dt = det();
    const float i11 = (m22 * m33 - m23 * m32) / dt;
    const float i12 = (m13 * m32 - m12 * m33) / dt;
    const float i13 = (m12 * m23 - m13 * m22) / dt;
    const float i21 = (m23 * m31 - m21 * m33) / dt;
    const float i22 = (m11 * m33 - m13 * m31) / dt;
    const float i23 = (m13 * m21 - m11 * m23) / dt;
    const float i31 = (m21 * m32 - m22 * m31) / dt;
    const float i32 = (m12 * m31 - m11 * m32) / dt;
    const float i33 = (m11 * m22 - m12 * m21) / dt;

    return Matrix3x3{i11, i12, i13, i21, i22, i23, i31, i32, i33};
}

// Global Scope
//=======================================================================
template <IsArithmetic T>
inline Matrix3x3 operator*(const T lhs, const Matrix3x3 &rhs)
{
    // @todo clang format でコードフォーマットさせない区域を作る
    rhs.m11 *= lhs;
    rhs.m12 *= lhs;
    rhs.m13 *= lhs;
    rhs.m21 *= lhs;
    rhs.m22 *= lhs;
    rhs.m23 *= lhs;
    rhs.m31 *= lhs;
    rhs.m32 *= lhs;
    rhs.m33 *= lhs;

    return rhs;
}

//=======================================================================
template <IsArithmetic T>
inline Matrix3x3 operator/(const Matrix3x3 &lhs, const T rhs)
{
    // ゼロ除算
    if (rhs == 0)
    {
        return lhs;
    }

    lhs.m11 /= rhs;
    lhs.m12 /= rhs;
    lhs.m13 /= rhs;
    lhs.m21 /= rhs;
    lhs.m22 /= rhs;
    lhs.m23 /= rhs;
    lhs.m31 /= rhs;
    lhs.m32 /= rhs;
    lhs.m33 /= rhs;

    return lhs;
}