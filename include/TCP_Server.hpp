#ifndef TCP_SERVER_HPP
#define TCP_SERVER_HPP
#include "TCP_acceptor.hpp"
#include "dispatcher.hpp"


namespace advcpp{

class IServer
{
public:
    virtual ~IServer() = 0;
    
    virtual void Run() = 0;
    virtual void Shutdown() = 0;

private:
    IServer(IServer const&);
    IServer& operator=(IServer const&);
};





class TCPServer : public IServer
{
public:
    typedef WaitableQueue<advcpp::ISocket*> WQSocket;
    typedef WaitableQueue<char*> WQMsg;

public:
    TCPServer(IAcceptor& a_acceptor, Dispatcher<>& a_dispatcher);
    ~TCPServer();
    
    virtual void Run();
    virtual void Shutdown();

private:
    void Init();
};

////////////////////////////////////////////////////////////////////////

IServer::~IServer()
{
}

void TCPServer::Run()
{

}


}//namespace advcpp
#endif //TCP_SERVER_HPP