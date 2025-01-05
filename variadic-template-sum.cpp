#include <iostream>

// The base case: we just have a single number.
template <typename T>
double sum(T t) {
    return t;
}

// The recursive case: we take a number, alongside
// some other numbers, and produce their sum.
template <typename T, typename... Rest>
double sum(T t, Rest... rest) {
    return t + sum(rest...);
}

int main()
{
    // see blog post https://kevinushey.github.io/blog/2016/01/27/introduction-to-c++-variadic-templates/

    int s = sum(1,2,3);
    std::cout << "Sum: " << s;

    return 0;
}