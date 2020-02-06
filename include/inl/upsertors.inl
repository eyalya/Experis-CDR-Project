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
    T msg;

    while (m_switch)
    {
        try
        {
            m_msgQue.Dequeue(msg);
            m_recorder.Generate(msg, m_record);
            m_dsCont.DsUpsert(m_record);
            SubscriberRecord sR(m_record);
            delete[] msg;
        }
        catch(const std::exception& e)
        {
            delete[] msg;
            std::cerr << e.what() << '\n';
        }
    }

}


} //namespace advcpp

#endif //UPSERTORS_INL