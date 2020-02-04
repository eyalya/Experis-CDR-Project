#include <iostream>

#include "TCP_acceptor.hpp"
#include "dispatcher.hpp"
#include "ds_container.hpp"
#include "hash_table_safe.hpp"
#include "upsertors.hpp"
#include "irecorder.hpp"
#include "cdr_decoder.hpp"
#include "reducer.hpp"
#include "cdr_factory.hpp"
#include "test_utils.hpp"

typedef size_t (*Hasher)(size_t a_key);

typedef advcpp::WaitableQueue<advcpp::ISocket*> WQSocket;
typedef advcpp::WaitableQueue<char *> WQMsg;
typedef advcpp::CdrRecievers<char*> Receivers;
typedef std::vector<advcpp::Irecievers*> RecieversVec;

typedef advcpp::TCPAcceptor Acceptor;
typedef typename advcpp::HashTableSafe<int, int, Hasher> IntHashSafe;
typedef advcpp::DsContainer HashConts;
typedef advcpp::Upsertors< char* > HashUpsertors;


static const char* LOOPBACK_ADDR = "127.0.0.1";
static const int port = 2300;

int main()
{    
    bool switchButton = true;
    const size_t nRecivers = advcpp::NT - 1;
    const size_t nUpsertors = 2;

    WQSocket queueSocket;
    WQMsg msgQue(10000);

    HashConts dsCont;

    std::vector<advcpp::Irecievers*> msgRecieversVec;
    ReciversCreate (msgRecieversVec, queueSocket, msgQue, switchButton, nRecivers);

    std::vector<advcpp::IReducing* > reducingVec;
    reducingVec.push_back (new advcpp::MCOReducing()); 
    reducingVec.push_back (new advcpp::MCOReducing());
    advcpp::Reducer reducer(reducingVec);

    std::vector<advcpp::IDecodeMassge* > decodersVec;
    decodersVec.push_back(new advcpp::DecodeMCO());
    decodersVec.push_back(new advcpp::DecodeMCO());
    advcpp::CdrDecoder decoder(decodersVec);

    advcpp::RecordAggregator<char*> recorder(decoder ,reducer);

    std::vector<HashUpsertors* > upsertorsVec;
    
    advcpp::UpsertorsCreate<char*>(upsertorsVec, msgQue, recorder, dsCont, switchButton, nUpsertors);

    advcpp::Dispatcher<advcpp::Irecievers*> dispatcher(msgRecieversVec, switchButton);
    dispatcher.ActivateWorkers();

    advcpp::CdrFactory<HashUpsertors*> cdrFactory(upsertorsVec, switchButton);
    cdrFactory.ActivateWorkers();

    advcpp::TCPAcceptor acceptor(LOOPBACK_ADDR, port, queueSocket);
    advcpp::AcceptorThread acceptorActivator(&acceptor);
    advcpp::Thread acceptorThread(&acceptorActivator);

    acceptorThread.Join();
    return 0;
}


