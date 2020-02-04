#include "mu_test.h"
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
UNIT(server_one_thread_each)
    bool switchButton = true;
    const size_t nRecivers = 1;
    const size_t nUpsertors = 1;

    WQSocket queueSocket;
    WQMsg msgQue(10000);

    HashConts dsCont;

    std::vector<advcpp::Irecievers*> msgRecieversVec;
    advcpp::ReciversCreate (msgRecieversVec, queueSocket, msgQue, switchButton, nRecivers);

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
    ASSERT_PASS();
END_UNIT

UNIT(server_multi)
    bool switchButton = true;
    const size_t nRecivers = advcpp::NT - 1;
    const size_t nUpsertors = 2;

    WQSocket queueSocket;
    WQMsg msgQue(10000);

    HashConts dsCont;

    std::vector<advcpp::Irecievers*> msgRecieversVec;
    advcpp::ReciversCreate (msgRecieversVec, queueSocket, msgQue, switchButton, nRecivers);

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
    ASSERT_PASS();
END_UNIT


TEST_SUITE(Collect knowledge from every place you can)
    TEST(server_multi)
    TEST(server_one_thread_each)
END_SUITE

