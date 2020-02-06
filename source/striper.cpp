//#include <iostream>
#include <algorithm>
//#include <sstream> //stringstream
#include "striper.hpp"

namespace advcpp{

ReplacerDelim::ReplacerDelim(char a_oldDelim, char a_newDelim)
: m_oldDelim(a_oldDelim)
, m_newDelim(a_newDelim)
{
}

void ReplacerDelim::Strip(std::string& a_record)
{	
	std::replace( a_record.begin(), a_record.end(), m_oldDelim, m_newDelim);	
}

} //namespace advcpp
