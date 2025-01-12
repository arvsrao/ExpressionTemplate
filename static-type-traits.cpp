#include <iostream>

template <typename T>
struct TraitStr {
    static const std::string type_str;
};

template <>
const std::string TraitStr<char>::type_str = "char";

template <>
const std::string TraitStr<int>::type_str = "int";

template <>
const std::string TraitStr<long>::type_str = "long";

int main()
{
    std::cout << TraitStr<long>::type_str << "\n";

    return 0;
}