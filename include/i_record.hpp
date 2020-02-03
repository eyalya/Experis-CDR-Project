#ifndef I_RECORD_H
#define I_RECORD_H

namespace advcpp
{

struct IRecord
{
    virtual ~IRecord() = 0;

    virtual void operator+= (const IRecord & i_record) = 0;
};

inline IRecord::~IRecord()
{
}

} // namespace advcpp

#endif // I_RECORD_H