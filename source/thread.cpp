#include <csignal>

#include "thread.hpp"

namespace advcpp
{

Thread::Thread(IRunnable* a_prun) THROW1(ThreadCreateException)
: m_joinable(false)
{
    assert(a_prun != NULL);

    if (pthread_create(&m_thread, 0, thunk, static_cast<void*>(a_prun)) != 0)
    {
        THROWX(ThreadCreateException);
    }
    m_joinable = true;
}

void Thread::Detach() NOEXCEPT
{
    //can't fail because it is prevented in class
    assert(joinable() == true);

    pthread_detach(getThread());
    joinable() = false;
}

void Thread::Join() THROW1(ThreadJoinException)
{
    //TODO: can it failed? all error prevented
    assert(joinable() == true);

    if (pthread_join(getThread(), NULL) != 0)
    {
        THROWX(ThreadJoinException);
    }
    joinable() = false;
}

void Thread::TryJoin(Nano a_timeout) THROW1(ThreadTimeoutException)
{
    assert(joinable() == true);

    const timespec timeout = a_timeout;
    if (pthread_timedjoin_np(getThread(), NULL, &timeout) != 0)
    {
        THROWX(ThreadTimeoutException);
    }
    joinable() = false;
}

void Thread::Kill(int a_signal) THROW1(ThreadUnValidSignalException)
{
    assert(joinable() == true);
    
    if (pthread_kill(getThread(), a_signal) != 0)
    {
        THROWX(ThreadUnValidSignalException);
    }
}

void* Thread::thunk(void* a_pctx) NOEXCEPT
{
    assert(a_pctx != NULL);

    advcpp::IRunnable* r = static_cast<advcpp::IRunnable*>(a_pctx);
    r->Run();
    return a_pctx;
}

} //namespace advcpp