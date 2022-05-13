/**
 * @file static.cpp
 * @author Jiangjie Gao (gaojiangjie@live.com)
 * @brief 
 * @version 0.1
 * @date 2022-05-12
 * 
 * 
 */

#include <iostream>

class GlobalConfig
{
private:
    GlobalConfig()
    {
        std::cout << "GlobalConfig::GlobalConfig()" << std::endl;
    }
    ~GlobalConfig()
    {
        std::cout << "GlobalConfig::~GlobalConfig()" << std::endl;
    }

private:
    static GlobalConfig instance;
};
GlobalConfig GlobalConfig::instance;

class TempValue
{
public:
    TempValue()
    {
        std::cout << "TempValue::TempValue()" << std::endl;
    }
    ~TempValue()
    {
        std::cout << "TempValue::~TempValue()" << std::endl;
    }
};

static TempValue g_default;

class CallCounter
{
public:
    CallCounter()
    {
        std::cout << "CallCounter::CallCounter()" << std::endl;
    }
    ~CallCounter()
    {
        std::cout << "CallCounter::~CallCounter()" << std::endl;
    }
};

int main()
{
    std::cout << "main() entry" << std::endl;
    static CallCounter s_cc;
    std::cout << "main() leave" << std::endl;
    return 0;
}

/* prints:

GlobalConfig::GlobalConfig()
TempValue::TempValue()
main() entry
CallCounter::CallCounter()
main() leave
CallCounter::~CallCounter()
TempValue::~TempValue()
GlobalConfig::~GlobalConfig()

*/