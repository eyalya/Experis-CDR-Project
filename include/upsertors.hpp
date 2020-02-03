#ifndef UPSERTORS_HPP
#define UPSERTORS_HPP

#include "thread.hpp"
#include "waitable_queue.hpp"
#include "irecorder.hpp"
#include "i_record.hpp"

namespace advcpp 
{

template <typename DsCont> 
class Upsertors: public IRunnable {
public:
    explicit Upsertors(WaitableQueue<char*>& a_msgQue, IRecorder<char*>& a_recorder, DsCont& a_dsCont, bool& a_switch);

    //~Upsertors() = default;
    //Upsertors(const Upsertors<T>& a_rhs) = default;
    //Upsertors& operator = (const Upsertors<T> a_rhs) = default;

    void Run();

private:
    void ReadMsgs();

private:
    WaitableQueue<char*>& m_msgQue;
    IRecorder<char*>& m_recorder;
    DsCont& m_dsCont;
    bool& m_switch; 
    RecordAggregator m_record;
};

} //namespace advcpp 

#include "upsertors.inl"
#endif //UPSERTORS_HPP