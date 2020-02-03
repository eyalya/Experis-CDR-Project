#include "mu_test.h"
#include "waitable_queue.hpp"
#include "thread.hpp"
#include "cat.hpp"

typedef advcpp::WaitableQueue<Cat> Q;
typedef std::vector<Cat> Vec;

namespace advcpp{

template <typename T, typename G>
class Creator : public IRunnable
{
public:
    Creator(size_t a_size, WaitableQueue<T>& a_queue, G a_gen);
    void Run();

private:
    WaitableQueue<T>& m_queue;
    const size_t m_size;
    G m_gen;
};

template <typename T, typename G>
Creator<T,G>::Creator(size_t a_size, WaitableQueue<T>& a_queue, G a_gen)
: m_queue(a_queue)
, m_size(a_size)
, m_gen(a_gen)
{    
}

template <typename T, typename G>
void Creator<T,G>::Run()
{
    for (size_t i=0 ; i<m_size ; ++i)
    {
        m_queue.Enqueue(m_gen(i));
    }
}

///////////////////////////////

class CatCreator
{
public:
    CatCreator(int a_age);
    //~CatCreator() = default;
    //CatCreator(CatCreator const& a_other) = default;
    //CatCreator& operator=(CatCreator const& a_rhs) = default;
    
    Cat operator()(int a_id);

private:
    int m_age;
};

CatCreator::CatCreator(int a_age)
: m_age(a_age)
{
}

Cat CatCreator::operator()(int a_id)
{
    return Cat(a_id, m_age);
}

/////////////////////////////////////

template <typename T>
class Eater : public IRunnable
{
public:
    Eater(size_t a_size, WaitableQueue<T>& a_queue, Vec& a_result);
    void Run();

private:
    const size_t m_size;
    WaitableQueue<T>& m_queue;
    Vec& m_result;
};

template <typename T>
Eater<T>::Eater(size_t a_size, WaitableQueue<T>& a_queue, Vec& a_result)
: m_size(a_size)
, m_queue(a_queue)
, m_result(a_result)
{    
}

template <typename T>
void Eater<T>::Run()
{
    for (size_t i=0 ; i<m_size ; ++i)
    {
        T temp;
        m_queue.Dequeue(temp);
        m_result.push_back(temp);
    }
}

///////////////////////////////////////////////////////////

} //namespace advcpp


void MergeOrdered(Vec& a_vec1, Vec& a_vec2, Vec& a_merged)
{
    Vec::iterator b1 = a_vec1.begin();
    Vec::iterator e1 = a_vec1.end();
    
    Vec::iterator b2 = a_vec2.begin();
    Vec::iterator e2 = a_vec2.end();

    while(b1 != e1 && b2 != e2)
    {
        if (*b1 < *b2)
        {
            a_merged.push_back(*b1);
            ++b1;
        }
        else
        {
            a_merged.push_back(*b2);
            ++b2;            
        }
        
    }
    if (b1 != e1)
    {
        while(b1 != e1)
        {
            a_merged.push_back(*b1);
            ++b1;
        }
    }
    else
    {
        while(b2 != e2)
        {
            a_merged.push_back(*b2);
            ++b2;
        }
    }    
}

void SplitResults(Vec& a_result, Vec& a_neg, Vec& a_pos)
{
    Vec::iterator b = a_result.begin();
    Vec::iterator e = a_result.end();

    while(b != e)
    {
        if (b->Age() < 0)
        {
            a_neg.push_back(*b);
        }
        else 
        {
            a_pos.push_back(*b);
        }
        ++b;
    }
}

void SplitMergeResults(Vec& a_res1, Vec& a_res2, Vec& a_pos, Vec& a_neg)
{
    Vec pos1;
    Vec neg1;
    SplitResults(a_res1, pos1, neg1);

    Vec pos2;
    Vec neg2;
    SplitResults(a_res2, pos2, neg2);

    MergeOrdered(pos1, pos2, a_pos);
    MergeOrdered(neg1, neg2, a_neg);
}

bool NotDone(std::vector<int> a_id)
{
    const size_t size = a_id.size();
    for (size_t i=0; i<size; ++i)
    {
        if (a_id[i] != -1)
        {
            return false;
        }
    }
    return true;
}

bool TryToPop(std::vector<std::vector<Cat> >& a_result, std::vector<int>& a_id)
{
    const int n = a_id.size();
    const int m = a_result.size();

    for (int i=0; i<n; ++i)
    {
        for(int j=0; j<m; ++j)
        {
            for (int k=0; k<(int)a_result[i].size(); ++k)
            {
                if (a_result[j][k].Age() == i && a_result[j][k].ID() == a_id[i])
                {
                    --a_id[i];
                    a_result[j].pop_back();
                    return true;
                }
            }
        }
    }
    return false;
}
//////////////////////////////////////////////////////////

UNIT(is_fifo)
    const int size = 1000000;
    Q q(size);

    advcpp::CatCreator catter(-9);
    advcpp::Creator<Cat, advcpp::CatCreator> creator(size, q, catter);
    creator.Run();

    Vec result;
    advcpp::Eater<Cat> eat(size, q, result);
    eat.Run();

    ASSERT_THAT(result.size() >0 );
    for (int i=0 ; i<size ; ++i)
    {
        ASSERT_EQUAL(result[i].ID(), i);
    }    

END_UNIT


UNIT(waitable_queue)
    const int size = 1000000;
    Q q(size);

    advcpp::CatCreator catter(-9);
    advcpp::Creator<Cat, advcpp::CatCreator> creator(size, q, catter);
    advcpp::Thread produce(&creator);
    
    Vec result;
    advcpp::Eater<Cat> eat(size, q, result);
    advcpp::Thread consume(&eat);

    produce.Join();
    consume.Join();

    ASSERT_THAT(result.size() >0 );

    for (int i=0 ; i<size ; ++i)
    {
        ASSERT_EQUAL(result[i].ID(), i);
    }    
