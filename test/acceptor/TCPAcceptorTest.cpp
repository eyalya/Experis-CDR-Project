#include "TCP_acceptor.hpp"

typedef advcpp::WaitableQueue<advcpp::ISocket*> WQueue;
typedef advcpp::TCPAcceptor Server;
static const char* LOOPBACK_ADDR = "127.0.0.1";
static const int port = 2300;

int main()
{    
    WQueue queue;
    Server server(LOOPBACK_ADDR, port, queue);
    
    while(true)
    {
        server.Run();
    }
    return 0;    
}


