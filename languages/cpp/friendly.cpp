/**
 * @file friendly.cpp
 * @author Jiangjie Gao (gaojiangjie@live.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-15
 * 
 * tail friend class
 */

#include <iostream>

class Rect
{
    friend class Measure;
public:
    explicit Rect(int nWidth, int nHeight)
        : m_nWidth(nWidth)
        , m_nHeight(nHeight)
    {}

private:
    int Width(){return m_nWidth;}
    int Height(){return m_nHeight;}

private:
    int m_nWidth;
    int m_nHeight;
};

class Round;
class Measure
{
public:
    static int OfRect(Rect& obj)
    {
        return obj.Width() * obj.Height();
    }
    static double OfRound(Round& obj);
};

class Round
{
public:
    explicit Round(int nRadius)
        : m_nRadius(nRadius)
    {}

private:
    int Radius()
    {
        return m_nRadius;
    }
    friend double Measure::OfRound(Round& obj);

private:
    int m_nRadius;
};

double Measure::OfRound(Round& obj)
{
    // impl to be after the friend declaration
    return obj.Radius() * 3.1415926;
}

int main(int argc, char* args[])
{
    Rect rect(3, 4);
    std::cout << "measure of rectangle is: "  << Measure::OfRect(rect) << std::endl;
    Round round(4);
    std::cout << "round of rectangle is: " << Measure::OfRound(round) << std::endl;
    return 0;
}


