#include <iostream>

template <typename T>
struct Traits {
    using Scalar = typename T::Scalar;
};

// forward declaration
template<typename T> struct Expression;

template<typename T, typename L, typename R>
struct Sum : Expression<Sum<T, L, R>>
{
    using Scalar = T;
    explicit Sum(const L& l, const R& r) : left(l), right(r) {}

    constexpr Scalar operator[](const int idx);

    L left;
    R right;
};

template<typename T>
struct Expression {
    using Scalar = typename Traits<T>::Scalar;

    Scalar operator[](const int idx) {
        return static_cast<T*>(this)->operator[](idx);
    }

    template<typename S>
    constexpr Sum<Scalar, Expression<T>, Expression<S>> operator+(const Expression<S>& other) const;
};

template<typename T>
struct Vector : Expression<Vector<T>>
{
    using Scalar = T;
    using Base = Vector<Scalar>;

    Scalar x, y, z;

    constexpr Sum<Scalar, Base, Base> operator+(const Base& other);

    template<typename R>
    constexpr Sum<Scalar, Base, Sum<Scalar, Base, R>> operator+(const Sum<Scalar, Base, R>& other);

    // base constructor
    Vector(Scalar x, Scalar y, Scalar z) : x(x), y(y), z(z) {}

    Scalar operator[](const int idx);
    void print();
};

template <typename T>
struct Traits<Vector<T>> {
    using Scalar = T;
};

template<typename T, typename L, typename R>
struct Traits<Sum<T, L, R>> {
    using Scalar = T;
};

template<typename T, typename L, typename R>
constexpr T Sum<T, L, R>::operator[](const int idx) {
    return left[idx] + right[idx];
}

template<typename T>
template<typename S>
constexpr Sum<typename Traits<T>::Scalar, Expression<T>, Expression<S>> Expression<T>::operator+(const Expression<S>& other) const {
    return Sum<typename Traits<T>::Scalar, Expression<T>, Expression<S>>(*this, other);
}

template<typename T>
constexpr Sum<T, Vector<T>, Vector<T>> Vector<T>::operator+(const Vector<T>& other)
{
    return Sum<T, Vector<T>, Vector<T>>(*this, other);
}

template<typename T>
template<typename R>
constexpr
Sum<T, Vector<T>, Sum<T, Vector<T>, R>>
Vector<T>::operator+(const Sum<T, Vector<T>, R>& other)
{
    return Sum<T, Vector<T>, Sum<T, Vector<T>, R>>(*this, other);
}

template<typename T>
void Vector<T>::print()
{
    std::cout << "(" << x << "," << y << "," << z << ")\n";
}

template<typename T>
T Vector<T>::operator[](const int idx)
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
    Vector<int> v(1,2,3), w(2,3,4), l(4,5,6), r(12,13,16);

    auto u = v + w + l + r;
    auto sumVec = Vector<int>(u[0], u[1], u[2]);
    sumVec.print();

    return 0;
}
