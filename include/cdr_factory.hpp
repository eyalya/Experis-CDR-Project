#ifndef CDR_FACTORY_HPP
#define CDR_FACTORY_HPP

#include <vector>

#include "thread.hpp"
#include "idata_upserter.hpp"

namespace advcpp 
{

class CdrFactory: public UnCopiable {
public:
    explicit CdrFactory(std::vector<IDataUpserter*>& a_receivers);

    //~CdrFactory() = default;
    //CdrFactory(const CdrFactory<T>& a_rhs) = delete;
    //CdrFactory& operator = (const CdrFactory<T> a_rhs) = delete;

    void ActivateWorkers();

private:
    void WorkersInit();

private:
    std::vector<IDataUpserter*>& m_recievers; 
    std::vector<Thread*> m_workers;
};

} //namespace advcpp 
#include "dispatcher.inl"
#endif //CDR_FACTORY_HPP