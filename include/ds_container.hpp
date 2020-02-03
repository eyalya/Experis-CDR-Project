#ifndef DS_CONTAINER_HPP
#define DS_CONTAINER_HPP

#include <map>
typedef std::map Hash

namespace advcpp 
{

template <typename T> 
class DsContainer {
public:
    explicit DsContainer();

    //~Class() = default;
    //Class(const Class<T>& a_rhs) = default;
    //Class& operator = (const Class<T> a_rhs) = default;

    DsUpserter();

private:
    T m_mmb;
};

} //namespace advcpp 

// #include "class.inl"
#endif //DS_CONTAINER_HPP