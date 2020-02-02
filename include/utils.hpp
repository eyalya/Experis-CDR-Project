#ifndef UTILS_HPP
#define UTILS_HPP

#include <set>
#include <cstdlib>

#include <utility>

namespace advcpp
{
namespace numbers
{

const double goldenRatio = 1.618;

template <typename T>
struct NumPred {
    NumPred(T const& a_num);

    bool operator () (T const& a_num) {return m_num == a_num; }
    T m_num;
};

size_t FindNextPrime(size_t a_num);

} // ending numbers

namespace predicates
{
template <typename T, typename U>
//T:: comparable with ==
bool MatchFirstInPair(std::pair<T,U> const& a_firstPair, std::pair<T,U> const& a_secondPair);

}// ending predicates


/////////////////////////////////////////////////////////////////////////////////////////////////////


template <typename T, typename U>
bool advcpp::predicates::MatchFirstInPair(std::pair<T,U> const& a_firstPair, std::pair<T,U> const& a_secondPair)
{
    return a_firstPair.first == a_secondPair.first;
}


} // ending advcpp
#endif //UTILS_HPP
