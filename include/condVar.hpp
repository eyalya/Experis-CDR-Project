#ifndef COND_VAR_H
#define COND_VAR_H

#include "common.hpp"
#include "enriched_exeptions.hpp" // EnrichedExeption
#include "locks.hpp" //mutexs

namespace advcpp
{

class VCException: public EnrichedExeption {
public:
    explicit VCException (InfoException a_info, const char* a_msg = "Vc Failed")
    : EnrichedExeption(a_msg, a_info) 
    {};
};

class CondVar: public UnCopiable {
public:
    explicit CondVar(Mutex& a_mutex) THROW1(VCException);
    ~CondVar() NOEXCEPT;
    //CondVar(const CondVar<T>& a_rhs) = deleted;
    //CondVar& operator = (const CondVar<T> a_rhs)  = deleted;

    template <typename Predicate>
    void Wait(Predicate const& a_pred) NOEXCEPT;
    void Notify() NOEXCEPT;
    void NotifyAll() NOEXCEPT;    
private:
    Mutex& m_mutex;
    pthread_cond_t m_vc;
};


} // namespace advcpp

#include "condVar.inl"

#endif //COND_VAR_H