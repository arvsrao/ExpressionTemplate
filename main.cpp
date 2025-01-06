#include <iostream>

template <typename T>
struct Traits
{
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

    constexpr Scalar operator[](const int idx) const {
        return left[idx] + right[idx];
    }

    Vector<Scalar> evaluate() const {
        return Vector<Scalar>(operator[](0), operator[](1), operator[](2));
    }

    L left;
    R right;
};

template<typename T>
struct Expression {
    using Scalar = typename Traits<T>::Scalar;

    constexpr Scalar operator[](const int idx) const {
        return static_cast<T*>(this)->operator[](idx);
    }

    template<typename S>
    constexpr Sum<T, S> operator+(const Expression<S>& other) const {
        return Sum<T, S>(static_cast<const T&>(*this), static_cast<const S&>(other));
    }

};

template<typename Scalar>
struct Vector : Expression<Vector<Scalar>>
{
    using Base = Vector<Scalar>;

    Scalar x, y, z;

    // base constructor
    Vector(Scalar x, Scalar y, Scalar z) : x(x), y(y), z(z) {}
    Vector(const Base& other) : x(other.x), y(other.y), z(other.z) {}
    Vector(const Base&& other) : x(other.x), y(other.y), z(other.z) {}

    constexpr Scalar operator[](const int idx) const {
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

    auto u = r + (a + v) + (w + l);
    auto sumVec = u.evaluate();
    sumVec.print();

    return 0;
}
