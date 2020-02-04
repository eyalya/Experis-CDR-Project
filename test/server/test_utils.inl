#ifndef TEST_UTILS_INL
#define TEST_UTILS_INL

#include "test_utils.hpp"

namespace advcpp
{


void ReciversCreate (std::vector<Irecievers* >& a_workers, WaitableQueue<ISocket*>& a_socketQue, WaitableQueue<char*>& a_msgQue, bool& a_switch, size_t a_nWorkers)
{
    while (--a_nWorkers)
    {
        advcpp::CdrRecievers<char*> * newWorker = new CdrRecievers<char*>(a_socketQue, a_msgQue, a_switch);
        a_workers.push_back(newWorker);
    }
}

template <typename DsCont> 
void UpsertorsCreate (std::vector<Upsertors<DsCont>* >& a_workers, WaitableQueue<char*>& a_msgQue, IRecorder<char*>& a_recorder, DsCont& a_dsCont, bool& a_switch, size_t a_nWorkers)
{
    while (--a_nWorkers)
    {
        Upsertors<DsCont>* newWorker = new Upsertors<DsCont>(a_msgQue, a_recorder, a_dsCont, a_switch);
        a_workers.push_back(newWorker);
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