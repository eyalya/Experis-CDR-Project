#ifndef MUTEX_HPP
#define MUTEX_HPP
#include <pthread.h>
#include "common.hpp"

namespace advcpp{

class MutexException: public ExtendedException
{
public:
    MutexException(const char* a_msg, ExtendInfo a_xInfo);
};

class Mutex: private Uncopyable
{
public:
    Mutex() THROW1(MutexException);
    ~Mutex() NOEXCEPT;
    
    void Lock() THROW1(MutexException);
    void Unlock() THROW1(MutexException);

    friend class CondVar;    

private:
    pthread_mutex_t* GetMutex() NOEXCEPT;

private:
    pthread_mutex_t m_mutex;
};

class Guard : private Uncopyable
{
public:    
    Guard(Mutex& a_mutex) THROW1(MutexException);
    ~Guard() NOEXCEPT;

private:
    Mutex& m_mutex;
};

} //namespace advcpp

#include "inl/mutex.inl"

#endif //MUTEX_HPP
