#pragma once

#include <type_traits>

#include "./my_concepts.hpp"

class Vector3
{
public:
    explicit Vector3(const float x, const float y, const float z);

    Vector3 operator+(const Vector3 &);
    Vector3 operator-(const Vector3 &);

    // 内積
    float dot(const Vector3 &rhs) const;
    // 外積
    Vector3 cross(const Vector3 &rhs) const;

    // Accessors
    float X() const;
    float Y() const;
    float Z() const;

private:
    float x;
    float y;
    float z;
};

Vector3::Vector3(const float x, const float y, const float z) : x(x), y(y), z(z)
{
}

Vector3 Vector3::operator+(const Vector3 &rhs)
{
    return Vector3{x + rhs.x, y + rhs.y, z + rhs.z};
}

Vector3 Vector3::operator-(const Vector3 &rhs)
{
    return Vector3{x - rhs.x, y - rhs.y, z - rhs.z};
}

float Vector3::dot(const Vector3 &rhs) const
{
    return x * rhs.x + y * rhs.y + z * rhs.z;
}

Vector3 Vector3::cross(const Vector3 &rhs) const
{
    return Vector3{
        y * rhs.z - z * rhs.y,
        z * rhs.x - x * rhs.z,
        x * rhs.y - y * rhs.x};
}

float Vector3::X() const
{
    return x;
}

float Vector3::Y() const
{
    return y;
}

float Vector3::Z() const
{
    return z;
}

template <IsArithmetic T>
inline Vector3 operator*(const T lhs, const Vector3 &rhs)
{
    return Vector3{lhs * rhs.X(), lhs * rhs.Y(), lhs * rhs.Z()};
}

template <IsArithmetic T>
inline Vector3 operator*(const Vector3 &lhs, const T rhs)
{
    return rhs * lhs;
}

template <IsArithmetic T>
inline Vector3 operator/(const Vector3 &lhs, const T rhs)
{
    return Vector3{lhs.X() / rhs, lhs.Y() / rhs, lhs.Z() / rhs};
}