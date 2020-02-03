#include "cdr_factory_worker.hpp"

namespace advcpp
{

template <typename DsCont> 
CdrFactoryWorker<DsCont>::CdrFactoryWorker(WaitableQueue<char*>& a_msgQue, IRecorder& a_recorder, DsCont& a_dsCont)
: m_msgQue(a_msgQue)
, m_switch(false)
{
}

template <typename DsCont> 
void CdrFactoryWorker<DsCont>::Run()
{
    while (m_switch)
    {
        char* msg = ReadMsgs();
        a_reporter.Generate(msg, m_report);
        DsCont.DsUpserter(m_report);
        delete[] msg;
    }
}

} //namespace advcpp