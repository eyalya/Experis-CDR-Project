#include <iostream>

#include "TCP_acceptor.hpp"
#include "dispatcher.hpp"


typedef advcpp::WaitableQueue<advcpp::ISocket*> WQSocket;
typedef advcpp::WaitableQueue<char *> WQMsg;
typedef advcpp::CdrRecievers<char*> Receivers;
typedef advcpp::TCPAcceptor Acceptor;
static const char* LOOPBACK_ADDR = "127.0.0.1";
static const int port = 2300;

int main()
{    
    bool switchButton = true;
    WQSocket queueSocket;

    WQMsg queReceivers(10);
    Receivers cdrRceiever(queueSocket, queReceivers, switchButton);

    std::vector<advcpp::Irecievers*> vec;
    vec.push_back(&cdrRceiever);

    advcpp::Dispatcher<advcpp::Irecievers*> dispatcher(vec, switchButton);
    dispatcher.ActivateWorkers();
    Acceptor acceptor(LOOPBACK_ADDR, port, queueSocket);
    
    while(true)
    {
        acceptor.Run();
    }
    return 0;
}


