#include <iostream>

#include "TCP_acceptor.hpp"
#include "dispatcher.hpp"
#include "ds_container.hpp"
#include "hash_table_safe.hpp"

typedef size_t (*Hasher)(size_t a_key);

typedef advcpp::WaitableQueue<advcpp::ISocket*> WQSocket;
typedef advcpp::WaitableQueue<char *> WQMsg;
typedef advcpp::CdrRecievers<char*> Receivers;
typedef std::vector<advcpp::Irecievers*> RecieversVec;
typedef advcpp::TCPAcceptor Acceptor;
typedef typename advcpp::HashTableSafe<int, int, Hasher> IntHashSafe;


static const char* LOOPBACK_ADDR = "127.0.0.1";
static const int port = 2300;

int main()
{    
    bool switchButton = true;
    const size_t nRecivers = 2;
    const size_t nUpsertors = 2;

    WQSocket queueSocket;
    WQMsg queReceivers(10);

    RecieversVec msgRecievers;
    Receivers cdrRceiever(queueSocket, queReceivers, switchButton);

    DsContainer<HashTableSafe> dsCont;

    ReciversCreate (msgRecievers, queueSocket, queReceivers, switchButton, nRecivers);
    UpsertorsCreate (std::vector<Upsertors<DsCont>* >& a_workers, WaitableQueue<char*>& a_msgQue, IRecorder& a_recorder, DsCont& a_dsCont, switchButton, nUpsertors)

    advcpp::Dispatcher<advcpp::Irecievers*> dispatcher(vec, switchButton);
    dispatcher.ActivateWorkers();
    Acceptor acceptor(LOOPBACK_ADDR, port, queueSocket);
    
    while(true)
    {
        acceptor.Run();
    }
    return 0;
}


