cmake_minimum_required(VERSION 3.31)
project(ExpressionTemplate)

set(CMAKE_CXX_STANDARD 17)

add_executable(compileTimeSum main.cpp)
add_executable(variadicTemplateSum variadic-template-sum.cpp)
