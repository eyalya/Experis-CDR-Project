#ifndef I_RECIEVERS_HPP
#define I_RECIEVERS_HPP

#include "thread.hpp"
#include "waitable_queue.hpp"
#include "socket_hpp"
#include "irunnable.hpp"

namespace advcpp 
{

class Irecievers {
public:
    
    ~Irecievers() {};

    //Irecievers();
    //Irecievers(const Irecievers<T>& a_rhs) = default;
    //Irecievers& operator = (const Irecievers<T> a_rhs) = default;

    virtual void Run() = 0;
};

class CdrRecievers: public Irecievers {
public:
    explicit CdrRecievers(WaitableQueue<Socket>& a_socketQue, WaitableQueue<char*> a_msgQue);

    //~CdrRecievers() = default;
    //CdrRecievers(const CdrRecievers<T>& a_rhs) = default;
    //CdrRecievers& operator = (const CdrRecievers<T> a_rhs) = default;

    void Run();

private:
    std::vector<Thread> m_threads;
    WaitableQueue<Socket>& m_socketQue;
    WaitableQueue<char*> m_msgQue;
};

} //namespace advcpp 

// #include "Iinterface.inl"
#endif //I_RECIEVERS_HPP
