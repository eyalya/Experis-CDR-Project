#include "mu_test.h"
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include "TCP_client.hpp"
#include "client_test_utils.hpp"
#include "hash_table_safe.hpp"
#include "hash_fun.h"

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
    ASSERT_EQUAL(result.m_cdr.m_imei, 10000085);
END_UNIT



UNIT(run_client)
    const size_t capacity = 1000;
    advcpp::HashTableSafe<uint, protocol::MOC, Hasher> mocTable(capacity, HashC);
    
    Client client(LOOPBACK_ADDR, port);
    const size_t size = 10000;
    for (size_t i=0; i<size; ++i)
    {
        std::ostringstream stream;
        stream << "Messege #" << i;
        std::cout << "sending msg: " << "Messege #" << i << "\n";
        std::string str =  stream.str();       
        client.Send(str.c_str());
    }
    client.Recv();
    client.Close();
    ASSERT_PASS();
END_UNIT


TEST_SUITE(hash table)
    TEST(fill_map)
    IGNORE_TEST(run_client)
END_SUITE

