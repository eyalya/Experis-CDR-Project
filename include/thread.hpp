#ifndef THREAD_HPP
#define THREAD_HPP

#include <pthread.h>
#include <vector>

#include "irunnable.hpp"
#include "common.hpp"
#include "enriched_exeptions.hpp"
#include "timer.hpp"

namespace advcpp
{

class ThreadCreateException: public EnrichedExeption {
public:
    explicit ThreadCreateException (InfoException a_info, const char* a_msg = "thread create failed")
    : EnrichedExeption(a_msg, a_info) 
    {};
};

class ThreadDetachedException: public EnrichedExeption {
public:
    explicit ThreadDetachedException (InfoException a_info, const char* a_msg = "thread detahced failed")
    : EnrichedExeption(a_msg, a_info) 
    {};
};

class ThreadJoinException: public EnrichedExeption {
public:
    explicit ThreadJoinException (InfoException a_info, const char* a_msg = "thread join failed")
    : EnrichedExeption(a_msg, a_info) 
    {};
};

class ThreadTimeoutException: public EnrichedExeption {
public:
    explicit ThreadTimeoutException (InfoException a_info, const char* a_msg = "thread join failed")
    : EnrichedExeption(a_msg, a_info) 
    {};
};

class ThreadUnValidSignalException: public EnrichedExeption {
public:
    explicit ThreadUnValidSignalException (InfoException a_info, const char* a_msg = "thread join failed")
    : EnrichedExeption(a_msg, a_info) 
    {};
};

class Thread: private UnCopiable {
public: 
    explicit Thread(IRunnable* a_prun) THROW1(ThreadCreateException);

    ~Thread() NOEXCEPT;

    bool IsJoinable() NOEXCEPT;
    void Detach() NOEXCEPT;    
    void Join() THROW1(ThreadJoinException);
    void TryJoin(Nano a_timeout)  THROW1(ThreadTimeoutException);

    void Cancel() NOEXCEPT;
    void Kill(int a_signal) THROW1(ThreadUnValidSignalException);

    static void Yield() NOEXCEPT;
    static void Exit(void* a_retval = 0);

private:
    static void* thunk(void* a_pctx) NOEXCEPT;

    bool& joinable();
    bool const& joinable() const;
    pthread_t& getThread();
    pthread_t const& getThread() const;
    
private:
    bool m_joinable;
    pthread_t m_thread;
};

} //namespace advcpp

#include "thread.inl"
#endif //THREAD_HPP
