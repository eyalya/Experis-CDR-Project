#ifndef I_INTERFACE_HPP
#define I_INTERFACE_HPP

namespace advcpp 
{

class Iinterface {
public:
    
    ~Iinterface() {};

    //Iinterface();
    //Iinterface(const Iinterface<T>& a_rhs) = default;
    //Iinterface& operator = (const Iinterface<T> a_rhs) = default;

    virtual void func() = 0;
};

} //namespace advcpp 

// #include "Iinterface.inl"
#endif //I_INTERFACE_HPP
