#ifndef CDR_DECODER_H
#define CDR_DECODER_H

#include <cstdlib> 
#include <vector> // vector
#include "protocol.hpp" // MCO Message ...

namespace advcpp
{

class IDecodeMassge
{
public:
    virtual ~IDecodeMassge() = 0;
    virtual void Decode(char * a_src, protocol::Message & a_message) = 0;
};

class DecodeMCO : public IDecodeMassge
{
    virtual void Decode(char * a_src, protocol::Message & a_message);
};

class CdrDecoder
{
public:
    CdrDecoder(std::vector<IDecodeMassge *> & a_decoders);
    
    void Decode(char * a_src, protocol::Message & a_message);

private:
    std::vector<IDecodeMassge *> & m_decoders;
};



} // namespace advcpp

#include "inl/decoder.inl"

#endif // CDR_DECODER_H
