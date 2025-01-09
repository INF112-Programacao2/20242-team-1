// myclass.cpp
#include "myclass.h"

MyClass::MyClass(std::string name) : name(name) {}

std::string MyClass::greet()
{
    return "Hello, " + name + "!";
}