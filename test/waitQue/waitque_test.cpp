#include "mu_test.h"
#include <iostream> //cout

#include "condVar.hpp"
#include "locks.hpp"
#include "waitable_queue.hpp"
#include "que_runners.hpp"
#include "thread_utils.hpp"
#include "utils.hpp" //makerandom

const size_t g_capacity = 100000;
const size_t g_size = 100000;
const size_t g_nThreads = advcpp::NT;

typedef typename advcpp::Enqueuers<int> Enques;
typedef typename advcpp::Dequeuers<int> Deques;

UNIT(test_vc)
    
    advcpp::Mutex mtx;
    try
    {
        advcpp::CondVar vc(mtx);
    }
    catch(advcpp::VCException& a_error)
    {
        std::cout << a_error.what() << "\n";
    }

    ASSERT_PASS();
  
END_UNIT

UNIT(test_fifo)
    const size_t capacity = g_capacity;
    const size_t size = g_size;
    advcpp::WaitableQueue<int> que(capacity);
    ASSERT_THAT(que.IsEmpty());

    advcpp::Enqueuers<int> enq (que, 0 ,size);
    advcpp::Thread producer(&enq);

    producer.Join();
    advcpp::Dequeuers<int> deq (que, size);
    advcpp::Thread consumer(&deq);
    consumer.Join();
    ASSERT_EQUAL(deq.IsRising(), true);

    std::vector<int>& result = deq.GetVector();
    ASSERT_EQUAL(result.size(), size);
    ASSERT_THAT(advcpp::utils::IsAscending(result.begin(), result.end(), 1));

END_UNIT

UNIT(test_two_producers_one_consumers)
    const size_t capacity = g_capacity;
    const size_t size = g_size;
    const size_t start = 0;
    const size_t nEnquers = 2;
    const size_t nDequers = 1;
    const size_t range = size / nEnquers;
    const size_t nReads = size / nDequers;
    advcpp::WaitableQueue<int> que(capacity);

    std::vector< Enques* > enquersSegments;
    advcpp::CreateSegments<int ,Enques>(que ,start, range, enquersSegments, nEnquers);
    advcpp::RunSegments<Enques>(enquersSegments, nEnquers);

    std::vector<Deques*> dequersSegments;
    advcpp::CreateSegments<int, Deques>(que, nReads, dequersSegments, nDequers);
    advcpp::RunSegments<Deques>(dequersSegments, nDequers);

    std::vector<int>& result = dequersSegments[0]->GetVector();
    ASSERT_EQUAL(result.size(), nReads);
    std::sort(result.begin(), result.end());
    ASSERT_THAT(advcpp::utils::IsAscending(result.begin(), result.end(), 1));
    
        
    // std::vector<int>& result;

    // for (size_t i = 0; i < nDequers; ++i)
    // {   
    //     result = dequersSegments[i].GetVector();
    //     ASSERT_EQUAL(result.size(), size);
    //     ASSERT_THAT(advcpp::utils::IsAscending(result.begin(), result.end()));
    // }
    // while (dequersSegments[0].GetVector())
    // ASSERT_EQUAL(result.size(), nReads);

    //std::for_each(enquersSegments.begin(), enquersSegments.end(), advcpp::iterFuncs::DeleteItems<Deques*>);    
    //std::for_each(dequersSegments.begin(), dequersSegments.end(), advcpp::iterFuncs::DeleteItems<Enques*>);

END_UNIT

UNIT(test_two_consumers_one_producer)
    const size_t capacity = g_capacity;
    const size_t size = g_size;
    const size_t start = 0;
    const size_t nEnquers = 1;
    const size_t nDequers = 2;
    const size_t range = size / nEnquers;
    const size_t nReads = size / nDequers;
    advcpp::WaitableQueue<int> que(capacity);

    std::vector< Enques* > enquersSegments;
    advcpp::CreateSegments<int ,Enques>(que ,start, range, enquersSegments, nEnquers);
    advcpp::RunSegments<Enques>(enquersSegments, nEnquers);

    std::vector<Deques*> dequersSegments;
    advcpp::CreateSegments<int, Deques>(que, nReads, dequersSegments, nDequers);
    advcpp::RunSegments<Deques>(dequersSegments, nDequers);

    for (size_t i = 0; i < nDequers; ++i)
    {   
        std::vector<int>& result = dequersSegments[i]->GetVector();
        ASSERT_EQUAL(result.size(), nReads);
        ASSERT_THAT(advcpp::utils::IsAscending(result.begin(), result.end()));
    }

    bool res =  advcpp::CheckConsumers<Deques, int>(dequersSegments, size, start);
    ASSERT_THAT(res == true);
    
    // std::for_each(enquersSegments.begin(), enquersSegments.end(), advcpp::iterFuncs::DeleteItems<Deques*>);    
    // std::for_each(dequersSegments.begin(), dequersSegments.end(), advcpp::iterFuncs::DeleteItems<Enques*>);

END_UNIT

UNIT(test_n_consumers_n_producer)
    const size_t capacity = g_capacity;
    const size_t size = g_size;
    const size_t start = 0;
    const size_t nTrheads = 5;
    const size_t range = size / nTrheads;
    const size_t nReads = size / nTrheads;
    advcpp::WaitableQueue<int> que(capacity);

    std::vector< Enques* > enquersSegments;
    advcpp::CreateSegments<int ,Enques>(que ,start, range, enquersSegments, nTrheads);

    std::vector<Deques*> dequersSegments;
    advcpp::CreateSegments<int, Deques>(que, nReads, dequersSegments, nTrheads);

    advcpp::RunSegments<Enques, Deques>(enquersSegments, dequersSegments, nTrheads);

    std::vector<int> merged(size);
    std::vector<int>::iterator iter = merged.begin();
    for (size_t i = 0; i < nTrheads; ++i)
    {   
        std::vector<int>& result = dequersSegments[i]->GetVector();
        ASSERT_EQUAL(result.size(), nReads);
        iter = std::copy(result.begin(), result.end(), iter);
            
    }

    std::sort(merged.begin(), merged.end());
    ASSERT_THAT(advcpp::utils::IsAscending(merged.begin(), merged.end(), 1));

    // std::for_each(enquersSegments.begin(), enquersSegments.end(), advcpp::iterFuncs::DeleteItems<Deques*>);    
    // std::for_each(dequersSegments.begin(), dequersSegments.end(), advcpp::iterFuncs::DeleteItems<Enques*>);

END_UNIT


TEST_SUITE(Tip#888262 patience pays off__ your time will come to rise)
    
    TEST(test_vc)
    TEST(test_fifo)
    TEST(test_two_producers_one_consumers)
    TEST(test_two_consumers_one_producer)
    TEST(test_n_consumers_n_producer)
END_SUITE   