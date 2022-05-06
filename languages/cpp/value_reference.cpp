/**
 * @file value_reference.cpp
 * @author Jiangjie Gao (gaojiangjie@live.com)
 * @brief 
 * @version 0.1
 * @date 2022-04-07
 * 
 * 
 */

#include <iostream>

class RefBox
{
public:
    //RefBox(){} error C2530
    RefBox(int& nValue)
        : m_nValue(nValue)
    {

    }

public:
    int& Value()
    {
        return m_nValue;
    }

private:
    int& m_nValue;
};

class EmptyBox {};

int main(void)
{
    int i = 0;
    int& l = i;
    //int& l = 0; error
    //int& l; error C2530
    const int& lc = 0;
    int&& r = 0;
    // int&& r = i; error
    std::cout << "&i = " << std::addressof(i) << std::endl;
    std::cout << "&l = " << std::addressof(l) << std::endl; // std::addressof(l) == std::addressof(i)
    std::cout << "&lc = " << std::addressof(lc) << std::endl; // std::addressof(lc) != std::addressof(i)
    std::cout << "&r = " << std::addressof(r) << std::endl; // std::addressof(r) != std::addressof(lc)

    RefBox boxi(i);
    RefBox boxl(l);
    RefBox boxr(r);
    std::cout << "&boxi.Value() = " << std::addressof(boxi.Value()) << std::endl; // std::addressof(boxi.Value()) == std::addressof(i)
    std::cout << "&boxl.Value() = " << std::addressof(boxl.Value()) << std::endl; // std::addressof(boxl.Value()) == std::addressof(boxi.Value())
    std::cout << "&boxr.Value() = " << std::addressof(boxr.Value()) << std::endl; // std::addressof(boxr.Value()) == std::addressof(r)
    std::cout << "sizeof(RefBox) = " << sizeof(RefBox) << std::endl; //`sizeof(RefBox) = 8` , x64
    std::cout << "sizeof(EmptyBox) = " << sizeof(EmptyBox) << std::endl; //`sizeof(EmptyBox) = 1`
}
