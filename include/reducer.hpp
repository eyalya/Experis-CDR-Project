#ifndef REDUCER_H
#define REDUCER_H

#include "ireducer.hpp"
#include "protocol.hpp"

namespace advcpp
{

class Reducer : public IReducer
{
public:
    Reducer(const protocol::MOC & a_moc);
    ~Reducer();

    virtual void Reduce(Report & a_report);

private:
    protocol::MOC m_moc;
};

inline Reducer::Reducer(const protocol::MOC & a_moc)
: m_moc(a_moc)
{
}

inline Reducer::~Reducer()
{
}


} // namespace advcpp

#endif  // REDUCER_H