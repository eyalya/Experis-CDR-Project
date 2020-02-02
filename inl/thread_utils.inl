#include <algorithm>
#include <numeric> 

#include "thread_utils.hpp"
#include "util.hpp"

namespace advcpp
{
template <typename Iter, typename Generator> 
ContainerFiller<Iter, Generator>::ContainerFiller(Iter a_begin, Iter a_end, Generator a_generator)
: m_begin(a_begin)
, m_end(a_end)
, m_generator(a_generator)
{
}

template <typename Iter, typename Generator> 
void ContainerFiller<Iter, Generator>::Run() NOEXCEPT
{
   while(m_begin != m_end)
   {
       *m_begin = m_generator();
       ++m_begin;
   }
}

template <typename Iter, typename T> 
CalcSum<Iter, T>::CalcSum(Iter a_begin, Iter a_end)
: m_begin(a_begin)
, m_end(a_end)
, m_sumResult(0)
{
}

template <typename Iter, typename T> 
void CalcSum<Iter, T>::Run() NOEXCEPT
{
    m_sumResult = std::accumulate(m_begin, m_end, 0);
}

template <typename Iter, typename T> 
T CalcSum<Iter, T>::Result() NOEXCEPT
{
    return m_sumResult;
}

template <typename Iter, typename T> 
CalcSum<Iter, T>::operator T () const NOEXCEPT
{
    return m_sumResult;
}

template <typename Iter, typename T>  
CalcMultiple<Iter, T>::CalcMultiple(Iter a_begin, Iter a_end)
: m_begin(a_begin)
, m_end(a_end)
, m_multipleResult(1)
{
}

template <typename Iter, typename T> 
void CalcMultiple<Iter, T>::Run() NOEXCEPT
{
   while(m_begin != m_end)
   {
       m_multipleResult *= *m_begin;
       ++m_begin;
   }
}

template <typename Iter, typename T> 
T CalcMultiple<Iter, T>::Result()
{
    return m_multipleResult;
}


template <typename T, typename Filler, typename Generator>
void CreateSegments(std::vector<T>& a_vec, std::vector<Filler*>& a_segments, size_t a_threadsNum, Generator a_generator)
{
    const size_t numbersSize = a_vec.capacity();
    size_t segmentSize = numbersSize / a_threadsNum;
    
    typename std::vector<T>::iterator it = a_vec.begin();
    typename std::vector<T>::iterator endSection = it + segmentSize;

    while (--a_threadsNum)
    {
        Filler* filler = new Filler(it, endSection, a_generator);
        a_segments.push_back(filler);
        it = endSection;
        endSection += segmentSize;
    }
    a_segments.push_back(new Filler(it, a_vec.end(), a_generator));
}

template <typename Iter, typename SegThread>
void CreateSegments(Iter a_begin, Iter a_end, std::vector<SegThread*>& a_segments, size_t a_threadsNum)
{
    const size_t numbersSize = a_end - a_begin;
    size_t segmentSize = numbersSize / a_threadsNum;
    Iter endSection = a_begin + segmentSize;

    while (--a_threadsNum)
    {
        a_segments.push_back(new SegThread(a_begin, endSection));
        a_begin = endSection;
        endSection += segmentSize;
    }
    a_segments.push_back(new SegThread(a_begin, a_end));
}

template <typename Filler>
void RunSegments(std::vector<Filler*>& a_segments, size_t a_threadsNum)
{
    std::vector<advcpp::Thread*> threads;
    threads.reserve(a_threadsNum);
    for (size_t i = 0; i < a_threadsNum; ++i)
    {
        try 
        {
            threads.push_back(new Thread(static_cast<advcpp::IRunnable*>(a_segments[i])));
        }
        catch(std::bad_alloc& a_bad)
        {
            std::cout << a_bad.what();
        }
        catch(advcpp::ThreadCreateException& a_create)
        {
            std::cout << a_create.what();
        }
    }
    JoinAll(threads, a_threadsNum);
    std::for_each(threads.begin(), threads.end(), advcpp::iterFuncs::DeleteItems<Thread*>);
}

inline void JoinAll(std::vector<advcpp::Thread*>& a_threads, size_t a_nThreads)
{
    for (size_t i = 0; i < a_nThreads; ++i)
    {
        assert(a_nThreads == a_threads.size());
        try 
        {
            a_threads[i]->Join();
        }
        catch (ThreadJoinException& a_catch)
        {
            std::cout << a_catch.what() << "\n";
        }
    }
}

template <typename T, typename Generator>
void FillVector(std::vector<T>& a_vec, size_t a_size, Generator a_generator, size_t a_nThread)
{
    typedef typename std::vector<T>::iterator Iter;
    typedef typename advcpp::ContainerFiller<Iter, Generator> Cont;
    
    a_vec.reserve(a_size);
    std::vector< Cont* > segments;

    CreateSegments(a_vec, segments, a_nThread, a_generator);
    RunSegments(segments, a_nThread);
    std::for_each(segments.begin(), segments.end(), advcpp::iterFuncs::DeleteItems<Cont*>);
}

template <typename Cont, typename Segments>
void ThreadsMaker(Cont const& a_cont, Segments& a_segments, size_t a_nThread)
{
    CreateSegments(a_cont.begin(), a_cont.end(), a_segments, a_nThread);
    RunSegments(a_segments, a_nThread);
}

template <typename Cont, typename T>
T Sum(Cont const& a_cont, T& a_result, size_t a_nThread)
{
    typedef typename Cont::const_iterator Iter;
    typedef typename advcpp::CalcSum<Iter, T> SumCalculator;

    std::vector< SumCalculator* > segments;
    ThreadsMaker(a_cont, segments, a_nThread);

    typename std::vector< SumCalculator*>::iterator begin = segments.begin();
    typename std::vector< SumCalculator*>::iterator end = segments.end();
    while (begin != end)
    {
        a_result += (*begin)->Result();
        ++begin;
    }
    //AccumulateRunnable(segments.begin(), segments.end(), a_result);
    std::for_each(segments.begin(), segments.end(), advcpp::iterFuncs::DeleteItems<SumCalculator*>);
    return a_result;
}

template <typename Cont, typename T>
void Multiple(Cont const& a_cont, T& a_result, size_t a_nThread)
{
    typedef typename Cont::const_iterator Iter;
    typedef typename advcpp::CalcMultiple<Iter, T> MulCalculator;
    
    std::vector< MulCalculator* > segments;
    ThreadsMaker(a_cont, segments, a_nThread);

    typename std::vector< MulCalculator*>::iterator begin = segments.begin();
    typename std::vector< MulCalculator*>::iterator end = segments.end();
    while (begin != end)
    {
        a_result *= (*begin)->Result();
        ++begin;
    }
    std::for_each(segments.begin(), segments.end(), advcpp::iterFuncs::DeleteItems<MulCalculator*>);
}

template <typename Cont>
void Avarage(Cont const& a_cont, double& a_result, size_t a_nThread)
{
    int sumResult = 0;
    advcpp::Sum(a_cont, sumResult, a_nThread);
    a_result = sumResult / a_cont.size();
}

template <typename Iter, typename T>
void AccumulateRunnable(Iter a_begin, Iter a_end, T& a_result)
{
    while (a_begin != a_end)
    {
        a_result += (*a_begin)->a_result();
        ++a_begin;
    }
    //a_result = std::accumulate(a_begin, end, 0);
}

} //namespace advcpp