END_UNIT

UNIT(one_producer_two_consumers)
    const int size = 1000000;
    Q q(size);

    advcpp::CatCreator catter(-9);
    advcpp::Creator<Cat, advcpp::CatCreator> creator(size, q, catter);
    advcpp::Thread produce(&creator);
    
    Vec result1;
    advcpp::Eater<Cat> eat1(size/2, q, result1);
    advcpp::Thread consume1(&eat1);

    Vec result2;
    advcpp::Eater<Cat> eat2(size/2, q, result2);
    advcpp::Thread consume2(&eat2);

    produce.Join();
    consume1.Join();
    consume2.Join();

    Vec merged;    
    MergeOrdered(result1, result2, merged);
    ASSERT_EQUAL(merged.size(), size);

    for (int i=0 ; i<size ; ++i)
    {
        ASSERT_EQUAL(merged[i].ID(), i);
    }
END_UNIT

UNIT(two_producers_one_consumer)
    const int size = 1000000;
    Q q(size);

    advcpp::CatCreator positive(555);
    advcpp::Creator<Cat, advcpp::CatCreator> creator1(size/2, q, positive);
    advcpp::Thread produce1(&creator1);
    
    advcpp::CatCreator negative(-99);
    advcpp::Creator<Cat, advcpp::CatCreator> creator2(size/2, q, negative);
    advcpp::Thread produce2(&creator2);

    Vec result;
    advcpp::Eater<Cat> eat(size, q, result);
    advcpp::Thread consume(&eat);

    produce1.Join();
    produce2.Join();
    consume.Join();
        
    ASSERT_EQUAL(result.size(), size);

    Vec res1;
    Vec res2;

    SplitResults(result, res1, res2);

    for (int i=0 ; i<size/2 ; ++i)
    {
        ASSERT_EQUAL(res1[i].ID(), i);
    }

    for (int i=0 ; i<size/2 ; ++i)
    {
        ASSERT_EQUAL(res2[i].ID(), i);
    }
END_UNIT

UNIT(two_producers_two_consumers)
    const int size = 1000000;
    Q q(size);

    advcpp::CatCreator positive(555);
    advcpp::Creator<Cat, advcpp::CatCreator> creator1(size/2, q, positive);
    advcpp::Thread produce1(&creator1);
    
    advcpp::CatCreator negative(-99);
    advcpp::Creator<Cat, advcpp::CatCreator> creator2(size/2, q, negative);
    advcpp::Thread produce2(&creator2);

    Vec result1;
    advcpp::Eater<Cat> eat1(size/2, q, result1);
    advcpp::Thread consume1(&eat1);

    Vec result2;
    advcpp::Eater<Cat> eat2(size/2, q, result2);
    advcpp::Thread consume2(&eat2);

    produce1.Join();
    produce2.Join();
    consume1.Join();
    consume2.Join();
        
    Vec pos;
    Vec neg;

    SplitMergeResults(result1, result2, pos, neg);

    for (int i=0 ; i<size/2 ; ++i)
    {
        ASSERT_EQUAL(pos[i].ID(), i);
    }

    for (int i=0 ; i<size/2 ; ++i)
    {
        ASSERT_EQUAL(neg[i].ID(), i);
    }
END_UNIT

UNIT(n_producers_m_consumers)    
    typedef advcpp::Creator<Cat, advcpp::CatCreator> Enque;
    typedef advcpp::Eater<Cat> Deque;

    
    const int size = 9900000;
    Q q(size);
    const size_t n = 130;
    const size_t m = 120;

    std::vector<advcpp::IRunnable*> enqueuers;
    std::vector<advcpp::Thread*> producers;
    for (size_t i=0; i<n-1; ++i)
    {               
        enqueuers.push_back(new Enque(size/n, q, advcpp::CatCreator(i)));
        producers.push_back(new advcpp::Thread(enqueuers[i]));
    }
    enqueuers.push_back(new Enque( size*(1-(n-1)/n), q, advcpp::CatCreator(n-1)));
    producers.push_back(new advcpp::Thread(enqueuers[n-1]));


    std::vector<advcpp::IRunnable*> dequeuers;
    std::vector<advcpp::Thread*> consumers;
    std::vector<std::vector<Cat> > result(m);
    for (size_t i=0; i<m-1; ++i)
    {               
        dequeuers.push_back(new Deque(size/m, q, result[i]));
        consumers.push_back(new advcpp::Thread(dequeuers[i]));
    }
    dequeuers.push_back(new Deque( size*(1-(m-1)/m), q, result[m-1]));
    consumers.push_back(new advcpp::Thread(dequeuers[m-1]));


    for (size_t i=0; i<n; ++i)
    {          
        producers[i]->Join();
    }

    for (size_t i=0; i<m; ++i)
    {          
        consumers[i]->Join();
    }
   

    std::vector<int> id(n);
    for (size_t i=0; i<n; ++i)
    {
        id[i] = size/n -1;
    }
    id[n-1] = size*(1-(n-1)/n) -1;


    while(NotDone(id))
    {
        if (!TryToPop(result, id))
        {
            ASSERT_FAIL("not found");
        }
    }   
    ASSERT_PASS();
END_UNIT

TEST_SUITE(waitable queue)
    TEST(is_fifo)
    TEST(waitable_queue)
    TEST(one_producer_two_consumers)
    TEST(two_producers_one_consumer)
    TEST(two_producers_two_consumers)
    TEST(n_producers_m_consumers)
END_SUITE