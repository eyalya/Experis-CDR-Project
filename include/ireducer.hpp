#ifndef I_REDUCER_H
#define I_REDUCER_H

#include "record.hpp"
#include "protocol.hpp"
#include "record.hpp"

namespace advcpp
{

class IReducer
{
public:
    virtual ~IReducer() = 0;

    virtual void Reduce(const protocol::Message & a_message, Record & a_record) = 0;

};

inline IReducer::~IReducer()
{
}

} // namespace advcpp

#endif // REDUCER_H