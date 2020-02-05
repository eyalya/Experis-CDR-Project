#ifndef TEST_UTILS_INL
#define TEST_UTILS_INL

#include "app_test_utils.hpp"

namespace advcpp
{


void ReciversCreate (std::vector<Irecievers* >& a_workers, WaitableQueue<ISocket*>& a_socketQue, WaitableQueue<char*>& a_msgQue, bool& a_switch, size_t a_nWorkers)
{
    while (a_nWorkers)
    {
        advcpp::CdrRecievers<char*> * newWorker = new CdrRecievers<char*>(a_socketQue, a_msgQue, a_switch);
        a_workers.push_back(newWorker);
        --a_nWorkers;
    }
}

template <typename T> 
void UpsertorsCreate (std::vector<Upsertors<T>* >& a_workers, WaitableQueue<T>& a_msgQue, IRecorder<T>& a_recorder, advcpp::DsContainer& a_dsCont, bool& a_switch, size_t a_nWorkers)
{
    while (a_nWorkers)
    {
        Upsertors<T>* newWorker = new Upsertors<T>(a_msgQue, a_recorder, a_dsCont, a_switch);
        a_workers.push_back(newWorker);
        --a_nWorkers;
    }
}

AcceptorThread::AcceptorThread(IAcceptor* a_acceptor)
:m_acceptor(a_acceptor) 
{}

void AcceptorThread::Run() 
{ 
    m_acceptor->Run(); 
}

} //namespace advcpp

#endif //TEST_UTILS_INL 