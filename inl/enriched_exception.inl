#include "enriched_exeptions.hpp"
#include <cassert>

namespace advcpp
{

inline InfoException::InfoException(const char* a_file, const char* a_func, size_t a_line) NOEXCEPT
: m_file(a_file)
, m_func(a_func)
, m_line(a_line)
{
    assert(a_file != 0 || a_func != 0);
}

inline EnrichedExeption::EnrichedExeption(const char* a_msg, InfoException const& a_info) NOEXCEPT
: logic_error(a_msg)
, m_info(a_info)
{
}

} //namespace advcpp