#include "irecievers.hpp"
#include "defs.hpp"
#include <iostream>

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
    std::cout << "wait for socket\n";
    while (m_switch)
    {
        m_socketQue.Dequeue(m_socket);
        std::cout << "got socket, queing msg\n";
        ReadMsgs();
    }
}

template <typename T> 
void CdrRecievers<T>::ReadMsgs()
{
    int byte = 1;
    while (byte)
    {
        char* buff = new char[BUFFER_SIZE];
        std::cout << "reading msg\n";
        byte = m_socket->Recv(buff);
        std::cout << "msg size " <<  byte << "\n";
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
