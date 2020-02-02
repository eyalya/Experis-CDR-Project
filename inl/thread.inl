#include <pthread.h> //threads
#include <cassert> //assert

#include "thread.hpp"

namespace advcpp
{
////////////// Public ///////////////////////////////////////////////////////////////////////////
inline Thread::~Thread() NOEXCEPT
{
    if(joinable() == true)
    {
        Detach();
    }
}   

inline bool Thread::IsJoinable() NOEXCEPT
{
    return joinable();
}

inline void Thread::Cancel() NOEXCEPT
{
    assert(joinable() == true);

    pthread_cancel(getThread());
}

////////////// Private ///////////////////////////////////////////////////////////////////////////
inline pthread_t& Thread::getThread() 
{
    return m_thread;
}

inline pthread_t const& Thread::getThread() const 
{
    return m_thread;
}

inline bool& Thread::joinable() 
{ 
    return m_joinable;
}

inline bool const& Thread::joinable() const 
{
    return m_joinable;
}

////////////// Static ///////////////////////////////////////////////////////////////////////////
inline static void Yield() NOEXCEPT
{
    pthread_yield();
}

inline static void Exit(void* a_retval) NOEXCEPT
{
    pthread_exit(a_retval);
}

} //namespace advcpp