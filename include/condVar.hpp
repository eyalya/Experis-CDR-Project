#ifndef CONDVAR_HPP
#define CONDVAR_HPP
#include "mutex.hpp"
namespace advcpp{

static const size_t INIT_RETRIES = 4;

class CondVarException : public ExtendedException
{
public:
    explicit CondVarException(const char* a_msg, ExtendInfo a_xInfo);
};

class CondVar : private Uncopyable
{
public:
    CondVar() THROW1(CondVarException);
    ~CondVar() NOEXCEPT;

    template <typename Pred>
    void Wait(Mutex& a_mutex, Pred a_pred) THROW1(CondVarException);
    void Notify() THROW1(CondVarException);
    void NotifyAll() THROW1(CondVarException);
    
private:
    pthread_cond_t m_cv;
};

}//namespace advcpp

#include "inl/condVar.inl"
#endif //CONDVAR_HPP