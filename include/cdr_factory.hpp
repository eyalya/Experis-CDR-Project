#ifndef CDR_FACTORY_HPP
#define CDR_FACTORY_HPP

#include <vector>

#include "dispatcher.hpp"

namespace advcpp 
{

template <typename Runnable>
class CdrFactory: public Dispatcher {
public:
    explicit CdrFactory(std::vector<Runnable>& a_upsertors);

    //~CdrFactory() = default;
    //CdrFactory(const CdrFactory<T>& a_rhs) = delete;
    //CdrFactory& operator = (const CdrFactory<T> a_rhs) = delete;

};

} //namespace advcpp 
#include "cdr_factory.inl"
#endif //CDR_FACTORY_HPP