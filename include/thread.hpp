#ifndef THREAD_H
#define THREAD_H
#include <pthread.h>
#include "common.hpp"

namespace advcpp{


class IRunnable : private Uncopyable
{
public:
    virtual ~IRunnable() = 0;
    virtual void Run() = 0;
};

enum Policy
{
    TERMINATE,
    JOIN
};

class ThreadException : public ExtendedException
{
public:
    explicit ThreadException(const char* a_msg, ExtendInfo a_xInfo);
};

class Thread : private Uncopyable
{
public:
    Thread(IRunnable *a_prun, Policy a_poli = TERMINATE) THROW1(ThreadException);
    ~Thread();    

    void Detach() THROW1(ThreadException);
    void Join() THROW1(ThreadException);
    void TryJoin(timespec a_timeOut) THROW1(ThreadException);
    void Cancel()THROW1(ThreadException);
    void Kill() THROW1(ThreadException); 
    
    static void Yield() THROW1(ThreadException);
    static void Exit(void* a_retVal = 0) NOEXCEPT;

private:
    static void* Thunk(void* a_pctx) NOEXCEPT;

private:
    pthread_t m_thread;
    bool m_isJoinable;
    Policy m_policy;
};


}//namespace advcpp

#include "inl/thread.inl"

#endif //THREAD_H