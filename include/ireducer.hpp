#ifndef I_REDUCER_H
#define I_REDUCER_H

#include "record.hpp"

namespace advcpp
{

class IReducer
{
public:
    virtual ~IReducer() = 0;

    virtual void Reduce(Record & a_record) = 0;

};

inline IReducer::~IReducer()
{
}

} // namespace advcpp

#endif // REDUCER_H