#include <algorithm> //foreach

#include "que_runners.hpp"
#include "util.hpp" //deleteitems
#include "thread_utils.hpp" //JoinAll


namespace advcpp
{

template <typename T>
Enqueuers<T>::Enqueuers(advcpp::WaitableQueue<T>& a_destQue, T a_start, size_t a_range) NOEXCEPT
: m_destQue(a_destQue)
, m_start (a_start)
, m_range (a_range)
{
}

template <typename T>
void Enqueuers<T>::Run() NOEXCEPT
{
    while (m_range)
    {
        m_destQue.Enqueue(m_start);
        ++m_start;
        --m_range;
    }
}

template <typename T>
bool Enqueuers<T>::GetRangeLeft() NOEXCEPT
{
    return m_range;
}

template <typename T>
Dequeuers<T>::Dequeuers(advcpp::WaitableQueue<T>& a_srcQue, size_t a_nReads) NOEXCEPT
: m_srcQue(a_srcQue)
, m_nReads (a_nReads)
, m_isRising (true)
, m_result()
{
}

template <typename T>
void Dequeuers<T>::Run() NOEXCEPT
{
    T result;
    m_srcQue.Dequeue(result);
    m_result.push_back(result);

    while (--m_nReads)
    {
        m_srcQue.Dequeue(result);
        // if (!IsSmallerThanPrevious(result))
        // {
        //     m_isRising = false;
        //     std::cout << "failed to read\n";
        //     break;
        // }
        m_result.push_back(result);
    }
}

template <typename T>
std::vector<T>& Dequeuers<T>::GetVector() NOEXCEPT
{
    return m_result;
}

template <typename T>
bool Dequeuers<T>::IsSmallerThanPrevious(T const& a_val) const
{
    return a_val > m_result.back();
}

template <typename T>
bool Dequeuers<T>::IsRising() NOEXCEPT
{
    return m_isRising;
}

template <typename T>
bool Dequeuers<T>::GetReadsLeft() NOEXCEPT
{
    return m_nReads;
}

/////////// Globals ///////////////////////////////////////////////////////////////////////////////////
 
template <typename T>
void EnqueueRunners(advcpp::WaitableQueue<T>& a_destQue, T a_start, size_t a_range, size_t a_nThread)
{
    typedef typename advcpp::Enqueuers<T> Enques;

    std::vector< Enques* > segments;
    CreateSegments(a_destQue ,a_start, a_range, segments, a_nThread);
    RunSegments(segments, a_nThread);

    std::for_each(segments.begin(), segments.end(), advcpp::iterFuncs::DeleteItems<Enques*>);
}

template <typename T>
void DequeueRunners(advcpp::WaitableQueue<T>& a_destQue, size_t a_nReads, size_t a_nThread)
{
    typedef typename advcpp::Dequeuers<T> Deques;

    std::vector< Deques* > segments;
    CreateSegments(a_destQue, a_nReads, segments, a_nThread);
    RunSegments(segments, a_nThread);

    std::for_each(segments.begin(), segments.end(), advcpp::iterFuncs::DeleteItems<Deques*>);
}

template <typename T, typename SegThread>
void CreateSegments(advcpp::WaitableQueue<T>& a_destQue, T a_start, size_t a_range, std::vector<SegThread*>& a_segments, size_t a_threadsNum)
{
    while (a_threadsNum)
    {
        a_segments.push_back(new SegThread(a_destQue, a_start, a_range));
        a_start += a_range;
        --a_threadsNum;
    }
}

template <typename T, typename SegThread>
void CreateSegments(advcpp::WaitableQueue<T>& a_destQue, size_t a_nReads, std::vector<SegThread*>& a_segments, size_t a_threadsNum)
{
    while (a_threadsNum)
    {
        a_segments.push_back(new SegThread(a_destQue, a_nReads));
        --a_threadsNum;
    }
}

template <typename SegThread, typename T>
bool CheckConsumers(std::vector<SegThread*>& a_segments, size_t a_sumAll, T a_start)
{
    std::vector<std::vector<T> > results;
    GetAllResults(a_segments, results);

    return CheckAllAscening<T>(results, a_sumAll, a_start);
}

template <typename T>
bool CheckAllAscening(std::vector<std::vector<T> >& a_results, size_t a_sumAll, T a_start)
{
    std::vector<size_t> indexes (a_results.size(), 0);

    while (--a_sumAll)
    {
        if (!CheckNextRisingByOne<T>(a_results, indexes, a_start))
        {
            return false;
        }
    }

    return true;
}

template <typename T>
bool CheckNextRisingByOne(std::vector<std::vector<T> >& a_results, std::vector<size_t>& a_indexes, T& a_start)
{
    const size_t size = a_indexes.size();
    T val = 0;
    size_t checkedIndex = 0;
    for (size_t i = 0; i < size; ++i)
    {
        checkedIndex = a_indexes[i];
        val = a_results[i][checkedIndex];

        if ( val == a_start)
        {
            ++a_start;
            ++a_indexes[i];
            return true;
        }
    }
    return false;
}

template <typename T>
bool CheckAllAsceningA(std::vector<std::vector<T> >& a_results, size_t a_capacity)
{
    std::vector<T> resultPosition (a_results.size(), 0);
    std::vector<size_t> indexes (a_results.size(), 0);
    SetIndexIntialValues(resultPosition, a_capacity);

    while (--a_capacity)
    {
        if (!CheckNextRisingByOne<T>(a_results, resultPosition))
        {
            return false;
        }
    }

    return true;
}

template <typename T>
void SetIndexIntialValues(std::vector<T>& a_resultPosition, size_t a_capacity)
{
    size_t size = a_resultPosition.size();
    size_t sectionSize = a_capacity/size;
    size_t current = 0;

    for (size_t i = 0; i < size; ++i)
    {
        a_resultPosition[i] = current;
        current += sectionSize;
    }
}

template <typename T>
bool CheckNextRisingByOneA(std::vector<std::vector<T> >& a_results, 
                           std::vector<size_t>& a_indexes, 
                           std::vector<T>& a_resultValues)
{
    const size_t size = a_resultValues.size();
    T val = 0;
    T checkedVal = 0;
    size_t checkedIndex = 0;

    for (size_t i = 0; i < size; ++i)
    {
        checkedIndex = a_indexes[i];
        checkedVal = a_resultValues[i];
        val = a_results[i][checkedIndex];

        if ( val == checkedVal)
        {
            ++a_resultValues[i];
            ++a_indexes[i];
            return true;
        }
    }
    return false;
}

template <typename SegThread, typename T>
void GetAllResults(std::vector<SegThread*>& a_segments, std::vector<std::vector<T> >& a_results)
{
    const size_t size = a_segments.size();
    for (size_t i = 0; i < size; ++i)
    {
        a_results.push_back(a_segments[i]->GetVector()); 
    }
}

template <typename FillerA, typename FillerB>
void RunSegments(std::vector<FillerA*>& a_segmentsA, std::vector<FillerB*>& a_segmentsB ,size_t a_threadsNum)/////TODO: pat )
{
    std::vector<advcpp::Thread*> threads;
    threads.reserve(a_threadsNum);
    for (size_t i = 0; i < a_threadsNum; ++i)
    {
        try 
        {
            threads.push_back(new Thread(static_cast<advcpp::IRunnable*>(a_segmentsA[i])));
            threads.push_back(new Thread(static_cast<advcpp::IRunnable*>(a_segmentsB[i])));
        }
        catch(...)
        {
            std::cout << "failed to create threads\n";
            advcpp::JoinAll(threads, threads.size());
            std::for_each(threads.begin(), threads.end(), advcpp::iterFuncs::DeleteItems<Thread*>);
        }
    }
    advcpp::JoinAll(threads, threads.size());
    std::for_each(threads.begin(), threads.end(), advcpp::iterFuncs::DeleteItems<Thread*>);
}

}//namespace advcpp