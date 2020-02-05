#include <cstdio>
#include "cdr_decoder.hpp"
#include <iostream>
#include <cstring>

namespace advcpp
{

template <typename T>
T DecodeT(const char * a_src, int a_len);

size_t DecodeCdr(protocol::CDR & a_cdr, const char * a_src);
size_t DecodeOperator(protocol::Operator & a_op, const char * a_src);
size_t DecodeTime(protocol::Time & a_time, const char * a_src);
size_t DecodeParty(protocol::Party & a_party, const char * a_src);
size_t DecodeDate(protocol::Date & a_date, const char * a_src);
size_t DecodeMoc(protocol::Message & a_moc, const char * a_src);

inline IDecodeMassge::~IDecodeMassge()
{
}


inline void DecodeMCO::Decode(const char * a_src, protocol::Message & a_message)
{
    DecodeMoc(a_message, a_src);
}

inline CdrDecoder::CdrDecoder(std::vector<IDecodeMassge *> & a_decoders)
: m_decoders(a_decoders)
{ 
}

inline void CdrDecoder::Decode(const char * a_src, protocol::Message & a_message)
{
    uchar index = DecodeT<uchar>(&(a_src[0]), sizeof(uchar));
    (void) index;
    // FIXME: fix decoder
    // m_decoders[index] -> Decode(a_src, a_message);
    m_decoders[1] -> Decode(a_src, a_message);
}


template <typename T>
T DecodeT(const char * a_src, int a_len)
{
    T newType;
    std::memcpy(&newType, a_src, a_len);

    return newType;
}




} // namespace advcpp
