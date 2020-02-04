#ifndef UPSERTORS_INL
#define UPSERTORS_INL

#include <iostream>
#include "upsertors.hpp"

namespace advcpp
{

template <typename T> 
Upsertors<T>::Upsertors(WaitableQueue<T>& a_msgQue, IRecorder<T>& a_recorder, DsContainer& a_dsCont, bool& a_switch)
: m_msgQue(a_msgQue)
, m_recorder (a_recorder)
, m_dsCont(a_dsCont)
, m_switch(a_switch)
, m_record()
{
}

template <typename T> 
void Upsertors<T>::Run()
{
    char* msg;
    std::cout << "running\n";
    while (m_switch)
    {
        std::cout << "waiting for message\n";
        m_msgQue.Dequeue(msg);
        std::cout << "got message\n";
        m_recorder.Generate(msg, m_record);
        std::cout << SubscriberRecord(m_record) << "\n";
        std::cout << "i am  here \n";
        m_dsCont.DsUpsert(m_record);
        std::cout << m_record << "\n";
        delete[] msg;
    }
}


} //namespace advcpp

#endif //UPSERTORS_INL