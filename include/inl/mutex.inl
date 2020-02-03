#ifndef MUTEX_INL
#define MUTEX_INL
#include "numbers.hpp"
namespace advcpp{

inline Mutex::Mutex() THROW1(MutexException)
{
    if (int num = pthread_mutex_init(&m_mutex, 0))
    {        
        throw MutexException(numbers::Itoa(num), ExtendInfo(XINFO));
    }
}

inline Mutex::~Mutex() NOEXCEPT
{
    pthread_mutex_destroy(&m_mutex);
}

inline void Mutex::Lock() THROW1(MutexException)
{
    if (int num = pthread_mutex_lock(&m_mutex))
    {
        throw MutexException(numbers::Itoa(num), ExtendInfo(XINFO));
    }
}

inline void Mutex::Unlock() THROW1(MutexException)
{
    if (int num = pthread_mutex_unlock(&m_mutex))
    {
        throw MutexException(numbers::Itoa(num), ExtendInfo(XINFO));
    }
}

inline pthread_mutex_t* Mutex::GetMutex() NOEXCEPT
{
    return &m_mutex;
}

inline MutexException::MutexException(const char* a_msg, ExtendInfo a_xInfo)
: ExtendedException(a_msg, a_xInfo)
{
}

inline Guard::Guard(Mutex& a_mutex) THROW1(MutexException)
: m_mutex(a_mutex)
{    
    m_mutex.Lock();
}

inline Guard::~Guard() NOEXCEPT
{
    try
    {
        m_mutex.Unlock();
    }
    catch(...)
    {        
    }    
}

}//namespace advcpp

#endif //MUTEX_INL
