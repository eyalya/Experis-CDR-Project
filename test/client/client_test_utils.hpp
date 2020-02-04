#ifndef CLIENT_TEST_UTILS_HPP
#define CLIENT_TEST_UTILS_HPP

#include <map>

#include "protocol.hpp"
#include "hash_table_safe.hpp"
#include "TCP_client.hpp"
namespace advcpp
{


void FillMocDetails(protocol::MOC& a_moc);

template <typename Key, typename Value, typename Hasher>
void FillMap(HashTableSafe<Key, Value, Hasher>& a_map, size_t a_size);



} //namespace advcpp

#include "client_test_utils.inl"
#endif //CLIENT_TEST_UTILS_HPP