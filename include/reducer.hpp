#ifndef REDUCER_H
#define REDUCER_H

#include <vector>
#include "ireducer.hpp"
#include "protocol.hpp"

namespace advcpp
{

class IReducing
{
public:
    virtual ~IReducing() = 0;

    virtual void Reduce(const protocol::Message & a_message, Record & a_record) = 0;
};

class MCOReducing : public IReducing
{
public:
    // MCOReducing(); = default
    // virtual ~MCOReducing();
    // MCOReducing & MCOReducing(const MCOReducing & a_red)
    // MCOReducing & operator= (const MCOReducing & a_red)


    virtual void Reduce(const protocol::Message & a_message, Record & a_record);
};


class MTCReducing : public IReducing
{
public:
    // MTCReducing(); = default
    // virtual ~MTCReducing();
    // MTCReducing & MTCReducing(const MTCReducing & a_red)
    // MTCReducing & operator= (const MTCReducing & a_red)

    virtual void Reduce(const protocol::Message & a_message, Record & a_record);
};

class SMSOReducing : public IReducing
{
public:
    // MTCReducing(); = default
    // virtual ~MTCReducing();
    // MTCReducing & MTCReducing(const MTCReducing & a_red)
    // MTCReducing & operator= (const MTCReducing & a_red)

    virtual void Reduce(const protocol::Message & a_message, Record & a_record);
};

class SMSTReducing : public IReducing
{
public:
    // MTCReducing(); = default
    // virtual ~MTCReducing();
    // MTCReducing & MTCReducing(const MTCReducing & a_red)
    // MTCReducing & operator= (const MTCReducing & a_red)

    virtual void Reduce(const protocol::Message & a_message, Record & a_record);
};


class Reducer : public IReducer
{
public:
    Reducer(std::vector<IReducing *> & a_reducers);
    ~Reducer();

    virtual void Reduce(const protocol::Message & a_message, Record & a_record);

private:
    std::vector<IReducing *> & m_reducers;
};

inline Reducer::Reducer(std::vector<IReducing *> & a_reducers)
: m_reducers(a_reducers)
{
}

inline Reducer::~Reducer()
{
}


inline IReducing::~IReducing(){}


} // namespace advcpp

#endif  // REDUCER_H