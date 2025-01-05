#include <iostream>

template <typename T>
struct Traits {
    using Scalar = typename T::Scalar;
};

// forward declaration
template<typename T> struct Expression;

template<typename L, typename R>
struct Sum : Expression<Sum<L, R>>
{
    using Scalar = typename Traits<L>::Scalar;
    explicit Sum(const L& l, const R& r) : left(l), right(r) {}

    constexpr Scalar operator[](const int idx) {
        return left[idx] + right[idx];
    }

    L left;
    R right;
};

template<typename T>
struct Expression {
    using Scalar = typename Traits<T>::Scalar;

    Scalar operator[](const int idx) const {
        return static_cast<T*>(this)->operator[](idx);
    }

    template<typename S>
    constexpr Sum<Expression<T>, Expression<S>> operator+(const Expression<S>& other) const {
        return Sum<Expression<T>, Expression<S>>(*this, other);
    }
};

template<typename T>
struct Vector : Expression<Vector<T>>
{
    using Scalar = T;
    using Base = Vector<Scalar>;

    Scalar x, y, z;

    constexpr Sum<Base, Base> operator+(const Base& other) {
        return Sum<Base, Base>(*this, other);
    }

    template<typename R>
    constexpr Sum<Base, Sum<Base, R>> operator+(const Sum<Base, R>& other) {
        return Sum<Base, Sum<Base, R>>(*this, other);
    }

    // base constructor
    Vector(Scalar x, Scalar y, Scalar z) : x(x), y(y), z(z) {}

    Scalar operator[](const int idx);
    void print();
};

template <typename T>
struct Traits<Vector<T>>
{
    using Scalar = T;
};

template<typename L, typename R>
struct Traits<Sum<L, R>>
{
    using Scalar = typename Traits<L>::Scalar;
};

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

    auto u = v + (w + (l + r));
    auto sumVec = Vector<int>(u[0], u[1], u[2]);
    sumVec.print();

    return 0;
}
