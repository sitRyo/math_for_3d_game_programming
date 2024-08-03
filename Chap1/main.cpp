// Vector3 Test

#include <iostream>

#include "Vector3.hpp"

bool test_plus()
{
    Vector3 v1{1.0f, 2.0f, 3.0f};
    Vector3 v2{2.0f, 3.0f, 4.0f};
    Vector3 v3 = v1 + v2;

    float x = 3.0f;
    float y = 5.0f;
    float z = 7.0f;

    return v3.X() == x && v3.Y() == y && v3.Z() == z;
}

bool test_minus()
{
    Vector3 v1{1.0f, 2.0f, 3.0f};
    Vector3 v2{2.0f, 3.0f, 4.0f};
    Vector3 v3 = v1 - v2;

    float x = -1.0f;
    float y = -1.0f;
    float z = -1.0f;

    return v3.X() == x && v3.Y() == y && v3.Z() == z;
}

bool test_multiply()
{
    Vector3 v1{1.0f, 2.0f, 3.0f};
    Vector3 v2 = 3 * v1;

    float x = 3.0f;
    float y = 6.0f;
    float z = 9.0f;

    return v2.X() == x && v2.Y() == y && v2.Z() == z;
}

bool test_division()
{
    Vector3 v1{1.0f, 2.0f, 3.0f};
    Vector3 v2 = v1 / 2;

    float x = 1.0f / 2;
    float y = 2.0f / 2;
    float z = 3.0f / 2;

    return v2.X() == x && v2.Y() == y && v2.Z() == z;
}

bool test_dot()
{
    Vector3 v1{1.0f, 2.0f, 3.0f};
    Vector3 v2{2.0f, 3.0f, 4.0f};

    float x = 1.0f * 2.0f;
    float y = 2.0f * 3.0f;
    float z = 3.0f * 4.0f;

    float r = v1.dot(v2);

    return r == (x + y + z);
}

bool test_cross()
{
    Vector3 v1{3.0f, 7.0f, 2.0f};
    Vector3 v2{5.0f, 2.0f, 1.0f};

    auto v = v1.cross(v2);

    float x = 3.0f;
    float y = 7.0f;
    float z = -29.0f;

    return v.X() == x && v.Y() == y && v.Z() == z;
}

int main()
{
    bool r = true;
    if (!test_plus())
    {
        std::cerr << "error: operator+" << "\n";
        r = false;
    }

    if (!test_minus())
    {
        std::cerr << "error: operator-" << "\n";
        r = false;
    }

    if (!test_multiply())
    {
        std::cerr << "error: operator*" << "\n";
        r = false;
    }

    if (!test_division())
    {
        std::cerr << "error: operator/" << "\n";
        r = false;
    }

    if (!test_dot())
    {
        std::cerr << "error: dot" << "\n";
        r = false;
    }

    if (!test_cross())
    {
        std::cerr << "error: cross" << "\n";
        r = false;
    }

    if (r)
    {
        std::cout << "Test completed!" << "\n";
    }
}
