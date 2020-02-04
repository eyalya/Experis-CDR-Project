#include "encoder.hpp"

namespace advcpp
{

template <typename T>
size_t EncodeT(char * a_dest, T & a_src)
{
    size_t len = sizeof(a_src);
    std::memcpy(a_dest, &a_src, len);
    return len;
}



} // namespace advcpp
