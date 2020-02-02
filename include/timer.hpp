#ifndef TIMER_HPP
#define TIMER_HPP

#include <ctime>

#include "common.hpp"

namespace advcpp
{

struct Nano {
    size_t value;

    Nano(size_t n);  
      
    operator size_t() const;      
    operator timespec() const;
};

void Sleep(Nano nano) NOEXCEPT;

} //namespace advcpp

#include "timer.inl"
#endif //TIMER_HPP
