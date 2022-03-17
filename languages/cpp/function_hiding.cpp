/**
 * @file function_hiding.cpp
 * @brief 
 * @version 0.1
 * @date 2022-03-09
 * 
 * see https://www.geeksforgeeks.org/function-overloading-vs-function-overriding-in-cpp/
 * 
 */

#include<iostream>
 
class BaseClass
{
public:
    void Display(int var)
    {
        std::cout << "This is BaseClass::Display(" << var << ") method." << std::endl;
    }
};
 
class DerivedClass : public BaseClass
{
public:
    // Hiding method 
    void Display(int var)
    {
        std::cout << "This is DerivedClass::Display(" << var << ") method." << std::endl;
    }
};
 
// Driver code
int main(int argc, char* args[])
{
    DerivedClass dr;
    BaseClass &bs = dr;
    bs.Display(1); // This is BaseClass::Display(1) method.
    dr.Display(2); // This is DerivedClass::Display(2) method.
}