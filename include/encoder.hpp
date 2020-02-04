#ifndef ENCODER_H
#define ENCODER_H
#include <cstdlib>
#include <cstring>
#include "protocol.hpp"
namespace advcpp
{

template <typename T>
size_t EncodeT(char * a_dest, T & a_src);


size_t EncodeMoc(char * a_dest, protocol::MOC & a_moc);

size_t EncodeCdr(char * a_dest, protocol::CDR & a_cdr);

size_t EncodeParty(char * a_dest, protocol::Party & a_party);

size_t EncodeOperator(char * a_dest, protocol::Operator & a_operator);

size_t EncodeDate(char * a_dest, protocol::Date & a_date);

size_t EncodeTime(char * a_dest, protocol::Time & a_time);

} // namespace advcpp

#include "inl/encoder.inl"
#endif // ENCODER_H
