#include <iostream>
#include <utility>
#include "mu_test.h"
#include "hash_table_safe.hpp"
//#include "thread.hpp"

typedef size_t (*Hasher)(size_t a_key);

typedef std::pair<int, int> Pair;
typedef typename std::list<Pair> Bucket;
typedef typename advcpp::HashTableSafe<int, int, Hasher> IntHashSafe;


template <typename T>
class Adder
{
public:
	void operator()(T& a_lhs, T const& a_rhs)
    { a_lhs += a_rhs; }
};

size_t HashC(size_t a_key)
{
    return a_key ^ 3 << 4 ^ 0x45d9f3b;
}

UNIT(find_finds_inserted_int_remove_removes)
    const size_t size = 1000;
    const size_t capacity = 7;
    IntHashSafe table(capacity, HashC);
    for (size_t i=0; i<size; ++i)
    {
        ASSERT_EQUAL(table.Insert(i, i*10), true);       
    }
    
    for (size_t i=0; i<size; ++i)
    {
        int data;
        ASSERT_EQUAL(table.Find(i, data), true);
        ASSERT_EQUAL(data, static_cast<int>(i*10));
    }
   
    int data;
    for (size_t i=0; i<size; ++i)
    {
        ASSERT_EQUAL(table.Remove(i, data), true);
        ASSERT_EQUAL(data, static_cast<int>(i*10));
        ASSERT_EQUAL(table.Size(), size-i-1);
    }
END_UNIT

UNIT(insert_doesnt_insert_existing_remove_remove_once)
    const size_t capacity = 7;
    IntHashSafe table(capacity, HashC);

    ASSERT_EQUAL(table.Insert(6, 666), true);
    ASSERT_EQUAL(table.Size(), 1);
    
    ASSERT_EQUAL(table.Insert(6, 666), false);
    ASSERT_EQUAL(table.Size(), 1);

    int data;
    ASSERT_EQUAL(table.Remove(6, data), true);
    ASSERT_EQUAL(data, 666);   
    ASSERT_THAT(table.IsEmpty());

    data = 123;
    ASSERT_EQUAL(table.Remove(6, data), false);
    ASSERT_EQUAL(data, 123);
    ASSERT_THAT(table.IsEmpty());
END_UNIT

UNIT(update_updates)
    const size_t capacity = 3;
    IntHashSafe table(capacity, HashC);
   
    table.Insert(6, 666);
    int data;
    table.Find(6, data);
    ASSERT_EQUAL(data, 666);
    ASSERT_EQUAL(table.Size(), 1);

    bool res = table.Upsert(6, 333, Adder<int>());
    ASSERT_EQUAL(res, true);
    ASSERT_EQUAL(table.Size(), 1);
    table.Find(6, data);    
    ASSERT_EQUAL(data, 999);    
END_UNIT
/*
UNIT(iterators_iterates_over_all_full)
    const size_t size = 1000;
    const size_t capacity = 7;
    IntHashSafe table(capacity, HashC);
    for (size_t i=0; i<size; ++i)
    {
       table.Insert(i, i*10);        
    }

    IntHashSafe::iterator begin = table.Begin();
    IntHashSafe::iterator end = table.End();
    size_t counter = 0;
    while(begin != end)
    {
        ASSERT_EQUAL((begin->first)*10, begin->second);
        ++begin;
        ++counter;
    }
    ASSERT_EQUAL(counter, size);
    ASSERT_EQUAL(table.Size(), size);
END_UNIT  

UNIT(iterators_iterates_over_all_not_full)
    const size_t size = 40;
    const size_t capacity = 100;
    IntHashSafe table(capacity, HashC);
    for (size_t i=0; i<size; ++i)
    {
       table.Insert(i, i*10);        
    }

    IntHashSafe::iterator begin = table.Begin();
    IntHashSafe::iterator end = table.End();
    size_t counter = 0;
    while(begin != end)
    {
        ASSERT_EQUAL((begin->first)*10, begin->second);
        ++begin;
        ++counter;
    }
    ASSERT_EQUAL(counter, size);
    ASSERT_EQUAL(table.Size(), size);
END_UNIT  
*/

UNIT(hash_table_upserts_thread_safely)
    /*
    clock_t t;    
    advcpp::Mutex mutex;
    advcpp::Context cont(a_times, mutex);
    pthread_t adderTh;
    pthread_t SubTh;
    
    t = clock();
    if (int r = pthread_create(&adderTh, 0, advcpp::AdderMutex, &cont))
    {
        throw ThreadException(numbers::Itoa(r), ExtendInfo(XINFO));
    }
    if (int r =pthread_create(&SubTh, 0, advcpp::SubtractorMutex, &cont))
    {
        throw ThreadException(numbers::Itoa(r), ExtendInfo(XINFO));
    }    
    void *status;
    pthread_join(adderTh, &status);
    pthread_join(SubTh, &status);
    t = clock() - t;
          
    if (0 == x)
    {
        std::cout << "PASS\n";
    }
    else
    {
        std::cout << "FAILED\n";
    }
    
    float tf = static_cast<float>(t) / CLOCKS_PER_SEC;
    std::cout <<  "Mutex: " << tf << "sec\n";  


    Thread adder(Add);
    Thread reducer(Reduce);
    */
END_UNIT

TEST_SUITE(hash table)
    TEST(find_finds_inserted_int_remove_removes)
    TEST(insert_doesnt_insert_existing_remove_remove_once)
    TEST(update_updates)
    //TEST(iterators_iterates_over_all_full)
    //TEST(iterators_iterates_over_all_not_full)
    //TEST(hash_table_upserts_thread_safely)
END_SUITE



