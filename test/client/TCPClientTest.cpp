#include "mu_test.h"
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <ctime>
#include "TCP_client.hpp"
#include "client_test_utils.hpp"
#include "hash_table_safe.hpp"
#include "hash_fun.h"
#include "encoder.hpp"
#include "i_decoder.hpp"
#include "record.hpp"

typedef advcpp::TCPClient Client;
static const int port = 2300;
static const char* LOOPBACK_ADDR = "127.0.0.1";
typedef size_t (*Hasher)(size_t a_key);
size_t HashC(size_t a_key)
{
    return a_key ^ 3 << 4 ^ 0x45d9f3b;
}

UNIT(fill_map)
    const size_t capacity = 1000;
    const size_t mocTSize = 100;
    advcpp::HashTableSafe<uint, protocol::MOC, Hasher> mocTable(capacity, HashC);
    advcpp::FillMap<uint, protocol::MOC, Hasher> (mocTable, mocTSize);

    protocol::MOC result;
    uint key = 10000085;
    mocTable.Find(key, result);
    ASSERT_EQUAL(result.m_cdr.m_msisdn, 10000085);
END_UNIT

UNIT(run_client_send_char)
    char buffer[] = "\0hey you";

    Client client(LOOPBACK_ADDR, port);
    client.Send(buffer);
    client.Close();
    ASSERT_PASS();
END_UNIT

UNIT(run_client_one)
    protocol::MOC moc;
    char buffer[sizeof(protocol::MOC)];

    moc.m_type = protocol::CALL_MOC;
    moc.m_cdr.m_msisdn = 1984;
    moc.m_cdr.m_imsi = 12;
    moc.m_duration = 20;
    advcpp::EncodeMoc(buffer, moc);
    Client client(LOOPBACK_ADDR, port);
    client.Send(buffer, sizeof(protocol::MOC));

    std::vector<advcpp::IDecodeMassge *>  a_decoders;
    advcpp::DecodeMCO dmco;
    a_decoders.push_back(&dmco);
    a_decoders.push_back(&dmco);
    advcpp::CdrDecoder cDecoder(a_decoders);
    protocol::Message a_message;
    cDecoder.Decode(buffer, a_message);

    std::vector<advcpp::IReducing *> a_reducers;
    advcpp::MCOReducing mcoreducering;
    a_reducers.push_back(&mcoreducering);
    a_reducers.push_back(&mcoreducering);
    advcpp::Reducer reducer(a_reducers);
    advcpp::Record record;
    reducer.Reduce(a_message, record);
    advcpp::SubscriberRecord sRecord(record);

    std::cout << sRecord;


    client.Close();
    ASSERT_PASS();
END_UNIT

UNIT(run_aggragte_message)
    size_t nSends = 10;
    protocol::MOC moc;

    char buffer[sizeof(protocol::MOC)];

    moc.m_type = protocol::CALL_MOC;
    moc.m_cdr.m_msisdn = 1984;
    moc.m_cdr.m_imsi = 12;
    moc.m_duration = 20;
    moc.m_cdr.m_operator.m_value = 10;
    advcpp::EncodeMoc(buffer, moc);
    Client client(LOOPBACK_ADDR, port);
    while (nSends)
    {
        client.Send(buffer, sizeof(protocol::MOC));
        --nSends;
    }
    client.Close();
    ASSERT_PASS();
END_UNIT

// UNIT(run_client)
//     const size_t capacity = 1000;
//     const size_t mocTSize = 100;
//     advcpp::HashTableSafe<uint, protocol::MOC, Hasher> mocTable(capacity, HashC);
//     advcpp::FillMap<uint, protocol::MOC, Hasher> (mocTable, mocTSize);
//     Client client(LOOPBACK_ADDR, port);
//     advcpp::MessageSender mSender(client);
//     mocTable.ForEach<advcpp::MessageSender>(mSender);
//     ASSERT_PASS();
// END_UNIT

// UNIT(run_client_with_adding)
//     const size_t capacity = 1000;
//     const size_t mocTSize = 100;
//     advcpp::HashTableSafe<uint, protocol::MOC, Hasher> mocTable(capacity, HashC);
//     advcpp::HashTableSafe<uint, advcpp::SubscriberRecord, Hasher> subscribersTable(capacity, HashC);
//     advcpp::FillMap<uint, protocol::MOC, Hasher> (mocTable, mocTSize);
//     Client client(LOOPBACK_ADDR, port);
//     advcpp::MessageSender mSender(client);
//     mocTable.ForEach<advcpp::MessageSender>(mSender);
//     ASSERT_PASS();
// END_UNIT


TEST_SUITE(hash table)
    TEST(fill_map)
    // TEST(run_client_one)
    TEST(run_aggragte_message)
    // TEST(run_client)
END_SUITE

