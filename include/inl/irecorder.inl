#include "irecorder.hpp"

namespace advcpp
{

template <typename T> 
RecordAggregator<T>::RecordAggregator(IDecoder& a_decoder, IReducer& a_reducer)
: m_decoder(a_decoder)
, m_reducer(a_reducer)
{
}

template <typename T> 
void RecordAggregator<T>::Generate(T& src, IRecord& a_record)
{
    
}


} //namespace advcpp