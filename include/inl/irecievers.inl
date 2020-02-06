#include <iostream>
#include <cassert>
#include <unistd.h>

#include "irecievers.hpp"
#include "defs.hpp"


namespace advcpp
{

static const size_t g_maxBuff = 60;

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
    static int cnt = 0;
    int byte = 1;
    int diff = g_maxBuff;
    char* buff = 0;

    while (byte)
    {
        byte = 0;
        diff = g_maxBuff;
        try 
        {
            buff = new char[BUFFER_SIZE];
        }
        catch(std::bad_alloc const& a_except)
        {
            std::cerr << "alloc falied" << "\n";
            sleep(1);
            //log
            continue;
        }

        while (byte != g_maxBuff)
        {
            byte += m_socket->Recv(buff, diff);
            diff = 60 - byte;
            if (byte <= 0)
            {
                delete[] buff;
                delete m_socket;
                //log it
                std::cout << "reciever cnt: " << cnt << "\n";
                return;
            }
        }
        
        assert (byte == 60);
        m_msgQue.Enqueue(buff);
        ++cnt;
    }
    
    
}

} //namespace advcpp
