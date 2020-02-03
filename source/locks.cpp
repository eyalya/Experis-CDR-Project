#include "locks.hpp"


namespace advcpp 
{

Mutex::Mutex() THROW1(MutexCreateException)
{
    if (pthread_mutex_init(&m_lock, NULL) != 0)
    {
        THROWX(MutexCreateException);
    }
}

void Mutex::TryLock(size_t a_nanoTime) THROW1(MutexLockingException)
{
    int result = 1;
    result  = pthread_mutex_trylock(&getLock());

    int n = 3;
    while (result && --n)
    {
        advcpp::Sleep(a_nanoTime);
        result  = pthread_mutex_trylock(&getLock());
    }

    if (result != 0)
    {
        THROWX(MutexLockingException);
    }
}

GuardAll::GuardAll(std::vector<Mutex*>& a_locks)
: m_locks(a_locks)
{
    std::vector<Mutex*>::iterator it = m_locks.begin();
    std::vector<Mutex*>::iterator end = m_locks.end();

    while (it != end)
    {
        (*it)->Lock();
        ++it;
    }
}

GuardAll::~GuardAll()
{
    std::vector<Mutex*>::iterator it = m_locks.begin();
    std::vector<Mutex*>::iterator end = m_locks.end();

    while (it != end)
    {
        (*it)->UnLock();
        ++it;
    }
}

} //namespace advcpp 