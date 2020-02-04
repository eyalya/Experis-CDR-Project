#ifndef I_RECIEVERS_HPP
#define I_RECIEVERS_HPP

#include "waitable_queue.hpp"
#include "socket.hpp"
#include "thread.hpp"

namespace advcpp 
{

class Irecievers: public IRunnable {
public:
    
    ~Irecievers() {};

    //Irecievers();
    //Irecievers(const Irecievers<T>& a_rhs) = delete;
    //Irecievers& operator = (const Irecievers<T> a_rhs) = delete;

    virtual void Run() = 0;
};

template <typename T> 
class CdrRecievers: public Irecievers {
public:
    explicit CdrRecievers(WaitableQueue<ISocket*>& a_socketQue, WaitableQueue<T>& a_msgQue, bool& a_switch);

    //~CdrRecievers() = default;
    //CdrRecievers(const CdrRecievers<T>& a_rhs) = default;
    //CdrRecievers& operator = (const CdrRecievers<T> a_rhs) = default;

    void Run();

private:
    void ReadMsgs();

private:
    WaitableQueue<ISocket*>& m_socketQue;
    WaitableQueue<T>& m_msgQue;
    bool& m_switch; 
    ISocket* m_socket;
};


} //namespace advcpp 

#include "inl/irecievers.inl"
#endif //I_RECIEVERS_HPP
