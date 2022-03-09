/**
 * @file function_overriding.cpp
 * @brief 
 * @version 0.1
 * @date 2022-03-09
 * 
 * see https://www.geeksforgeeks.org/function-overloading-vs-function-overriding-in-cpp/
 * see https://blog.csdn.net/gatieme/article/details/50899343
 * 
 */

#include<iostream>
 
class BaseClass
{
public:
    virtual void Display()
    {
        std::cout << "This is BaseClass::Display() method." << std::endl;
    }
    void Show()
    {
        std::cout << "This is BaseClass::Show() method." << std::endl;
    }
};
 
class DerivedClass : public BaseClass
{
public:
    // Overriding method - new working of
    // base class's display method
    virtual void Display() override
    {
        std::cout << "This is DerivedClass::Display() method." << std::endl;
    }
    void DisplayBase()
    {
        BaseClass::Display();
    }
};
 
// Driver code
int main()
{
    DerivedClass dr;
    BaseClass &bs = dr;
    bs.Display(); // This is DerivedClass::Display() method.
    dr.DisplayBase(); // This is BaseClass::Display() method.
    dr.Show(); // This is BaseClass::Show() method.
}