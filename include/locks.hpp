#ifndef MUTEX_HPP
#define MUTEX_HPP

#include <pthread.h>
#include <vector>

#include "enriched_exeptions.hpp"
#include "timer.hpp"
#include "common.hpp"

namespace advcpp
{



class MutexCreateException: public EnrichedExeption {
public:
    explicit MutexCreateException (InfoException a_info, const char* a_msg = "Mutex create failed")
    : EnrichedExeption(a_msg, a_info) 
    {};
};

class MutexLockingException: public EnrichedExeption {
public:
    explicit MutexLockingException (InfoException a_info, const char* a_msg = "Mutex locking or unlocking failed")
    : EnrichedExeption(a_msg, a_info) 
    {};
};

class CondVar;

class Mutex: public UnCopiable {
public: 
    Mutex() THROW1(MutexCreateException);
    ~Mutex() NOEXCEPT;

    void Lock() THROW1(MutexLockingException);
    void UnLock() THROW1(MutexLockingException);
    void TryLock(size_t a_nanoTime) THROW1(MutexLockingException);
    
    friend class CondVar;
private:
    pthread_mutex_t& getLock();

private:
    pthread_mutex_t m_lock;
};

class Guard: public UnCopiable {
public:
    Guard(Mutex& a_mutex);
    ~Guard();
private:
    Mutex& m_mutex;
};

class GuardAll: public UnCopiable {
public:
    GuardAll(std::vector<Mutex*>& a_locks);
    ~GuardAll();
private:
    std::vector<Mutex*>& m_locks;
};


} //namespace advcpp

#include "locks.inl"
#endif //MUTEX_HPP
