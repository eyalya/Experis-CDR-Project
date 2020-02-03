#include "cdr_factory_worker.hpp"

namespace advcpp
{

template <typename DsCont> 
Upsertors<DsCont>::Upsertors(WaitableQueue<char*>& a_msgQue, IRecorder& a_recorder, DsCont& a_dsCont, bool& a_switch)
: m_msgQue(a_msgQue)
, m_recorder (a_recorder)
, m_dsCont(a_dsCont)
, m_switch(a_switch)
{
}

template <typename DsCont> 
void Upsertors<DsCont>::Run()
{
    while (m_switch)
    {
        char* msg = ReadMsgs();
        m_reporter.Generate(msg, m_report);
        DsCont.DsUpserter(m_report);
        delete[] msg;
    }
}

} //namespace advcpp