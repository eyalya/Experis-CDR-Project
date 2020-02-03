#ifndef UTIL_HPP
#define UTIL_HPP

#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime> //Time
#include <vector>
#include <cassert>
#include <sstream>

namespace advcpp
{
namespace utils
{

struct Seed{
    Seed()
    {
        srand(time(0));
    }
};
static Seed g_seed;

template <typename T>
struct RandomGenerator {    
    T m_range;
    RandomGenerator(T a_range) : m_range(a_range) {}
    T operator()() {
        T res = rand() % m_range;
        return res;
    }    
};

template <typename T>
RandomGenerator<T> MakeRandomNum (T a_range) 
{    
    return RandomGenerator<T>(a_range);
}

template <typename T, typename U>
struct Sequence {    
    T m_initialValue;
    U m_delta;
    Sequence(U const& delta, T const& iv = T()) : m_initialValue(iv), m_delta(delta) {}
    T operator()() {
        T v = m_initialValue;
        m_initialValue += m_delta;
        return v;
    }    
};

template <typename T, typename U>
Sequence<T,U> MakeSequence(T const& iv, U const& delta)
{
    return Sequence<T,U>(iv, delta);
}

template <typename T>
Sequence<T,T> MakeSequence(T const& iv = T())
{
    return Sequence<T,T>(iv, T());
}

template <typename Iter>
bool IsAscending (Iter a_begin, Iter a_end) 
{
    if (a_begin == a_end)
    {
        return true;
    }

    Iter next = a_begin;
    ++next;
    while (next != a_end)
    {
        if (*next < *a_begin)
        {
            return false;
        }
        ++next;
        ++a_begin;
    }
    return true;
}

template <typename Iter, typename T>
bool IsAscending (Iter a_begin, Iter a_end, T a_delta) 
{
    if (a_begin == a_end)
    {
        return true;
    }

    Iter next = a_begin;
    ++next;
    int cnt = 0;
    while (next != a_end)
    {
        if (*next < *a_begin || *next - *a_begin != a_delta)
        {
            return false;
        }
        ++next;
        ++a_begin;
        ++cnt;
    }
    return true;
}

template <typename T>
void DestroyAllElements(std::vector<T>& a_vec)
{
    T var;
    while (a_vec.size() > 0)
    {
        var = a_vec.back();
        a_vec.pop_back();
        delete var; 
    }
}

template <typename T>
void CopyArray(T* a_dest, const T* a_arr, size_t a_size)
{
    assert (a_dest != 0 && a_arr != 0);
    for (size_t i = 0; i < a_size; i++)
    {   
        a_dest[i] = a_arr[i];
    }
}

void CopyStringArray(std::string a_dest[], const std::string a_arr[], size_t a_size)
{
    for (size_t i = 0; i < a_size; i++)
    {   
        a_dest[i] = a_arr[i];
    }
}
void RemoveLastLetter(std::string& a_word)
{
    if (a_word.size() > 0)
    {
        a_word.erase(--a_word.end());
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
void inline Swap(T &a_a, T &a_b)
{
	T temp = a_a;
	a_a = a_b;
	a_b = temp;
}

} //namespace utils

namespace iterFuncs
{
    template <typename Iter>
    void PrintArray(Iter a_begin, Iter a_end)
    {
        while (a_begin != a_end)
        {
            std::cout << *a_begin << ", ";
            ++a_begin;
        }
        std::cout << "\n";
    }

    template <typename Iter>
    double Average(Iter a_begin, Iter a_end)
    {
        int sum = 0;
        size_t cnt = 0;
        while (a_begin != a_end)
        {
            sum += *a_begin;
            ++cnt;
            ++a_begin;
        }
        return sum / cnt;
    }

    template <typename Iter>
    double Multiply(Iter a_begin, Iter a_end)
    {
        int mutliply = 1;
        while (a_begin != a_end)
        {
            mutliply *= *a_begin;
            ++a_begin;
        }
        return mutliply;
    }

    template <typename T>
    void DeleteItems(T a_val)
    {
        delete a_val;
    }

} // namespace iterFuncs

namespace exceptions
{
    std::string ExceptionMessageBuild(const char* a_file, const char* a_func, int a_line, const char* a_msg)
    {
        std::ostringstream msg;
        msg << "File: " << a_file << " Function: " << a_func << " Line: " << a_line << " Message: " << a_msg << "\n";
        return msg.str();
    }
}

} // namespace advcpp
#endif //UTIL_HPP
