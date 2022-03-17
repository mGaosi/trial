/**
 * @file dynamic_cast.cpp
 * @brief 
 * @version 0.1
 * @date 2022-02-24
 * 
 * trail dynamic_cast
 */

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
public:
    virtual ~InheritVirtualBase()
    {

    }
};

int main(int argc, char* args[])
{
    {
        Base* pB = new InheritBase();
        // compile error C2683 
        // https://docs.microsoft.com/en-us/cpp/error-messages/compiler-errors-2/compiler-error-c2683
        //InheritBase* pIB = dynamic_cast<InheritBase*>(pB);
        // ok
        InheritBase* pIB = static_cast<InheritBase*>(pB);
        delete pB;
    }
    {
        VirtualBase* pVB = new VirtualBase();
        // ok pIVB == nullptr
        InheritVirtualBase* pIVB = dynamic_cast<InheritVirtualBase*>(pVB);
        delete pVB;
        pVB = new InheritVirtualBase();
        // ok
        pIVB = dynamic_cast<InheritVirtualBase*>(pVB);
        delete pVB;
    }
    return 0;
}
