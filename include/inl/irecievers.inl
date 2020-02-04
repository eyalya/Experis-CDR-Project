#include <iostream>
#include <cassert>
#include "irecievers.hpp"
#include "defs.hpp"

namespace advcpp
{
    
template <typename T> 
CdrRecievers<T>::CdrRecievers(WaitableQueue<ISocket*>& a_socketQue, WaitableQueue<T>& a_msgQue, bool& a_switch)
: m_socketQue(a_socketQue)
, m_msgQue (a_msgQue)
, m_switch(a_switch)
{
}

template <typename T> 
void CdrRecievers<T>::Run()
{
    while (m_switch)
    {
        m_socketQue.Dequeue(m_socket);
        ReadMsgs();
    }
}

template <typename T> 
void CdrRecievers<T>::ReadMsgs()
{
    int byte = 1;
    char* buff = 0;
    while (byte)
    {
        try 
        {
            buff = new char[BUFFER_SIZE];
        }
        catch(...)
        {
            std::cout << "alloc falied" << "\n";
            continue;
        }
        byte = m_socket->Recv(buff);
        if (byte <= 0)
        {
            delete[] buff;
            m_socket->Close();
            //log it
            break;
        }

        m_msgQue.Enqueue(buff);
    }
}

} //namespace advcpp
