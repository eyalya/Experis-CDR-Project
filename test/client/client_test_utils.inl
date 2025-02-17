#ifndef CLIENT_TEST_UTILS_INL
#define CLIENT_TEST_UTILS_INL

#include <set>

#include "client_test_utils.hpp"
#include "util.hpp"
#include "encoder.hpp"
#include "irecorder.hpp"

namespace advcpp
{

void FillMocDetails(protocol::MOC& a_moc, SeqGen& a_msisdnGen, OpGen& a_operator, RandGen& a_randGen)
{
    
    a_moc.m_cdr.m_msisdn = a_msisdnGen();
    a_moc.m_cdr.m_operator.m_value = a_operator();
    a_moc.m_duration = a_randGen();
}

template <typename Cont>
void FillCont(Cont& a_map, size_t a_size)
{
    const uint iv = 0;
    const uint delta = 1;

    utils::Sequence<uint, uint> seqGen = utils::MakeSequence<uint, uint>(iv, delta);

    protocol::MOC newMoc;

    while (--a_size)
    {
        newMoc.m_cdr.m_msisdn = seqGen();
        a_map.Insert(newMoc.m_cdr.m_msisdn ,newMoc);
    }
}

template <typename Cont>
void GetSampleMoc(Cont& a_map, size_t a_misdnRange, protocol::MOC& a_moc)
{
    const uint durationRange = 100;
    const uchar operatorRange = 255;

    static utils::RandomGenerator<uint> durationGen = utils::MakeRandomNum<uint>(durationRange);
    static utils::RandomGenerator<uint> misdnGen = utils::MakeRandomNum<uint>(a_misdnRange);
    static utils::RandomGenerator<uchar> operatorGen = utils::MakeRandomNum<uchar>(operatorRange);

    a_map.Find(misdnGen(), a_moc);
    a_moc.m_cdr.m_operator.m_value = operatorGen();
    a_moc.m_duration = durationGen();
}

class MessageSender
{
public:
    MessageSender(TCPClient & a_client);

    void operator()(protocol::MOC & a_moc);

private:
    TCPClient  & m_client;
};

inline MessageSender::MessageSender(TCPClient & a_client)
: m_client(a_client)
{
}

inline void MessageSender::operator()(protocol::MOC& a_moc)
{
    char buffer[sizeof(protocol::MOC)];
    EncodeMoc(buffer, a_moc);
    m_client.Send(buffer);
}

template <typename Hasher>
class SenderAndAdd
{
public:
    SenderAndAdd(TCPClient & a_client, 
                HashTableSafe<uint, SubscriberRecord, Hasher> & a_subContainer,
                RecordAggregator<char *> & a_aggregator);

    void operator()(protocol::MOC & a_moc);

private:
    TCPClient  & m_client;
    HashTableSafe<uint, SubscriberRecord, Hasher> & m_subContainer;
    RecordAggregator<char *> & m_aggregator;
    
};

template <typename Hasher>
SenderAndAdd<Hasher>::SenderAndAdd(TCPClient & a_client, 
                            HashTableSafe<uint, SubscriberRecord, Hasher> & a_subContainer,
                            RecordAggregator<char *> & a_aggregator)
: m_client(a_client)
, m_subContainer(a_subContainer)
, m_aggregator(a_aggregator)
{
}

template <typename Hasher>
void SenderAndAdd<Hasher>::operator()(protocol::MOC & a_moc)
{
    char buffer[sizeof(protocol::MOC)];
    EncodeMoc(buffer, a_moc);
    m_client.Send(buffer);
    Record rec;
    m_aggregator.Generate(buffer, rec);
    m_subContainer.Insert(rec);
}

} //namespace advcpp

#endif //CLIENT_TEST_UTILS_INL 