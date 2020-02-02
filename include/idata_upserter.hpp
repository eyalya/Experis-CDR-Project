#ifndef I_DATA_UPSERTER_HPP
#define I_DATA_UPSERTER_HPP

#include "thread.hpp"
#include "waitable_queue.hpp"
#include "socket.hpp"
#include "irunnable.hpp"

namespace advcpp 
{

class IDataUpserter: public IRunnable {
public:
    
    ~IDataUpserter() {};

    //IDataUpserter();
    //IDataUpserter(const IDataUpserter<T>& a_rhs) = delete;
    //IDataUpserter& operator = (const IDataUpserter<T> a_rhs) = delete;

    virtual void Run() = 0;
};

template <typename T> 
//T must be a pointer allocated with new
class CdrUpserter: public IDataUpserter {
public:
    explicit CdrRecievers(WaitableQueue<T>& a_msgQue, IDecoder a_decoder, IReducer a_reducer);

    //~CdrRecievers() = default;
    //CdrRecievers(const CdrRecievers<T>& a_rhs) = default;
    //CdrRecievers& operator = (const CdrRecievers<T> a_rhs) = default;

    void Run();

private:
    void ReadMsgs();

private:
    WaitableQueue<T>& m_msgQue;
    bool m_switch; 
    T m_socket;
};

} //namespace advcpp 

#include "irecievers.inl"
#endif //I_DATA_UPSERTER_HPP