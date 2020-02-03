#ifndef I_REPORT_H
#define I_REPORT_H

namespace advcpp
{

struct IReport
{
    virtual ~IReport() = 0;

    virtual void operator+= (const IReport & i_report) = 0;
};

inline IReport::~IReport()
{
}

} // namespace advcpp

#endif // I_REPORT_H