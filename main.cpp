#include <iostream>

template <typename T>
struct Traits {
    using Scalar = typename T::Scalar;
};

// forward declarations
template<typename T> struct Expression;
template<typename T> struct Vector;

template<typename L, typename R>
struct Sum : Expression<Sum<L, R>>
{
    using Scalar = typename Traits<L>::Scalar;
    Sum(const L& l, const R& r) : left(l), right(r) {}
    Sum(const Sum<L, R>& other) : left(other.left), right(other.right) {}
    Sum(const Sum<L, R>&& other) : left(other.left), right(other.right) {}

    constexpr Scalar operator[](const int idx) {
        return left[idx] + right[idx];
    }

    constexpr Sum<Sum<L, R>, Vector<Scalar>> operator+(const Vector<Scalar>& other) const {
        return Sum<Sum<L, R>, Vector<Scalar>>(*this, other);
    }

    template<typename L1, typename R1>
    constexpr Sum<Sum<L, R>, Sum<L1, R1>> operator+(const Sum<L1, R1>& other) const {
        return Sum<Sum<L, R>, Sum<L1, R1>>(*this, other);
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

    Scalar operator[](const int idx) {
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

    void print() {
        std::cout << "(" << x << "," << y << "," << z << ")\n";
    }
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

int main()
{
    Vector<int> v(1,2,3), w(2,3,4), l(4,5,6), r(12,13,16), a(23,42,53);

    auto u = (a + v) + (w + l + r);
    auto sumVec = Vector<int>(u[0], u[1], u[2]);
    sumVec.print();

    return 0;
}
