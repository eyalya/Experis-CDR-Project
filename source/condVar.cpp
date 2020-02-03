#include <pthread.h> //conditional variable
#include <cassert> // assert

#include "condVar.hpp"

namespace advcpp 
{
CondVar::CondVar(Mutex& a_mutex) THROW1(VCException)
:m_mutex(a_mutex)
{
    if (pthread_cond_init(&m_vc, 0) != 0)
    {
        THROWX(VCException);
    }
}

CondVar::~CondVar() NOEXCEPT
{
    int res = pthread_cond_destroy(&m_vc);
    assert(res == 0);
}



void CondVar::Notify() NOEXCEPT
{
    pthread_cond_signal(&m_vc);
}

void CondVar::NotifyAll() NOEXCEPT
{
    pthread_cond_broadcast(&m_vc);
}

} //namespace advcpp 