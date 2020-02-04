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

template <typename DsCont> 
void UpsertorsCreate (std::vector<Upsertors<DsCont>* >& a_workers, WaitableQueue<char*>& a_msgQue, IRecorder<char*>& a_recorder, DsCont& a_dsCont, bool& a_switch, size_t a_nWorkers);

class AcceptorThread: public IRunnable {
public:
    explicit AcceptorThread(IAcceptor* a_acceptor);

    //~AcceptorThread() = default;

    void Run();

private:
    IAcceptor* m_acceptor;
};




} //namespace advcpp

#include "test_utils.inl"
#endif //TEST_UTILS_HPP