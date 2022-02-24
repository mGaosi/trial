#pragma once

class Base
{
public:
    Base()
        : m_nVal(0)
    {
        
    }
    ~Base()
    {

    }

private:
    int m_nVal;
};

class VirtualBase
{
public:
    VirtualBase()
        : m_nVal(0)
    {

    }
    virtual ~VirtualBase()
    {

    }

private:
    int m_nVal;
};

class InheritBase : public Base
{

};

class InheritVirtualBase : public VirtualBase
{

};

int main(int argc, char* args[])
{
    {
        Base* pB = new InheritBase();
        // compile error C2683 
        // https://docs.microsoft.com/en-us/cpp/error-messages/compiler-errors-2/compiler-error-c2683
        InheritBase* pIB = dynamic_cast<InheritBase*>(pB);
        // ok
        InheritBase* pIB = static_cast<InheritBase*>(pB);
        delete pB;
    }
    {
        VirtualBase* pVB = new InheritVirtualBase();
        // ok
        InheritVirtualBase* pIVB = dynamic_cast<InheritVirtualBase*>(pVB);
        delete pVB;
    }
    return 0;
}
