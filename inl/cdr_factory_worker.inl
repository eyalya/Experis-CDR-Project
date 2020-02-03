#include "cdr_factory_worker.hpp"

template <typename T, typename DsCont> 
CdrFactoryWorker<T, DsCont>::CdrFactoryWorker(WaitableQueue<T>& a_msgQue, IDecoder& a_decoder, IReducer& a_reducer, DsCont& a_dsCont)
: m_msgQue(a_msgQue)
, m_decoder(a_decoder)
, m_reducer(a_reducer)
, m_switch(false)
{
}
