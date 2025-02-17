#include "mu_test.h"
#include <iostream>
#include <utility>
#include <vector>
#include "hash_table_safe.hpp"
#include "thread.hpp"

typedef size_t (*Hasher)(size_t a_key);

typedef std::pair<int, int> Pair;
typedef typename std::list<Pair> Bucket;
typedef typename advcpp::HashTableSafe<int, int, Hasher> IntHashSafe;
typedef advcpp::Thread Thread;
typedef std::vector<advcpp::IRunnable*> RunPull;
typedef std::vector<Thread*> ThreadPull;

template <typename T>
class MultBy
{
public:
    MultBy(T a_factor) : m_factor(a_factor) {};
    //rule 3

    void operator()(T& a_value){a_value *= m_factor;}

private:
    T m_factor;
};

template <typename Key, typename Value, typename Hasher>
void UpsertHash(advcpp::HashTableSafe<Key, Value, Hasher>& a_table, unsigned int a_pairs, size_t size);

size_t HashC(size_t a_key)
{
    return a_key ^ 3 << 4 ^ 0x45d9f3b;
}

template <typename T>
class Adder
{
public:
	void operator()(T& a_lhs, T const& a_rhs)
    { a_lhs += a_rhs; }
};

////////////////////////////////////////////////////////////////////////

template <typename Key, typename Value, typename Hasher>
class AddUp : public advcpp::IRunnable
{
public:
    AddUp(advcpp::HashTableSafe<Key, Value, Hasher>& a_table, size_t a_size);
    //rule 3 = default;
    virtual void Run();

private:
    advcpp::HashTableSafe<Key, Value, Hasher>& m_table;
    size_t m_size;
};

template <typename Key, typename Value, typename Hasher>
AddUp<Key, Value, Hasher>::AddUp(advcpp::HashTableSafe<Key, Value, Hasher>& a_table, size_t a_size)
: m_table(a_table)
, m_size(a_size)
{
}

template <typename Key, typename Value, typename Hasher>
void AddUp<Key, Value, Hasher>::Run()
{
    size_t i = 0;
    while(i < m_size)
    {
        m_table.Upsert(i, 1, Adder<Key>());
        ++i;
    }
}

////////////////////////////////////////////////////////////////////////

template <typename Key, typename Value, typename Hasher>
class AddDown : public advcpp::IRunnable
{
public:
    AddDown(advcpp::HashTableSafe<Key, Value, Hasher>& a_table, size_t a_size);
    //rule 3 = default;
    virtual void Run();

private:
    advcpp::HashTableSafe<Key, Value, Hasher>& m_table;
    size_t m_size;
};

template <typename Key, typename Value, typename Hasher>
AddDown<Key, Value, Hasher>::AddDown(advcpp::HashTableSafe<Key, Value, Hasher>& a_table, size_t a_size)
: m_table(a_table)
, m_size(a_size)
{
}

template <typename Key, typename Value, typename Hasher>
void AddDown<Key, Value, Hasher>::Run()
{
    size_t i = m_size;
    while(i --> 0)
    {
        m_table.Upsert(i, 1, Adder<Key>());       
    }
}
////////////////////////////////////////////////////////////////////////

template <typename Key, typename Value, typename Hasher>
class ReduceDown : public advcpp::IRunnable
{
public:
    ReduceDown(advcpp::HashTableSafe<Key, Value, Hasher>& a_table, size_t a_size);
    //rule 3 = default;
    virtual void Run();

private:
    advcpp::HashTableSafe<Key, Value, Hasher>& m_table;
    size_t m_size;
};

template <typename Key, typename Value, typename Hasher>
ReduceDown<Key, Value, Hasher>::ReduceDown(advcpp::HashTableSafe<Key, Value, Hasher>& a_table, size_t a_size)
: m_table(a_table)
, m_size(a_size)
{
}

template <typename Key, typename Value, typename Hasher>
void ReduceDown<Key, Value, Hasher>::Run()
{
    size_t i = m_size;
    while(i-->0)
    {
        m_table.Upsert(i, -1, Adder<Key>());
    }
}

