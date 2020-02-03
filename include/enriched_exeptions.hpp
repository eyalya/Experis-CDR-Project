#ifndef ENRICHED_EXCEPTION_HPP
#define ENRICHED_EXCEPTION_HPP

#include <stdexcept>

#include "common.hpp"

namespace advcpp
{

class InfoException {
public:
    InfoException(const char* a_file, const char* a_func, size_t a_line) NOEXCEPT;
    //~InfoException();
    //InfoException(InfoException const& a_rhs);
    //InfoException& operator = (InfoException const& a_rhs);

private:
    const char* m_file;
    const char* m_func;
    size_t m_line;
}; 

class EnrichedExeption: public std::logic_error {
protected: 
    EnrichedExeption(const char* a_msg, InfoException const& a_info) NOEXCEPT;
    //~EnrichedExeption() NOEXCEPT = 0;

private:
    InfoException m_info;
};


} //namespace advcpp

#include "inl/enriched_exception.inl"
#endif //ENRICHED_EXCEPTION_HPP
