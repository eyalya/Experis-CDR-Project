#ifndef I_DECODER_H
#define I_DECODER_H

namespace advcpp
{

class IDecoder
{
public:
    virtual ~IDecoder() = 0;
};

inline IDecoder::~IDecoder()
{
}

} // namespace advcpp


#endif // I_DECODER_H