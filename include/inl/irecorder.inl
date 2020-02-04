#include "irecorder.hpp"
#include "cdr_decoder.hpp"
#include "reducer.hpp"
#include "protocol.hpp"

namespace advcpp
{

template <typename T> 
RecordAggregator<T>::RecordAggregator(CdrDecoder & a_decoder, Reducer & a_reducer)
: m_decoder(a_decoder)
, m_reducer(a_reducer)
{
}

template <typename T> 
void RecordAggregator<T>::Generate(char * src, Record& a_record)
{
    for(size_t i = 0; i < sizeof(src); ++i)
    {
        src[i] -= 'a';
    }
    protocol::Message msg;
    m_decoder.Decode(src, msg);
    m_reducer.Reduce(msg, a_record);
}


} //namespace advcpp