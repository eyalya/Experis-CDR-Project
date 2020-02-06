#include <iostream>
#include <cassert>
#include <unistd.h>
#include <cstring>

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
        HandleSocket();
    }
}

template <typename T> 
void CdrRecievers<T>::HandleSocket()
{
    char* buff = 0;
    const size_t forever = 1;

    while (forever)
    {
        try 
        {
            buff = new char[g_maxBuff + 1];
        }
        catch(std::bad_alloc const& a_except)
        {
            std::cerr << "alloc falied" << "\n";
            sleep(1);
            //log
            continue;
        }

        if (ReadMsg(buff) <= 0)
        {
            delete[] buff;
            delete m_socket;
            //log it
            return;
        }

        m_msgQue.Enqueue(buff);
    }
}

template <typename T> 
int CdrRecievers<T>::ReadMsg(char* a_newMsg)
{
    int byteRead = 0;
    int accumulateRead = 0;
    int diff = g_maxBuff;
    char temp[g_maxBuff];
    
    while (accumulateRead != g_maxBuff)
    {
        byteRead = m_socket->Recv(temp, diff);
        if (byteRead <= 0)
        {
            return byteRead;
        }

        memcpy(a_newMsg + accumulateRead, temp, diff);
        accumulateRead += byteRead; 
        diff = g_maxBuff - accumulateRead;
    }
    
    assert (accumulateRead == g_maxBuff);
    return accumulateRead;
}




} //namespace advcpp
