#ifndef IRUNNABLE_HPP
#define IRUNNABLE_HPP

#include "common.hpp" // Uncopiable

namespace advcpp
{

class IRunnable : private UnCopiable {
public:
    virtual ~IRunnable();
    virtual void Run() = 0;
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline IRunnable::~IRunnable()
{
}


} //namespace advcpp

#endif //IRUNNABLE_HPP
