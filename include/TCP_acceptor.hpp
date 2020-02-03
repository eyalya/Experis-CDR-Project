#ifndef TCP_ACCEPTOR_HPP
#define TCP_ACCEPTOR_HPP
#include "waitable_queue.hpp"
#include "socket.hpp"

namespace advcpp{

static const int DEBUG = 1; //TODO: from configuration file
static const size_t QUEUE_SIZE = 1024; //TODO: from configuration file

class TCPAcceptorException : private ExtendedException
{
public:
    TCPAcceptorException(const char* a_msg, ExtendInfo a_xInfo)
    : ExtendedException(a_msg, a_xInfo) {}
};

class IAcceptor
{
public:
    IAcceptor() {};
    virtual ~IAcceptor() = 0;

    virtual void Run() = 0;
    virtual void ShutDown() = 0;

private:
    IAcceptor(IAcceptor const&);
    IAcceptor& operator=(IAcceptor const&);
};

class TCPAcceptor : public IAcceptor
{
public:
    TCPAcceptor(const char* a_ip, int a_port, WaitableQueue<ISocket*>& a_queue);
    ~TCPAcceptor() {};

    virtual void Run();
    virtual void ShutDown();

private:
    std::string			m_ip;
	int 				m_port;
    Socket                      m_socket;
	WaitableQueue<ISocket*>&     m_queue;    
    char                        m_buff[MAX_BUFF_LEN];
};

}//namespace advcpp

#endif //TCP_ACCEPTOR_HPP