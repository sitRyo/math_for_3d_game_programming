#pragma once

#include "./my_concepts.hpp"
#include "./Vector3.hpp"

class Matrix3x3
{
public:
    explicit Matrix3x3(float m11, float m12, float m13, float m21, float m22, float m23, float m31, float m32, float m33);

    // 行列同士の加減算
    Matrix3x3 operator+(const Matrix3x3 &);
    Matrix3x3 operator-(const Matrix3x3 &);
    Matrix3x3 operator*(const Matrix3x3 &);

    // 3x1ベクトルとの乗算
    Matrix3x3 operator*(const Vector3 &);

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