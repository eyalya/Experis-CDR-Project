#ifndef CLIENT_TEST_UTILS_INL
#define CLIENT_TEST_UTILS_INL

#include "client_test_utils.hpp"
#include "util.hpp"

namespace advcpp
{

void FillMocDetails(protocol::MOC& a_moc, utils::Sequence<uint, uint>& a_seqGen, utils::RandomGenerator<uint>& a_randGen)
{
    
    a_moc.m_cdr.m_imei = a_seqGen();
    a_moc.m_duration = a_randGen();
}

template <typename Key, typename Value, typename Hasher>
void FillMap(HashTableSafe<Key, Value, Hasher>& a_map, size_t a_size)
{
    const uint iv = 10000001;
    const uint delta = 1;
    const uint range = 100;


    utils::Sequence<uint, uint> seqGen = utils::MakeSequence<uint, uint>(iv, delta);
    utils::RandomGenerator<uint> randGen = utils::MakeRandomNum<uint>(range);

    protocol::MOC newMoc;

    while (--a_size)
    {
        FillMocDetails(newMoc, seqGen, randGen);
        a_map.Insert(newMoc.m_cdr.m_imei ,newMoc);
    }
}

} //namespace advcpp

#endif //CLIENT_TEST_UTILS_INL 