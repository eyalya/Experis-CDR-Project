#ifndef I_REDUCER_H
#define I_REDUCER_H

#include "report.hpp"

namespace advcpp
{

class IReducer
{
public:
    virtual ~IReducer() = 0;

    virtual void Reduce(Report & a_report) = 0;

};

inline IReducer::~IReducer()
{
}

} // namespace advcpp

#endif // REDUCER_H