#include "timer.hpp"

namespace advcpp
{

inline Nano::Nano(size_t n)
: value(n)
{
}

inline Nano::operator size_t() const 
{ 
    return value; 
}

inline Nano::operator timespec() const
{
    timespec t;
    t.tv_nsec = value;
    return t;
}

inline void Sleep(Nano nano) NOEXCEPT
{
    timespec ts = nano;
    nanosleep(&ts, 0);
}


} //namespace advcpp