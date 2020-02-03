#ifndef CDR_FACTORY_WORKER_HPP
#define CDR_FACTORY_WORKER_HPP

#include "thread.hpp"
#include "waitable_queue.hpp"
#include "irunnable.hpp"
#include "irecorder.hpp"
#include "i_record.hpp"

namespace advcpp 
{

template <typename DsCont> 
class CdrFactoryWorker: public IRunnable {
public:
    explicit CdrFactoryWorker(WaitableQueue<char*>& a_msgQue, IRecorder& a_recorder, DsCont& a_dsCont);

    //~CdrRecievers() = default;
    //CdrRecievers(const CdrRecievers<T>& a_rhs) = default;
    //CdrRecievers& operator = (const CdrRecievers<T> a_rhs) = default;

    void Run();

private:
    void ReadMsgs();

private:
    WaitableQueue<char*>& m_msgQue;
    IRecorder& m_recorder;
    bool m_switch; 
    IRecord & m_record;
};

} //namespace advcpp 

#include "cdr_factory_worker.inl"
#endif //CDR_FACTORY_WORKER_HPP