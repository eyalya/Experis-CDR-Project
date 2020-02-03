#ifndef I_RECORDER_HPP
#define I_RECORDER_HPP

//TODO: pesuod need to replace
#include "record.hpp"
#include "cdr_decoder.hpp"
#include "reducer.hpp"

namespace advcpp 
{

//TODO: irecorder need to get t template

template <typename T> 
class IRecorder {
public:
    
    virtual ~IRecorder() {};

    //IRecorder();
    //IRecorder(const IRecorder<T>& a_rhs) = default;
    //IRecorder& operator = (const IRecorder<T> a_rhs) = default;

    virtual void Generate(char * src, Record& a_record) = 0;
};

//TODO: change src to T from char*
template <typename T> 
class RecordAggregator: public IRecorder<T> 
{
public:
    explicit RecordAggregator(CdrDecoder & a_decoder, Reducer & a_reducer);

    //~RecordAggregator() = default;
    //RecordAggregator(const RecordAggregator<T>& a_rhs) = default;
    //RecordAggregator& operator = (const RecordAggregator<T> a_rhs) = default;

    virtual void Generate(char * src, Record& a_record);

private:
    CdrDecoder & m_decoder; 
    Reducer & m_reducer;
};


} //namespace advcpp 

#include "irecorder.inl"
#endif //I_RECORDER_HPP
