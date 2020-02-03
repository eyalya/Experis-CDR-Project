#include "idata_upserter.hpp"

namespace advcpp
{
    
// template <typename T> 
// CdrRecievers<T>::CdrRecievers(WaitableQueue<ISocket*>& a_socketQue, WaitableQueue<char*>& a_msgQue)
// : m_socketQue(a_socketQue)
// , m_msgQue (a_msgQue)
// , m_switch(true)
// {
// }

// template <typename T> 
// void CdrRecievers<T>::Run()
// {
//     while (m_switch)
//     {
//         std::cout << "running\n";
//         m_socketQue.Dequeue(m_socket);
//         ReadMsgs();
//     }
// }

// template <typename T> 
// void CdrRecievers<T>::ReadMsgs()
// {
//     int byte = 1;
//     while (byte)
//     {
//         char* buff = new char[BUFFER_SIZE];
//         byte = m_socket->Recv(buff);
//         if (byte <= 0)
//         {
//             delete[] buff;
//             m_socket->Close();
//             //log it
//             break;
//         }

//         m_msgQue.Enqueue(buff);
//     }
// }

} //namespace advcpp