////////////////////////////////////////////////////////////////////////

template <typename Key, typename Value, typename Hasher>
void UpsertHash(advcpp::HashTableSafe<Key, Value, Hasher>& a_table, unsigned int a_pairs, size_t a_size)
{   
	RunPull addsUp;
    RunPull addsDown;
    for (size_t i=0; i<a_pairs; ++i)
    {
        addsUp.push_back(new AddUp<Key, Value, Hasher>(a_table, a_size));
        addsDown.push_back(new AddDown<Key, Value, Hasher>(a_table, a_size));
    }    
   
    ThreadPull threads;   
    for (size_t i=0; i<a_pairs; ++i)
    {
        threads.push_back(new Thread(addsUp[i]));
        threads.push_back(new Thread(addsDown[i]));
    }

    for (size_t i=0; i<2*a_pairs; ++i)
    {
        threads[i]->Join();
        delete threads[i];        
    }

    for (size_t i=0; i<a_pairs; ++i)
    {       
        delete addsUp[i];
        delete addsDown[i];
    }   
}

////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

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

UNIT(upsert_single_upserts)
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

UNIT(upsert_many_upserts)
    const size_t capacity = 3;
    IntHashSafe table(capacity, HashC);
   
    const int size = 100;
    const int n = 5;
    for (size_t i=0; i<size; ++i)
    {
        table.Upsert(i, 1, Adder<int>());
        ASSERT_EQUAL(table.Size(), i+1);
    }
    
    for (int i=0; i<n; ++i)
    {
        for (int j=0; j<size; ++j)
        {
            table.Upsert(j, 1, Adder<int>());
            int data;
            table.Find(j, data);
            ASSERT_EQUAL(data, i+2);
            ASSERT_EQUAL(table.Size(), size);
        }
    }
END_UNIT

UNIT(foreach_works_on_full_map)
    const size_t size = 100000;
    const size_t capacity = 100;
    IntHashSafe table(capacity, HashC);
    
    for (size_t i=0; i<size; ++i)
    {
       table.Insert(i, i);
    }
    int factor = 10;
    size_t counter = table.ForEach(MultBy<int>(factor));
    ASSERT_EQUAL(counter, size);
    
    for (int i=0; i<(int)size; ++i)
    {
       int data;
       table.Find(i, data);
       ASSERT_EQUAL(data, i*factor);
    }    
    ASSERT_EQUAL(table.Size(), size);
END_UNIT  

UNIT(foreach_works_on_non_full_map)
    const size_t size = 100;
    const size_t capacity = 1000;
    IntHashSafe table(capacity, HashC);
    
    for (size_t i=0; i<size; ++i)
    {
       table.Insert(i, i);
    }
    int factor = 10;
    size_t counter = table.ForEach(MultBy<int>(factor));
    ASSERT_EQUAL(counter, size);
    
    for (int i=0; i<(int)size; ++i)
    {
       int data;
       table.Find(i, data);
       ASSERT_EQUAL(data, i*factor);
    }    
    ASSERT_EQUAL(table.Size(), size);
END_UNIT  

UNIT(hash_table_upserts_thread_safely)
    const size_t capacity = 100;
    IntHashSafe table(capacity, HashC);

    const size_t pairs = 20;
    const size_t size = 10000;

    UpsertHash<int, int, Hasher>(table, pairs, size);
    
    for (size_t i=0; i < 2 * pairs; ++i)
    {
        int data;
        ASSERT_EQUAL(table.Find(i, data), true);
        ASSERT_EQUAL(data, pairs*2);
    }
    ASSERT_EQUAL(table.Size(), size);
END_UNIT

///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

TEST_SUITE(hash table)
    TEST(find_finds_inserted_int_remove_removes)
    TEST(insert_doesnt_insert_existing_remove_remove_once)
    TEST(upsert_single_upserts)
    TEST(upsert_many_upserts)
    TEST(foreach_works_on_full_map)
    TEST(foreach_works_on_non_full_map)
    TEST(hash_table_upserts_thread_safely)
END_SUITE

////////////////////////////////////////////////////////////////////////////
