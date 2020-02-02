#include "condVar.hpp"
namespace advcpp
{


template <typename Predicate>
void CondVar::Wait(Predicate const& a_pred) NOEXCEPT
{
    while (a_pred())
    {
        int res = pthread_cond_wait(&m_vc ,&m_mutex.getLock());
        assert(res == 0);
    }
}


} //namespace advcpp