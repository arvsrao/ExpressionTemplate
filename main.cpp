#include <iostream>

struct Expression
{

};

template<typename Scalar = int>
struct Vector
{
    Scalar x, y, z;
    Scalar operator[](const int idx);
    Vector<Scalar> operator+(const Vector<Scalar>& other);
};

template<typename Scalar>
Vector<Scalar> Vector<Scalar>::operator+(const Vector<Scalar>& other)
{
    std::cout << "(" << x << "," << y << "," << z << ")\n";
    return Vector { x + other.x, y + other.y, z + other.z };
}

template<typename Scalar>
Scalar Vector<Scalar>::operator[](const int idx)
{
    switch (idx)
    {
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
        default:
            throw std::invalid_argument("index out of bounds");
    }
}

int main()
{
    Vector<> v {1, 2, 3}, w {2, 3, 4 }, l {4, 5, 6};
    auto u = v + w + l;

    for (int i = 0; i < 3; i++) std::cout << u[i] << ", ";
    return 0;
}
