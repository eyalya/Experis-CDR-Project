#ifndef QUE_RUNNERS_H
#define QUE_RUNNERS_H

#include "irunnable.hpp" 
#include "common.hpp"
#include "thread.hpp"

namespace advcpp
{
template <typename T>
class Enqueuers: public advcpp::IRunnable {
public:
    explicit Enqueuers(advcpp::WaitableQueue<T>& a_destQue, T a_start, size_t a_range) NOEXCEPT;

    void Run() NOEXCEPT;
    bool GetRangeLeft() NOEXCEPT;
private:
    advcpp::WaitableQueue<T>& m_destQue;
    T m_start;
    size_t m_range;
};

template <typename T>
class Dequeuers: public advcpp::IRunnable {
public:
    explicit Dequeuers(advcpp::WaitableQueue<T>& a_srcQue, size_t a_nReads) NOEXCEPT;

    void Run() NOEXCEPT;
    std::vector<T>& GetVector() NOEXCEPT;

    bool IsRising() NOEXCEPT;
    bool GetReadsLeft() NOEXCEPT;
private:
    bool IsSmallerThanPrevious(T const& a_val) const;
private:
    advcpp::WaitableQueue<T>& m_srcQue;
    size_t m_nReads;
    bool m_isRising;
    std::vector<T> m_result;
};

template <typename T>
void EnqueueRunners(advcpp::WaitableQueue<T>& a_destQue, T a_start, size_t a_range, size_t a_nThread = advcpp::NT);

template <typename T, typename SegThread>
void CreateSegments(advcpp::WaitableQueue<T>& a_destQue, T a_start, size_t a_range, std::vector<SegThread*>& a_segments, size_t a_threadsNum = advcpp::NT);

template <typename T, typename SegThread>
void CreateSegments(advcpp::WaitableQueue<T>& a_destQue, size_t a_nReads, std::vector<SegThread*>& a_segments, size_t a_threadsNum  = advcpp::NT);

template <typename SegThread, typename T>
bool CheckConsumers(std::vector<SegThread*>& a_segments, size_t a_sumAll, T a_start);

template <typename SegThread, typename T>
void GetAllResults(std::vector<SegThread*>& a_segments, std::vector<std::vector<T>& >& a_results);

template <typename T>
bool CheckNextRisingByOne(std::vector<std::vector<T> >& a_results, std::vector<size_t>& a_indexes, T& a_start);

template <typename T>
bool CheckAllAscening(std::vector<std::vector<T> >& a_results, size_t a_sumAll, T a_start);

template <typename FillerA, typename FillerB>
void RunSegments(std::vector<FillerA*>& a_segmentsA, std::vector<FillerB*>& a_segmentsB ,size_t a_threadsNum);

template <typename T>
bool CheckAllAsceningA(std::vector<std::vector<T> >& a_results, size_t a_capacity);

template <typename T>
void SetIndexIntialValues(std::vector<T>& a_indexes, size_t a_capacity);

template <typename T>
bool CheckNextRisingByOneA(std::vector<std::vector<T> >& a_results, std::vector<size_t>& a_indexes);

}// namespace advcpp

#include "que_runners.inl"
#endif //QUE_RUNNERS_H
