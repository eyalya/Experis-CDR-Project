#ifndef CLASS_HPP
#define CLASS_HPP

namespace advcpp 
{

template <typename T> 
class Class {
public:
    explicit Class();

    //~Class() = default;
    //Class(const Class<T>& a_rhs) = default;
    //Class& operator = (const Class<T> a_rhs) = default;

    func();

private:
    T m_mmb;
};

} //namespace advcpp 

// #include "class.inl"
#endif //CLASS_HPP