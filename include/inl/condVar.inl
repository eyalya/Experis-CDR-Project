#ifndef CONDVAR_INL
#define CONDVAR_INL
#include <pthread.h>
#include <cerrno> //errno
#include <cstring> //strerror

#include "defs.hpp" //g_defsSystemFail
#include "common.hpp"

namespace advcpp{

inline CondVarException::CondVarException(const char* a_msg, ExtendInfo a_xInfo)
: ExtendedException(a_msg, a_xInfo)
{    
}

inline CondVar::~CondVar() NOEXCEPT
{
    pthread_cond_destroy(&m_cv);
}

template<typename Pred>
void CondVar::Wait(Mutex& a_mutex, Pred a_pred) THROW1(CondVarException)
{
    while(a_pred())
    {
        if (pthread_cond_wait(&m_cv, a_mutex.GetMutex()) == g_defsSystemFail)
        {
            throw CondVarException(strerror(errno), ExtendInfo(XINFO));
        }
    }
}


}//namespace advcpp

#endif //CONDVAR_INL