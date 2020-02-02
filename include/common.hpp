#ifndef COMMON_HPP
#define COMMON_HPP

#include <sys/sysinfo.h> //nprocs

namespace advcpp
{
//Macros 
#define NOEXCEPT throw()
#define THROW1(x) throw(x)
#define THROW2(x,y) throw(x,y)
#define THROW3(x,y,z) throw(x,y,z)

#define THROWX(x) throw x(InfoException(__FILE__, __func__, __LINE__))

#define BYTE 8

const size_t NT  = get_nprocs() - 1; 

class UnCopiable {
protected:
    UnCopiable() {};
private: 
    UnCopiable(UnCopiable const& a_rhs);
    UnCopiable& operator = (UnCopiable const& a_rhs);
};



} //namespace advcpp

#endif //COMMON_HPP
