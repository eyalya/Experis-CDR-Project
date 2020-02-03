#include <pthread.h>
#include <errno.h> 
#include "condVar.hpp"
#include "common.hpp"
#include "numbers.hpp"

namespace advcpp{

CondVar::CondVar() THROW1(CondVarException)
{
    size_t retry = INIT_RETRIES;
    
    int r = pthread_cond_init(&m_cv, 0);
    if (r == 0)
    {
        return;
    }
    if (r == EAGAIN)
    {
        while (retry--)
        {
            if (! pthread_cond_init(&m_cv, 0))
            {
                return;
            }
        }
    }
    throw CondVarException(numbers::Itoa(r), ExtendInfo(XINFO));    
}

void CondVar::Notify() THROW1(CondVarException)
{
    if (int r = pthread_cond_signal(&m_cv))
    {
        throw CondVarException(numbers::Itoa(r), ExtendInfo(XINFO));
    }    
}

void CondVar::NotifyAll() THROW1(CondVarException)
{
    if (int r = pthread_cond_broadcast(&m_cv))
    {
        throw CondVarException(numbers::Itoa(r), ExtendInfo(XINFO));
    }
}

}//namespace advcpp