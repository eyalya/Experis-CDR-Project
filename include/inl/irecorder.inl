#include "irecorder.hpp"
#include "cdr_decoder.hpp"
#include "reducer.hpp"
#include "protocol.hpp"

namespace advcpp
{

template <typename T> 
RecordAggregator<T>::RecordAggregator()
{
}

template <typename T> 
void RecordAggregator<T>::Generate(char * src, Record& a_record)
{
    protocol::Message msg;
    DecodeMoc(msg, src);
    (void)a_record;
    // Reducer reducer(Message);
    // reducer.Reduce(a_record);
}


} //namespace advcpp