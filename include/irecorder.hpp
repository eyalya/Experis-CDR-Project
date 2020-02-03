#ifndef I_RECORDER_HPP
#define I_RECORDER_HPP

//TODO: pesuod need to replace
typedef char IDecoder;
typedef char IReducer;

namespace advcpp 
{

class IRecorder {
public:
    
    ~IRecorder() {};

    //IRecorder();
    //IRecorder(const IRecorder<T>& a_rhs) = default;
    //IRecorder& operator = (const IRecorder<T> a_rhs) = default;

    virtual Generate(T& src, IRecord& a_record) = 0;
};

template <typename T> 
class RecordAggregator: public IRecorder {
public:
    explicit RecordAggregator(IDecoder& a_decoder, IReducer& a_reducer);

    //~RecordAggregator() = default;
    //RecordAggregator(const RecordAggregator<T>& a_rhs) = default;
    //RecordAggregator& operator = (const RecordAggregator<T> a_rhs) = default;

    void Generate(T& src, IRecord& a_record);

private:
    IDecoder& m_decoder; 
    IReducer& m_reducer;
};


} //namespace advcpp 

#include "irecorder.inl"
#endif //I_RECORDER_HPP
