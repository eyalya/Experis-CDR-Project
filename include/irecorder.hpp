#ifndef I_RECORDER_HPP
#define I_RECORDER_HPP

//TODO: pesuod need to replace
#include "record.hpp"

namespace advcpp 
{

template <typename T> 
class IRecorder {
public:
    
    virtual ~IRecorder() {};

    //IRecorder();
    //IRecorder(const IRecorder<T>& a_rhs) = default;
    //IRecorder& operator = (const IRecorder<T> a_rhs) = default;

    virtual void Generate(char * src, Record& a_record) = 0;
};

template <typename T> 
class RecordAggregator: public IRecorder<T> 
{
public:
    explicit RecordAggregator();

    //~RecordAggregator() = default;
    //RecordAggregator(const RecordAggregator<T>& a_rhs) = default;
    //RecordAggregator& operator = (const RecordAggregator<T> a_rhs) = default;

    virtual void Generate(char * src, Record& a_record);
    
};


} //namespace advcpp 

#include "irecorder.inl"
#endif //I_RECORDER_HPP
