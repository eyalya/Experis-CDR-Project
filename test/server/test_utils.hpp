#ifndef TEST_UTILS_HPP
#define TEST_UTILS_HPP

#include <vector>

#include "irecievers.hpp"
#include "upsertors.hpp"
#include "TCP_acceptor.hpp"

namespace advcpp
{

void ReciversCreate (std::vector<CdrRecievers<char*>* >& a_workers, WaitableQueue<ISocket*>& a_socketQue, WaitableQueue<char*>& a_msgQue, bool& a_switch, size_t a_nWorkers)
{
    while (--a_nWorkers)
    {
        advcpp::CdrRecievers<char*> * newWorker = new CdrRecievers(a_socketQue, a_msgQue, a_switch);
        a_workers.push_back(newWorker);
    }
}

template <typename DsCont> 
void UpsertorsCreate (std::vector<Upsertors<DsCont>* >& a_workers, WaitableQueue<char*>& a_msgQue, IRecorder& a_recorder, DsCont& a_dsCont, bool& a_switch, size_t a_nWorkers)
{
    while (--a_nWorkers)
    {
        Upsertors<DsCont>* newWorker = new Upsertors(a_msgQue, a_recorder, a_dsCont, a_switch);
        a_workers.push_back(newWorker);
    }
}

template <typename DsCont> 
class AcceptorThread: public IRunnable {
public:
    explicit AcceptorThread(IAcceptor* a_acceptor) :m_acceptor(a_acceptor) {};

    //~AcceptorThread() = default;
    //AcceptorThread(const AcceptorThread<T>& a_rhs) = default;
    //AcceptorThread& operator = (const AcceptorThread<T> a_rhs) = default;

    void Run() { m_acceptor.Run(); };

private:
    IAcceptor* m_acceptor;
};



} //namespace advcpp

#endif //TEST_UTILS_HPP