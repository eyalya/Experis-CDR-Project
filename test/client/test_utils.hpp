#ifndef TEST_UTILS_HPP
#define TEST_UTILS_HPP

#include <set>

#include "irecievers.hpp"
#include "upsertors.hpp"
#include "TCP_acceptor.hpp"
#include "irecorder.hpp"
#include "util.hpp"

namespace advcpp
{

void FillWithPhoneNumber (std::set<int> a_numbers, size_t a_contSize)
{
    while (--a_contSize)
    {
        a_numbers.insert(MakeSequence(1000000, 1));
    } 
}



} //namespace advcpp

#include "test_utils.inl"
#endif //TEST_UTILS_HPP