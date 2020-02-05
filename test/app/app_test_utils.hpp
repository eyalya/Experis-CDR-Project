#ifndef TEST_UTILS_HPP
#define TEST_UTILS_HPP

#include <vector>

#include "irecievers.hpp"
#include "upsertors.hpp"
#include "TCP_acceptor.hpp"
#include "irecorder.hpp"

namespace advcpp
{

void ReciversCreate (std::vector<Irecievers* >& a_workers, WaitableQueue<ISocket*>& a_socketQue, WaitableQueue<char*>& a_msgQue, bool& a_switch, size_t a_nWorkers);

template <typename T> 
void UpsertorsCreate (std::vector<Upsertors<T>* >& a_workers, WaitableQueue<T>& a_msgQue, IRecorder<T>& a_recorder,
                      advcpp::DsContainer& a_dsCont, bool& a_switch, size_t a_nWorkers);

class AcceptorThread: public IRunnable {
public:
    explicit AcceptorThread(IAcceptor* a_acceptor);

    //~AcceptorThread() = default;

    void Run();

private:
    IAcceptor* m_acceptor;
};



} //namespace advcpp

#include "app_test_utils.inl"
#endif //TEST_UTILS_HPP