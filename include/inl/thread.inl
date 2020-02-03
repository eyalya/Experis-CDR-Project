//#define _XOPEN_SOURCE = 500
#ifndef THREAD_INL
#define THREAD_INL
#include <cassert>
#include "numbers.hpp"
#include <signal.h>

namespace advcpp{


inline IRunnable::~IRunnable()
{    
}

inline ThreadException::ThreadException(const char* a_msg, ExtendInfo a_xInfo)
: ExtendedException(a_msg, a_xInfo)
{    
}

Thread::Thread(IRunnable* a_prun, Policy a_poli) THROW1(ThreadException)
: m_isJoinable(true)
, m_policy(a_poli)
{
    if (int r = pthread_create(&m_thread, 0, Thunk, static_cast<void*>(a_prun)))
    {
        throw ThreadException(numbers::Itoa(r), ExtendInfo(XINFO));
    }
}

inline Thread::~Thread() 
{
    if (!m_isJoinable)
    {
        return;
    }
    if (JOIN == m_policy)
    {
        Join();
        return;
    }
    std::terminate();
}

inline void Thread::Detach() THROW1(ThreadException)
{
    if (int r = pthread_detach(m_thread))
    {
        throw ThreadException(numbers::Itoa(r), ExtendInfo(XINFO));
    }
    m_isJoinable = false;
}

inline void Thread::Join() THROW1(ThreadException)
{
    if (int r = pthread_join(m_thread, 0))
    {
        throw ThreadException(numbers::Itoa(r), ExtendInfo(XINFO));
    }    
    m_isJoinable = false;
}

inline void Thread::TryJoin(timespec a_timeOut) THROW1(ThreadException)
{
    if (int r = pthread_timedjoin_np(m_thread, 0, &a_timeOut))
    {
        throw ThreadException(numbers::Itoa(r), ExtendInfo(XINFO));
    }    
}

inline void Thread::Cancel() THROW1(ThreadException)
{
    if (int r = pthread_cancel(m_thread))
    {
        throw ThreadException(numbers::Itoa(r), ExtendInfo(XINFO));
    }
}

inline void Thread::Yield() THROW1(ThreadException)
{
    if (int r = pthread_yield())
    {
        throw ThreadException(numbers::Itoa(r), ExtendInfo(XINFO));
    }
}

inline void Thread::Kill() THROW1(ThreadException)
{
    if (int r = pthread_kill(m_thread, SIGKILL))
    {
        throw ThreadException(numbers::Itoa(r), ExtendInfo(XINFO));
    }
}

inline void Thread::Exit(void* a_retVal) NOEXCEPT
{
    pthread_exit(a_retVal);
}

inline void* Thread::Thunk(void* a_pctx) NOEXCEPT
{
    IRunnable* r = static_cast<IRunnable*>(a_pctx);
    r->Run();
    return 0;
}

} //namespace advcpp
#endif //THREAD_INL