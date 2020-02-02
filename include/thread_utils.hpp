#ifndef THREAD_UTILS_H
#define THREAD_UTILS_H

#include <vector>
#include <cassert>

#include "irunnable.hpp" 
#include "locks.hpp"
#include "common.hpp"
#include "thread.hpp"

namespace advcpp
{

template <typename Iter, typename Generator>
class ContainerFiller: public advcpp::IRunnable {
public:
    explicit ContainerFiller(Iter a_begin, Iter a_end, Generator a_generator);

    void Run() NOEXCEPT;

private:
    Iter m_begin;
    Iter m_end;
    Generator m_generator;
};

template <typename Iter, typename T>
class CalcSum: public advcpp::IRunnable {
public:
    explicit CalcSum(Iter a_begin, Iter a_end);

    void Run() NOEXCEPT;
    T Result() NOEXCEPT;

    operator T () const NOEXCEPT;
private:
    Iter m_begin;
    Iter m_end;
    T m_sumResult;
};

template <typename Iter, typename T>
class CalcMultiple: public advcpp::IRunnable {
public:
    explicit CalcMultiple(Iter a_begin, Iter a_end);

    void Run() NOEXCEPT;
    T Result();
private:
    Iter m_begin;
    Iter m_end;
    T m_multipleResult;
};

template <typename Iter, typename T> 
class AvgCalc: public advcpp::IRunnable {
public:
    explicit AvgCalc(std::vector<T>& a_numbers) THROW1(MutexCreateException);

    void Run() NOEXCEPT;
    T Result() NOEXCEPT;
private:    
    T m_avg;
    std::vector<T>& m_numbers;
    advcpp::Mutex m_lock;
};

template <typename T, typename Filler, typename Generator>
void CreateSegments(std::vector<T>& a_vec, std::vector<Filler>& a_segments, size_t a_threadsNum, Generator a_generator);

template <typename Iter, typename SegThread>
void CreateSegments(Iter a_begin, Iter a_end, std::vector<SegThread*>& a_segments, size_t a_threadsNum, 
                    int& a_res, advcpp::Mutex& a_lock);

template <typename Filler>
void RunSegments(std::vector<Filler>& a_segments, size_t a_threadsNum);

void JoinAll(std::vector<advcpp::Thread*>& a_threads, size_t a_nThreads);

template <typename T, typename Generator>
void FillVector(std::vector<T>& a_vec, size_t a_size, Generator a_generator, size_t a_nThread = advcpp::NT);

template <typename Cont, typename Segments>
void ThreadsMaker(Cont const& a_cont, Segments& a_segments, size_t a_nThread);

template <typename Cont, typename T>
T Sum(Cont const& a_cont, T& a_result, size_t a_nThread = advcpp::NT);

template <typename Cont, typename T>
void Multiple(Cont const& a_cont, T& a_result, size_t a_nThread = advcpp::NT);

template <typename Cont>
void Avarage(Cont const& a_cont, double& a_result, size_t a_nThread = advcpp::NT);

template <typename Iter, typename T>
void AccumulateRunnable(Iter a_begin, Iter a_end, T& a_result);
} // namespace advcpp

#include "thread_utils.inl"
#endif //THREAD_UTILS
