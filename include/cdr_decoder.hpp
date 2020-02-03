#ifndef CDR_DECODER_H
#define CDR_DECODER_H

#include <cstdlib>

namespace advcpp
{

class CdrDecoder
{
public:
    CdrDecoder();
    //const Reducer & Decode(char * a_msg);

private:

};


} // namespace advcpp

#include "inl/decoder.inl"

#endif // CDR_DECODER_H


// IMSI
// Outgoing voice calls duration to a subscriber within the mobile operator
// Incoming voice calls duration to a subscriber within the mobile operator
// Outgoing voice calls duration to a subscriber outside the mobile operator
// Incoming voice calls duration to a subscriber outside the mobile operator
// SMS messages sent within the mobile operator
// SMS messages received within the mobile operator
// SMS messages sent outside the mobile operator
// SMS messages received outside the mobile operator
// MB downloaded
// MB uploaded


// 7.2
// Inter-Operator Settlement
// A file with a header having the following fields separated by “,” :
// Date in YYYY/MM/DD format
// Time in HH:MM:SS format
// For each operator, one line record with following fields separated by “,” :
// Operator MCC/MNC
// Operator Brand name
// Incoming voice call durations
// Outgoing voice call durations
// Incoming SMS messages
// Outgoing SMS Messages


//United Counter Format

// Operator MCC/MNC
// Operator Brand name
// Outgoing voice calls duration to a subscriber within the mobile operator
// Incoming voice calls duration to a subscriber within the mobile operator
// Outgoing voice calls duration to a subscriber outside the mobile operator
// Incoming voice calls duration to a subscriber outside the mobile operator
// SMS messages sent within the mobile operator
// SMS messages received within the mobile operator
// SMS messages sent outside the mobile operator
// SMS messages received outside the mobile operator
// MB downloaded
// MB uploaded