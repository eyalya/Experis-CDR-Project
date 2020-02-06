#ifndef UPSERTORS_INL
#define UPSERTORS_INL

#include <iostream>
#include "upsertors.hpp"

namespace advcpp
{

//FIXME: change char* to T
template <typename T> 
Upsertors<T>::Upsertors(WaitableQueue<T>& a_msgQue, IRecorder<T>& a_recorder, DsContainer& a_dsCont, bool& a_switch)
: m_msgQue(a_msgQue)
, m_recorder (a_recorder)
, m_dsCont(a_dsCont)
, m_switch(a_switch)
, m_record()
{
}

//FIXME: add exception handling
template <typename T> 
void Upsertors<T>::Run()
{
    static int cnt = 0;
    char* msg;
    while (m_switch)
    {
        m_msgQue.Dequeue(msg);
        m_recorder.Generate(msg, m_record);
        m_dsCont.DsUpsert(m_record);
        SubscriberRecord sR(m_record);
        delete[] msg;
        ++cnt;
        std::cout << "upsertor cnt: " << cnt << "\n";
    }

}


} //namespace advcpp

#endif //UPSERTORS_INL