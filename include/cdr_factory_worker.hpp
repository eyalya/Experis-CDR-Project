#ifndef CDR_FACTORY_WORKER_HPP
#define CDR_FACTORY_WORKER_HPP

#include "thread.hpp"
#include "waitable_queue.hpp"
#include "socket.hpp"
#include "irunnable.hpp"

namespace advcpp 
{

template <typename T, typename DsCont> 
//T must be a pointer allocated with new
class CdrFactoryWorker: public IRunnable {
public:
    explicit CdrRecievers(WaitableQueue<T>& a_msgQue, IDecoder& a_decoder, IReducer& a_reducer, DsCont& a_dsCont);

    //~CdrRecievers() = default;
    //CdrRecievers(const CdrRecievers<T>& a_rhs) = default;
    //CdrRecievers& operator = (const CdrRecievers<T> a_rhs) = default;

    void Run();

private:
    void ReadMsgs();

private:
    WaitableQueue<T>& m_msgQue;
    IDecoder& m_decoder; 
    IReducer& m_reducer;
    bool m_switch; 

};

} //namespace advcpp 

#include "cdr_factory_worker.inl"
#endif //CDR_FACTORY_WORKER_HPP