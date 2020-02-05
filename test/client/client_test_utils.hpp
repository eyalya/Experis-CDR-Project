#ifndef CLIENT_TEST_UTILS_HPP
#define CLIENT_TEST_UTILS_HPP

#include <map>

#include "protocol.hpp"
#include "hash_table_safe.hpp"
#include "TCP_client.hpp"
#include "util.hpp"

namespace advcpp
{

typedef utils::Sequence<uint, uint> SeqGen; 
typedef utils::RandomGenerator<uint> RandGen;
typedef utils::RandomGenerator<uchar> OpGen;

void FillMocDetails(protocol::MOC& a_moc, SeqGen& a_msisdnGen, OpGen& a_operator, RandGen& a_randGen);

template <typename Cont>
void FillCont(Cont& a_map, size_t a_size);

template <typename Cont>
void GetSampleMoc(Cont& a_map, size_t a_misdnRange);

} //namespace advcpp

#include "client_test_utils.inl"
#endif //CLIENT_TEST_UTILS_HPP