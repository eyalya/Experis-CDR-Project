#ifndef UPSERTORS_HPP
#define UPSERTORS_HPP

#include "thread.hpp"
#include "waitable_queue.hpp"
#include "irecorder.hpp"
#include "i_record.hpp"
#include "ds_container.hpp"

namespace advcpp 
{

template <typename T>
class Upsertors: public IRunnable {
public:
    explicit Upsertors(WaitableQueue<T>& a_msgQue, IRecorder<T>& a_recorder, DsContainer& a_dsCont, bool& a_switch);

    //~Upsertors() = default;
    //Upsertors(const Upsertors<T>& a_rhs) = default;
    //Upsertors& operator = (const Upsertors<T> a_rhs) = default;

    void Run();

private:
    WaitableQueue<T>& m_msgQue;
    IRecorder<T>& m_recorder;
    DsContainer& m_dsCont;
    bool& m_switch; 
    Record m_record;
};

} //namespace advcpp 

#include "upsertors.inl"
#endif //UPSERTORS_HPP