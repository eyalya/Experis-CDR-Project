#ifndef UPSERTORS_INL
#define UPSERTORS_INL

#include "upsertors.hpp"

namespace advcpp
{

//TODO: irecorder need to get t template
template <typename DsCont> 
Upsertors<DsCont>::Upsertors(WaitableQueue<char*>& a_msgQue, IRecorder<char*>& a_recorder, DsCont& a_dsCont, bool& a_switch)
: m_msgQue(a_msgQue)
, m_recorder (a_recorder)
, m_dsCont(a_dsCont)
, m_switch(a_switch)
, m_record()
{
}

template <typename DsCont> 
void Upsertors<DsCont>::Run()
{
    char* msg;
    while (m_switch)
    {
        m_msgQue.Dequeue(msg);
        m_recorder.Generate(msg, m_record);
        m_dsCont.DsUpserter(&m_record);
        delete[] msg;
    }
}


} //namespace advcpp

#endif //UPSERTORS_INL