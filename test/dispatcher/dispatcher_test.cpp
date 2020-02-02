#include "mu_test.h"
#include <iostream> //cout
#include <vector>

#include "common.hpp"
#include "dispatcher.hpp"

const size_t g_capacity = 100000;
const size_t g_size = 100000;
const size_t g_nThreads = advcpp::NT;


UNIT(test_vc)
    advcpp::WaitableQueue<char *> queReceivers(10);
    advcpp::WaitableQueue<advcpp::ISocket*> queSockets(10);
    
    advcpp::CdrRecievers<char*> cdrRceiever(queSockets, queReceivers);
    std::vector<advcpp::Irecievers*> vec;
    vec.push_back(&cdrRceiever);

    advcpp::Dispatcher<advcpp::Irecievers*> dispatcher(vec);
    dispatcher.ActivateWorkers();
    ASSERT_PASS();
  
END_UNIT



TEST_SUITE(Tip#888262 patience pays off__ your time will come to rise)
    
    TEST(test_vc)
END_SUITE   